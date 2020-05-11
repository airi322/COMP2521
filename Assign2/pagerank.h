#ifndef PAGERANK_H
#define PAGERANK_H

#include "list.h"
#include "graph.h"

// open each text file and insert into edge of graph
// return graph 
Graph read_collection (List L, char *collectionFilename);

// main function for calculating pagerank
List PageRankW(Graph g, List L, double d, double diffPR, int maxIterations);

// calculating W_in 
double calculate_Win(Graph g, Vertex j, Vertex i);

// calculating W_out 
double calculate_Wout(Graph g, Vertex j, Vertex i);

// print list into pagerankList.txt 
void printList(Graph g, List L);

// open collection txt and open every url text file
// insert url into each node of linked list 
List createList(char *collectionFilename);

// count number of outlinks for pagerankList.txt 
int count_Outlink(Graph g, int v);

#endif
