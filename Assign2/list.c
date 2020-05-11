
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "list.h"

/** Create a new, empty List. */
// from 2521 lab01
List newList (void)
{
	struct ListRep *L = malloc (sizeof *L);
	if (L == NULL) err (EX_OSERR, "couldn't allocate List");
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

/** Release all resources associated with an List. */
// from 2521 lab01
void freeList (List L)
{
	if (L == NULL) return;

	for (struct ListNode *curr = L->first, *next;
		 curr != NULL; curr = next) {
		next = curr->next;
		free (curr);
	}

	free (L);
}

/** create a new ListNode with value v
 * (this function is local to this ADT) */
// from 2521 lab01
static struct ListNode *newListNode (char *v)
{
	struct ListNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate List node");
	n->name = malloc(sizeof(char) *100);
	strcpy(n->name, v);
	n->num = 0;
	n->pagerank = 0;
	n->next = NULL;
	return n;
}

/** Apppend one integer to the end of an List. */
// from 2521 lab01
List ListInsert (List L, char *v)
{
	assert (L != NULL);
	struct ListNode *n = newListNode (v);
	if (L->first == NULL) {
		L->first = L->last = n;
	} else {
		L->last->next = n;
		L->last = n;
	}
	L->size++;
	n->num = L->size - 1;
	return L;
}


/** Return number of elements in an List. */
// from 2521 lab01
int ListLength (List L)
{
	assert (L != NULL);
	return L->size;
}

// returning the string in graph.c function printList for testing 
char* PrintList (List L, int v) {
    
    
    struct ListNode *curr = L->first;
    while (curr != NULL) {
        if (v == curr->num) {
            return curr->name;
        }
        curr = curr->next;
    }
    return 0;
}

// printing the list in order with bubblesort 
List List_inorder(List L) {
    
    struct ListNode *curr1;
    struct ListNode *curr2;
    char *string;
    int nums;
    double temp;

    for (curr1 = L->first; curr1->next != NULL; curr1 = curr1->next) {
        for (curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next) {
            if (curr1->pagerank < curr2->pagerank) {
                temp = curr1->pagerank;
                string = curr1->name;
                nums = curr1->num;
                curr1->pagerank = curr2->pagerank;
                curr1->name = curr2->name;
                curr1->num = curr2->num;
                curr2->pagerank = temp;
                curr2->name = string;
                curr2->num = nums;
            }
        }
    }
    return L;
}

