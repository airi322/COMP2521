// for part 2

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "inverted_list.h"

/** Create a new, empty List. */

static struct WordNode *newWordNode (char *v);
static struct UrlNode *newUrlNode (char *v);

// creating a new 2D list 
// based off 2521 lab01
WordList newWordList (void)
{
	struct WordListRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate WordList");
	new->first = new->last = NULL;
	//new->nitems = 0;
	return new;
}

/** Release all resources associated with an List. */
// based off 2521 lab01
void freeWordList (WordList L)
{
    if (L == NULL) return;
    
	for (struct WordNode *curr = L->first, *next;
		 curr != NULL; curr = next) {
		for (struct UrlNode *curr1 = curr->Urls, *next1;
		curr1 != NULL; curr1 = next1) {
		    next1 = curr1->next;
		    free(curr1);
		}
		next = curr->next;
		free (curr);
	}
    
	free (L);
}

/** create a new WordNode with value v
 * (this function is local to this ADT) */
static struct WordNode *newWordNode (char *v)
{
	struct WordNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate List node");
	n->word = malloc(sizeof(char) *100);
	strcpy(n->word, v);
	n->next = NULL;
	return n;
}

/** create a new UrlNode with value v
 * (this function is local to this ADT) */
static struct UrlNode *newUrlNode (char *v)
{
	struct UrlNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate List node");
	n->url_name = malloc(sizeof(char) *100);
	strcpy(n->url_name, v);
	n->next = NULL;
	return n;
}

/** Apppend one integer to the end of an List. */
// based on 2521 lab01
WordList WordListInsert (WordList L, char *v)
{

	struct WordNode *n = newWordNode (v);
	if (L->first == NULL) {
        L->first = n;
        L->last = n;
	} else {
		L->last->next = n;
		L->last = n;
	}

	return L;
}

// inserting the url list to the word node 
WordList UrlInsert(WordList L, char *v, char *o) {
    
    struct UrlNode *n = newUrlNode (v);
    struct WordNode *curr = L->first; 
    
    while (curr != NULL) {
        if (strcmp(o, curr->word) == 0) break;
        curr = curr->next;
    }
    if (curr->Urls == NULL) {
        curr->Urls = n;
        return L;
    }
    struct UrlNode *curr1 = curr->Urls;
    
    while (curr1->next != NULL) {
        curr1 = curr1->next;
    }
    curr1->next = n;

    return L;
}

