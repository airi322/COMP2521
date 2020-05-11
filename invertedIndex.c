#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "invertedIndex.h"
#include "FrequencyList.h"
#include "BST.h"
#include "FileList.h"
#include "TfIdfList.h"

//reads data from collection.txt 
//generates "inverted index" 
//each list of filenames in inverted index should be alphabetically ordered 
//use fscanf --> don't need restriction on line length 

//output should give inverted index tree to file named "invertedIndex.txt"
//one line per word, words should be alphabetically ordered, ascending

void trim(char * str);
void remove_punctuation_mark(char *str);
void InvertedIndexBSTFind (InvertedIndexBST t, int count, char *v, double freq, char *file);
void InvertedIndexBSTInfix (InvertedIndexBST t, FILE *outf);
TfIdfList find_TfIdf_word (TfIdfList L, InvertedIndexBST t, char *v, int D);
TfIdfList Retrieve_TfIdfList(TfIdfList L, InvertedIndexBST t, char *v, int D);

    /*
     1. Check if collection can be opened 
     2. Scan each text file and initialise Frequency List 
     3. Open each file and normalise word in text file 
     4. Insert word into Tree 
     4. Count frequency with frequency list and count number of words in file 
     5. Find tf and insert into linked list with search function below 
    */ 
    
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    
    // scan files from collections 
    // open files and scan word by word 
    FILE *fp = fopen(collectionFilename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    // scan collectionfilename 
    // scan each text file then add each file into a linked list
    
    double count = 0;
    char word[100];
    char file[100];
    
    // initialise tree 
    InvertedIndexBST t = newInvertedIndexBST();
    while (fscanf(fp, "%s", file) != EOF) {

        FILE *fp2 = fopen(file, "r");
        //initialise Frequency List
        FrequencyList L = newFrequencyList();
        while (fscanf(fp2, "%s", word) != EOF) {
            // normalise each word 
            normaliseWord(word);
            t = InvertedIndexBSTInsert(t, word);
            // linked list to find frequency 
            FrequencyListInsert(L, word);
            // count number of words in the file 
            count++;
        }

        FrequencyListNode *frequencyList = L->first;
        // iterate through frequency List to insert frequency of value 
        while (frequencyList != NULL) {
            InvertedIndexBSTFind(t, count, frequencyList->value, frequencyList->freq, file);
            frequencyList = frequencyList->next;
        }
        
        freeFrequencyList(L);
        count = 0;
        fclose(fp2);

    }

    fclose(fp);

    return t;
    
}

// Based on COMP2521 LAB 3
// Find node in tree equal to char *v
// Calculate tf and Insert into FileList  
void InvertedIndexBSTFind (InvertedIndexBST t, int count, char *v, double freq, char *file)
{
    // this function is called from invertedIndexgenerate function 
	if (t == NULL) {
		return;
	} else if (strcmp(v, t->word) < 0) {
		return InvertedIndexBSTFind (t->left, count, v, freq, file);
	} else if (strcmp(v, t->word) > 0) {
		return InvertedIndexBSTFind (t->right, count, v, freq, file);
	} else {// (v == t->word)
	
	    // calculating tf 
        double frequency = (freq/count);
	    FileListInsertInOrder(t, file, frequency);
    }   
}

void printInvertedIndex(InvertedIndexBST tree) {
    
    //loop through tree of each node + the filenames of the linked list it is linked to 
    //print it out to a textfile invertedIndex.txt 
    FILE *f = fopen("invertedIndex.txt", "w");
    
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    InvertedIndexBSTInfix (tree, f);
    
    fclose(f);

}

// Based on COMP2521 LAB 3
// go through infix order and print out tree node with linked list
void InvertedIndexBSTInfix (InvertedIndexBST t, FILE *outf)
{
	if (t == NULL) return;

	InvertedIndexBSTInfix (t->left, outf);
	fprintf(outf, "%s ", t->word);
	PrintFileListInOrder (t, outf);
	InvertedIndexBSTInfix (t->right, outf);
}

    /*
     1. find searchword in tree and for all linked list linked to the node, iterate through and take the filename and tf value 
     2. calculate idf 
     --> log of D/(number of files)
     3. calculate tfidf 
     4. insert into TfIdfList
     5. insert into descending order of tfidf
     6. if tfidf values are the same, insert based on filename in ascending order. 
    */
    // make a new list for tfidf and make it an argument in find word 
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {

    TfIdfList L = newTfIdfList();
    L = find_TfIdf_word (L, tree, searchWord, D); 
    
    return L;
}

