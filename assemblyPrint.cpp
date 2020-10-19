#include "TreeNode.h"
#include "reading.h"
#include "table.h"

int tempCont;
int leftSideOfAssignment = 0;
int isAnAddress = 0;
int isAnOffset = 0;
int labelNumber = 0;
int currentBreak = 0;
int exprBlock = 0;
int localBlock = 0;
declarationsList *globalList;
declarationsList *localList;
programNode* program;
declarationsList* currentExprVariable;

void declarationsList::assemblyPrint(){
    int spaceValue;
    if (type==INT){
        idTable.fPrintEntry(outFile, id);
        idTable.printEntry(id);
        printf ("\n");
        if (arraySize == -1){
            fprintf (outFile, ": .word 0");
            fprintf (outFile, "\n");
        } else {
            fprintf (outFile, ": .space ");
            spaceValue = 4*intTable.stringToValue(arraySize);
            fprintf (outFile, " %d\n", spaceValue);
            fprintf (outFile, "\n");
        }
    } else {
        idTable.fPrintEntry(outFile, id);
        idTable.printEntry(id);
        printf ("\n");
        fprintf (outFile, ": .space ");
        structNode *sNode = program->structList->varSweep(type);
        if (sNode != NULL) {
            fprintf (outFile, " %d\n", sNode->structVariables->maxOffset());
        }
    }
    if (nextDeclaration!=NULL)
        nextDeclaration->assemblyPrint();
}

void programNode::assemblyPrint(){
    globalList = globalVariables;
    program = this;
    structList->calcOffset();
    if (globalVariables!=NULL){
        fprintf(outFile, "\t.data\n\n");
        globalVariables->assemblyPrint();
    }
    literalTable.printStrings(outFile);
    if (functionList!=NULL){
        fprintf(outFile, "\n\t.text\n");
        functionList->assemblyPrint();
    }
}

void structNode::assemblyPrint(){
    fprintf(outFile, "#structnode");
}

void functionNode::assemblyPrint(){
    int mainID = idTable.insertNewString("main", 4);
    exprBlock = maxRight;
    localList = functionVariables;
    int localBlockSize;
    if (functionVariables != NULL) {
        functionVariables->calcOffset(0);
        localBlockSize = functionVariables->maxOffset();
    } else {
        localBlockSize = 0;
    }
    localBlock = localBlockSize;
    idTable.fPrintEntry(outFile, functionID);
    fprintf(outFile, ":\n");
    fprintf(outFile, "\n\tsubu $sp, $sp, %d\n", maxRight+localBlockSize+8);
    funcStmtList->assemblyPrint();
    if (functionID == mainID){
        fprintf(outFile, "\t#End of program.\n");
        fprintf(outFile, "\tli $v0, 17\n");
        fprintf(outFile, "\tli $a0, 0\n");
        fprintf(outFile, "\tsyscall\n");
    } else {
        fprintf(outFile, "\n\taddu $sp, $sp, %d\n", maxRight+localBlockSize+8);
        fprintf (outFile, "\tjr $ra\n");
    }
}

void classNode::assemblyPrint(){
    fprintf(outFile, "#classnode");
}

///5
void nodeList::assemblyPrint(){
    if (currentNode==NULL) return;
    currentNode->assemblyPrint();
    nodeList *listSweep;
    listSweep = nextListNode;
    while (listSweep != NULL) {
        listSweep->currentNode->assemblyPrint();
        listSweep = listSweep->nextListNode;
    }
}

void exprNodeList::assemblyPrint(){
    fprintf(outFile, "#exprnodelist\n");
}

void breakNode::assemblyPrint(){
    fprintf(outFile, "#breaknode\n");
    fprintf(outFile, "\tb label%d\n", currentBreak);
}

void ifNode::assemblyPrint(){
    int elseLabel = labelNumber;
    labelNumber++;
    int ifExitLabel = labelNumber;
    labelNumber++;
    fprintf(outFile, "\t#ifnode\n");
    logicNode->exprAssemblyPrint(0);
    fprintf(outFile, "\tbeq $t0, $zero, label%d\n", elseLabel);
    trueNode->assemblyPrint();
    fprintf(outFile, "\tb label%d\n", ifExitLabel);
    fprintf (outFile, "label%d:\n", elseLabel);
    if (falseNode!=NULL) falseNode->assemblyPrint();
    fprintf (outFile, "label%d:\n", ifExitLabel);
}

