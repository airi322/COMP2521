#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct ListRep *List;

struct ListNode {
	char *name;
	int num;
	double pagerank;
	struct ListNode *next;
	                    /**< pointer to node containing next element */
};

struct ListRep {
	int size;           /**< number of elements in list */
	struct ListNode *first;
	                    /**< node containing first value */
	struct ListNode *last;
	                    /**< node containing last value */
};

/** Create a new, empty List. */
List newList (void);

/** Release all resources associated with an List. */
void freeList (List L);

/** Apppend one integer to the end of an List. */
List ListInsert (List L, char *v);

/** Return number of elements in an List. */
int ListLength (List L);

// returning the string in graph.c function printList for testing 
char* PrintList (List L, int v);

// printing the list in order with bubblesort
List List_inorder(List L);

#endif 
