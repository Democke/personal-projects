#include "makeArgs.h"
//Kyle Hermens
void clean(int argc, char **argv)
{
	if(argc < 0)
		return;
	if(argv != NULL){
		int i = 0;
		for(; i < argc+1; i++){
			free(argv[i]);		
		}
		free(argv);

	}



}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	int num = 0, i = 0;
	char * safety1, * safety2, * token;
	if(strlen(s) != 0){
		//create copies of s to tokenize
		char * clone1 = (char *)calloc(strlen(s)+1,sizeof(char));
		strcpy(clone1, s);
		char * clone2 = (char *)calloc(strlen(s)+1,sizeof(char));
		strcpy(clone2, s);

		//count the number of arguments
		token = strtok_r(clone1, " \t\n", &safety1);
		while(token != NULL){
			
			num++;
			token = strtok_r(NULL, " \t\n", &safety1);
			
		}
		//allocate those arguments
		*argv = (char **)calloc(num+1, sizeof(char *));
		token = strtok_r(clone2, " \t\n", &safety2);
		while(token != NULL){
			
			(*argv)[i]= (char *)calloc(strlen(token)+1, sizeof(char));
			strcpy((*argv)[i], token);
			token = strtok_r(NULL, " \t\n", &safety2);
			i++;
		}
		
		free(clone1);
		free(clone2);
		if(num > 0)//prevents inputs only delimiters
		return num;
	}
	
   return -1;

}// end makeArgs
