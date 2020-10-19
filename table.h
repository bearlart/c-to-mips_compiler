#include "node.h"
///Nó que conterá informações das strings inseridas.

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
    ///pode ser aumentado por realloc em tempo de execução.

    int nextFreeSlot;
    ///variavel que armazena a proxima posição vazia do vetor de strings.

    Node* table[HASHING_PRIME];
    /// tabela de hashing que armazena ponteiros para nós
    /// que conterão as posições onde começam as strings armazenadas.

    int vectorSize;
    ///Variável usada para aumentar o vetor com uma Progressão Aritmética,
    ///se seu espaço não for suficiente.

    ///////FUNÇÕES//////
    ////////////////////

    SymbolTable ();
    ~SymbolTable ();

    int insertNewString (char* newString, int endOfString);
    ///Função que insere uma nova string na tabela.
    ///Retorna -1 caso a string já esteja inserida.

    int lookUp (char* newString, int endOfString);
    ///Função que retorna:
    ///UM VALOR POSITIVO, se a palavra em newString ja estiver inserida;
    ///MENOS UM, se a palavra não estiver inserida.

    int hashing (char* newString, int endOfString);
    ///Função de hashing. Retorna a chave da string.

    void printStrings(FILE* outFile = stdout);
    ///Função que imprime sistematicamente todas as strings da tabela.

    void printEntry (int entryKey);
    ///Função que imprime uma entrada da tabela, recebendo sua chave.

    void fPrintEntry (FILE* outFile, int entryKey);
    ///Função que imprime uma entrada na tabela no arquivo especificado no segundo argumento.

    int stringToValue(int entryKey);
    ///Função que transforma uma string em um inteiro.
};

#endif
