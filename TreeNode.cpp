#include "TreeNode.h"

/////////////////
///programNode///
/////////////////

programNode::programNode(){
    globalVariables = NULL;
    structList = new structNodeList();
    classList = new nodeList();
    functionList = new nodeList();
}

programNode::~programNode(){
    cout << "desalocando programa.\n";
}

////////////////////
///structNodeList///
////////////////////

structNode::structNode(){
    structVariables = new declarationsList();
}

structNode::~structNode(){
}

//////////////////////
///declarationsList///
//////////////////////

declarationsList::declarationsList(){
    type = -1;
    id = -1;
    pointer = 0;
    arraySize = -1;
    isPrivate = 0;
    nextDeclaration = NULL;
}

declarationsList::~declarationsList(){
}

void declarationsList::insertDeclaration (declarationsList *newDecl){
    declarationsList* listSweep = this;
    if (listSweep==NULL) { listSweep = newDecl; return;}
    while (listSweep->nextDeclaration != NULL) listSweep = listSweep->nextDeclaration;
    listSweep->nextDeclaration = newDecl;
}

///////////////
///classNode///
///////////////

classNode::classNode(){
    classID = -1;
    superclassID = -1;
    classVariables = NULL;
    classFunctions = new nodeList();
}

classNode::~classNode(){
}

//////////////////
///functionNode///
//////////////////

functionNode::functionNode(){
    functionID = -1;
    returnType = -1;
    isPrivate = 0;
    maxRight = 200;
    parameters = NULL;
    functionVariables = NULL;
    funcStmtList = new nodeList();
}

functionNode::~functionNode() {
}

///////////////
///printNode///
///////////////
printNode::printNode(){
    stmtExpr = new exprNodeList();
}

printNode::~printNode() {
}

//////////////
///exprNode///
//////////////

exprNode::exprNode(int op, int unary, int idCode=-1){
    opCode = op;
    isUnary = unary;
    id = idCode;
    leftChild = NULL;
    rightChild = NULL;
    callParameters = NULL;
    if (opCode == CALL){
        callParameters = new exprNodeList();
    }
}

void exprNode::visitorPrint (int indent){
    printIndent(indent);
    if (isUnary){
        printUnaryCode(opCode, id);
        if (rightChild!=NULL)
        rightChild->visitorPrint(indent+1);
    } else {
        printBinaryCode(opCode);
        if(leftChild!=NULL) leftChild->visitorPrint(indent+1);
        else cout << "filho esq vazio.";
        printIndent(indent);
        printf ("-------------------------------\n");
        if(rightChild!=NULL) rightChild->visitorPrint(indent+1);
        else cout << "filho dir vazio.";
    }
    if (opCode == CALL){
        callParameters->visitorPrint(indent+1);
    }
}

exprNode::~exprNode(){}

//////////////////
///exprNodeList///
//////////////////

exprNodeList::exprNodeList(){
    currentExprNode = NULL;
    nextExprNodeList = NULL;
}

exprNodeList::~exprNodeList(){
    //printf("Chamou o destrutor de exprNL\n");
}

void exprNodeList::insertListNode(exprNode *node){
    if (currentExprNode==NULL){
        currentExprNode = node;
        return;
    //} else if (nextListNode==NULL) nextListNode = new
    } else {
        exprNodeList *newList = new exprNodeList();
        newList->currentExprNode = node;
        exprNodeList* listSweep = nextExprNodeList;
        if (nextExprNodeList==NULL) nextExprNodeList = newList;
        else {
            while (listSweep->nextExprNodeList != NULL) {listSweep = listSweep->nextExprNodeList;}
            listSweep->nextExprNodeList = newList;
        }
    }
}

void exprNodeList::visitorPrint (int indent){
    if (currentExprNode==NULL) return;
    currentExprNode->visitorPrint(indent);
    exprNodeList *listSweep;
    listSweep = nextExprNodeList;
    while (listSweep != NULL) {
        if (listSweep->currentExprNode!=NULL)
        listSweep->currentExprNode->visitorPrint(indent);
        listSweep = listSweep->nextExprNodeList;
    }
}

///////////////////
///functionCall///
//////////////////

//functionCall::functionCall(int id=0, int i=100, int j=-1){
//    functionID = id;
//    callParameters = new exprNodeList();
//}
//
//functionCall::~functionCall(){}
//
//void functionCall::visitorPrint(int indent){
//    printIndent(indent);
//    printf("call:");
//    idTable.printEntry(functionID);
//    printf (" Parameters: \n");
//    callParameters->visitorPrint(indent+1);
//}

///////////////////
///exprStack///////
///////////////////

