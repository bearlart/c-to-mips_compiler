#include <stdio.h>
#include <stdlib.h>
#include "TreeNode.h"
#include "parser.h"
#include "sampleVisitor.h"


class semantycVisitor: public Visitor {
public:
    semantycVisitor();
    ~semantycVisitor();
    void visit(programNode *node){
        cout << "programNode" << endl;
    }
    void visit(structNode *node){
        cout << "structNode" << endl;
    }
    void visit(functionNode *node){
        cout << "functionNode" << endl;
    }
    void visit(classNode *node){
        cout << "classNode" << endl;
    }
    void visit(declarationsList *list){
        cout << "declarationsList" << endl;
    }
    ///5
    void visit(nodeList *list){
        cout << "nodeList" << endl;
    }
    void visit(exprNodeList *list){
        cout << "exprNodeList" << endl;
    }
    void visit(breakNode *node){
        cout << "breakNode" << endl;
    }
    void visit(ifNode *node){
        cout << "ifNode" << endl;
    }
    void visit(whileNode *node){
        cout << "whileNode" << endl;
    }
    ///10
    void visit(printNode *node){
        cout << "printNode" << endl;
    }
    void visit(readlnNode *node){
        cout << "readlnNode" << endl;
    }
    void visit(returnNode *node){
        cout << "returnNode" << endl;
    }
    void visit(switchNode *node){
        cout << "switchNode" << endl;
    }
    void visit(caseList *list){
        cout << "caseList" << endl;
    }
    ///15
    void visit(exprNode *node){
        cout << "exprNode" << endl;
    }
    void visit(structNodeList *list){
        cout << "structNodeList" << endl;
    }

};

void runSemantycAnalyzer(programNode *programNode);

