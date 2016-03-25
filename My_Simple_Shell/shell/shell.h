#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#include "../utils/myUtils.h"
#include "../linkedlist/listUtils.h"
#include "../alias/alias.h"
#include "../history/history.h"
#include "../process/process.h"
#include "../tokenize/makeArgs.h"

FILE *openShellFiles(int *success, int mode, char *filename);
void sillyInit(LinkedList **aliasList, LinkedList **histList, char **pathVarName);
void initFromRCFile(FILE * rcFile, LinkedList **aliasList, LinkedList **histList, char **pathVarName);
char * parsePath(char * line);
char * assignPath(char * s);
void changeDirect(char * path);
void alterArgs(LinkedList *aliasList, LinkedList *histList, char *** argv);
void writeToHistFile(LinkedList *histList, char *histLocale);
int checkArgs(char * comparator, char ** argv);
void parseInput(LinkedList ** aliasList, LinkedList ** histlist, char *** argv);
void modAlias(LinkedList **aliasList, char *parsable, int mode);
int checkArgsContents(char * content, char ** argv);
void histReRun(LinkedList **histlist, char *trigger, LinkedList *aliasList);
history * histListCrawler(LinkedList * histList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *));
#endif
