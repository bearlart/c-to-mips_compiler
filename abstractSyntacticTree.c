//#include "abstractSyntacticTree.h"
//
//#include <cstring>
//#include <stdlib.h>
//#include <stdio.h>
//
//
//using namespace std;
//
//TreeNode *root = new TreeNode();
////TreeNode *tail = new TreeNode();
////
//void beginTree(){ //quando eu começo a árvore, só tenho 1 nó e
//   //root = new TreeNode("Program");
//   //root = node;
////   root->next = tail; // o prox da raiz recebe nulo
////   tail = root; // e a cauda recebe a raiz
//
//}
//
//void addNode (TreeNode *node){
//    TreeNode *aux = root;
//    while (root->next != NULL)
//        root = root->next;
//    root->next = node;
//    root = aux;
//
////    tail->next = node;
////    tail = tail->next;
////    tail->next = NULL;
//}
////
//void printTree(){
//    printf("\n\n***Abstract Syntactic Tree (begin)***\n");
//    int i;
//    while (root != NULL){
//        for (i = 0; i < strlen(root->name); i++){
//            printf("%c", root->name[i]);
//        }
//        printf("\n");
//
//        root = root->next;
//   }
//   printf("***Abstract Syntactic Tree (end)***\n\n");
//}
