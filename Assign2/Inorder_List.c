// for part 2

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "Inorder_List.h"


static struct FreqNode *newFreqNode (char *v);

/** Create a new, empty List. */
// based on 2521 lab01
FreqList newFreqList (void)
{
	struct FreqListRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate WordList");
	new->first = new->last = NULL;
	return new;
}

/** Release all resources associated with an List. */
// based on 2521 lab01
void freeFreqList (FreqList L)
{
	if (L == NULL) return;

	for (struct FreqNode *curr = L->first, *next;
		 curr != NULL; curr = next) {
		next = curr->next;
		free (curr);
	}
    
	free (L);
}

/** create a new ListNode with value v
 * (this function is local to this ADT) */
static struct FreqNode *newFreqNode (char *v)
{
	struct FreqNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate List node");
	n->word = malloc(sizeof(char) *100);
	strcpy(n->word, v);
	n->freq = 1;
	n->pagerank = 0;
	n->next = NULL;
	return n;
}

/** Apppend one integer to the end of an List. */
// finding frequency 
FreqList FreqListInsert (FreqList L, char *v, double p)
{

    assert(L != NULL);
	// if words are equal 
	struct FreqNode *curr = L->first;
	
	while (curr != NULL) {
	 
	    if (strcmp(v, curr->word) == 0) {
	        curr->freq++;
	        return L;
	    }
	    curr = curr->next;
	}
	
	struct FreqNode *n = newFreqNode (v);
	n->pagerank = p;
	// if list is empty 
	if (L->first == NULL) {
        L->first = n;
        L->last = n;
	} else {
	    L->last->next = n;
	    L->last = n;
	}
	
	return L;

}

// putting it in order 
FreqList FreqListInorder (FreqList L) {
    
    struct FreqNode *curr1;
    struct FreqNode *curr2;
    char *string; // word
    int nums; // freq
    double temp; // pagerank
    
    // sort TfIdfLists 
    
    for (curr1 = L->first; curr1->next != NULL; curr1 = curr1->next) {
        for (curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next) {
            if (curr1->freq < curr2->freq) {
                temp = curr1->pagerank;
                string = curr1->word;
                nums = curr1->freq;
                curr1->pagerank = curr2->pagerank;
                curr1->word = curr2->word;
                curr1->freq = curr2->freq;
                curr2->pagerank = temp;
                curr2->word = string;
                curr2->freq = nums;
            } else if (curr1->freq == curr2->freq) {
                if (curr1->pagerank < curr2->pagerank) {
                    temp = curr1->pagerank;
                    string = curr1->word;
                    curr1->pagerank = curr2->pagerank;
                    curr1->word = curr2->word;
                    curr2->pagerank = temp;
                    curr2->word = string;
                }
            }
        }
    }
    return L;
}

