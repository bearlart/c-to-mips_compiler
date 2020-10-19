#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "table.h"
#include "errors.h"
#include "reservedTable.h"
#define BUFFER_SIZE 4096
#define ID_BUFFER 20

///constantes das palavras reservadas
#define BOOL 1
#define BREAK 2
#define CASE 3
#define CATCH 4
#define CHAR 5
#define CLASS 6
#define ELSE 7
#define FALSE 8
#define FLOAT 9
#define IF 10
#define INT 11
#define NEW 12
#define PRINT 13
#define PRIVATE 14
#define PUBLIC 15
#define READLN 16
#define RETURN 17
#define STRUCT 18
#define SWITCH 19
#define THIS 20
#define THROW 21
#define TRUE 22
#define TRY 23
#define TYPEDEF 24
#define WHILE 25

///constantes dos tokens de pontuação
#define L_BRACKET 26 //[
#define R_BRACKET 27 //]
#define L_PARENTHESIS 28
#define R_PARENTHESIS 29 //)
#define L_BRACE 30 //{
#define R_BRACE 31 //}
#define LESS_THAN 32 //<
#define LESS_EQUAL 33 //<=
#define MORE_THAN 34 //>
#define MORE_EQUAL 35 //>=
#define ASSIGNMENT 36 //=
#define EQUALS 37 //==
#define BIT_AND 38 //&
#define LOGIC_AND 39 //&&
#define BIT_OR 40 //|
#define LOGIC_OR 41 //||
#define NOT 42 // !
#define NOT_EQUAL 43 // !=
#define MINUS 44 //-
#define ARROW 45 //->
#define PLUS 46 //+
#define SLASH 47 // /
#define ASTERISK 48 //*
#define PERCENT 49 //%
#define DOT 50 //.
#define COMMA 51 //,
#define SEMICOLON 52 //;
#define COLON 53 //:

///constantes dos tokens de strings
#define ID 54
#define LITERAL 56
#define NUMINT 57
#define NUMFLOAT 58
#define ASCII 59

#define EOF_TOKEN 60

#define CALL 120

#ifndef ANALEX_H_INCLUDED
#define ANALEX_H_INCLUDED

extern int position;
///controle da posicao do buffer
extern int tableKey;

extern int endOfReading;
///controle para final de leitura
extern int lines;
///quantidade de linhas
extern int columns;
///quantidade de colunas
extern int strBufferPos;
///armazena a posição do vetor com a string a ser adicionada na tabela
extern char *strBuffer;
///vetor que armazena a string a ser armazenada na tabela
extern int state;
///controle dos estados do autômato
extern int strBufferSize;
///controla o tamanho do vetor da string que esta sendo analisada.
///será incrementado caso seja necessário aumentar o vetor por realloc.
extern SymbolTable idTable;
/// tabela de IDs.
extern SymbolTable literalTable;
/// tabela de "literais".
extern SymbolTable intTable;
/// tabela com inteiros.
extern SymbolTable floatTable;
/// tabela com floats.
extern SymbolTable charTable;
/// tabela com chars.
extern ReservedTable reservedTable;
/// tabela com palavras reservadas.

int DFA();
///Implementacao do automato finito deterministico

void readNext ();
///Funcao auxiliar para consumir um caracter, auxiliar na gerencia das colunas e verificar se existe a necessidade de atualizar a variavel que guarda a entrada

void resetDFA();
///Funcao auxiliar para levar o AFD novamente ao seu estado inicial

void addLines();
///Funcao para auxiliar o controle da quantidade de linhas e colunas

char* insertChar (char* c);
///Funcao para auxiliar a insercao de um caracter no buffer strBuffer

void updateFeed(char entrada[]);
///Funcao para auxiliar a atualizacao da variavel que guarda a entrada, caso ela atinja o seu limite

void printTokenName(int tokenNumber);
///Funcao auxiliar para imprimir o nome dos tokens

void printTokenNameSTDERR(int tokenNumber);
///Funcao auxiliar para imprimir o nome dos tokens na saida STDERR

void printAmountOfLines();
///Funcao auxiliar para imprimir a quantidade de linhas lidas

int returnEOF();
///Funcao auxiliar para sinalizar o fim da leitura do arquivo

#endif // ANALEX_H_INCLUDED
