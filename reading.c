#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include "analex.h"

FILE *file;
FILE *outFile;
int charactersRead;

char feed[BUFFER_SIZE];

void toRead(int argc, char **argv){
    lines = 1;
    if (verifyArguments(argc, argv) == 0){
        file = fopen(argv[1], "rb");
    }
    else{
        file = stdin;
    }
    file = fopen("teste.txt", "rb"); //comentar esta linha, serve apenas para facilitar os testes
    outFile = fopen("output.s", "w");
    charactersRead = fread(feed, sizeof(char), BUFFER_SIZE, file);

}

void fixExtension (char *c){
    int sizeOfC = strlen(c);

    if (c[sizeOfC-4] == '.' && c[sizeOfC-3] == 'c' && c[sizeOfC-2] == 'p' && c[sizeOfC-1] == 'm'){
    } else
        strcat (c, ".cpm");
}

///parece que no windows a posicao argv[0] esta reservada, o parametro (nome do arquivo) passado na chamada cai na posicao argv[1]
int verifyArguments(int argc, char **argv){
    int fixForLinux = 0; ///se precisar, alterar aqui para o valor 1
    if (argc == 2 - fixForLinux){ ///verifica se a quantidade de parametros passada eh igual a 1
                                  ///(a verificao eh com dois pois aparantemente no windows um
                                  ///parametro sempre vai ser passado(eh reservado), no caso, o q esta na posicao argv[0]

        fixExtension(argv[1 - fixForLinux]); ///verifica se o nome do arquivo tem a extensao .cpm
        return 0;
    } else {
        printf("\nQuantidade de argumentos passada incompativel.\nA leitura sera feita a partir do teclado.\n");
        return -1;
    }
}
