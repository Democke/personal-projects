#ifndef PIPES_H
#define PIPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../linkedlist/linkedList.h"
#include "../history/history.h"
#include "../alias/alias.h"
#include "../shell/shell.h"

int containsPipe(char *s);
char ** parsePrePipe(char *s, int * preCount);
char ** parsePostPipe(char *s, int * postCount);
void pipeIt(char **prePipe, char **postPipe, LinkedList *histList, LinkedList *aliasList);
int checkForRedirect(char **argv, LinkedList *histList, LinkedList *aliasList);

#endif 

