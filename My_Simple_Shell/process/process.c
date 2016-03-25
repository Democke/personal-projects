#include "process.h"

/*void forkIt(char ** argv){
	int  status = 0;
	pid_t pid = fork();

	if(pid == 0){
		
		status = execvp(argv[0], argv);
		exit(status);

	}
	else{
		waitpid(pid, &status, 0);
		
	}
 
}*/
void forkIt(char **argv, LinkedList *histList, LinkedList *aliasList) {
	int  status = 0;
	pid_t pid = fork();

	if(pid == 0){

		status = checkForRedirect(argv, histList, aliasList);
		exit(status);

	}
	else{
		waitpid(pid, &status, 0);

	}

}


