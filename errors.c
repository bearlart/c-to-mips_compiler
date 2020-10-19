#include "errors.h"
#include "analex.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int returnErrorLexer(int state){
    switch (state){
        case 44:
            return ERROR_MISSING_END_COMMENT;
        case 52:
            return ERROR_NO_EXPONENT;
        case 36:
            return ERROR_MISSING_END_QUOTE;
        case 56:
            return ERROR_INVALID_CHARACTER;
        case 61:
            return ERROR_MISSING_END_APOSTROPHE;
        case 63:
            return ERROR_EXCEEDS_CHAR_SIZE;
        default:
            return -1;
    }
    return -1;
}

int printErrorLexer(int state){
    int i;
    switch (state){
        case ERROR_MISSING_END_QUOTE:
            fprintf(stderr, "\nERROR_MISSING_END_QUOTE (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        case ERROR_MISSING_END_COMMENT:
            fprintf(stderr, "\nERROR_MISSING_END_COMMENT (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        case ERROR_NO_EXPONENT:
            fprintf(stderr, "\nERROR_NO_EXPONENT (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        case ERROR_INVALID_CHARACTER:
            fprintf(stderr, "\nERROR_INVALID_CHARACTER (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        case ERROR_EXCEEDS_CHAR_SIZE:
            fprintf(stderr, "\nERROR_EXCEEDS_CHAR_SIZE (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        case ERROR_MISSING_END_APOSTROPHE:
            fprintf(stderr, "\nERROR_MISSING_END_APOSTROPHE (AT [%d, %d])", lines, columns-1);
            fprintf(stderr, ": ");
            for (i = 0; i< strBufferPos; i++){
                fprintf(stderr, "%c", strBuffer[i]);
            }
            fprintf(stderr, "\n");
            break;
        default:
            return -1;
    }
    return -1;
}

void parserError(int tokenExpected){
    fprintf (stderr, "\nLine %d Column %d: syntactical error. ", lines, columns);
    fprintf (stderr, "Found: ");
    printTokenNameSTDERR(token);
    fprintf (stderr, " Expected: ");
    printTokenNameSTDERR(tokenExpected);
//    switch (tokenExpected){
//        case INT: case FLOAT: case CHAR: case ID: case BOOL:
//            fprintf (stderr, "INT or FLOAT or CHAR or ID or BOOL ");
//            break;
//        default:
//            printTokenNameSTDERR(tokenExpected);
//            break;
//    }
    fprintf (stderr, ".\n");
}
