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
    size_t **edges;   // adjacency matrix
    Vertex *vertexes;
    int    nV;        // #vertices
    int    nE;        // #edges
} Graph_Repr;

graph graph_create(){
    graph g = malloc(sizeof(Graph_Repr));
    if(!g){
        return NULL;
    }
    g->nV = 0;
    g->nE = 0;
    return g;
}

void graph_destroy (graph G){
    if(!G){
        return;
    }
    for (int i = 0; i < G->nV; i++){
        free(G->edges[i]);
    }
    free(G->edges);
    free(G->vertexes);
    free(G);
}
//?
//void graph_show (graph G, FILE *file, list ignore)
void graph_show (graph G){
    if(!G){
        return;
    }
    int len = graph_vertices_count(G);   // get the number of vertexes
    // output the name of each vertex
    for (int i = 0; i < len; i++) {
        printf("\t%s\n", G->vertexes[i]);
    }
    for (int k = 0; k < len; k++) {
        for (int j = 0; j < len; j++) {
            if(G->edges[k][j] != 0){
                printf("\t%s %s %d\n", G->vertexes[k], G->vertexes[j], G->edges[k][j]);
            }
        }
    }
}

void graph_add_vertex (graph G, string vertex){
    if(graph_has_vertex(G, vertex)){
        return;
    }

    int len = graph_vertices_count(G);
    // when add a new vertex, allocate memory for G->vertexes
    if(len == 0){
        G->vertexes = malloc(sizeof(string));
    }else{
        G->vertexes = realloc(G->vertexes, (len+1) * sizeof(string));
    }
    //G->vertexes = realloc(G->vertexes, (len+1) * sizeof(string));

    if(!G->vertexes){
        return;
    }
    // allocate memory for each row and column of edges
    if(len == 0){
        G->edges = malloc(sizeof(size_t *));
    }else{
        G->edges = realloc(G->edges, (len+1) * sizeof(size_t *));
    }
    //G->edges = realloc(G->edges, sizeof(size_t *));
    if(!G->edges){
        return;
    }

    //G->edges[len] = calloc((len+1), sizeof(size_t));
    for (int i = 0; i < len + 1; i++) {
        if(i == len){
            G->edges[i] = calloc((len+1), sizeof(size_t));
        }else{
            G->edges[i] = realloc(G->edges[i], (len+1) * sizeof(size_t));
            for (int j = 0; j < len + 1; j++) {
                G->edges[i][j] = 0;
            }

        }
        if(!G->edges[len]){
            return;
        }
    }

    G->vertexes[G->nV] = vertex;
    //strcpy(G->vertexes[G->nV], vertex);
    //if(G->nV>0) {printf("*********%s\n", G->vertexes[--G->nV]);G->nV++; }
    //printf("^^^^^^^^^%s\n", G->vertexes[G->nV]);
    //printf("&&&&&&&&&%s\n", G->vertexes[1]);
    G->nV++;
}

bool graph_has_vertex (graph G, string vertex){
    if(!G){
        return false;
    }
    int len = graph_vertices_count(G);
    for (int i = 0; i < len; i++) {
        if(vertex == G->vertexes[i]){
            return true;
        }
    }
    return false;
}

size_t graph_vertices_count (graph G){
    return G->nV;
}

void graph_add_edge (graph G, string vertex1, string vertex2, size_t weight){
    // Judge the existence of these two vertices
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return;
    }
    int index1, index2;
    int len = graph_vertices_count(G);      // get the number of vertexes
    for (int i = 0; i < len; i++) {          // get the index of the corresponding string vertex.
        if(G->vertexes[i] == vertex1){
            index1 = i;
        }
        if(G->vertexes[i] == vertex2){
            index2 = i;
        }
    }

    /***
    size_t a = G->edges[index1][index2];
    if(index1 ==0 && index2==2){
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                printf("~~~: %d-%d-%d\n",i,j,G->edges[i][j]);
            }
        }

        printf("0-2:: %d\n", a);
    }
    ***/

    if(G->edges[index1][index2] == 0){     // edge of these two vertexes not in graph
        G->edges[index1][index2] = weight;
        G->nE++;
    }
}

bool graph_has_edge (graph G, string vertex1, string vertex2){
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return false;
    }
    int index1, index2;
    int len = graph_vertices_count(G);
    for (int i = 0; i < len; i++) {
        if(G->vertexes[i] == vertex1){
            index1 = i;
        }
        if(G->vertexes[i] == vertex2){
            index2 = i;
        }
    }
    return (G->edges[index1][index2] != 0);
}

void graph_set_edge (graph G, string vertex1, string vertex2, size_t weight){
    int index1, index2;
    int len = graph_vertices_count(G);
    for (int i = 0; i < len; i++) {
        if(G->vertexes[i] == vertex1){
            index1 = i;
        }
        if(G->vertexes[i] == vertex2){
            index2 = i;
        }
    }
    if(graph_has_edge(G, vertex1, vertex2)){    //this edge in graph
        G->edges[index1][index2] = weight;
    }
}

size_t graph_get_edge (graph G, string vertex1, string vertex2){
    int index1, index2;
    int len = graph_vertices_count(G);
    for (int i = 0; i < len; i++) {
        if(G->vertexes[i] == vertex1){
            index1 = i;
        }
        if(G->vertexes[i] == vertex2){
            index2 = i;
        }
    }
    if(graph_has_edge(G, vertex1, vertex2)){
        return G->edges[index1][index2];
    }else{
        return 0;
    }
}

size_t graph_edges_count (graph G, string vertex){
    int index;
    int count = 0;
    int len = graph_vertices_count(G);
    if(!graph_has_vertex(G, vertex)){
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if(G->vertexes[i] == vertex){
            index = i;
        }
    }

    for (int i = 0; i < len; i++){
        if(G->edges[index][i] != 0){
            count++;
        }
    }
    return count;
}

graph_pagerank(){

}

graph_viewrank(){

}