// Based on COMP2521 LAB 3
// Find node in tree equal to char *v
// Calculate tfidf and Insert into TfIdfList 
TfIdfList find_TfIdf_word (TfIdfList L, InvertedIndexBST t, char *v, int D) {

    // go through tree until find the word 
	if (t == NULL) {
		return L;
	} else if (strcmp(v, t->word) < 0) {
		return find_TfIdf_word (L, t->left, v, D);
	} else if (strcmp(v, t->word) > 0) {
		return find_TfIdf_word(L, t->right, v, D);
	} else {// (v == t->word)
	    
	    // count number of files connected to a word node
        double count = FileCount(t);
        count = D/count;
        // find the log 
        double result = log10(count);
		// iterate through the linked list 
		struct FileListNode *curr = t->fileList;
		while (curr != NULL) {
		    double value = result*curr->tf;
		    // include the new file in the insert argument 
		    L = TfIdf_Insert(L, value, curr->filename);
		    curr = curr->next;
		}
    }  
    
    L = insert_inorder(L);
    return L; 

}
/*
// Used for testing 
void printTfIdfList(char *TfIdfFileList, TfIdfList L) {
    
    FILE *f = fopen(TfIdfFileList, "w");
    
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    printTfIdfListfunction(L, f);
    fclose(f);

}*/
/*
//Used for testing 
void printTfIdfListfunction(TfIdfList L, FILE *outf) {

    struct TfIdfNode *curr = L;
    while (curr != NULL) {
        //printf("%f %s\n", curr->tfidf_sum, curr->filename);
        fprintf(outf, "%f  %s\n", curr->tfidf_sum, curr->filename);
        curr = curr->next;
    }

}
*/

// Create a list where each node contains a filename and the summation of tfidf for the given search words
// loop to the node of the tree, calculate tfidf of each fileList
// loop to other nodes and continue adding to the filename 
TfIdfList retrieve(InvertedIndexBST tree, char* searchWords[] , int D) {

    TfIdfList newL = newTfIdfList();
    int i = 0;
    while (searchWords[i] != NULL) {
        newL = Retrieve_TfIdfList(newL, tree, searchWords[i], D);
        i++;
    }
    
    return newL;
    
}

// Based on COMP2521 LAB 3
// Find node in tree equal to char *v
// Calculate tf and Insert into TfIdfList 
TfIdfList Retrieve_TfIdfList(TfIdfList L, InvertedIndexBST t, char *v, int D) {
   
// go through tree until find the word 
	if (t == NULL) {
		return L;
	} else if (strcmp(v, t->word) < 0) {
		return Retrieve_TfIdfList (L, t->left, v, D);
	} else if (strcmp(v, t->word) > 0) {
		return Retrieve_TfIdfList(L, t->right, v, D);
	} else {// (v == t->word)
        // go through filelist */
        // find idf 
        
        double count = FileCount(t);
        count = D/count;
        // find the log 
        double result = log10(count);
        struct FileListNode *curr = t->fileList;
        while (curr != NULL) {
            double value = result*curr->tf;
            L = Retrieve_Insert(L, value, curr->filename);
            curr = curr->next;
        }
    }
    L = insert_inorder(L);
    return L;
}

//normalising the words 
char * normaliseWord(char *str) {

    trim(str);
    
    // convert to lowercase 
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    remove_punctuation_mark(str);
    
    return str;
}

// might not be needed since fscanf already trims characters
// help session tutor said required since functions are tested independently
void trim(char *str) {
    
    if (strlen(str) == 0) return;
    if (str[0] == '\0') return;
    
    // trim leading space and newline  
         
    int index = 0;
    while(str[index] == ' ' || str[index] == '\n') {
        index++;
    }
    
    int i = 0;
    while (str[i + index] != '\0') {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0';
    
    // trim trailing space and newline
    
    i = 0;
    index = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' || str[i] == '\n') index = i;
        i++;
    }    
    
    str[index + 1] = '\0';

}
     
void remove_punctuation_mark(char *str) {
    
    // second last character including '\0' (assuming that there isn't a new line character)
    int len = strlen(str) - 1;
    
    if (str[len] == '.' || str[len] == ',' || str[len] == ';' || str[len] == '?') {
        str[len] = '\0';
    }
}
   