exprStack::exprStack(){
    exprStackTop = new exprNodeList();
}

exprStack::~exprStack(){}

void exprStack::pushNode (exprNode *nodeExpr){
    exprNodeList *node = new exprNodeList();
    node->currentExprNode = nodeExpr;
//    if (exprStackTop == NULL) printf ("exprStackTop esta nulo\n");
//    else printf ("address stack top %p", exprStackTop);
    node->nextExprNodeList = exprStackTop;
    exprStackTop = node;
}

void exprStack::insertNode (exprNode *nodeExpr){
    //exprNodeList *node = new exprNodeList();
    //node->currentExprNode = nodeExpr;
    //node->currentExprNode->rightChild = exprStackTop->currentExprNode;
    nodeExpr->rightChild = exprStackTop->currentExprNode;
    Pop();
    if ((nodeExpr->isUnary)!=1){
        if (exprStackTop!=NULL){
         exprNode *suchNode = exprStackTop->currentExprNode;
         nodeExpr->leftChild = suchNode;
        //exprStackTop = exprStackTop->nextExprNodeList;
        Pop();
        }
    }
    //exprStackTop = node;
    pushNode(nodeExpr);
}

void exprStack::Pop(){
    if (exprStackTop!=NULL){
        exprNodeList* stackSweep;
        stackSweep = exprStackTop;
        exprStackTop = exprStackTop->nextExprNodeList;
        //delete stackSweep;
        stackSweep->~exprNodeList();
    }
}


////////////////////
///nodeList/////////
////////////////////

nodeList::nodeList(){
    currentNode = NULL;
    nextListNode = NULL;
}

nodeList::~nodeList(){}

void nodeList::insertNode (treeNode *newNode){
    if (currentNode==NULL){
        currentNode = newNode;
        return;
    //} else if (nextListNode==NULL) nextListNode = new
    } else {
        nodeList *newList = new nodeList();
        newList->currentNode = newNode;
        nodeList* listSweep = nextListNode;
        if (nextListNode==NULL) nextListNode = newList;
        else {
            while (listSweep->nextListNode != NULL) {listSweep = listSweep->nextListNode;}
            listSweep->nextListNode = newList;
        }
    }
}

void nodeList::visitorPrint(int indent){
    if (currentNode==NULL) return;
    currentNode->visitorPrint(indent);
    nodeList *listSweep;
    listSweep = nextListNode;
    while (listSweep != NULL) {
        listSweep->currentNode->visitorPrint(indent);
        listSweep = listSweep->nextListNode;
    }
}

structNodeList::structNodeList(){
    currentStructNode = NULL;
    nextStructNodeList = NULL;
}

structNodeList::~structNodeList(){}

void structNodeList::insertStructNode (structNode *newNode){
    if (currentStructNode==NULL){
        currentStructNode = newNode;
        return;
    //} else if (nextStructNodeList==NULL) nextStructNodeList = new
    } else {
        structNodeList *newList = new structNodeList();
        newList->currentStructNode = newNode;
        structNodeList* listSweep = nextStructNodeList;
        if (nextStructNodeList==NULL) nextStructNodeList = newList;
        else {
            while (listSweep->nextStructNodeList != NULL) {listSweep = listSweep->nextStructNodeList;}
            listSweep->nextStructNodeList = newList;
        }
    }
}

void structNodeList::visitorPrint(int indent){
    if (currentStructNode==NULL) return;
    currentStructNode->visitorPrint(indent);
    structNodeList *listSweep;
    listSweep = nextStructNodeList;
    while (listSweep != NULL){
        if (listSweep->currentStructNode!=NULL)
        listSweep->currentStructNode->visitorPrint(indent);
        listSweep = listSweep->nextStructNodeList;
    }
}

void caseList::insertCaseList (caseList *newList){
        caseList* listSweep = nextCaseList;
        if (nextCaseList==NULL) nextCaseList = newList;
        else {
            while (listSweep->nextCaseList != NULL) {listSweep = listSweep->nextCaseList;}
            listSweep->nextCaseList = newList;
    }
}

////////////////////
///visitorPrint()///
////////////////////

void programNode::visitorPrint(int indent){
    printf ("\n--------------------------------\n");
    printf ("---ARVORE DE SINTAXE ABSTRATA---\n");
    printf ("--------------------------------\n");
    printIndent (indent);
    printf ("Program\n");

    ///imprime variáveis globais
    declarationsList *declSweep;
    declSweep = globalVariables;
    if (declSweep != NULL) {
        declSweep->visitorPrint(indent+1);
        declSweep = declSweep->nextDeclaration;
    }

    ///imprime structs
    structList->visitorPrint(indent+1);

    ///imprime funções
    functionList->visitorPrint(indent+1);

    ///imprime classes
    classList->visitorPrint(indent+1);
}

