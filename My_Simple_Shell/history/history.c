#include "history.h"

/*int makeargs(char *s, char *** argv){

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
}*/

void * buildHistItem(int lineNum, char *line){
	history * story = (history *)calloc(1,sizeof(history));

	story->command = (char *)calloc(strlen(line)+1, sizeof(char));
    strcpy(story->command, line);
	story->lineNum = lineNum;

	return story;
}

void printType(void * passedIn){
	history * printable = (history *)passedIn;
	

		printf("%d %s\n", printable->lineNum, printable->command);

}

void * buildType(FILE * fin){
	return fin;
}


void * buildType_Prompt(FILE * fin){
	return fin;
}

int compareHistItem(const void *p1, const void *p2){
	history * hist1 = (history *)p1;
    history * hist2 = (history *)p2;
    return hist1->lineNum - hist2->lineNum;
    //return strcmp(hist1->command, hist2->command);
}

void cleanHistItem(void *passedIn){

	history * cleanable = (history *)passedIn;
	if(cleanable->command != NULL){
		free(cleanable->command);

	}
	free(cleanable);

}

void printHistToFileNum(void *convert, FILE *fout){
    history * entry = (history * ) convert;
    fprintf(fout, "%d %s\n", entry->lineNum, entry->command);

}

void printHistToFileLine(void *convert, FILE *fout){
    history * entry = (history * ) convert;
    fprintf(fout, "%s\n", entry->command);

}


