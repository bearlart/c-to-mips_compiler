#include "analex.h"
#include "reading.h"

int position;
int endOfReading;
int lines;
int columns;
int strBufferPos = 0;
int strBufferSize = 1;
char *strBuffer;
int state = 0;
int tableKey = -1;

SymbolTable idTable;
SymbolTable literalTable;
SymbolTable intTable;
SymbolTable floatTable;
SymbolTable charTable;
ReservedTable reservedTable;

int returnEOF(){
    return endOfReading;
}

void readNext (){
    columns++;
    position++;

    if (position > BUFFER_SIZE - 1){
        updateFeed(feed);
    }
}

void updateFeed(char feed[]){
    position = 0;
    charactersRead = fread(feed, sizeof(char), BUFFER_SIZE, file);
}

void printAmountOfLines(){
     printf ("Amount of lines is: %d\n", lines);
}

void addLines(){
    columns = 0;
    lines++;
}

void resetDFA(){
    state = 0;
}

char* insertChar (char* c){
    if (strBufferPos == strBufferSize * ID_BUFFER) {
        strBufferSize++;
        c = (char *) realloc(c, ID_BUFFER*strBufferSize);
    }
    c[strBufferPos] = feed[position];
    strBufferPos++;

    return c;
}

void printTokenNameSTDERR(int tokenNumber){
    int i;
    switch(tokenNumber){
        case EOF_TOKEN: fprintf (stderr, "EOF_TOKEN"); break;
        case BOOL: fprintf (stderr, "bool"); break;
        case BREAK: fprintf (stderr, "break"); break;
        case CASE: fprintf (stderr, "case"); break;
        case CATCH: fprintf (stderr, "catch"); break;
        case CHAR: fprintf (stderr, "char"); break;
        case CLASS: fprintf (stderr, "class"); break;
        case ELSE: fprintf (stderr, "else"); break;
        case FALSE: fprintf (stderr, "false"); break;
        case FLOAT: fprintf (stderr, "float"); break;
        case IF: fprintf (stderr, "if"); break;
        case INT: fprintf (stderr, "int"); break;
        case NEW: printf ("new"); break;
        case PRINT: fprintf (stderr, "print"); break;
        case PRIVATE: fprintf (stderr, "private"); break;
        case PUBLIC: fprintf (stderr, "public"); break;
        case READLN: fprintf (stderr, "readln"); break;
        case RETURN: fprintf (stderr, "return"); break;
        case STRUCT: fprintf (stderr, "struct"); break;
        case SWITCH: fprintf (stderr, "switch"); break;
        case THIS: fprintf (stderr, "this"); break;
        case THROW: fprintf (stderr, "throw"); break;
        case TRUE: fprintf (stderr, "true"); break;
        case TRY: fprintf (stderr, "try"); break;
        case TYPEDEF: fprintf (stderr, "typedef"); break;
        case WHILE: fprintf (stderr, "while"); break;
        case L_BRACKET: fprintf (stderr, "L_BRACKET"); break;
        case R_BRACKET: fprintf (stderr, "R_BRACKET"); break;
        case L_PARENTHESIS: fprintf (stderr, "L_PARENTHESIS"); break;
        case R_PARENTHESIS: fprintf (stderr, "R_PARENTHESIS"); break;
        case L_BRACE: fprintf (stderr, "L_BRACE"); break;
        case R_BRACE: fprintf (stderr, "R_BRACE"); break;
        case LESS_THAN: fprintf (stderr, "LESS_THAN"); break;
        case LESS_EQUAL: fprintf (stderr, "LESS_EQUAL"); break;
        case MORE_THAN: fprintf (stderr, "MORE_THAN"); break;
        case MORE_EQUAL: fprintf (stderr, "MORE_EQUAL"); break;
        case ASSIGNMENT: fprintf (stderr, "ASSIGNMENT"); break;
        case EQUALS: fprintf (stderr, "EQUALS"); break;
        case BIT_AND: fprintf (stderr, "BIT_AND"); break;
        case LOGIC_AND: fprintf (stderr, "LOGIC_AND"); break;
        case BIT_OR: fprintf (stderr, "BIT_OR"); break;
        case LOGIC_OR: fprintf (stderr, "LOGIC_OR"); break;
        case NOT: fprintf (stderr, "NOT"); break;
        case NOT_EQUAL: fprintf (stderr, "NOT_EQUAL"); break;
        case MINUS: fprintf (stderr, "MINUS"); break;
        case ARROW: fprintf (stderr, "ARROW"); break;
        case PLUS: fprintf (stderr, "PLUS"); break;
        case SLASH: fprintf (stderr, "SLASH"); break;
        case ASTERISK: fprintf (stderr, "ASTERISK"); break;
        case PERCENT: fprintf (stderr, "PERCENT"); break;
        case DOT: fprintf (stderr, "DOT"); break;
        case COMMA: fprintf (stderr, "COMMA"); break;
        case SEMICOLON: fprintf (stderr, "SEMICOLON"); break;
        case COLON: fprintf (stderr, "COLON"); break;
        case ID: fprintf (stderr, "ID");
            fprintf (stderr, ".");
            for (i = 0; i< strBufferPos; i++){
                fprintf (stderr, "%c", strBuffer[i]);
            }
            fprintf (stderr, " ");
            idTable.insertNewString(strBuffer, strBufferPos);
            break;
        case LITERAL: fprintf (stderr, "LITERAL");
            fprintf (stderr, ".");
            for (i = 0; i< strBufferPos; i++){
                fprintf (stderr, "%c", strBuffer[i]);
            }
            fprintf (stderr, " ");
            literalTable.insertNewString(strBuffer, strBufferPos);
            break;
        case NUMINT: fprintf (stderr, "NUMINT");
            fprintf (stderr, ".");
            for (i = 0; i< strBufferPos; i++){
                fprintf (stderr, "%c", strBuffer[i]);
            }
            fprintf (stderr, " ");
            intTable.insertNewString(strBuffer, strBufferPos);
            break;
        case NUMFLOAT: fprintf (stderr, "NUMFLOAT");
            fprintf (stderr, ".");
            for (i = 0; i< strBufferPos; i++){
                fprintf (stderr, "%c", strBuffer[i]);
            }
            fprintf (stderr, " ");
            floatTable.insertNewString(strBuffer, strBufferPos);
            break;
        case ASCII: fprintf (stderr, "ASCII");
            fprintf (stderr, ".");
            for (i = 0; i< strBufferPos; i++){
                fprintf (stderr, "%c", strBuffer[i]);
            }
            fprintf (stderr, " ");
            charTable.insertNewString(strBuffer, strBufferPos);
            break;
        default:
             fprintf (stderr, " state:%d ", tokenNumber);
            printErrorLexer(tokenNumber);
            break;
        }
}