void whileNode::assemblyPrint(){
    ///fprintf(outFile, "#whilenode\n");
    int loopLabel = labelNumber;
    labelNumber++;
    int exitLabel = labelNumber;
    labelNumber++;
    int breakBuffer = currentBreak;
    currentBreak = exitLabel;
    fprintf (outFile, "label%d:\n", loopLabel);
    logicNode->exprAssemblyPrint(0);
    fprintf(outFile, "\tbeq $t0, $zero, label%d\n", exitLabel);
    loopNode->assemblyPrint();
    fprintf (outFile, "\tb label%d\n", loopLabel);
    fprintf (outFile, "label%d:\n", exitLabel);
    currentBreak = breakBuffer;
}

///10
void printNode::assemblyPrint(){
    //declarationsList* thisVariable;
    exprNodeList *exprSweep;
    //thisVariable = globalList->varSweep(stmtExpr->id);
    exprSweep = stmtExpr;
    while (exprSweep!=NULL){
        fprintf(outFile, "\t#Impressao\n");
        if (exprSweep->currentExprNode->opCode==LITERAL) {
            fprintf(outFile, "\tli $v0, 4\n");
            fprintf(outFile, "\tla $a0, str%d\n", exprSweep->currentExprNode->id);
            fprintf(outFile, "\tsyscall\n\n");
        } //else if {}
        else {
            //isAnAddress = 1;
            exprSweep->currentExprNode->exprAssemblyPrint(0);
            //isAnAddress = 0;
            fprintf(outFile, "\tli $v0, 1\n");
            fprintf(outFile, "\tmove $a0, $t0");
            fprintf(outFile, "\n\tsyscall\n\n");
        }
        exprSweep = exprSweep->nextExprNodeList;
    }
}

void readlnNode::assemblyPrint(){
    fprintf(outFile, "#readlnnode\n");
    fprintf(outFile, "\tli $v0, 5\n");
    fprintf(outFile, "\tsyscall\n\n");
    isAnAddress = 1;
    stmtExpr->assemblyPrint();
    isAnAddress = 0;
    fprintf(outFile, "\tsw $v0, ($t0)");
}

void returnNode::assemblyPrint(){
    fprintf(outFile, "#returnnode\n");
}

void switchNode::assemblyPrint(){
    int exitLabel = labelNumber;
    labelNumber++;
    int breakBuffer = currentBreak;
    currentBreak = exitLabel;
    logicTest->exprAssemblyPrint(0);
    caseList* caseSweep = cases;
    while (caseSweep!=NULL){
        fprintf (outFile, "\tli $t1, ");
        intTable.fPrintEntry(outFile, caseSweep->caseInt);
        fprintf (outFile, "\n");
        caseSweep->caseLabel = labelNumber;
        labelNumber++;
        fprintf (outFile, "\tbeq $t0, $t1, label%d\n", caseSweep->caseLabel);
        caseSweep = caseSweep->nextCaseList;
    }
    fprintf (outFile, "\tb label%d\n", exitLabel);
    caseSweep = cases;
    while (caseSweep!=NULL){
            caseSweep->assemblyPrint();
            caseSweep = caseSweep->nextCaseList;
    }
    fprintf (outFile, "label%d:\n", exitLabel);
    currentBreak = breakBuffer;
}

void caseList::assemblyPrint(){
    fprintf(outFile, "#caselist\n");
    fprintf(outFile, "label%d:\n", caseLabel);
    currentNode->assemblyPrint();
}

