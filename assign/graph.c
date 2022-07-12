#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

// vertices are strings
typedef string Vertex;

// edges are pairs of vertices (end-points) with a weight
typedef struct Edge {
    Vertex v;
    Vertex w;
    int    weight;
} Edge;

typedef struct Graph_Repr {
    Vertex **edges;   // adjacency matrix
    Vertex *vertexes
    int    nV;        // #vertices
    int    nE;        // #edges
} Graph_Repr;
//
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
//
void graph_destroy (graph G){
    if(!G){
        return;
    }
    for (int i = 0; i < G->nV; i++){
        free(G->edges[i]);
    }
    free(G->edges);
    free(G);
}
//
void graph_show (graph G, FILE *file, list ignore){

}

void graph_add_vertex (graph G, string vertex){
    if(graph_has_vertex(G, vertex)){
        return;
    }
    G->vertexes[++G->nV] = vertex;
}

bool graph_has_vertex (graph G, string vertex){
    if(!G){
        return false;
    }
    int len = strlen(G->vertexes);
    for (int i = 0; i < len; ++i) {
        if(vertex == G->vertexes[i]){
            return true
        }
    }
    return false;
}

size_t graph_vertices_count (graph G){
    return G->nV;
}

void graph_add_edge (graph G, string vertex1, string vertex2, size_t weight){

}