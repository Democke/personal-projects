/**
 * @file genericData.h
 * @author Stu Steiner
 * @date 29 Dec 2015
 * @brief The basic genericData.h file contains the prototypes for your specific type functions
 *
 * The genericData.h specifies the standard set of functions required for any type to
 * work with your generic linked list.
 *
 * @note This file will never be changed
 */

#ifndef GENERICDATA_H
#define GENERICDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void printType(void * passedIn);




void * buildType(FILE * fin);


void * buildType_Prompt(FILE * fin);


int compareHistItem(const void *p1, const void *p2);


void cleanHistItem(void *passedIn);


#endif // GENERICDATA_H
