#include "table.h"

#ifndef RESERVED_TABLE
#define RESERVED_TABLE

class ReservedTable: public SymbolTable {

    private:
    int insertNewString (const char newString[], int endOfString, int returnCode);
    //fun��o difere da fun��o da superclasse pela adi��o de um par�metro returnCode,
    //que � o valor de TOKEN que a palavra reservada retornar� em caso de ser encontrada no lookUp.
    int hashing (const char newString[], int endOfString);
    //ao contr�rio da fun��o an�loga da superclasse SymbolTable, usa-se uma constante char ao inv�s de um ponteiro char.

    public:
    ReservedTable();
    ~ReservedTable();

    int lookUp (char* newString, int endOfString);
    //lookUp retorna:
    //a chave de uma palavra reservada, que SER� UM VALOR POSITIVO; ou
    //-1, caso a string em quest�o n�o seja uma string reservada.
};

#endif // RESERVED_TABLE
