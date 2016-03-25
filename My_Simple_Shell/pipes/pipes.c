#include "pipes.h"
#include "../tokenize/makeArgs.h"
#include "../linkedlist/linkedList.h"

int containsPipe(char *s){
	const char * pipeChar = "|";
	int pipeCount = 0, i = 0;
	char * ret = strchr(s, *pipeChar);
	if(!ret) {

        return 0;
    }
	for(; i < strlen(s); i++){
		if(s[i] == *pipeChar)
        pipeCount++;
	}

        return pipeCount;
}
char ** parsePrePipe(char *s, int * preCount){
        const char * pipeChar = "|";
        const char * spaceChar = " ";
        char ** argv;
        int i = 1;
        size_t preChunk = strcspn(s,"|");
        //makes pointer to "|" in string, then checks for space before "|"
        char * pipeSpot = strchr(s, *pipeChar);
        while(preChunk != 0 && *(pipeSpot - i) == *spaceChar){
            preChunk--; //if space is found, one less byte will be allocated for copy string.
            i++;
        }



        char * copy = (char *)calloc((preChunk+1), sizeof(char));
        strncpy(copy, s, preChunk);


        *preCount = makeargs(copy, &argv);



        free(copy);
    if(*preCount == -1){ //to avoid empty garbage arguments
        return NULL;
    }
        return argv;
}
char ** parsePostPipe(char *s, int * postCount){
    const char * pipeChar = "|";
    const char * spaceChar = " ";
    char ** argv;
    int i = 1;
    //makes pointer to "|" in string, then checks for space after "|"
    char * pipeSpot = strchr(s, *pipeChar);
    size_t preChunk = strcspn(s,"|")+1;
    while(*(pipeSpot + i) == *spaceChar){ //&& *(pipeSpot+i) != '\0'){
        preChunk++;
        i++; //if space is found, one less byte will be allocated for copy string.
    }



    size_t postChunk = strlen(s)-preChunk;
    char * copy = (char *)calloc((postChunk+1), sizeof(char));
    strncpy(copy, s+preChunk, postChunk);


    *postCount = makeargs(copy, &argv);



    free(copy);
    if(*postCount == -1){ //to avoid empty garbage arguments
        return NULL;
    }
    return argv;
}
void pipeIt(char **prePipe, char **postPipe, LinkedList *histList, LinkedList *aliasList) {
        parseInput(&aliasList, &histList, &prePipe);
        parseInput(&aliasList, &histList, &prePipe);
    if(!prePipe || !postPipe){
        return;
    }

    pid_t pid1, pid2;
    int fd[2], res, status = 0;

    pid1 = fork();

    if(pid1 != 0){
        waitpid(pid1, &status, 0);//grand parent waits on children.
    }
    else {

        res = pipe(fd);

        if(res < 0){
            perror("Pipe Failure\n");
            exit(-1);
        }
        pid2 = fork();

        if (pid2 != 0) { //if child, execute second part of pipe.



                close(fd[1]);
                close(0);
                dup(fd[0]);
                close(fd[0]);
                status = checkForRedirect(postPipe, histList, aliasList);


            exit(status);

        }
        else { //if grand child, execute first part of pipe
            close(fd[0]);
            close(1);
            dup(fd[1]);
            close(fd[1]);

                status = checkForRedirect(prePipe, histList, aliasList);

            exit(status);
        }
    }


}

int checkForRedirect(char **argv, LinkedList *histList, LinkedList *aliasList) {
    int i = 0, k = 0, n = 0, fdout, fdin, lastInp = -2, lastOut = -2;
    char * fout = NULL, * fin = NULL;
    const char * directTo = ">";
    const char * directFrom = "<";


    while(argv[i] != NULL){ //find the last instance of the write to file operator

        if(strchr(argv[i], *directTo) != NULL){
            fout = strchr(argv[i], *directTo) +1 ;
            lastOut = i;
        }

        if(strchr(argv[i], *directFrom) != NULL) {
            fin = strchr(argv[i], *directTo) + 1;
            lastInp = i;
        }

        if(strcmp(argv[i], ">") == 0 && argv[i+1] != NULL){ //could pass in the number of args to make the search faster
           fout = argv[i+1];
            lastOut = i;

        }
        if(strcmp(argv[i], "<") == 0 && argv[i+1] != NULL){
            fin = argv[i+1];
            lastInp = i;

        }


        i++;
    }

        if(fout != NULL){
           if(strcmp(fout, "&1") == 0)
                fout = "/dev/stdout";
            int fdout = open(fout, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP  | S_IWUSR | S_IWGRP);
            if(fdout != -1){
                dup2(fdout, 1); //replace stdout with fdout's file descriptor
            }
        }
        if(fin != NULL){
            if(strcmp(fin, "&0") == 0)
                fin = "/dev/stdin";
            int fdin = open(fin, O_RDONLY);
            if(fdin != -1){
                dup2(fdin, 0);
            }
        }

        for(n= 0, k = 0; argv[k] != NULL;){
            if(k == lastOut || k ==lastOut+1 || k == lastInp || k == lastInp +1)
                k++;
            else{
                k++, n++;
            }
        }
    char ** altArgv = (char **)calloc(n+1,sizeof(char*));
    for(n= 0, k = 0; argv[k] != NULL;){
        if(k == lastOut || k ==lastOut+1 || k == lastInp || k == lastInp +1)
            k++;
        else{
            altArgv[n] = (char *)calloc(strlen(argv[k])+1,sizeof(char));
            strcpy(altArgv[n],argv[k]);
            k++, n++;
        }
    }
        //close(fdout);
        //close(fdin );
        if(strcmp(argv[0], "history") == 0) {

            printListToFile(histList, stdout, atol(getenv("HISTCOUNT")), printHistToFileNum);
            return 0;
        }
        else if(strcmp(argv[0], "alias") == 0 && altArgv[1] == NULL){

            printListToFile(aliasList, stdout, 0, printAliasToFile);
            return 0;
         }
        else{
            execvp(altArgv[0], altArgv);
            clean(i, altArgv);
            return -1;
        }
}




    /*close(fd[0]);
    close(1);
    dup(fd[1]);
    close(fd[1]);
    execvp(argv[0], argv);*/


