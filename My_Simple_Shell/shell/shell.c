#include "shell.h"


FILE *openShellFiles(int *success, int mode, char *filename) {
    FILE * shellFile = NULL;
    if(mode == 0) {

        shellFile = fopen(filename, "r");
    }
    else if(mode == 1) {
        shellFile = fopen(filename, "w+");
    }
    else if(mode == 2){
        shellFile = fopen(filename, "a");
    }

    if(shellFile == NULL){
        *success = -1;
        printf("The file %s failed to open because: %s\n",filename, strerror(errno));
        return shellFile;
    }

    *success = 1;
    return shellFile;

}

void sillyInit(LinkedList **aliasList, LinkedList **histList, char **pathVarName) {
    int rcsuccess = 0;
    int histsuccess = 0;
    FILE * rcFile = openShellFiles(&rcsuccess, 0, ".msshrc");
    FILE * histFile = openShellFiles(&histsuccess, 0, ".msshrc_history");

    *aliasList = linkedList();
    *histList = linkedList();
    if(rcFile != NULL){

        initFromRCFile(rcFile, aliasList, histList, pathVarName);
        fclose(rcFile);
    }
    else{

       setenv("HISTCOUNT","100", 1);
        setenv("HISTFILECOUNT", "1000", 1);
    }

    //update history struct here

    if(histFile != NULL){
        char  histStr[MAX], inclusion[MAX];
        int i = 0;
        while(fgets(histStr,MAX, histFile) != NULL){
            strip(histStr);
            addFirst(*histList, buildNode_Type(buildHistItem(i + 1, histStr)));
            i++;
        }

        fclose(histFile);
    }
}

void initFromRCFile(FILE * rcFile, LinkedList **aliasList, LinkedList **histList, char **pathVarName){
         char s[MAX] = {0};
        char **argv = NULL;
        int argc = 0;

        fgets(s, MAX, rcFile);
        strip(s);
        char * token1 = strtok(s, "=");
        char * token2 = strtok(NULL, "=");
        setenv(token1,token2, 1);

        fgets(s, MAX, rcFile);
        strip(s);
        char * token3 = strtok(s, "=");
        char * token4 = strtok(NULL, "=");
        setenv(token3, token4, 1);


        while(fgets(s, MAX, rcFile) != NULL){
            //if contains alias, add Node to alias List
                if(strstr(s, "alias") != NULL){
                    strip(s);
                    const char * spaceChar = " ";
                    char * spacespot = strchr(s,*spaceChar) + 1;
                    addLast(*aliasList, buildNode_Type(buildType_Str(spacespot)));
                }
                else if(strstr(s, "PATH") != NULL){
                strip(s);
                assignPath(s);
            }

        }

}

char * assignPath(char * s){
    char * retVal = NULL;
    char * copy = strdup(s);
    char * name = strtok(copy, "=");
    char * value = strtok(NULL, "=");
    if(value != NULL && strstr(value, "$PATH") != NULL){
        parsePath(value);

    }
    else {
        if(value != NULL) {
            setenv(name, value, 1);
        }
        else {
            setenv(name,"",1);
        }
    }
    free(copy);
    return retVal;
}



char * parsePath(char * line) {
    const char *colonChar = ":";

    if (strstr(line, "$PATH")) {
        char s[500] = {0};
        strcpy(s, getenv("PATH"));
        size_t concatLength = strlen(s) + 1;

        char *token1 = strtok(line, ":");
        char *token2 = strtok(NULL, ":");
        char *token3 = strtok(NULL, ":");


        if (token1 != NULL && token3 != NULL) {
            concatLength += strlen(token1)+1;
            concatLength += strlen(token3)+1;

        }
        else if (token1 != NULL && strcmp(token1, "$PATH") == 0) {
            concatLength += strlen(token2)+1;
        }
        else{
            concatLength += strlen(token1);
        }

        char *retVal = (char *) calloc(concatLength, sizeof(char));
        if (token1 != NULL && token3 != NULL) {
            strcpy(retVal, token1);
            strcat(retVal, ":");
            strcat(retVal, getenv("PATH"));
            strcat(retVal, token3);

        }
        else if (token2 != NULL) {

            if (strcmp(token1, "$PATH") == 0) {
                strcpy(retVal, getenv("PATH"));
                strcat(retVal, token2);
            }
            else {
                strcpy(retVal, token1);
                strcat(retVal,":");
                strcat(retVal, getenv("PATH"));
            }
        }
        else {
            strcpy(retVal, getenv("PATH"));
        }
        setenv("PATH", retVal, 1);

        free(retVal);

        return retVal;
    }

    return NULL;

}

