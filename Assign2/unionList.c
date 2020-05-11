#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "unionList.h"

static struct UnionNode *newUnionListNode (char *v);

/** Create a new, empty List. */
UnionList newUnionList (void)
{
	struct UnionListRep *L = malloc (sizeof *L);
	if (L == NULL) err (EX_OSERR, "couldn't allocate List");
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

/** Release all resources associated with an List. */
void freeUnionList (UnionList L)
{
	if (L == NULL) return;

	for (struct UnionNode *curr = L->first, *next;
		 curr != NULL; curr = next) {
		next = curr->next;
		free(curr->url);
		free (curr);
	}

	free (L);
}

/** create a new ListNode with value v
 * (this function is local to this ADT) */
static struct UnionNode *newUnionListNode (char *v)
{
	struct UnionNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate List node");
	n->url = malloc(sizeof(char) *100);
	strcpy(n->url, v);
	n->next = NULL;
	return n;
}

/** Apppend one integer to the end of an List. */
UnionList UnionListInsert (UnionList L, char *v)
{
	assert (L != NULL);
	struct UnionNode *n = newUnionListNode (v);
	
	if (L->first == NULL) {
	    //printf("FIRST IN LIST\n");
		L->first = L->last = n;
		L->size++;
		return L;
    }
    //printf("%s %s\n", L->first->url, v);
    if (strcmp(L->first->url, v) > 0) {
        //printf("BEFORE FIRST\n");
        n->next = L->first;
        L->first = n;
        L->size++;
        return L;
    }
 
    struct UnionNode *curr = L->first; 
    struct UnionNode *prev = NULL;
    
    while (curr != NULL) {
        if (strcmp(curr->url, v) == 0) {
            //printf("%s %s same\n", curr->url, v);
            free(n->url);
            free(n);
            return L;
        } 
        if (strcmp(curr->url, v) < 0) {
            //printf("LARGER\n");
            prev = curr;
            curr = curr->next;
        } else {
            prev->next = n;
            n->next = curr;
            L->size++;
            return L;
        }
    }
    
    if (curr == NULL) {
        //printf("reached end\n");
        prev->next = n;
        n->next = NULL;
        L->size++;
        return L;
    }
    free(n->url);
    free(n);
	return L;
}


/** Return number of elements in an List. */
int UnionListLength (UnionList L)
{
	assert (L != NULL);
	return L->size;
}