void functionNode::visitorPrint(int indent){
    printIndent (indent);
    if (isPrivate == 1) printf ("private ");
    printf ("function ");
    printType(returnType);
    if (returnPointer==1) printf ("* ");
    idTable.printEntry(functionID);

    ///imprime parametros
    printf (" (");
    declarationsList *declSweep;
    declSweep = parameters;
    printf ("\n");
    if (declSweep != NULL) {
        declSweep->visitorPrint(indent+1);
        declSweep = declSweep->nextDeclaration;
    }

    printIndent (indent+1);
    printf (")");
    printf ("\n");

    ///imprime variaveis locais
    declSweep = functionVariables;
    if (declSweep != NULL) {
        declSweep->visitorPrint(indent+1);
        declSweep = declSweep->nextDeclaration;
    }
    printf ("\n");
    ///imprime statements da função
    if (funcStmtList->currentNode == NULL) cout << "funcStmtList está nulo.\n";
    funcStmtList->visitorPrint(indent+1);
    printf ("\n");
    //printar variaveis locais
    //printar statements
}

void classNode::visitorPrint(int indent){
    printIndent(indent);
    printf ("class ");
    printType(classID);
    if (superclassID!=-1){
            printf (": ");
        idTable.printEntry(superclassID);
    }
    printf ("\n");

    ///print variables
    declarationsList *declSweep;
    declSweep = classVariables;
    if (declSweep != NULL) {
        declSweep->visitorPrint(indent+1);
        declSweep = declSweep->nextDeclaration;
    }

    ///print functions
    classFunctions->visitorPrint(indent+1);
}

void declarationsList::visitorPrint(int indent){
    printIndent (indent);
    if (isPrivate == 1) printf ("private ");
    printf ("var ");
    printType(type);
    if (pointer==1) printf ("* ");
    idTable.printEntry (id);
    //idTable.printEntry(structID);
    if (arraySize != -1) {
        printf (" [ ");
        intTable.printEntry(arraySize);
        printf (" ]");
    }
    printf ("\n");
    if (nextDeclaration != NULL) nextDeclaration->visitorPrint(indent);
}

void structNode::visitorPrint(int indent){
    printIndent (indent);
    printf ("struct ");
    idTable.printEntry(structID);
    printf ("\n");
    structVariables->visitorPrint (indent+1);
}

///////////////////////////
///visitorPrints de stmt///
///////////////////////////

void ifNode::visitorPrint(int indent){
    printIndent(indent);
    printf("IF\n");
    printIndent(indent+1);
    printf("CONDITION\n");
    logicNode->visitorPrint(indent+2);
    if (trueNode!=NULL){
        printIndent(indent+1);
        printf("IF TRUE\n");
        trueNode->visitorPrint(indent+2);
    }
    if (falseNode!=NULL){
        printIndent(indent+1);
        printf("IF FALSE\n");
        falseNode->visitorPrint(indent+2);
    }
}

void breakNode::visitorPrint(int indent){
    printIndent(indent);
    printf("BREAK\n");
}

void printNode::visitorPrint(int indent){
    printIndent(indent);
    printf("PRINT\n");
    stmtExpr->visitorPrint(indent+1);
}

void readlnNode::visitorPrint(int indent){
    printIndent(indent);
    printf("READLN\n");
    stmtExpr->visitorPrint(indent+1);
}

void returnNode::visitorPrint(int indent){
    printIndent(indent);
    printf("RETURN\n");
    stmtExpr->visitorPrint(indent+1);
}

void whileNode::visitorPrint(int indent){
    printIndent(indent);
    printf("WHILE\n");
    printIndent(indent+1);
    printf("CONDITION\n");
    logicNode->visitorPrint(indent+2);
    printIndent(indent+1);
    printf("IF TRUE\n");
    loopNode->visitorPrint(indent+2);
}

void switchNode::visitorPrint(int indent){
    printIndent(indent);
    printf("SWITCH\n");
    printIndent(indent+1);
    printf("CHOICE VALUE");
    printf("\n");
    if (logicTest!=NULL)
    logicTest->visitorPrint(indent+2);
    caseList* caseSweep;
    caseSweep = cases;
    while (caseSweep != NULL){
        caseSweep->visitorPrint(indent+1);
        caseSweep = caseSweep->nextCaseList;
    }

//    if (cases!=NULL)
//    cases->visitorPrint(indent+1);
}

