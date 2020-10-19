#include <stdio.h>
#include <iostream>

#ifndef NODE_H
#define NODE_H

class Node {
public:
    int key;
    ///Vari�vel com o valor da chave de hashing da palavra.
    ///Poderia ter sido omitida.
    int returnValue;
    ///Valor de retorno do n�, importante para a tabela de palavras reservadas.
    int locationOnArray;
    ///inteiro que armazena onde est� o primeiro caracter da palavra em quest�o no vetor da tabela.
    int numberOfChars;
    ///numero de caracteres que a palavra tem.
    Node* nextNode;
    ///Proximo no com o mesmo valor de hashing.

    Node(){
    nextNode = NULL;
    }
};

#endif // NODE_H
