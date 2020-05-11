// InvertedIndexBST.h ... interface to binary search tree ADT

#ifndef InvertedIndexBST_H
#define InvertedIndexBST_H
#include "invertedIndex.h" 
typedef struct InvertedIndexNode *BSTLink;

// create an empty InvertedIndexBST
InvertedIndexBST newInvertedIndexBST (void);
// free memory associated with InvertedIndexBST
void dropInvertedIndexBST (InvertedIndexBST);

// insert a new value into a InvertedIndexBST
InvertedIndexBST InvertedIndexBSTInsert (InvertedIndexBST, char*);

#endif

