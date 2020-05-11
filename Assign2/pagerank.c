// Part 1
// Find the weight of each node 
// Think can use graph structure and the visited[w] (as the neighbour) and those kind of things 

/*
1. scan through collection.txt --> DONE
2. open each txt file and scan through them --> DONE 
3. read from #start Section-1 --> #end Section-1 and each url will be the node (vertex) in the graph --> DONE 
------> lecturer is saying to map each url string to a number so it will be easier to read 
4. Name of the text file has outgoing links to each url in its file --> DONE
------> can use the graph.c/h and it is a directed graph 
4 a). Need to check if the graph is working properly --> DONE
understanding the code 
5. 
i. PR(pi;0) = 1/N
---> for each url in collection = 1/N (they all have equal weight)
ii. diff = .....
--->
for all url find the absolute value of pagerank of url at iteration (t + 1) - pagerank of url at iteration (t) 

iii. pR(pit +1) ...
--->

for all nodes with outgoing links (pj) to pi, find it's pagerank * W(in) and W(out)

---> will explain W(in) and W(out) in more detail  

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "pagerank.h"

//gcc -Wall -lm -std=c11 pagerank.c list.c graph.c -o pagerank

int main (int argc, char **argv) {
    
    // initialise List for mapping the urls 
    List L = createList("collection.txt"); 
    
    // initialise Adjacency List Representation 
    Graph g = read_collection(L, "collection.txt");
    
    // error handling 
    if (argc != 4) perror("Not enough arguments\n");
    
    // retrieving data from command line 
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    
    //printf("%lf, %lf, %d\n", d, diffPR, maxIterations);
    
    // generate pagerank 
    L = PageRankW(g, L, d, diffPR, maxIterations);
    
    // generate pagerankList.txt 
    printList(g, L);
    
    freeList(L);
    dropGraph(g);
    
    return 0;
}

// open collection txt and open every url text file
// insert url into each node of linked list 
List createList(char *collectionFilename) {

    char text_file[100];
    
    FILE *fp = fopen(collectionFilename, "r");

    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    List L = newList();
    while (fscanf(fp, "%s", text_file) != EOF) {
        L = ListInsert(L, text_file);
    }
    
    fclose(fp);
    return L;

}
    
// open each text file and insert into edge of graph
// return graph 
Graph read_collection (List L, char *collectionFilename) {
    
    char text_file[100];
    char url[100];
    int count = 0; 

    FILE *fp = fopen(collectionFilename, "r");

    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    while (fscanf(fp, "%s", text_file) != EOF) {
        count++;
    }

    fclose(fp);
    
    // initialise graph
    Graph g = newGraph(count);
    
    FILE *fp2 = fopen(collectionFilename, "r");
   
    if (fp2 == NULL) {
        perror("Error opening file");
        exit(1);
    }

    
    // need to make every url to have their own number  
    
    // scan through the file and open each text file 
    int j = 0;
    while (fscanf(fp2, "%s", text_file) != EOF) {
        // open each file 
        char *result = malloc(strlen(text_file) + strlen(".txt") + 1);
        strcpy(result, text_file);
        strcat(result, ".txt");
        
        FILE *fp3 = fopen(result, "r"); 
        // scan each url into a graph vertex 
        if(fp3 == NULL) {
            perror("Error opening file");
        }
        char *find_end = "#end";
        char *find_start = "#start";
        char *find_start2 = "Section-1";
        while (fscanf(fp3, "%s", url) != EOF && strcmp(url, find_end) != 0) {
            // if start_section 1, ignore the line 

            if (strcmp(url, find_start) == 0 || strcmp(url, find_start2) == 0) {
                //printf("---------found start\n");
                continue;
            }
             
            //printf("%s\n", url);
            struct ListNode *curr = L->first;
            while (curr != NULL) {
                if (strcmp(url, curr->name) == 0) {
                    addEdge(g, j, curr->num);
                    //printf("j = %d, name = %s, num = %d\n", j, curr->name, curr->num);
                }
                curr = curr->next;
            }           
  
        }
        //printf("text file %s\n", text_file);
        j++;
    }
    //show(g, L);
    return g;
    

}

// print list into pagerankList.txt 
void printList(Graph g, List L) {
    
    FILE *fp = fopen("pagerankList.txt", "w");
    
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    struct ListNode *curr2 = L->first;
    while (curr2 != NULL) {
        fprintf(fp, "%s, %d, %.7f\n", curr2->name, count_Outlink(g, curr2->num), curr2->pagerank);
        curr2 = curr2->next;
    }
        
    return;
}

// count number of outlinks for pagerankList.txt 
int count_Outlink(Graph g, int v) {
    
    GraphList m = g->Outlink[v];
    int count = 0;
    while (m != NULL) {
        count++;
        m = m->next;
    }
    return count;

}
    
// all doubles ---> d = damping factor; diffPR; maxIterations
// need to return a List then print out the list 
// main function for calculating pagerank 
List PageRankW(Graph g, List L, double d, double diffPR, int maxIterations) {
    
    int N = g->nV; 
    int i;
    double old_pagerank[N];
    
    // for calculating initial pagerank values 
    for (i = 0; i < g->nV; i++) {
        old_pagerank[i] = 1.0/N;
    }
    //printf("OLD PAGERANK %lf\n", old_pagerank[0]);
    int iteration = 0;
    double diff = diffPR;
    
    double new_pagerank[N]; 
    while (iteration < maxIterations && diff >= diffPR) {
        int i;
        for (i = 0; i < g->nV; i++) {
            GraphList n = g->Inlink[i];
            double value = 0;
            while (n != NULL) {
                // Win(pj, pi) where pi = i && where pj = n->v
                double W_in = calculate_Win(g, n->v, i);
                double W_out = calculate_Wout(g, n->v, i);
                double W = W_in*W_out; 
                value = old_pagerank[n->v]*W + value;
                n = n->next;
            }
            double result = ((1.0-d)/N) + (d*value);
            new_pagerank[i] = result;
            //printf("---------------->%d %.7f %lf %lf\n", i, new_pagerank[i], old_pagerank[i], result);
        }
        // calculating diff
        diff = 0;
        for (i = 1; i < g->nV; i++) {
            diff = fabs(new_pagerank[i] - old_pagerank[i]) + diff;
            //printf("diff %lf diffPR %lf\n", diff, diffPR);
        }
        // moving all of newpagerank to old_pagerank
        for (i = 0; i < g->nV; i++) {
            old_pagerank[i] = new_pagerank[i];
        }
        iteration++;
    }
    
    // copying all of the final pagerank values into the pagerank linked list
    struct ListNode *curr = L->first;
    int k = 0;
    while (curr != NULL) {
        curr->pagerank = new_pagerank[k];
        k++;
        curr = curr->next;
    }
    
    // to make the linked list in order 
    List_inorder(L);
    return L;

}
  
double calculate_Win(Graph g, Vertex j, Vertex i) {
    
    // Vertex i = pi 
    // Vertex j = pj
    // find the number of inlinks of the given url node 
    // find the number of inlinks of each of the other connected nodes
    
    // finding inlinks of pi (i) 

    GraphList n = g->Inlink[i];
    double ncount = 0;
    while (n != NULL) {
        ncount++;
        n = n->next;
    }
    
    // go to all the reference points (outlinks) of pj (j) 
    GraphList m = g->Outlink[j];
    
    double mcount = 0;
    while (m != NULL) {
        GraphList m2 = g->Inlink[m->v];
        while (m2 != NULL) {
            mcount++;
            m2 = m2->next;
        }
        m = m->next;
    }
    
    double result = ncount/mcount;
    return result;
}

double calculate_Wout(Graph g, Vertex j, Vertex i) {

    // Vertex i = pi 
    // Vertex j = pj
    
    // find the number of outlinks of the given url node 
    // find the number of outlinks of each of the other connected nodes 
    
    // finding outlinks of pi (i) 
    GraphList n = g->Outlink[i];
    double ncount = 0;
    while(n != NULL) {
        ncount++;
        n = n->next;
    }
    if (ncount == 0) ncount = 0.5;
    
    GraphList m = g->Outlink[j];
    
    double mcount = 0;
    while (m != NULL) {
        GraphList m2 = g->Outlink[m->v];
        int tracking = 0;
        while (m2 != NULL) {
            tracking++;
            mcount++;
            m2 = m2->next;
        }
        if (tracking == 0) mcount = mcount + 0.5;
        m = m->next;
    }

    double result = ncount/mcount;
    
    return result;
}
    
    
    
       