void changeDirect(char * path){
    strip(path);
    char ** argv = NULL;
    int argc = 0;
    argc = makeargs(path,&argv);
    int result = chdir(path);
    if(result == -1){
        printf("cd failed. Error: %s", strerror(errno));
    }
    setenv("PWD",path, 1);
    clean(argc,argv);


}

void alterArgs(LinkedList *aliasList, LinkedList *histList, char *** argv){

            if(aliasList != NULL && aliasList->head->next != NULL) {

                int i = 0;
                for (i = 0 ; (*argv)[i] != NULL; i++) {
                        Node * aliascurr =  aliasList->head->next;
                        Alias * checkable = (Alias *) (aliascurr->data);

                    for(; aliascurr != NULL  ;aliascurr = aliascurr->next);{
                        //Alias * checkable = (Alias *) aliascurr->data;
                        if(strcmp((*argv)[i], checkable->changeFrom) == 0){
                            free((*argv)[i]);
                            (*argv)[i] = (char *)calloc(strlen(checkable->changeTo)+1, sizeof(char));
                            strcpy((*argv)[i], checkable->changeTo);
                        }
                    }
                }
            }

        }



void writeToHistFile(LinkedList *histList, char *histLocale) {
    char * tempPath = (char *)calloc(strlen(histLocale)+strlen("/.msshrc_history")+1,sizeof(char));
    strcpy(tempPath, histLocale);
    strcat(tempPath, "/.msshrc_history");
    int histsuccess;
    FILE * histFile = openShellFiles(&histsuccess, 1, tempPath);
    long histBound = atol(getenv("HISTFILECOUNT"));

    printListToFile(histList, histFile, histBound, printHistToFileLine);
    fclose(histFile);
    free(tempPath);
}

void parseInput(LinkedList ** aliasList, LinkedList ** histlist, char *** argv){
    int spot = -1;
        if( *aliasList != NULL){
            spot = checkArgs("alias", *argv);
            if(spot != -1 && (*argv)[spot+1] != NULL)
                modAlias(aliasList, (*argv)[spot + 1], 0);

            spot = checkArgs("unalias", *argv);
            if(spot != -1 && (*argv)[spot+1] != NULL)
                modAlias(aliasList, (*argv)[spot +1], 1);

        }
    alterArgs(*aliasList, *histlist, argv);

        spot = checkArgs("cd", *argv);
        if(spot != -1 && (*argv)[spot+1] != NULL) {

            changeDirect((*argv)[spot +1]);
         }
        spot = checkArgsContents("PATH", *argv);
        if(spot != -1){
            assignPath((*argv)[spot]);
        }
        spot = checkArgsContents("!", *argv);
        if(spot != -1){
            histReRun(histlist, (*argv)[spot], *aliasList);
        }
}

