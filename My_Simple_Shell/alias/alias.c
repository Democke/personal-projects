#include "alias.h"

void * buildType_Str(char * argument){
    Alias * change = (Alias *)calloc(1,sizeof(Alias));
    char * s;

    s = strtok(argument, "=\"");
    change->changeFrom = (char *)calloc(strlen(s)+1, sizeof(char));
    strcpy(change->changeFrom, s);

    s = strtok(NULL, "=\"");
    change->changeTo = (char *)calloc(strlen(s)+1, sizeof(char));
    strcpy(change->changeTo, s);

    return change;
}

void printAlias(void * passedIn){
    Alias * printable = (Alias *)passedIn;


        printf("Alias: %s='%s' \n", printable->changeFrom, printable->changeTo);
}




int compareAlias(const void * p1, const void * p2){
    Alias * alias1 = (Alias *) p1;
    Alias * alias2 = (Alias *)p2;

    return strcmp(alias1->changeFrom, alias2->changeFrom);
}

void cleanAlias(void * passedIn){

    Alias * cleanable = (Alias *)passedIn;
    if(cleanable->changeFrom != NULL){
        free(cleanable->changeFrom);
        free(cleanable->changeTo);

    }
    free(cleanable);

}

void printAliasToFile(void *convert, FILE *fout){
    Alias * entry = (Alias *) convert;
    fprintf(fout, "alias %s=%s\n", entry->changeFrom,entry->changeTo);
}