#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../pipes/pipes.h"
void forkIt(char **argv, LinkedList *histList, LinkedList *aliasList);

#endif
