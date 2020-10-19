#include <stdio.h>
#include "analex.h"
//#include "abstractSyntacticTree.h"
#include "TreeNode.h"

#ifndef PARSER
#define PARSER


extern int contador ;

void eat ();
void skipTo (int *stop);
programNode *runParser();

void Program();
void StructDecl();
void ClassDecl();
void ClassDeclTail();
void LocalDecl();
void TypeDecl();
void TypeDeclTail();
void IdList();
void IdListTail();
void VarDecl();
void Pointer();
void Array();
void FunctionDecl();
void StmtOrDecl();
void StmtOrDeclTail();
void FormalList();
void FormalRest();
void Type();
void StmtList();
void Stmt();
void CaseBlock();
void ExprList();
void ExprListTail();
void Expr();
void ExprTail();
void ExprO();
void ExprOTail();
void ExprA();
void ExprATail();
void ExprE();
void ExprETail();
void ExprC();
void ExprCTail();
void ExprB();
void ExprBTail();
void ExprT();
void ExprTTail();
void ExprU();
void ExprP();
void ExprPTail();
void Primary();
void ListTest();

void printAmountOfErrors();

extern int token;
extern int pastToken;
extern int i;
extern int vector[100];
extern int control;
extern int amountOfErrors;
extern programNode *programRoot;
extern int currentPointer;
extern int currentType;

extern int synchProgram[];// $
extern int synchStructDecl[];// int, float, bool, ID, char, class, typedef, $
extern int synchClassDecl[];// int, float, bool, ID, char, class, typedef, $
extern int synchClassDeclTail[];// int, float, bool, ID, char, class, typedef, $
extern int synchLocalDecl[];// };
extern int synchTypeDecl[];// public:, private:, int, float, bool, ID, char, class, typedef, };, $
extern int synchTypeDeclTail[];// public:, private:, int, float, bool, ID, char, class, typedef, };, $
extern int synchIdList[];// ;
extern int synchIdListTail[];// ;
extern int synchVarDecl[];// }
extern int synchPointer[];// ID
extern int synchArray[];// ,, IdlistTail, ;, )
extern int synchFunctionDecl[];// public:, private:, int, float, bool, ID, char, class, typedef, };, $
extern int synchStmtOrDecl[];// }
extern int synchStmtOrDeclTail[];// }
extern int synchFormalList[];// )
extern int synchFormalRest[];// )
extern int synchType[];// *, ID
extern int synchStmtList[];// case, }
extern int synchStmt[];// else, catch, if, while, switch, break, print, readln, return, throw, {, try, +, -, !, *, &, ID, NUM, LITERAL, true, false, this, ‘ASCII‘, (, new, case, }
extern int synchCaseBlock[];// }
extern int synchExprList[];// )
extern int synchExprListTail[];// )
extern int synchExpr[];// ), ,, ;
extern int synchExprTail[];// ;, ), ,
extern int synchExprOr[];// =, ;, ), ,
extern int synchExprOrTail[];// DOUBLEPIPE, =, ;, ), ,
extern int synchExprAnd[];// DOUBLEPIPE, =, ;, ), ,
extern int synchExprAndTail[];// DOUBLEPIPE, =, ;, ), ,
extern int synchExprEqual[];// &&, DOUBLEPIPE, =, ;, ), ,
extern int synchExprEqualTail[];// DOUBLEPIPE, =, ;, &&, ), ,
extern int synchExprCompare[];// ==, !=, DOUBLEPIPE, =, ;, &&, ), ,
extern int synchExprCompareTail[];// ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprBin[];// <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprBinTail[];// <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprTimes[];// +, -, PIPE, <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprTimesTail[];// +, -, PIPE, <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprUnary[];// *, /, %, &, +, -, PIPE, <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprPointer[];// *, /, %, &, +, -, PIPE, <, <=, >, >=, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchExprPointerTail[];// ], +, -, PIPE, <, <=, >, >=, *, /, %, &, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchPrimary[];// FLEXA, ., [, ], +, -, PIPE, <, <=, >, >=, *, /, %, &, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
extern int synchListTest[];//FLEXA, ., [, ], +, -, PIPE, <, <=, >, >=, *, /, %, &, ==, !=, DOUBLEPIPE, =, ;, &&, ), ,, }
#endif


