// List ADT

// FileList.c - Lists of integers
// Written by John Shepherd, July 2008

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "FileList.h"

static struct FileListNode *newFileListNode (char *v);
/*
FileList newFileList (void)
{
	return NULL;
}
*/
/** Release all resources associated with an FileList. */
void freefileList (InvertedIndexBST t)
{

    struct FileListNode *curr = t->fileList;
    
    if (curr == NULL) return;
    
    struct FileListNode *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

	free (t);
}

 // From COMP2521 LAB 1
/** create a new FileListNode with value v
 * (this function is local to this ADT) */
static struct FileListNode *newFileListNode (char *v)
{
	struct FileListNode *n = malloc (sizeof *n);
	if (n == NULL) err (EX_OSERR, "couldn't allocate FileList node");
	n->filename = malloc(sizeof(char) *100);
	strcpy(n->filename, v);
	n->next = NULL;
	return n;
}

// insert FileList in Order 
void FileListInsertInOrder (InvertedIndexBST t, char *v, double p)
{

	struct FileListNode *n = newFileListNode(v);
	n->tf = p;
	
	// if List is empty
	if (t->fileList == NULL) {
	    t->fileList = n;
	    t->fileList->next = NULL;
	    return;
	}
	
	// if head of list is larger than new node 
	// make new value head of list 
	if (strcmp(t->fileList->filename, n->filename) > 0) {
	    n->next = t->fileList;
	    t->fileList = n;
	    return;
	}
	
	struct FileListNode *curr = t->fileList->next;
	struct FileListNode *prev = t->fileList;
	
	// insert if in the middle 
	while (curr != NULL){
	    int comp = strcmp(curr->filename, n->filename);
	    if (comp == 0) return;
	    if (comp < 0){
	        prev = curr;
	        curr = curr->next;
	    }else{
	        prev->next = n;
	        n->next = curr;
	        return;
	    }
	}
	
	if (curr == NULL) {
	    prev->next = n;
	    n->next = NULL;
	}
	
	return;
	
}

void PrintFileListInOrder (InvertedIndexBST t, FILE *outf) {
    
    struct FileListNode *curr = t->fileList;
    
    while (curr != NULL) {
        fprintf(outf, "%s ", curr->filename);
        curr = curr->next;
    }
    fprintf(outf, "\n");
}

double FileCount (InvertedIndexBST t) {
    
    struct FileListNode *curr = t->fileList;
    double count = 0;
    
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }   
    return count;
}    
    
