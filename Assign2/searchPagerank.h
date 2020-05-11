#include "inverted_list.h"
#include "Inorder_List.h"

// insert inverted index into a 2D list 
WordList read_invertedIndex ();

// finding the frequency list
FreqList find_order (FreqList F, WordList L, char *v);

// finding the pagerank
double read_PageRank(char *v);

// print the frequency list 
void printFreqList (FreqList F);

