



#include "./tokenize/makeArgs.h"
#include "./shell/shell.h"



int main()
{
    int argc, pipeCount;
    char **argv = NULL, s[MAX], * cdir = NULL;
    int preCount = 0, postCount = 0;
    char ** prePipe = NULL, ** postPipe = NULL;
    LinkedList * aliasList = NULL, * histlist = NULL;
    cdir = getcwd(cdir, 0);
    char * pathVarName;
    history *temp = NULL;

    sillyInit(&aliasList, &histlist, &pathVarName);


    printf("command?: ");
    fgets(s, MAX, stdin);
    strip(s);


    while(strcmp(s, "exit") != 0)
    {

        if(histlist->head->next != NULL)
            temp = (history *) histlist->head->next->data;
        else{
            addFirst(histlist, buildNode_Type(buildHistItem(1, s)));
        }

        if(temp != NULL && strcmp(s, temp->command) != 0){
            addFirst(histlist, buildNode_Type(buildHistItem(temp->lineNum + 1, s)));
        }


        pipeCount = containsPipe(s);
        if(pipeCount > 0)
        {
            prePipe = parsePrePipe(s, &preCount);
            postPipe = parsePostPipe(s, &postCount);
            parseInput(&aliasList, &histlist, &prePipe);
            parseInput(&aliasList, &histlist, &prePipe);
            pipeIt(prePipe, postPipe, histlist, aliasList);
            clean(preCount, prePipe);
            clean(postCount, postPipe);
        }// end if pipeCount

        else
        {
            argc = makeargs(s, &argv);
            parseInput(&aliasList, &histlist, &argv);

            if(argc != -1)
                forkIt(argv, histlist, aliasList);
                //checkForRedirect(argv, histlist, aliasList);
            clean(argc, argv);
            argv = NULL;
        }

        printf("command?: ");
        fgets(s, MAX, stdin);
        strip(s);

    }// end while
    writeToHistFile(histlist, cdir);
    free(cdir);
    clearList(aliasList, cleanAlias);
    free(aliasList);
    clearList(histlist, cleanHistItem);
    free(histlist);


    return 0;

}// end main