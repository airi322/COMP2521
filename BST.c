// ADT Tree for assignment

// InvertedIndexBST.c ... implementation of binary search tree ADT

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "BST.h"


// create a new empty InvertedIndexBST
InvertedIndexBST newInvertedIndexBST (void)
{
	return NULL;
}
// From COMP2521 LAB 3
// make a new node containing a word
static BSTLink newBSTNode (char *v)
{
	BSTLink new = malloc (sizeof*new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate BST node");
	new->word = malloc(sizeof(char) *100);
	strcpy(new->word, v); 
	new->left = new->right = NULL;
	new->fileList = NULL;
	return new;
}

// From COMP2521 LAB 3
// free memory associated with InvertedIndexBST
void dropInvertedIndexBST (InvertedIndexBST t)
{
	if (t == NULL)
		return;

	dropInvertedIndexBST (t->left);
	dropInvertedIndexBST (t->right);
	free (t);
}

// From COMP2521 LAB 3
// insert a new word into a InvertedIndexBST
InvertedIndexBST InvertedIndexBSTInsert (InvertedIndexBST t, char *v)
{

	if (t == NULL)
		return newBSTNode (v);
	else if (strcmp(v, t->word) < 0)
		t->left = InvertedIndexBSTInsert (t->left, v);
	else if (strcmp(v, t->word) > 0) 
		t->right = InvertedIndexBSTInsert (t->right, v);
	else // (v == t->word)
		/* don't insert duplicates */;
	return t;
}

