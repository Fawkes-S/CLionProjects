#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

typedef struct Graph_Repr {
    int  **edges;   // adjacency matrix
    int    nV;      // #vertices
    int    nE;      // #edges
} Graph_Repr;

graph graph_create(){
    graph g = malloc(sizeof(Graph_Repr));
    int i;
    if(!g){
        return NULL;
    }
    g->nV = 0;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

void graph_destroy (graph G){

}