// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008

#ifndef TfIdfList_H
#define TfIdfList_H

#include <stdbool.h>
#include <stdio.h>
#include "invertedIndex.h"

/** External view of IntList ... implementation in IntList.c */

/** Release all resources associated with an IntList. */
void freeTfIdfList (TfIdfList);

TfIdfList newTfIdfList (void);

/** Insert an integer into correct place in a sorted IntList. */
TfIdfList TfIdf_Insert (TfIdfList, double, char*);

TfIdfList Retrieve_Insert(TfIdfList L, double v, char *name);

TfIdfList insert_inorder(TfIdfList L);

#endif
