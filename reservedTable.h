#include "table.h"

#ifndef RESERVED_TABLE
#define RESERVED_TABLE

class ReservedTable: public SymbolTable {

    private:
    int insertNewString (const char newString[], int endOfString, int returnCode);
    //função difere da função da superclasse pela adição de um parâmetro returnCode,
    //que é o valor de TOKEN que a palavra reservada retornará em caso de ser encontrada no lookUp.
    int hashing (const char newString[], int endOfString);
    //ao contrário da função análoga da superclasse SymbolTable, usa-se uma constante char ao invés de um ponteiro char.

    public:
    ReservedTable();
    ~ReservedTable();

    int lookUp (char* newString, int endOfString);
    //lookUp retorna:
    //a chave de uma palavra reservada, que SERÁ UM VALOR POSITIVO; ou
    //-1, caso a string em questão não seja uma string reservada.
};

#endif // RESERVED_TABLE
