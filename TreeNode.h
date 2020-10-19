#include <cstddef>
#include <string>
#include <stdio.h>
#include "analex.h"

#ifndef TREENODE_H
#define TREENODE_H

using namespace std;

class treeNode;

class exprNode;
class stmtNode;

class stmtNodeList;
class exprNodeList;
class structNodeList;

///classes que herdam de stmt
class ifNode;
class whileNode;
class switchNode;
class breakNode;
class printNode;
class readlnNode;
class returnNode;
class throwNode;
class blockNode;
class tryNode;
class caseBlockList;
class exprStmtNode;
class caseList;

///

class functionCall;
class declarationsList;
class nodeList;
class exprStack;

class functionNode;
class classNode;
class structNode;
class programNode;
class Visitor;

void printType (int type);
void printIndent (int indent);
void printUnaryCode (int opCode, int value);
void printBinaryCode (int opCode);

///////////////////////////
///descrição das classes///
///////////////////////////


///treeNode
class treeNode {
public:
    virtual void visitorPrint(int indent) = 0;
    virtual void accept(Visitor *v) = 0;
    virtual void assemblyPrint() = 0;
//    void accept(Visitor &v){
//        v.visit(this);
//    }
};

//////////////////////////////
///classes relativas a expr///
//////////////////////////////

class exprNode: public treeNode {
public:
    int opCode;
    ///Armazena o codigo da operação.
    int isUnary;
    ///int tratado como booleano, que diz se a operação é unária ou binária.
    int id;
    ///usado para algumas expr que tem um identificador associado (chamadas de funções, variáveis)
    exprNode* leftChild;
    exprNode* rightChild;
    ///nós que apontam para os operandos da operação em questão no nó presente.
    exprNodeList *callParameters;
    ///ponteiro para lista de parâmetros. Usado para chamadas de função.
    exprNode(int op, int unary, int idCode);
    ///construtor que recebe os dados da expr em questão como parâmetros.
    ~exprNode();
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
    void exprAssemblyPrint(int temp = 0);
};

class exprNodeList: public treeNode {
public:
    exprNodeList();
    ~exprNodeList();
    exprNode* currentExprNode;
    exprNodeList* nextExprNodeList;
    void insertListNode (exprNode *node);
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class exprStack {
public:
    exprNodeList* exprStackTop;

    exprStack();
    ~exprStack();
    void pushNode (exprNode *node);
    void insertNode (exprNode *node);
    void Pop();
    void visitorPrint(int indent);
};

///nodeList///

class nodeList: public treeNode {
public:
    treeNode *currentNode;
    nodeList *nextListNode;

    nodeList();
    ~nodeList();
    void insertNode (treeNode* newNode);
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};


class structNodeList: public nodeList {
public:
    structNode *currentStructNode;
    structNodeList *nextStructNodeList;

    structNodeList();
    ~structNodeList();
    void insertStructNode (structNode * newNode);
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void calcOffset();
    structNode* varSweep (int key);
};

//////////////////
///classes Stmt///
//////////////////

class breakNode: public treeNode {
public:
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class ifNode: public treeNode {
public:
    exprNode *logicNode;
    treeNode *trueNode;
    treeNode *falseNode;
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class whileNode: public treeNode {
public:
    exprNode *logicNode;
    treeNode *loopNode;
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class printNode: public treeNode {
public:
    exprNodeList *stmtExpr;
    printNode();
    ~printNode();
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class readlnNode: public treeNode {
public:
    exprNode *stmtExpr;
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class returnNode: public treeNode {
public:
    exprNode *stmtExpr;
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class switchNode: public treeNode {
public:
    exprNode *logicTest;
    caseList *cases;
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class caseList: public nodeList {
public:
    int caseInt;
    int caseLabel;
    caseList *nextCaseList;
    void insertCaseList(caseList* newCaseList);
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

/////////////////////////
///lista de declarações//
/////////////////////////

class declarationsList: public treeNode {
public:
    int type;
    int id;
    int pointer; ///1 se a variável for um ponteiro; 1 se não for
    int arraySize; ///1 é o valor default
    int isPrivate; ///1 se a variável for privada; 0 se não for; só faz sentido dentro de classes
    declarationsList* nextDeclaration;
    int offsetStart;
    int offset;

    declarationsList();
    ~declarationsList();
    void insertDeclaration (declarationsList *newDecl);

    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
    declarationsList* varSweep(int key);
    void calcOffset (int currentOffset);
    int maxOffset();
};

class functionNode: public treeNode {
public:
    int functionID;
    int returnType;
    int returnPointer;
    int isPrivate; ///só é relevante dentro de uma classe
    int maxRight;


    functionNode();
    ~functionNode();
    void visitorPrint(int indent);
    declarationsList *parameters;
    declarationsList *functionVariables;
    nodeList *funcStmtList;
    void accept(Visitor *v);
    void assemblyPrint();
};

class classNode: public treeNode {
public:
    int classID;
    int superclassID;
    declarationsList *classVariables;
    nodeList *classFunctions;

    classNode();
    ~classNode();
    void visitorPrint(int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class structNode: public treeNode {
public:
    int structID;
    declarationsList *structVariables;

    structNode();
    ~structNode();
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

class programNode: public treeNode {
public:
    structNodeList *structList;
    nodeList *classList;
    nodeList *functionList;
    declarationsList *globalVariables;

    programNode();
    ~programNode();
    void visitorPrint (int indent);
    void accept(Visitor *v);
    void assemblyPrint();
};

///Classe abstrata Visitor

class Visitor {
//virtual void visit ( *node) = 0;
public:
    ///nó raiz do programa
    virtual void visit(programNode *node) = 0;

    ///estruturas de mais alto nível
    virtual void visit (structNode *node) = 0;
    virtual void visit (functionNode *node) = 0;
    virtual void visit (classNode *node) = 0;

    ///lista de declarações
    virtual void visit(declarationsList *list) = 0;

    ///listas de nodes
    virtual void visit(nodeList *list) = 0;
    virtual void visit(exprNodeList *list) = 0;
    virtual void visit(structNodeList *list) = 0;

    ///visits dos stmts
    virtual void visit (breakNode *node) = 0;
    virtual void visit (ifNode *node) = 0;
    virtual void visit (whileNode *node) = 0;
    virtual void visit (printNode *node) = 0;
    virtual void visit (readlnNode *node) = 0;
    virtual void visit (returnNode *node) = 0;
    virtual void visit (switchNode *node) = 0;
    virtual void visit (caseList *list) = 0;

    ///visit de expr
    virtual void visit (exprNode *node) = 0;
};


#endif // TREENODE_H
