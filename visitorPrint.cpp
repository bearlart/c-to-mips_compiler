#include "visitorPrint.h"

void visitorPrint::visit(programNode *node){
    int indent = 0;
    printf ("\n--------------------------------\n");
    printf ("---ARVORE DE SINTAXE ABSTRATA---\n");
    printf ("--------------------------------\n");
    printIndent (indent);
    printf ("Program\n");

    ///imprime vari�veis globais
    declarationsList *declSweep;
    declSweep = node->globalVariables;
    if (declSweep != NULL) {
        declSweep->visitorPrint(indent+1);
        declSweep = declSweep->nextDeclaration;
    }

    ///imprime structs
    node->structList->visitorPrint(indent+1);

    ///imprime fun��es
    node->functionList->visitorPrint(indent+1);

    ///imprime classes
    node->classList->visitorPrint(indent+1);
}


