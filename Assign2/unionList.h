#ifndef UnionLIST_H
#define UnionLIST_H

#include <stdbool.h>
#include <stdio.h>

typedef struct UnionListRep *UnionList;

struct UnionNode {
	char *url;
	struct UnionNode *next;
	                    /**< pointer to node containing next element */
};

struct UnionListRep {
	int size;           /**< number of elements in list */
	struct UnionNode *first;
	                    /**< node containing first value */
	struct UnionNode *last;
	                    /**< node containing last value */
};

UnionList newUnionList (void);
void freeUnionList (UnionList L);
UnionList UnionListInsert (UnionList L, char *v);
int UnionListLength (UnionList L);

#endif 
