#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include "list.h"

typedef int Vertex;

typedef struct Node{
	Vertex v;
    struct Node *next;
} Node;

typedef struct Node *GraphList;

typedef struct GraphRep {
    Node **Inlink;
    Node **Outlink;
	int nV;		 // #vertices
	int nE;		 // #edges
} GraphRep;

typedef struct GraphRep *Graph;

// creating a new graph 
Graph newGraph(int vertices);

// droping the graph 
void dropGraph(Graph g);

// creating a linked list representation connected to an array 
GraphList insertGraphList(GraphList L, int value);

// to check if the edge is already in the list or not 
int inList(GraphList L, Vertex v);

// adding edge into a list in both Inlink and Outlink array 
void addEdge(Graph g, Vertex src, Vertex dest);

// show the graph for testing 
void show(Graph g, List L);

#endif 
