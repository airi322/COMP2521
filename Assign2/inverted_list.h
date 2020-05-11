
typedef struct WordListRep *WordList;

struct UrlNode {
    char *url_name;
    struct UrlNode *next;
};

struct WordNode {
	char *word;
	struct UrlNode *Urls;
	struct WordNode *next;
	                    
};

struct WordListRep {
	//size_t nitems;      /**< count of items in list */
	struct WordNode *first;  /**< first node in list */
	struct WordNode *last;   /**< last node in list */
} WordListRep;

// creating a new 2D list 
WordList newWordList (void);

/** Release all resources associated with an List. */
void freeWordList (WordList L);

// inserting the url list to the word node 
WordList UrlInsert(WordList L, char *v, char *o);

/** Apppend one integer to the end of an List. */
WordList WordListInsert (WordList L, char *v);
