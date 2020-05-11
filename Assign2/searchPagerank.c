// part 2 
/*
1. Use invertedIndex.txt provided to us and the data from pagerankList.txt  ---> DONE 
2. Can put the words in the invertedIndex.txt into a tree or a linked list and the following urls into a linked list --> DONE 
3. Print out to stdout top 30 pages: --> DONE
i. Descending order of number of search terms found (number of urls per word) and, 
ii. Within this group, descending order of Weighted PageRank (from pagerankList.txt part 1) 
iii. If less than 30 pages print out all of them --> DONE

*/

// make a 2D linked list 
// read the words and find the words and insert into another linked list 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "searchPagerank.h"

//gcc -Wall -lm -std=c11  searchPagerank.c inverted_list.c Inorder_List.c   -o searchPagerank

int main (int argc, char **argv) {
    
    // error handling for command line arguments 
    if (argc < 2) perror("Not enough arguments\n");
    
    // initialise and return 2D linked list 
    WordList L = read_invertedIndex ();

    // initialise 
    FreqList F = newFreqList();

    for (int i = 1; i < argc; i++) {
        F = find_order (F, L, argv[i]);
    }

    printFreqList(F);
    
    freeFreqList(F);
    freeWordList(L);
    
}

// insert inverted index into a 2D list 
WordList read_invertedIndex () {
    
    FILE *fp = fopen("invertedIndex.txt", "r");
    
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    char word[100];
    char *url = "url";
    
    WordList L = newWordList();
    while (fscanf(fp, "%s", word) != EOF) {
        
        char word_insert[100];
        if (strstr(word, url) == NULL) {
            strcpy(word_insert, word);
            WordListInsert(L, word);
        } else if(strstr(word, url) != NULL) {
            UrlInsert(L, word, word_insert);
        }
    }

    return L; 
   
}

// print the frequency list 
void printFreqList (FreqList F) {

    struct FreqNode *curr = F->first;
    for (int i = 0; i <= 30; i++) {
        while (curr != NULL) {
            //printf("%s --> %d --> %lf \n", curr->word, curr->freq, curr->pagerank);
            printf("%s\n", curr->word);
            curr = curr->next;
        } 
    }
    
    return;
}

// finding the frequency list 
FreqList find_order (FreqList F, WordList L, char *v) {
    
    struct WordNode *curr = L->first;

    while (curr != NULL) {
        //printf("%s\n", curr->word);
        if (strcmp(curr->word, v) == 0) {
            struct UrlNode *curr1 = curr->Urls;
            while (curr1 != NULL) {
                //printf("------------>%s\n", curr1->url_name);
                double value = read_PageRank(curr1->url_name);
                //printf("%s\n", curr1->url_name);
                F = FreqListInsert(F, curr1->url_name, value);           
                curr1 = curr1->next;
            }
        }
        curr = curr->next;
    }
    F = FreqListInorder (F);
    return F;

}

// finding the pagerank 
double read_PageRank(char *v) {
    
    FILE *fp = fopen("pagerankList.txt", "r");
    
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    char word[100];
    int scan = 0;
    int num = 0;
    while (fscanf(fp, "%s", word) != EOF) {

        scan++;
        if (strstr(word, v) != NULL) {
            num = scan + 2;
        }
        if (num == scan) {
            break;
        }
        
    }
    double result;
    result = atof(word);
    return result;
}
            
    
    
    
