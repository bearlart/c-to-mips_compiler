#include "node.h"
///N� que conter� informa��es das strings inseridas.

#define HASHING_PRIME 769
///Primo a ser usado no hashing das strings.
#define BUFFER 2000
///Tamanho, em sizeof char, do buffer a ser usado para armazenar strings.

#ifndef TABLE_H
#define TABLE_H

class SymbolTable {
public:
    char* stringVector;
    ///vetor dinamicamente alocado de caracteres que armazena strings.
    ///pode ser aumentado por realloc em tempo de execu��o.

    int nextFreeSlot;
    ///variavel que armazena a proxima posi��o vazia do vetor de strings.

    Node* table[HASHING_PRIME];
    /// tabela de hashing que armazena ponteiros para n�s
    /// que conter�o as posi��es onde come�am as strings armazenadas.

    int vectorSize;
    ///Vari�vel usada para aumentar o vetor com uma Progress�o Aritm�tica,
    ///se seu espa�o n�o for suficiente.

    ///////FUN��ES//////
    ////////////////////

    SymbolTable ();
    ~SymbolTable ();

    int insertNewString (char* newString, int endOfString);
    ///Fun��o que insere uma nova string na tabela.
    ///Retorna -1 caso a string j� esteja inserida.

    int lookUp (char* newString, int endOfString);
    ///Fun��o que retorna:
    ///UM VALOR POSITIVO, se a palavra em newString ja estiver inserida;
    ///MENOS UM, se a palavra n�o estiver inserida.

    int hashing (char* newString, int endOfString);
    ///Fun��o de hashing. Retorna a chave da string.

    void printStrings(FILE* outFile = stdout);
    ///Fun��o que imprime sistematicamente todas as strings da tabela.

    void printEntry (int entryKey);
    ///Fun��o que imprime uma entrada da tabela, recebendo sua chave.

    void fPrintEntry (FILE* outFile, int entryKey);
    ///Fun��o que imprime uma entrada na tabela no arquivo especificado no segundo argumento.

    int stringToValue(int entryKey);
    ///Fun��o que transforma uma string em um inteiro.
};

#endif