void printTokenName(int tokenNumber){
    int i;
    switch(tokenNumber){
        case EOF_TOKEN: printf("EOF_TOKEN\n"); break;
        case BOOL: printf("bool\n"); break;
        case BREAK: printf("break\n"); break;
        case CASE: printf("case\n"); break;
        case CATCH: printf("catch\n"); break;
        case CHAR: printf("char\n"); break;
        case CLASS: printf("class\n"); break;
        case ELSE: printf("else\n"); break;
        case FALSE: printf("false\n"); break;
        case FLOAT: printf("float\n"); break;
        case IF: printf("if\n"); break;
        case INT: printf("int\n"); break;
        case NEW: printf ("new\n"); break;
        case PRINT: printf("print\n"); break;
        case PRIVATE: printf("private\n"); break;
        case PUBLIC: printf("public\n"); break;
        case READLN: printf("readln\n"); break;
        case RETURN: printf("return\n"); break;
        case STRUCT: printf("struct\n"); break;
        case SWITCH: printf("switch\n"); break;
        case THIS: printf("this\n"); break;
        case THROW: printf("throw\n"); break;
        case TRUE: printf("true\n"); break;
        case TRY: printf("try\n"); break;
        case TYPEDEF: printf("typedef\n"); break;
        case WHILE: printf("while\n"); break;
        case L_BRACKET: printf("L_BRACKET\n"); break;
        case R_BRACKET: printf("R_BRACKET\n"); break;
        case L_PARENTHESIS: printf("L_PARENTHESIS\n"); break;
        case R_PARENTHESIS: printf("R_PARENTHESIS\n"); break;
        case L_BRACE: printf("L_BRACE\n"); break;
        case R_BRACE: printf("R_BRACE\n"); break;
        case LESS_THAN: printf("LESS_THAN\n"); break;
        case LESS_EQUAL: printf("LESS_EQUAL\n"); break;
        case MORE_THAN: printf("MORE_THAN\n"); break;
        case MORE_EQUAL: printf("MORE_EQUAL\n"); break;
        case ASSIGNMENT: printf("ASSIGNMENT\n"); break;
        case EQUALS: printf("EQUALS\n"); break;
        case BIT_AND: printf("BIT_AND\n"); break;
        case LOGIC_AND: printf("LOGIC_AND\n"); break;
        case BIT_OR: printf("BIT_OR\n"); break;
        case LOGIC_OR: printf("LOGIC_OR\n"); break;
        case NOT: printf("NOT\n"); break;
        case NOT_EQUAL: printf("NOT_EQUAL\n"); break;
        case MINUS: printf("MINUS\n"); break;
        case ARROW: printf("ARROW\n"); break;
        case PLUS: printf("PLUS\n"); break;
        case SLASH: printf("SLASH\n"); break;
        case ASTERISK: printf("ASTERISK\n"); break;
        case PERCENT: printf("PERCENT\n"); break;
        case DOT: printf("DOT\n"); break;
        case COMMA: printf("COMMA\n"); break;
        case SEMICOLON: printf("SEMICOLON\n"); break;
        case COLON: printf("COLON\n"); break;
        case ID: printf("ID");
            printf(".");
            idTable.printEntry(tableKey);
            printf("\n");
            break;
        case LITERAL: printf("LITERAL");
            printf(".");
            literalTable.printEntry(tableKey);
            printf("\n");
            break;
        case NUMINT: printf("NUMINT");
            printf(".");
            intTable.printEntry(tableKey);
            printf("\n");
            break;
        case NUMFLOAT: printf("NUMFLOAT");
            printf(".");
            floatTable.printEntry(tableKey);
            printf("\n");
            break;
        case ASCII: printf("ASCII");
            printf(".");
            charTable.printEntry(tableKey);
            printf("\n");
            break;
        default:
            printf ( "\nstate:%d\n", tokenNumber);
            printErrorLexer(tokenNumber);
            break;
        }
}

