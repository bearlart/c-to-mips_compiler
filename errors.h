
///erros
#define ERROR_MISSING_END_QUOTE 101
#define ERROR_MISSING_END_COMMENT 102
#define ERROR_NO_EXPONENT 103
#define ERROR_INVALID_CHARACTER 104
#define ERROR_EXCEEDS_CHAR_SIZE 105
#define ERROR_MISSING_END_APOSTROPHE 106

#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

int returnErrorLexer(int state);
int printErrorLexer(int state);
void parserError(int tokenExpected);

#endif // ERRORS_H_INCLUDED
