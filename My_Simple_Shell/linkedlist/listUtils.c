/**
 * @file listUtils.c
 * @author Kyle Hermens
 * @date January 4th, 2015
 * @brief Supporting functions for the basic linked list
 *
 * The purpose of this file is to outline functions to help build a basic
 * doubly linked list.  The presumption is the information will be read
 * from a file.  A node of the specific data will be built and be added
 * to the list usually by calling the addFirst method.
 *
*/




#include "listUtils.h"


Node * buildNode(FILE * fin, void *(*buildData)(FILE * in) ){
	Node * nn = (Node *)calloc(1,sizeof(Node));
	nn->data = buildData(fin);
	return nn;
}

Node * buildNode_Type(void * passedIn){
	Node * nn = (Node *)calloc(1,sizeof(Node));
	nn->data = passedIn;
	return nn;
	
}

void sort(LinkedList * theList, int (*compare)(const void *, const void *)){
	if(theList == NULL)
		exit(-99);
	if(theList->size > 1){
		Node * smallest, * start, * curr;
		void * temp;
		for(start = theList->head->next; start->next != NULL; start = start->next){
			smallest = start;
			for(curr = start->next; curr != NULL; curr = curr->next){
				if(compare(curr->data,smallest->data) < 0){
					smallest = curr;
				}
			}	
			temp = smallest->data;
			smallest->data = start->data;
			start->data = temp;
		}
	}
}

void buildList(LinkedList * myList, int total, FILE * fin, void * (*buildData)(FILE * in)){

	if(myList == NULL || total < 1)
		exit(-99);

	int i;
	for(i = 0; i < total; i++){
		addFirst(myList, buildNode(fin, buildData));	
	}


}


