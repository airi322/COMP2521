#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "TfIdfList.h"
#include "invertedIndex.h"



TfIdfList newTfIdfList (void)
{
	return NULL;
}

// From COMP2521 LAB 1
/** Release all resources associated with an TfIdfList. */
void freeTfIdfList (TfIdfList L)
{
	if (L == NULL) return;

	for (struct TfIdfNode *curr = L, *next = NULL;
		 curr != NULL; curr = next) {
		next = curr->next;
		free (curr);
	}

	free (L);
}

// From COMP2521 LAB 1
/** create a new TfIdfNode with value v
 * (this function is local to this ADT) */
static struct TfIdfNode *newTfIdfNode (double v)
{
	struct TfIdfNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate TfIdf node");
	n->tfidf_sum = v;
	n->next = NULL;
	return n;
}
// tfidf inserted in descending order 
TfIdfList TfIdf_Insert (TfIdfList L, double v, char *name) {

    // make newnode have tfidf value 
	struct TfIdfNode *n = newTfIdfNode(v);
    n->filename = name;
    
    // make a new list if NULL 
    if (L == NULL) {
        L = n;
        L->filename = name;
        L->next = NULL; 
        return L;
    } 
    
	// insert nodes in after last node in list 
	
	struct TfIdfNode *curr = L;
	struct TfIdfNode *prev = NULL; 

	while (curr != NULL) {
	    prev = curr; 
	    curr = curr->next;
	}
	
	prev->next = n;
	n->next = NULL;
	
	
    return L;

}

TfIdfList Retrieve_Insert(TfIdfList L, double v, char *name) {

    // make newnode have tfidf value 
	struct TfIdfNode *n = newTfIdfNode(v);
    n->filename = name;
    
    // make a new list if NULL    
    if (L == NULL) {
        L = n;
        L->filename = name;
        L->next = NULL; 
        return L;
    } 
	
	struct TfIdfNode *curr = L;
	struct TfIdfNode *prev = NULL; 
	
	// if filenames are equal, simply add current tfidf value with new value
	// else insert new node after last node in list 
	while (curr != NULL) {
	    if (strcmp(curr->filename, name) == 0) {
	        curr->tfidf_sum = curr->tfidf_sum + v;
	        
	        free(n);
	        return L;
	    }
	    prev = curr; 
	    curr = curr->next;
	}

	prev->next = n;
	n->next = NULL;
	
    return L;

}

TfIdfList insert_inorder(TfIdfList L) {
    
    struct TfIdfNode *curr1;
    struct TfIdfNode *curr2;
    double temp; 
    char *string;
    
    // sort TfIdfLists 
    
    for (curr1 = L; curr1->next != NULL; curr1 = curr1->next) {
        for (curr2 = curr1->next; curr2 != NULL; curr2 = curr2->next) {
            if (curr1->tfidf_sum < curr2->tfidf_sum) {
                temp = curr1->tfidf_sum;
                string = curr1->filename;
                curr1->tfidf_sum = curr2->tfidf_sum;
                curr1->filename = curr2->filename;
                curr2->tfidf_sum = temp;
                curr2->filename = string;
            } else if (curr1->tfidf_sum == curr2->tfidf_sum) {
                int comp = strcmp(curr1->filename, curr2->filename);
                if (comp > 0) {
                    string = curr1->filename;
                    curr1->filename = curr2->filename;
                    curr2->filename = string;
                }
                    
            }
        }
    }
    return L;
}

	
    
    