void caseList::visitorPrint(int indent){
    printIndent (indent);
    printf ("CASE ");
    intTable.printEntry(caseInt);
    printf ("\n");
    if (currentNode==NULL) return;
    currentNode->visitorPrint(indent+1);
    nodeList *listSweep;
    listSweep = nextListNode;
    while (listSweep != NULL) {
        //cout << "laco\n";
        listSweep->currentNode->visitorPrint(indent+1);
        listSweep = listSweep->nextListNode;
    }
}

////////////////////
///VISITOR ACCEPT///
////////////////////

void programNode::accept(Visitor *v){v->visit(this);}
void structNode::accept(Visitor *v){v->visit(this);}
void functionNode::accept(Visitor *v){v->visit(this);}
void classNode::accept(Visitor *v){v->visit(this);}
void declarationsList::accept(Visitor *v){v->visit(this);}
void nodeList::accept(Visitor *v){v->visit(this);}
void exprNodeList::accept(Visitor *v){v->visit(this);}
void structNodeList::accept(Visitor *v){v->visit(this);}
void breakNode::accept(Visitor *v){v->visit(this);}
void ifNode::accept(Visitor *v){v->visit(this);}
void whileNode::accept(Visitor *v){v->visit(this);}
void printNode::accept(Visitor *v){v->visit(this);}
void readlnNode::accept(Visitor *v){v->visit(this);}
void returnNode::accept(Visitor *v){v->visit(this);}
void switchNode::accept(Visitor *v){v->visit(this);}
void caseList::accept(Visitor *v){v->visit(this);}
void exprNode::accept(Visitor *v){v->visit(this);}


////////////////////////
///Funções auxiliares///
////////////////////////

void printType (int type){
    if (type==1) printf ("bool ");
    else if (type==5) printf ("char ");
    else if (type==9) printf ("float ");
    else if (type==11) printf ("int ");
    else { idTable.printEntry(type); printf (" "); }
}

void printIndent (int indent){
    for (int cont=0; cont<indent; cont++) printf ("\t");
}

void printUnaryCode (int opCode, int value){
    switch (opCode){
        ///casos de operadores
        case CALL:
            printf("call:");
            idTable.printEntry(value);
            break;
        case ASTERISK:
            printf ("POINTER");
            break;
        case BIT_AND:
            printf ("ADDRESS");
            break;
        case NOT:
            printf ("NEGATION");
            break;
        case MINUS:
            printf ("MINUS");
            break;
        case PLUS:
            printf ("PLUS");
            break;
        case NEW:
            printf ("NEW");
            break;
        ///casos de palavras reservadas
        case THIS:
            printf ("THIS");
            break;
        case TRUE:
            printf ("TRUE");
            break;
        case FALSE:
            printf ("FALSE");
            break;
        ///casos de strings
        case NUMINT:
            printf ("int.");
            intTable.printEntry(value);
            break;
        case NUMFLOAT:
            printf ("float.");
            floatTable.printEntry(value);
            break;
        case ASCII:
            printf ("char.");
            //printf ("asciiCode:(%d)", value);
            charTable.printEntry(value);
            break;
        case LITERAL:
            printf ("literal.");
            literalTable.printEntry(value);
            break;
        case ID:
            printf ("id.");
            idTable.printEntry(value);
            break;
    }
    printf ("\n");
}

void printBinaryCode (int opCode){
    switch (opCode){
        case ASSIGNMENT:
            printf("ASSIGNMENT");
            break;
        case LOGIC_OR:
            printf ("LOGIC OR");
            break;
        case LOGIC_AND:
            printf ("LOGIC_AND");
            break;
        case EQUALS:
            printf ("EQUALS");
            break;
        case NOT_EQUAL:
            printf ("NOT_EQUAL");
            break;
        case MORE_THAN:
            printf ("MORE_THAN");
            break;
        case MORE_EQUAL:
            printf ("MORE_EQUAL");
            break;
        case LESS_THAN:
            printf ("LESS_THAN");
            break;
        case LESS_EQUAL:
            printf ("LESS_EQUAL");
            break;
        case PLUS:
            printf ("PLUS");
            break;
        case MINUS:
            printf ("MINUS");
            break;
        case BIT_OR:
            printf ("BIT_OR");
            break;
        case ASTERISK:
            printf ("MULTIPLY");
            break;
        case SLASH:
            printf ("SLASH");
            break;
        case PERCENT:
            printf ("PERCENT");
            break;
        case BIT_AND:
            printf ("BIT_AND");
            break;
        case ARROW:
            printf ("POINTER DEREFERENCE");
            break;
        case DOT:
            printf ("NORMAL DEREFERENCE");
            break;
        case L_BRACKET:
            printf ("ARRAY INDEX ACCESS");
            break;
    }
    printf ("\n");
}
