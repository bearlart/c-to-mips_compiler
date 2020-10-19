#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "reservedTable.h"

ReservedTable::ReservedTable (){
    nextFreeSlot = 0;
    //A posição 0 do vetor começa vazia.
    vectorSize = 1;
    //O tamanho do vetor de strings começa com o 1o valor da progressão aritmética.
    stringVector = (char*) malloc (vectorSize* BUFFER *sizeof *stringVector);
    //Aloca o vetor de strings.

    for (int cont = 0; cont < HASHING_PRIME; cont++) table[cont] = NULL;
    //Inicializa a tabela de nós com valores nulos, já que não há palavras inseridas.
    insertNewString("bool", 4, 1);
    insertNewString("break", 5, 2);
    insertNewString("case", 4, 3);
    insertNewString("catch", 5, 4);
    insertNewString("char", 4, 5);
    insertNewString("class", 5, 6);
    insertNewString("else", 4, 7);
    insertNewString("false", 5, 8);
    insertNewString("float", 5, 9);
    insertNewString("if", 2, 10);
    insertNewString("int", 3, 11);
    insertNewString("new", 3, 12);
    insertNewString("print", 5, 13);
    insertNewString("private", 7, 14);
    insertNewString("public", 6, 15);
    insertNewString("readln", 6, 16);
    insertNewString("return", 6, 17);
    insertNewString("struct", 6, 18);
    insertNewString("switch", 6, 19);
    insertNewString("this", 4, 20);
    insertNewString("throw", 5, 21);
    insertNewString("true", 4, 22);
    insertNewString("try", 3, 23);
    insertNewString("typedef", 7, 24);
    insertNewString("while", 5, 25);
}

ReservedTable::~ReservedTable() {}

int ReservedTable::insertNewString (const char newString[], int endOfString, int returnCode){
    int index = 0;
    int hashkey = hashing (newString, endOfString);
    //teste do tamanho do buffer, para ver se cabe a palavra a ser inserida.
    //if (lookUp (newString, endOfString) == 0) return -1;

    if (nextFreeSlot + endOfString >= vectorSize*BUFFER){
        vectorSize++;
        stringVector = (char*) realloc (stringVector, vectorSize* BUFFER * sizeof *stringVector);
    }
    //inserção da string no vetor.
    while (index < endOfString){
        stringVector[nextFreeSlot + index] = newString[index];
        //printf ("%c char.", idVector[nextFreeSlot + index]);
        //printf ("%c chaar.", newID[index]);
        index++;
    }
    //Criação do novo nó.
    Node* inserted = new Node();
    inserted->key = hashkey;
    inserted->returnValue = returnCode;
    inserted->numberOfChars = endOfString;
    inserted->locationOnArray = nextFreeSlot;
    nextFreeSlot = nextFreeSlot + endOfString;
    inserted->nextNode = NULL;
    //Inserção do nó na tabela.
    Node* next;
    //int pos = 0;
    next = table[hashkey];
     if (next != NULL) {
        while (next->nextNode != NULL) {
            //pos++;
            next = next->nextNode;
            //printf ("Inseriu na posicao %d\n", pos);
            }
            next->nextNode = inserted;
    } else table[hashkey] = inserted;
    return inserted->returnValue;
}

int ReservedTable::hashing (const char newString[], int endOfString){
    int sum = 0; //variável que armazenará a soma dos caracteres.
    int index = 0; //variavel que sera usada para controlar a soma.
    int hashkey;
    //calculo da soma dos caracteres
    while (index < endOfString){
        sum = sum + newString[index]*(index+1);
        //multiplicando pelo índice, palavras como aab, aba, baa tem valores diferentes de hashing.
        index++;
    }
    if (sum<0) sum = -sum;
    //printf ("Sum: %d\n", sum);
    //funcao de hashing
    hashkey = sum % HASHING_PRIME;
    return hashkey;
}

int ReservedTable::lookUp (char* newString, int endOfString){
    int hashkey = hashing (newString, endOfString);
    Node* pointer = table[hashkey]; //pega o ponteiro que aponta para as chaves com o hashing em questão.
    while (pointer!=NULL){
        if (endOfString == pointer->numberOfChars){
            if  (0 == strncmp (stringVector+(pointer->locationOnArray), newString, endOfString)){
                //strncmp é uma função da string.h que compara duas strings pela quantidade de elementos
                //especificada no 3o parametro. Os dois primeiros parametros sao ponteiros para as strings.
                //No caso, o primeiro parâmetro está sendo um ponteiro que é o ponteiro stringVector
                //deslocado pelo numero de posicoes onde a palavra que estamos considerando começa.
                return pointer->returnValue;
            }
        }
        pointer = pointer->nextNode;
    }
    return -1; //para teste, temporariamente
}
