// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008

#ifndef INTLIST_H
#define INTLIST_H

#include <stdbool.h>
#include <stdio.h>

/** External view of IntList ... implementation in IntList.c */

// FROM 2521 LAB 4
typedef struct FrequencyListNode {
	char *value;        /**< value of this list item (string) */
	double freq;         
	struct FrequencyListNode *prev;
	                    /**< pointer to previous node in list */
	struct FrequencyListNode *next;
	                    /**< pointer to next node in list */
} FrequencyListNode;

typedef struct FrequencyListRep {
	size_t nitems;      /**< count of items in list */
	FrequencyListNode *first;  /**< first node in list */
	FrequencyListNode *last;   /**< last node in list */
} FrequencyListRep;

typedef struct FrequencyListRep *FrequencyList;

/** Create a new, empty IntList. */
FrequencyList newFrequencyList (void);

/** Release all resources associated with an IntList. */
void freeFrequencyList (FrequencyList);

/** Insert an integer into correct place in a sorted IntList. */
void FrequencyListInsert (FrequencyList, char*);

/** Return number of elements in an IntList. */
int FrequencyListLength (FrequencyList);


#endif 
