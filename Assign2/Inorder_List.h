typedef struct FreqListRep *FreqList;

struct FreqNode {
    char *word;
    int freq; 
    double pagerank;
    struct FreqNode *next;  
};

struct FreqListRep {
	struct FreqNode *first;  /**< first node in list */
	struct FreqNode *last;   /**< last node in list */
	
} FreqListRep;

// creating a new list 
FreqList newFreqList (void);

// freeing the list 
void freeFreqList (FreqList L);

// finding frequency 
FreqList FreqListInsert (FreqList L, char *v, double p);

// putting it in order 
FreqList FreqListInorder (FreqList L) ;
