// FileList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008

#ifndef FileList_H
#define FileList_H

#include "invertedIndex.h" 
#include <stdbool.h>
#include <stdio.h>
#include "BST.h"

/** Release all resources associated with an FileList. */
void freefileList (InvertedIndexBST);

/** Insert an integer into correct place in a sorted FileList. */
void FileListInsertInOrder (InvertedIndexBST, char*, double);

void PrintFileListInOrder (InvertedIndexBST, FILE *);

double FileCount (InvertedIndexBST t);

#endif