int DFA(){
    int leavingFlag = 1;
    int reservedTest;
    endOfReading = 0;

    //tableKey = -1;
    strBufferSize = 1;
    strBufferPos = 0;
    state = 0;
    strBuffer = (char*)malloc (ID_BUFFER * strBufferSize * sizeof *strBuffer);
    int aux; //variavel para resolver imprevisto de ultimo hora, passagem do estado atual para o modulo de erros

    while (1){
        if(position==charactersRead && leavingFlag == 1){
            endOfReading = 1;
            return EOF_TOKEN;
        }
        switch (state){
            case 0:
                switch (feed[position]){
                    case ' ':
                        readNext(); break;
                    case '\r':
                        readNext(); break;
                    case '\t':
                        readNext(); break;
                    case '{':
                        state = 1; break;
                    case '}':
                        state = 2; break;
                    case '[':
                        state = 3; break;
                    case ']':
                        state = 4; break;
                    case '(':
                        state = 5; break;
                    case ')':
                        state = 6; break;
                    case '+':
                        state = 7; break;
                    case '%':
                        state = 8; break;
                    case ':':
                        state = 9; break;
                    case ';':
                        state = 10; break;
                    case '!':
                        state = 11; break;
                    case '=':
                        state = 14; break;
                    case '>':
                        state = 17; break;
                    case '<':
                        state = 20; break;
                    case '&':
                        state = 23; break;
                    case '|':
                        state = 26; break;
                    case '-':
                        state = 29; break;
                    case '\n':
                        state = 32; break;
                    case '*':
                        state = 33; break;
                    case '"':
                        state = 34; break;
                    case '/':
                        state = 40; break;
                    case '.':
                        state = 54; break;
                    case ',':
                        state = 57; break;
                    case '\'':
                        state = 58; break;
                    default:
                        if (isdigit(feed[position])){
                            state = 45;
                        } else if (isalpha(feed[position]) || feed[position] == '_' ){ //verificar comeco de identificadores
                            state = 38;
                        }
                        else state = 56;
                        break;
                }
                break;
            case 1:
                readNext(); return L_BRACE;
            case 2:
                readNext(); return R_BRACE;
            case 3:
                readNext(); return L_BRACKET;
            case 4:
                readNext(); return R_BRACKET;
            case 5:
                readNext(); return L_PARENTHESIS;
            case 6:
                readNext(); return R_PARENTHESIS;
            case 7:
                readNext(); return PLUS;
            case 8:
                readNext(); return PERCENT;
            case 9:
                readNext(); return COLON;
            case 10:
                readNext(); return SEMICOLON;
            case 11: // !
                readNext();
                if (feed[position]== '=')
                    state = 12;
                else
                    state = 13;
                break;
            case 12: // !=
                readNext(); return NOT_EQUAL;
            case 13: // !
                return NOT;
            case 14: // =
                readNext();
                if (feed[position]== '=')
                    state = 15;
                else
                    state = 16;
                break;
            case 15: // ==
                readNext(); return EQUALS;
            case 16: // =
                return ASSIGNMENT;
            case 17: // >
                readNext();
                if (feed[position]== '='){
                    state = 18;
                }
                else {
                    state = 19;
                }
                break;
            case 18: // >=
                readNext(); return MORE_EQUAL;
            case 19: // >
                return MORE_THAN;
            case 20: // <
                readNext();
                if (feed[position]== '='){
                    state = 21;
                }
                else {
                    state = 22;
                }
                break;
            case 21: // <=
                readNext(); return LESS_EQUAL;
            case 22: // <
                return LESS_THAN;
            case 23: // <
                readNext();
                if (feed[position]== '&'){
                    state = 24;
                }
                else {
                    state = 25;
                }
                break;
            case 24: // <=
                readNext(); return LOGIC_AND;
            case 25: // <
                return BIT_AND;
            case 26: // |
                readNext();
                if (feed[position]== '|'){
                    state = 27;
                }
                else {
                    state = 28;
                }
                break;
            case 27: // ||
                readNext(); return LOGIC_OR;
            case 28: // |
                return BIT_OR;
            case 29: // -
                readNext();
                if (feed[position]== '>'){
                    state = 30;
                }
                else {
                    state = 31;
                }
                break;
            case 30: // ->
                readNext(); return ARROW;
            case 31: // -
                return MINUS;
            case 32:
                addLines();
                readNext();
                state = 0;
                break;
            case 33:
                readNext(); return ASTERISK;
            case 34:
                readNext();
                if (feed[position] == '"'){
                    state = 35;
                    break;
                }
                else if (feed[position]== '\\'){
                    strBuffer = insertChar(strBuffer);
                    state = 37;
                    break;
                }
                else if (position==charactersRead){
                    leavingFlag = 0;
                    state = 36;
                    break;
                }
                else if (feed[position]== '\n'){
                        addLines();
                }
                strBuffer = insertChar(strBuffer);
                break;
            case 35:
                tableKey = literalTable.insertNewString(strBuffer, strBufferPos);
                readNext(); return LITERAL;
            case 36: //estado de erro, missing end quotation
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
            case 37:
                readNext();
                strBuffer = insertChar(strBuffer);
                state = 34;
                break;
            case 38: //identificador
                strBuffer = insertChar(strBuffer);
                readNext();
                if (isalpha(feed[position]) || feed[position] == '_' || isdigit(feed[position])){
                    break;
                }
                else{
                    state = 39;
                    break;
                }
            case 39:
                state = 0;
                //testa se é uma palavra reservada
                reservedTest = reservedTable.lookUp(strBuffer, strBufferPos);
                if (reservedTest != -1) return reservedTest;
                //testa se a palavra já foi inserida
                tableKey = idTable.insertNewString(strBuffer, strBufferPos);
                return ID;
            case 40:
                readNext();
                if (feed[position] == '*'){
                    state = 41;
                }
                else
                    state = 43;
                break;
            case 41:
                readNext();
                if (feed[position] == '*'){
                    state = 42;
                }
                else if (position==charactersRead){
                    leavingFlag = 0;
                    state = 44;
                }
                else if (feed[position]== '\n')
                        addLines();
                break;
            case 42:
                readNext();
                if (feed[position] == '/'){
                    readNext();
                    state = 0;
                }
                else if (position==charactersRead){
                    leavingFlag = 0;
                    state = 44;
                }
                break;
            case 43:
                return SLASH;
            case 44:
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
            case 45:
                strBuffer = insertChar(strBuffer);
                readNext();

                if(feed[position] == '.'){
                    state = 46;
                }
                else if(feed[position] == 'e' || feed[position] == 'E'){
                    state = 47;
                }
                else if (!isdigit(feed[position]))
                    state = 48;
                break;
            case 46:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(feed[position] == 'e' || feed[position] == 'E'){
                    state = 47;
                }
                else if (!isdigit(feed[position]))
                    state = 49;
                break;
            case 47:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(isdigit(feed[position])){
                    state = 50;
                }
                else if(feed[position] == '+' || feed[position] == '-'){
                    state = 51;
                }
                else
                    leavingFlag = 0;
                    state = 52;
                break;
            case 48:
                tableKey = intTable.insertNewString(strBuffer, strBufferPos);
                return NUMINT;
            case 49:
                tableKey = floatTable.insertNewString(strBuffer, strBufferPos);
                return NUMFLOAT;
            case 50:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(!isdigit(feed[position]))
                    state = 49;
                break;
            case 51:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(isdigit(feed[position]))
                    state = 53;
                else
                    state = 52;
                break;
            case 52:
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
            case 53:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(!isdigit(feed[position]))
                    state = 49;
                break;
            case 54:
                strBuffer = insertChar(strBuffer);
                readNext();
                if(isdigit(feed[position]))
                    state = 46;
                else
                    state = 55;
                break;
            case 55:
                return DOT;
            case 56:
                readNext();
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
            case 57:
                readNext(); return COMMA;
            case 58:
               // strBuffer = insertChar(strBuffer);
                readNext();
                if (isalpha(feed[position])){
                    state = 59;
                }
                else if (feed[position] == '\''){
                    state = 62;
                    break;
                }
                else if (feed[position]== '\\'){
                    state = 60;
                }
                else if (position==charactersRead){
                    leavingFlag = 0;
                    state = 61;
                }
                else
                    if (feed[position]== '\n')
                        addLines();
                strBuffer = insertChar(strBuffer);
                break;
            case 59:
                //tableKey = (int) feed[position];
                //printf ("table key ta valendo %d\n", tableKey);
                readNext();
                if (feed[position] == '\''){
                    state = 62;
                }
                else if (position==charactersRead){
                    leavingFlag = 0;
                    state = 61;
                }
                else { //se nao for apostrofo e nem EOF
                    if (feed[position]== '\n') //pode ser que seja quebra de linha
                        addLines();
                    if (feed[position]== '\t') //ou tabulacao
                        break;
                    else { //mas se nao for nenhum dos dois, excede o tamanho maximo 1 pra um caractere
                       state = 63;
                    }
                }
                //strBuffer = insertChar(strBuffer);
                break;
            case 60:
                if (position==charactersRead){
                    leavingFlag = 0;
                    state = 61;
                }
                else { state = 58;
                }
                break;
            case 61:
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
            case 62:
                tableKey = charTable.insertNewString(strBuffer, strBufferPos);
                readNext(); return ASCII;
            case 63:
                aux = state;
                resetDFA();
                return returnErrorLexer(aux);
        }
    }
}
