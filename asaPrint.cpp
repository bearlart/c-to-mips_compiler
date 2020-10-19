#include "asaPrint.h"

void asaPrint::visit(programNode *node, int indent){
    //int indent = 0;
    printf ("\n--------------------------------\n");
    printf ("---ARVORE DE SINTAXE ABSTRATA---\n");
    printf ("--------------------------------\n");
    printIndent (indent);
    printf ("Program\n");

    ///imprime variáveis globais
    declarationsList *declSweep;
    declSweep = node->globalVariables;
    if (declSweep != NULL) {
        //declSweep->visitorPrint(indent+1);
        //declSweep = declSweep->nextDeclaration;
        visit(declSweep, indent+1);
    }

    ///imprime structs
    node->structList->visitorPrint(indent+1);
    //visit((structNode*) node->structList->currentNode, indent+1);

    ///imprime funções
    node->functionList->visitorPrint(indent+1);

    ///imprime classes
    node->classList->visitorPrint(indent+1);
}

void asaPrint::visit (structNode *node, int indent){
    printIndent(indent);
    printf ("struct ");
    idTable.printEntry(node->structID);
    printf ("\n");
    //node->structVariables->visitorPrint (indent+1);
    //visit()
}

void asaPrint::visit(declarationsList *list, int indent){
    printIndent (indent);
    if (list->isPrivate == 1) printf ("private ");
    printf ("var ");
    printType(list->type);
    if (list->pointer==1) printf ("* ");
    idTable.printEntry (list->id);
    //idTable.printEntry(structID);
    if (list->arraySize != 1) {
        printf (" [ ");
        intTable.printEntry(list->arraySize);
        printf (" ]");
    }
    printf ("\n");
    if (list->nextDeclaration != NULL) list->nextDeclaration->visitorPrint(indent);
}

////////////////////////
///asaPrints de stmts///

void asaPrint::visit (breakNode *node, int indent){
    printIndent(indent);
    printf("BREAK\n");
}
