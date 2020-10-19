#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "table.h"

SymbolTable::SymbolTable (){
    nextFreeSlot = 0;
    ///A posição 0 do vetor começa vazia.
    vectorSize = 1;
    ///O tamanho do vetor de strings começa com o 1o valor da progressão aritmética.
    stringVector = (char*) malloc (vectorSize* BUFFER *sizeof *stringVector);
    ///Aloca o vetor de strings.
    for (int cont = 0; cont < HASHING_PRIME; cont++) table[cont] = NULL;
    ///Inicializa a tabela de nós com valores nulos, já que não há palavras inseridas.
}

SymbolTable::~SymbolTable () {}

int SymbolTable::hashing (char* newString, int endOfString){
    int sum = 0; ///variável que armazenará a soma dos caracteres.
    int index = 0; ///variavel que sera usada para controlar a soma.
    int hashkey;

    //calculo da soma dos caracteres
    while (index < endOfString){
        sum = sum + newString[index]*(index+1);
        ///multiplicando pelo índice, palavras como aab, aba, baa tem valores diferentes de hashing.
        index++;
    }
    if (sum<0) sum = -sum;
    ///printf ("Sum: %d\n", sum);
    ///funcao de hashing
    hashkey = sum % HASHING_PRIME;
    return hashkey;
}

int SymbolTable::lookUp (char* newString, int endOfString){
    int hashkey = hashing (newString, endOfString);
    Node* pointer = table[hashkey]; ///pega o ponteiro que aponta para as chaves com o hashing em questão.
    while (pointer!=NULL){
        if (endOfString == pointer->numberOfChars){
            if  (0 == strncmp (stringVector+(pointer->locationOnArray), newString, endOfString)){
                    //strncmp é uma função da string.h que compara duas strings pela quantidade de elementos
                    //especificada no 3o parametro. Os dois primeiros parametros sao ponteiros para as strings.
                    //No caso, o primeiro parâmetro está sendo um ponteiro que é o ponteiro stringVector
                    //deslocado pelo numero de posicoes onde a palavra que estamos considerando começa.
                    return pointer->key;
            }
        }
            ///if (cont == endOfID) return 123;//pointer->returnValue;
        pointer = pointer->nextNode;
    }
    return -1; ///para teste, temporariamente
}

int SymbolTable::insertNewString (char* newString, int endOfString){
    int index = 0, i = 0, testKey;
    int hashkey = hashing (newString, endOfString);
    //teste do tamanho do buffer, para ver se cabe a palavra a ser inserida.
    if ((testKey = lookUp (newString, endOfString)) != -1) return testKey;

    if (nextFreeSlot + endOfString >= vectorSize*BUFFER){
        vectorSize++;
        stringVector = (char*) realloc (stringVector, vectorSize* BUFFER * sizeof *stringVector);
    }
    ///inserção da string no vetor.
    while (index < endOfString){
        stringVector[nextFreeSlot + index] = newString[index];
        index++;
    }
    ///Criação do novo nó.
    Node* inserted = new Node();
    inserted->key = hashkey;
    inserted->returnValue = hashkey;
    inserted->numberOfChars = endOfString;
    inserted->locationOnArray = nextFreeSlot;
    nextFreeSlot = nextFreeSlot + endOfString;
    inserted->nextNode = NULL;
    ///Inserção do nó na tabela.
    Node* next;
    next = table[hashkey];
    if (next != NULL) {
            i++;
        while (next->nextNode != NULL) {
            i++;
            next = next->nextNode;
            }
            next->nextNode = inserted;
    } else table[hashkey] = inserted;
    inserted->key = hashkey+(HASHING_PRIME*i);
    //printf ("Gerando key %d na tabela ID. I = %d\n", inserted->key, i);
    return inserted->key;
}


void SymbolTable::printStrings(FILE* outFile){
    int index = 0;
    Node* next;
    for (int cont = 0; cont < HASHING_PRIME; cont++){
    ///Loop exterior com o for, que varrerá todos os valores de hashing.
            next = table[cont];
        while (next!=NULL){
            if (outFile != stdout) {
                fprintf (outFile, "str%d: .asciiz \"", next->key);
            }
            ///Loop interior com o while, que varrerá todas as strings que tem um certo valor de hashing.
            while (index<(next->numberOfChars)){
                fprintf (outFile, "%c", stringVector[index+next->locationOnArray]);
                index++;
            }
            if (outFile != stdout) fprintf (outFile, "\"");
            fprintf (outFile, "\n");
            index = 0;
            next = next->nextNode;
        }
    }
}

void SymbolTable::printEntry(int entryKey){
    int hashkey = entryKey % HASHING_PRIME;
    Node* pointer = table[hashkey]; ///pega o ponteiro que aponta para as chaves com o hashing em questão.
    while (pointer!=NULL){
        if (entryKey == pointer->key){
            for (int cont=0; cont<pointer->numberOfChars; cont++)
            printf ("%c", stringVector[pointer->locationOnArray+cont]);
        }
        pointer = pointer->nextNode;
    }
}

void SymbolTable::fPrintEntry(FILE* outFile, int entryKey){
    int hashkey = entryKey % HASHING_PRIME;
    Node* pointer = table[hashkey]; ///pega o ponteiro que aponta para as chaves com o hashing em questão.
    while (pointer!=NULL){
        if (entryKey == pointer->key){
            for (int cont=0; cont<pointer->numberOfChars; cont++)
            fprintf (outFile, "%c", stringVector[pointer->locationOnArray+cont]);
        }
        pointer = pointer->nextNode;
    }
}

int SymbolTable::stringToValue(int entryKey){
    int hashkey = entryKey % HASHING_PRIME;
    int value;
    Node* pointer = table[hashkey]; ///pega o ponteiro que aponta para as chaves com o hashing em questão.
    while (pointer!=NULL){
        if (entryKey == pointer->key){
            char word[pointer->numberOfChars+1];
            word[pointer->numberOfChars] = '\0';
            for (int cont=0; cont<pointer->numberOfChars; cont++)
                word[cont] = stringVector[pointer->locationOnArray+cont];
            value = atoi(word);
            //printf ("VALUE: %d\n", value);
            return value;
        }
        pointer = pointer->nextNode;
    }
    return 0;
}