void histReRun(LinkedList **histlist, char *trigger, LinkedList *aliasList) {
    int pipeCount, preCount, postCount, argc;
    char **prePipe, **postPipe, **argv;
    char *retCommand;
    const char * exclamChar = "!";
    if ((*histlist)->head->next->next != NULL) {
        if (strcmp(trigger, "!!") == 0) {

            history *story = (history *) (*histlist)->head->next->next->data;
            retCommand = story->command;

        }
        else if(strchr(trigger, *exclamChar) != NULL){
          char * pastExclam =  strchr(trigger, *exclamChar) +1;
            int comnum = atoi(pastExclam);
            if(comnum > 0 && comnum < atoi(getenv("HISTCOUNT"))){
               history * story = buildHistItem(comnum, "junk");
               history * retstory = histListCrawler(*histlist, buildNode_Type(story), cleanHistItem, compareHistItem);
                retCommand = retstory->command;
            }

        }

        pipeCount = containsPipe(retCommand);
        if (pipeCount > 0) {
            prePipe = parsePrePipe(retCommand, &preCount);
            postPipe = parsePostPipe(retCommand, &postCount);
            pipeIt(prePipe, postPipe, *histlist, NULL);
            clean(preCount, prePipe);
            clean(postCount, postPipe);
        }// end if pipeCount

        else {
            argc = makeargs(retCommand, &argv);
            parseInput(&aliasList, histlist, &argv);
            if (argc != -1)
                forkIt(argv, *histlist, aliasList);
            clean(argc, argv);
            argv = NULL;
        }
    }
}

history * histListCrawler(LinkedList * histList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *)){


    Node * curr = histList->head->next;
    Node * temp;
    while(curr != NULL && compare(curr->data,nn->data) != 0){
        curr = curr->next;
    }

    removeData(nn->data);
    free(nn);
    return curr->data;
}

/*void modAlias(LinkedList **aliasList, char *parsable, int mode) {
        const char * spaceChar = " ";
        char * safe1, * safe2, *safe3;
        char * copy1 = strdup(parsable);
        char * copy2 = strdup(parsable);
        char * copy3 = strdup(parsable);
        int i = 7;


        if(strstr(parsable, "=") != NULL && strcmp(parsable, "=") != 0){
            char * token1 = strtok_r(copy1, "=\"", &safe1);
            char * token2 = strtok_r(NULL, "=\"", &safe1);
            char * token3 = strtok_r(NULL, "=\"", &safe1);
            if(strstr(token1,"alias") != NULL && token2 != NULL){
                char * spaceStart = strstr(copy2, "unalias");
                if(spaceStart == NULL) {
                    spaceStart = strstr(copy2, "alias");
                    i -= 2;
                }
                while(spaceStart[i] == *spaceChar){
                    i++;
                }
                removeItem(*aliasList, buildNode_Type(buildType_Str(copy2+i)),cleanAlias, compareAlias);
                if(mode == 0)
                addLast(*aliasList, buildNode_Type(buildType_Str(copy3+i)));
            }
        }

        free(copy1);
        free(copy2);
        free(copy3);
}*/

int checkArgs(char * comparator, char ** argv){
    if(argv != NULL){
        int i;
        for(i = 0; argv[i] != NULL; i++){
            if(strcmp(comparator,argv[i]) == 0){
                return i;
            }
        }
    }
    return -1;
}

int checkArgsContents(char * content, char ** argv){
    if(argv != NULL){
        int i;
        for(i = 0; argv[i] != NULL; i++){
            if(strstr(argv[i], content) != NULL){
                return i;
            }
        }
    }
    return -1;
}

void modAlias(LinkedList **aliasList, char *parsable, int mode) {
    char * safe1, * safe2;
    char * copy1 = strdup(parsable);
    char * copy2 = strdup(parsable);
    char * copy3 = strdup(parsable);
    if(strstr(parsable, "=") != NULL && strcmp(parsable, "=") != 0){
        char * token1 = strtok_r(copy1, "=\"", &safe1);
        char * token2 = strtok_r(NULL, "=\"", &safe1);
        if(token2 != NULL){
            removeItem(*aliasList, buildNode_Type(buildType_Str(copy2)),cleanAlias, compareAlias);
            if(mode == 0)
                addLast(*aliasList, buildNode_Type(buildType_Str(copy3)));
        }
    }

    free(copy1);
    free(copy2);
    free(copy3);
}