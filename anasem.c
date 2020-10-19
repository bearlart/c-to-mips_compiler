#include "anasem.h"

semantycVisitor::semantycVisitor(){
}

semantycVisitor::~semantycVisitor(){
}

void runSemantycAnalyzer(programNode *programTest){
    int variavelThiago;

    semantycVisitor *v = new semantycVisitor();
    //v->visit(programTest);

    programTest->functionList->visitorPrint(0);
    variavelThiago = programTest->globalVariables->id;
    printf ("\nVariavel do thiago: ");
    idTable.printEntry (variavelThiago);
    printf ("\n");
//    programTest->structList

}
