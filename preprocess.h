/*
 * API: preprocessor(FILE *source, FILE *target)
 * open source in readmode and target in writemode and pass as parameters
 * close files after function call.
 * 
 * Call freeAll() to free all the memory used by preprocessor();
 * 
 * The other functions are helper functions for preprocessor()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertMacro(char *macro);
int isIncluded(char *macro);
int stringMatchN(char *line, char *key, int len);
void concat(char *a, char *b);
char *isPreprocessor(char *line);
char *getMacro(char *line);
char *readLine(FILE *source, int bufferSize);
void writeLine(FILE *target, char *line) ;
void preprocessor(FILE *source, FILE *target);
void freeAll();
