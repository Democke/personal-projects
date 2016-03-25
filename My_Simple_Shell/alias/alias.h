#ifndef ALIAS_H
#define ALIAS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct alias{
    char * changeFrom;
    char * changeTo;
};
typedef struct alias Alias;

void cleanAlias(void * passedIn);

void * buildType_Str(char * argument);

void printAlias(void * passedIn);

int compareAlias(const void * p1, const void * p2);
void printAliasToFile(void *convert, FILE *fout);
#endif
