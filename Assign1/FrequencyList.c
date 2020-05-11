// FrequencyList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "FrequencyList.h"

// data structures representing FrequencyList

static FrequencyListNode *newFrequencyListNode(char *it);
static void freeFrequencyListNode(FrequencyListNode *node);

//From COMP2521 LAB 4
/** Create a new, empty FrequencyList. */
FrequencyList newFrequencyList (void)
{
	FrequencyListRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate FrequencyList");
	new->first = new->last = NULL;
	new->nitems = 0;
	return new;
}

//From COMP2521 LAB 4
/** Release all resources associated with a FrequencyList. */
void freeFrequencyList (FrequencyList L)
{
	if (L == NULL) return;

	FrequencyListNode *curr = L->first;
	while (curr != NULL) {
		FrequencyListNode *next = curr->next;
		freeFrequencyListNode (curr);
		curr = next;
	}
	free (L);
}

//From COMP2521 LAB 4
/** Create a new FrequencyListNode (private function) */
static FrequencyListNode *newFrequencyListNode (char *it)
{
	FrequencyListNode *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate FrequencyList node");
	new->value = malloc(sizeof(char) *100);
	strcpy(new->value, it);
	new->prev = new->next = NULL;
	new->freq = 1;
	return new;
}

//From COMP2521 LAB 4
/** Release a FrequencyListNode (private function) */
static void freeFrequencyListNode (FrequencyListNode *node)
{
	if (node == NULL) return;
	free (node->value);
	free (node);
}

/** insert an item after current item
 * new item becomes current item */
void FrequencyListInsert (FrequencyList L, char *it)
{
	assert (L != NULL);
	
    FrequencyListNode *curr = L->first;
    while (curr != NULL) {
        if (strcmp(curr->value, it) == 0) {
            curr->freq++;
            return;
        }
        curr = curr->next;
    }
	/// COMPLETE THIS FUNCTION
	FrequencyListNode *n = newFrequencyListNode(it);

    L->nitems++;

    // for an empty list
	if (L->first == NULL) {
	    L->first = n;
	    L->last = n;
	    return;
	}
    

    L->last->next = n;
    n->prev = L->last;
    L->last = n;

    return;

}

/** return number of elements in a list */
int FrequencyListLength (FrequencyList L)
{
	return L->nitems;
}

    