///15
void exprNode::exprAssemblyPrint(int temp){
    int exprBlockBuffer;
    int localBlockBuffer;
    int isAnAddressBuffer;
    declarationsList* localListBuffer = NULL;
    declarationsList* exprVariable = NULL;
    if (isUnary == 1){
        if (opCode==NUMINT){
            fprintf(outFile, "\tli $t0, ");
            intTable.fPrintEntry(outFile, id);
            fprintf(outFile, "\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
        }
        else if (opCode==ID){
            if (isAnOffset){
                exprVariable = currentExprVariable;
                structNode* sNode = program->structList->varSweep(exprVariable->id);
                    if (sNode!=NULL) {
                        declarationsList *test = sNode->structVariables->varSweep(id);
                        if (test!=NULL){
                            fprintf (outFile, "\tli $t0, %d\n", test->offsetStart);
                            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
                        }
                    }
                }
            if (localList!=NULL) exprVariable = localList->varSweep(id);
            if (exprVariable!=NULL) {
                currentExprVariable = exprVariable;
                if (isAnAddress) {
                    fprintf (outFile, "\tla $t0, %d($sp)", exprVariable->offsetStart + exprBlock);
                    fprintf (outFile, "\n");
                    fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
                } else {
                    fprintf (outFile, "\tlw $t0, %d($sp)", exprVariable->offsetStart + exprBlock);
                    fprintf (outFile, "\n");
                    fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
                }
            }
            else {
                if (globalList != NULL) exprVariable = globalList->varSweep(id);
                if (exprVariable!=NULL){
                    currentExprVariable = exprVariable;
                    if (isAnAddress){
                        fprintf (outFile, "\tla $t0, ");
                        idTable.fPrintEntry(outFile, id);
                        fprintf (outFile, "\n");
                        fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
                    } else {
                        fprintf (outFile, "\tlw $t0, ");
                        idTable.fPrintEntry(outFile, id);
                        fprintf (outFile, "\n");
                        fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
                    }
                } else {
                    printf ("VARIÁVEL USADA NÃO SENDO DECLARADA. CÓDIGO GERADO SERÁ INVÁLIDO.\n");
                }
            }
        } else if (opCode==PLUS){
            rightChild->exprAssemblyPrint(temp);
        } else if (opCode==MINUS){
        rightChild->exprAssemblyPrint(temp);
        fprintf(outFile, "\tneg $t%d, $t%d\n", temp, temp);
        } else if (opCode==NOT){
            rightChild->exprAssemblyPrint(temp);
            fprintf(outFile, "\tseq $t%d, $t%d, $zero\n", temp, temp);
        } else if (opCode == CALL){
            exprBlockBuffer = exprBlock;
            localListBuffer = localList;
            localBlockBuffer = localBlock;
            ///store ra
            fprintf (outFile, "\tsw $ra, %d($sp)\n", exprBlock + localBlock+4);
            fprintf (outFile, "\tjal ");
            idTable.fPrintEntry(outFile, id);
            ///write ra
            fprintf (outFile, "\n");
            fprintf (outFile, "\tlw $ra, %d($sp)\n", exprBlock + localBlock+4);
            exprBlock = exprBlockBuffer;
            localList = localListBuffer;
            localBlock = localBlockBuffer;
        }
    }
    ///operações binárias
    else {
        switch (opCode){
        case DOT:
            isAnAddressBuffer = isAnAddress;
            isAnAddress = 1;
            leftChild->exprAssemblyPrint(temp);
            isAnAddress = 0;
            isAnOffset = 1;
            rightChild->exprAssemblyPrint(temp+1);
            isAnOffset = 0;
            isAnAddress = isAnAddressBuffer;
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\taddu $t0, $t0, $t1\n");
            if (isAnAddress)
                fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            else {
                fprintf (outFile, "\tlw $t0, ($t0)\n");
                fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            }
            break;
        case L_BRACKET:
            isAnAddressBuffer = isAnAddress;
            isAnAddress = 1;
            leftChild->exprAssemblyPrint(temp);
            isAnAddress = 0;
            rightChild->exprAssemblyPrint(temp+1);
            isAnAddress = isAnAddressBuffer;
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf (outFile, "\tli $t2, 4\n");
            fprintf (outFile, "\tmulou $t1, $t1, $t2\n");
            fprintf(outFile, "\taddu $t0, $t0, $t1\n");
            if (isAnAddress)
                fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            else {
                fprintf (outFile, "\tlw $t0, ($t0)\n");
                fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            }
            fprintf(outFile, "\t#---Fim do acesso a vetor---\n");
            break;
        ///operações aritméticas
        case PLUS:
            fprintf(outFile, "\t#---PLUS---\n");
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tadd $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tadd $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            fprintf(outFile, "\t#---Fim do plus---\n");;
            break;
        case MINUS:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tsub $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsub $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case ASTERISK:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tmulo $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tmulo $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case SLASH:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tdiv $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tdiv $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case PERCENT:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\trem $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\trem $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case ASSIGNMENT:
            fprintf (outFile, "\t#---Assignment---\n");
            rightChild->exprAssemblyPrint(temp);
            fprintf (outFile, "\t#---Fim do right print---\n");
            //fprintf(outFile, "\tmove $s0, $t0\n");
            isAnAddress = 1;
            leftChild->exprAssemblyPrint(temp+1);
            fprintf (outFile, "\t#---Fim da left print---\n");
            isAnAddress = 0;
            fprintf (outFile, "\t#---Momento do assignment---\n");
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsw $t0, ($t1)\n");
            fprintf (outFile, "\t#---Fim do assignment---\n");
            break;
        ///operações lógicas
        case LESS_THAN:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tslt $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tslt $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case LESS_EQUAL:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tsle $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsle $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case MORE_THAN:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tsgt $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsgt $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case MORE_EQUAL:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tsge $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsge $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case EQUALS:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tseq $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tseq $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case NOT_EQUAL:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tsne $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsne $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case BIT_AND:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tand $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tand $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case BIT_OR:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tor $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tor $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        case LOGIC_AND:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf(outFile, "\tsne $t0, $t0, $zero\n");
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tsne $t1, $t1, $zero\n");
            fprintf(outFile, "\tand $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
//            fprintf(outFile, "\tsne $t%d, $t%d, $zero\n", temp, temp);
//            fprintf(outFile, "\tsne $t%d, $t%d, $zero\n", temp+1, temp+1);
//            fprintf(outFile, "\tand $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            break;
        case LOGIC_OR:
            leftChild->exprAssemblyPrint(temp);
            rightChild->exprAssemblyPrint(temp+1);
            //fprintf(outFile, "\tor $t%d, $t%d, $t%d\n", temp, temp, temp+1);
            fprintf (outFile, "\tlw $t0, %d($sp)\n", 4*temp);
            fprintf (outFile, "\tlw $t1, %d($sp)\n", 4*(temp+1));
            fprintf(outFile, "\tor $t0, $t0, $t1\n");
            fprintf (outFile, "\tsw $t0, %d($sp)\n", 4*temp);
            break;
        }
    }
}

void exprNode::assemblyPrint(){
    exprAssemblyPrint(0);
}

///retorna NULL se a variável especificada por key não está na lista
///retorna o ponteiro para ela se ela está presente
declarationsList* declarationsList::varSweep(int key){
    if (this==NULL) return NULL;
    else if (id==key) return this;
    else if (nextDeclaration==NULL) return NULL;
    else return nextDeclaration->varSweep(key);
}

void declarationsList::calcOffset(int currentOffset){
    int blockSize;
    offsetStart = currentOffset;
    structNode* sNode;
    if (type==INT) {
        if (arraySize==-1) {
            offset = currentOffset + 4;
        } else {
            blockSize = intTable.stringToValue(arraySize);
            offset = currentOffset + (4*blockSize);
        }
    }
    else {
        sNode = program->structList->varSweep(type);
        if (sNode != NULL) offset = currentOffset + sNode->structVariables->maxOffset();
    }
    printf ("Offset = %d\n", offset);
    if (nextDeclaration!=NULL)
    nextDeclaration->calcOffset(offset);
}

int declarationsList::maxOffset(){
    if (nextDeclaration==NULL) return offset;
    else return nextDeclaration->maxOffset();
}

structNode* structNodeList::varSweep (int key){
    if (this==NULL) return NULL;
    else if (currentStructNode == NULL) return NULL;
    else if (currentStructNode->structID == key)
        return currentStructNode;
    else return nextStructNodeList->varSweep(key);
}

void structNodeList::calcOffset(){
    if (currentStructNode==NULL) return;
    currentStructNode->structVariables->calcOffset(0);
    structNodeList *listSweep;
    listSweep = nextStructNodeList;
    while (listSweep != NULL) {
        listSweep->currentStructNode->structVariables->calcOffset(0);
        listSweep = listSweep->nextStructNodeList;
    }
}


//void idPrint (int id)
//{
    ///varre locais
    ///varre parametros
    ///varre globais
//}
