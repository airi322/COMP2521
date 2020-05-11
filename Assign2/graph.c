#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "graph.h"

// from 2521 lecture 
Graph newGraph(int vertices) {
    
    assert(vertices >= 0);
    
    Graph g = malloc(sizeof(GraphRep));
    
    if (g == NULL) return NULL; 
    
    g->nV = vertices;
    g->nE = 0;
    
    g->Outlink = malloc(vertices * sizeof(struct Node *));
    g->Inlink = malloc(vertices * sizeof(struct Node *));
    for (int i = 0; i < vertices; i++) {
        g->Outlink[i] = NULL;
        g->Inlink[i] = NULL;
    }
    return g;

}

// based off 2521 lab07
void dropGraph(Graph g) {
    
    int i;
    struct Node *curr;
    struct Node *next;
    
    struct Node *curr1;
    struct Node *next1;
    
    
    assert(g != NULL);
    assert(g->Outlink != NULL);
    assert(g->Inlink != NULL);
    
    for (i = 0; i < g->nV; i++) {
        curr = g->Outlink[i];
        while (curr != NULL) {
            next = curr->next;
            free(curr);
            curr = next;
        }
        curr1 = g->Inlink[i];
        while (curr1 != NULL) {
            next1 = curr1->next;
            free(curr1);
            curr1 = next1;  
        }      
    }
    
    free (g);

}


// inserting into a list
// based off 2521 lab07
GraphList insertGraphList(GraphList L, Vertex v) {
    
    struct Node *n = malloc(sizeof(struct Node));
    n->v = v;

    n->next = L;
    L = n;
    return n;
}

// to check if its in the list or not 
int inList(GraphList L, Vertex v) {
    
    GraphList curr = L;
    while (curr != NULL) {
        if (curr->v ==v) {
            return 1;
        }
        curr = curr->next;
    }
    
    return 0;

}

// adding edge into a graph 
// based on 2521 lecture
void addEdge(Graph g, Vertex src, Vertex dest) {
    
    assert(g != NULL);
    
    // inserting in both outlink/inlike array List 
    //if statement to check if theres already a link 
    if (!inList(g->Outlink[src], dest) && !inList(g->Inlink[dest], src) && src != dest) {
        g->Outlink[src] = insertGraphList(g->Outlink[src], dest);
        g->Inlink[dest] = insertGraphList(g->Inlink[dest], src);
        g->nE++;
    } 

}

// used for testing 
// based on 2521 lab07
void show(Graph g, List L)
{
   assert(g != NULL);
   //printf("V=%d, E=%d\n", g->nV, g->nE);
   int i;
   for (i = 0; i < g->nV; i++) {
      GraphList n = g->Outlink[i];
      printf("--------------------------------\n");
      printf("link is %d\n", i);
      while (n != NULL) {
         printf("OUTLINK %d --> %s\n", n->v, PrintList(L, n->v));
         //printf("%d\n", n->v);
         n = n->next;
      }
      GraphList p = g->Inlink[i];
      while (p != NULL) {
         printf("INLINK %d --> %s\n", p->v, PrintList(L, p->v));
         //printf("%d\n", n->v);
         p = p->next;
      }
        
   }
}
