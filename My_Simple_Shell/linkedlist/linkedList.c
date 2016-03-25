
#include "linkedList.h"

LinkedList * linkedList(){
	LinkedList * thelist = (LinkedList *)calloc(1,sizeof(LinkedList));
	thelist->head = (Node *)calloc(1,sizeof(Node));
	return thelist;
}



void addLast(LinkedList * theList, Node * nn){
	if(theList == NULL)
		exit(-99);
	if(nn == NULL)
		exit(-99);

	Node * curr = theList->head;
	while(curr->next != NULL){
		curr = curr->next;	
	}

	curr->next = nn;
	nn->prev = curr;
	theList->size++;

}


void addFirst(LinkedList * theList, Node * nn){//Check logical flow
	if(theList == NULL || nn == NULL)
		exit(-99);

	if(theList->size > 0){
		theList->head->next->prev = nn;
	}
		nn->next = theList->head->next;
		nn->prev = theList->head;
		theList->head->next = nn;
		theList->size++;
}



void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *)){

	if(theList == NULL || nn == NULL)
		exit(-99);

	Node * curr = theList->head->next;
	Node * temp;
	while(curr != NULL && compare(curr->data,nn->data) != 0){
		curr = curr->next;
	}

	if(curr != NULL){
		curr->prev->next = curr->next;
		
			if(curr->next != NULL)
				curr->next->prev = curr->prev;
				
		curr->prev = NULL;
		removeData(curr->data);
		theList->size--;
		free(curr);	
		}
	removeData(nn->data);
	free(nn);
	

}



void clearList(LinkedList * theList, void (*removeData)(void *)){

	if(theList != NULL){
		Node * temp;
		Node * curr = theList->head->next;
		while(curr != NULL){
			temp = curr;
			curr = curr->next;
			removeData(temp->data);
			free(temp);	
		}
		free(theList->head);
	}
	
}



void printList(const LinkedList * theList, void (*convertData)(void *)){
	if(theList != NULL){
		Node * curr = theList->head->next;
		while( curr != NULL){
			convertData(curr->data);
			printf("\n");
			curr = curr->next;		
		}
	}
}

void printListToFile(LinkedList *theList, FILE *fout, long mode, void (*filePrint)(void *, FILE *)){

    if(mode == 0) {


        if (theList != NULL) {
            Node *curr = theList->head->next;
            while (curr != NULL) {
                filePrint(curr->data, fout);
                curr = curr->next;
            }
        }
    }
    else if (mode > 0){
        int i = 0;

        if (theList != NULL && theList->head->next != NULL) {
            Node *curr = theList->head->next;
            while (curr->next != NULL && i < mode) {
                curr = curr->next;
                i++;
            }
            while( curr != theList->head && i >= 0){
                filePrint(curr->data, fout);
                curr = curr->prev;
                i--;
            }
        }
    }

}


