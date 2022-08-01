#include "graph.h"
#include <stdlib.h>
#include "string.h"
#include "math.h"

// vertices are strings
typedef string Vertex;

typedef struct List_Node{
    int index;                    // value
    size_t weight;
    struct List_Node *next;           // pointer
}ListNode, * EdgeList;
/* both are struct pointer type
 * generally, ListNode emphasize pointer variables of any node
 * while EdgeList emphasize the header pointer of a linked list
 */

typedef struct Graph_Repr{
    EdgeList *edges;       // an array which store linked list of adjacency vertices
    Vertex *vertices;      // an array which store all vertices
    double *oldrank;
    double *pagerank;      // two double arrays for calculation of pagerank
    int    nV;             // #vertices
    int    nE;             // #edges
}Graph_Repr;

ListNode *makeListNode (int index, size_t weight){
    // create a new linked list node
    ListNode *newNode = malloc(sizeof(ListNode));
    if(!newNode){
        return NULL;
    }
    newNode->index = index;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

graph graph_create(){
    graph G = malloc(sizeof(Graph_Repr));
    if(!G){
        return NULL;
    }
    G->nV = 0;
    G->nE = 0;
    return G;
}

// a function of free the linked list
void freeList(EdgeList L){
    if(L){
        freeList(L->next);
        free(L);
    }
}

void graph_destroy (graph G){
    if(!G){
        return;
    }
    for (int i = 0; i < G->nV; i++){             // free all lists
        EdgeList edges = G->edges[i];
        freeList(edges);
    }
    free(G->edges);
    free(G->vertices);
    free(G);
}
//?
void graph_show (graph G, FILE *file, list ignore){
    if(!G){
        return;
    }
    int len = graph_vertices_count(G);   // get the number of vertexes
    if(!file){                           // when file is null, print to stdout
        // output the name of each vertex which is not in ignore_list
        for (int i = 0; i < len; i++) {
            if(!list_contains(ignore, G->vertices[i])){       // G->vertices[i] not in ignore_list
                fprintf(stdout, "\t%s\n", G->vertices[i]);
            }
        }
        // output edges
        for (int i = 0; i < len; i++) {
            //ListNode *node = G->edges[i];
            EdgeList edges = G->edges[i];
            if(!list_contains(ignore, G->vertices[i])){
                while (edges->next){
                    int i_vertices = edges->index;
                    fprintf(stdout, "\t%s %s %zu\n", G->vertices[i], G->vertices[i_vertices], edges->weight);
                    edges = edges->next;
                }
            }
        }
    }else{                              // when file is not null, print to file
        // output the name of each vertex which is not in ignore_list
        for (int i = 0; i < len; i++) {
            if(!list_contains(ignore, G->vertices[i])){       // G->vertices[i] not in ignore_list
                fprintf(file, "\t%s\n", G->vertices[i]);
            }
        }
        // output edges
        for (int i = 0; i < len; i++) {
            //ListNode *node = G->edges[i];
            EdgeList edges = G->edges[i];
            if(!list_contains(ignore, G->vertices[i])){
                while (edges->next){
                    int i_vertices = edges->index;
                    fprintf(file, "\t%s %s %zu\n", G->vertices[i], G->vertices[i_vertices], edges->weight);
                    edges = edges->next;
                }
            }
        }
    }

}

void graph_show1 (graph G){
    if(!G){
        return;
    }
    int num = graph_vertices_count(G);   // get the number of vertexes
    // output the name of each vertex
    for (int i = 0; i < num; i++) {
        printf("\t%s\n", G->vertices[i]);
    }
    // output edges
    for (int i = 0; i < num; i++) {
        //ListNode *node = G->edges[i];
        EdgeList edges = G->edges[i];
        while (edges->next){
            int i_vertices = edges->index;
            printf("\t%s %s %zu\n", G->vertices[i], G->vertices[i_vertices], edges->weight);
            edges = edges->next;
        }
    }
}

void graph_add_vertex (graph G, string vertex){
    if(graph_has_vertex(G, vertex)){
        return;
    }

    int num = graph_vertices_count(G);
    // when add a new vertex, allocate memory for G->vertexes
    //G->vertices = realloc(G->vertices, (num+1) * sizeof(string));
    if(num == 0){
        G->vertices = malloc(sizeof(string));
        G->edges = malloc(sizeof(ListNode *));
        G->edges[0] = malloc(sizeof(ListNode));
        G->edges[0]->next = NULL;
    }else{
        G->vertices = realloc(G->vertices, (num+1) * sizeof(string));
        G->edges = realloc(G->edges, (num+1) * sizeof(ListNode *));
        G->edges[num] = malloc(sizeof(ListNode));
        G->edges[num]->next = NULL;
    }
    if(!G->vertices|| !G->edges ){
        return;
    }
    G->vertices[num] = vertex;
    G->nV++;
}

bool graph_has_vertex (graph G, string vertex){
    if(!G){
        return false;
    }
    for (int i = 0; i < G->nV; i++) {
        if(vertex == G->vertices[i]){
            return true;
        }
    }
    return false;
}

size_t graph_vertices_count (graph G){
    return G->nV;
}

void graph_add_edge (graph G, string vertex1, string vertex2, size_t weight){
    // determine the existence of these two vertices
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return;
    }
    int index1, index2;
    index1 = index2 = 0;
    int len = graph_vertices_count(G);      // get the number of vertexes
    for (int i = 0; i < len; i++) {         // get the index of the corresponding string vertex.
        if(G->vertices[i] == vertex1){
            index1 = i;
        }
        if(G->vertices[i] == vertex2){
            index2 = i;
        }
    }
    // determine whether this edge already exists
    if(graph_has_edge(G, vertex1, vertex2)){
        return;
    }
    // create a new List Node, and add it at the beginning of the list
    ListNode *listNode = makeListNode(index2, weight);
    listNode->next = G->edges[index1];
    G->edges[index1] = listNode;

    G->nE++;
}

bool graph_has_edge (graph G, string vertex1, string vertex2){
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return false;
    }
    int index1, index2;
    index1 = index2 = 0;
    int num = graph_vertices_count(G);
    for (int i = 0; i < num; i++) {
        if(G->vertices[i] == vertex1){
            index1 = i;
        }
        if(G->vertices[i] == vertex2){
            index2 = i;
        }
    }
    // determine string vertex2 whether in list of G->edges[index1]
    EdgeList edges = G->edges[index1];
    while (edges->next){
        if(edges->index != index2){
            edges = edges->next;
        }else{                                  // when equals, return true
            return true;
        }
    }
    return false;
}

void graph_set_edge (graph G, string vertex1, string vertex2, size_t weight){
    int index1, index2;
    index1 = index2 = 0;
    for (int i = 0; i < G->nV; i++) {
        if(G->vertices[i] == vertex1){
            index1 = i;
        }
        if(G->vertices[i] == vertex2){
            index2 = i;
        }
    }
    // find the node in list of G->edges[index1]
    EdgeList edges = G->edges[index1];
    while (edges->next){
        if(edges->index != index2){
            edges = edges->next;
        }else{                                  // when equals, find this node and set the weight
            edges->weight = weight;
            break;
        }
    }
}

size_t graph_get_edge (graph G, string vertex1, string vertex2){
    int index1, index2;
    index1 = index2 = 0;
    int num = graph_vertices_count(G);
    for (int i = 0; i < num; i++) {
        if(G->vertices[i] == vertex1){
            index1 = i;
        }
        if(G->vertices[i] == vertex2){
            index2 = i;
        }
    }
    // find the node in list of G->edges[index1]
    EdgeList edges = G->edges[index1];
    while (edges->next){
        if(edges->index != index2){
            edges = edges->next;
        }else{                                  // when equals, return this node's weight
            return edges->weight;
        }
    }
    return 0;
}

size_t graph_edges_count (graph G, string vertex){
    int index = 0;
    size_t count = 0;
    // determine the existence of the vertex
    if(!graph_has_vertex(G, vertex)){
        return 0;
    }
    for (int i = 0; i < G->nV; i++) {
        if(G->vertices[i] == vertex){
            index = i;
        }
    }
    EdgeList edges = G->edges[index];
    while (edges->next){
        edges = edges->next;
        count++;
    }
    return count;
}

void graph_pagerank(graph G, double damping, double delta, list ignore){
    int num = graph_vertices_count(G);
    // allocate num * sizeof(double) memory for these two array;
    G->oldrank = malloc(num * sizeof(double));
    G->pagerank = malloc(num * sizeof(double));
    for (int i = 0; i < num; i++){
        G->oldrank[i] = 0;
        G->pagerank[i] = 1 / num;
    }
    for(int i = 0; i < num; i++){
        while(fabs(G->pagerank[i]-G->oldrank[i]) > delta){
            for (int k = 0; k < num; k++){
                G->oldrank[k] = G->pagerank[k];
            }
            double sink_rank = 0;
            for (int j = 0; j < num; ++j) {
                // find all vertices in G that have no outbound edges, two situations
                if(!G->edges[j]->next){                 // when the EdgeList is null
                    sink_rank += (damping * (G->oldrank[j] / num));
                } else {                                // when the EdgeList is not null, but the vertex is in ignore_list
                    EdgeList edges = G->edges[j];
                    int flag = -1;
                    while (edges->next){                // traverse all edges of a certain vertex
                        if(list_contains(ignore, G->vertices[edges->index] )){
                            edges = edges->next;
                        }else{
                            flag = 0;                   // not all vertices in ignore_list, so have outbound edges
                            break;
                        }
                    }
                    if(flag == -1){                     // only when flag not change, it has no outbound edges
                        sink_rank += (damping * (G->oldrank[j] / num));
                    }
                }
            }
            for (int t = 0; t < num; t++){
                G->pagerank[t] = sink_rank + ((1 - damping) / num);
                for (int u = 0; u < num; u++) {
                    EdgeList edges = G->edges[u];
                    while (edges->next){
                        // find all vertices that have an edge to vertex with index t and this vertex not in ignore_list
                        if(edges->index == t && !list_contains(ignore, G->vertices[edges->index])){
                            G->pagerank[t] += ( (damping * G->oldrank[u]) / (int)(graph_edges_count(G, G->vertices[u])) );
                        }else{
                            edges = edges->next;
                        }
                    }
                }
            }

        }
    }
}
//                        EdgeList edges = G->edges[u]->next;
//                        while (edges){
//                            // find all vertices that have an edge to vertex with index t and this vertex not in ignore_list
//                            if(edges->index == t && !list_contains(ignore, G->vertices[edges->index])){
//
//                                if(!list_contains(ignore, G->vertices[])){
//                                    G->pagerank[t] += ( (damping * G->oldrank[u]) / (double)(graph_edges_count(G, G->vertices[u])) );
//                                }
//
//                            }// else{
//
//                            edges = edges->next;
//                        }
void graph_viewrank(graph G, FILE *file, list ignore){
    for (int i = 1; i < G->nV; i++) {
        if(!list_contains(ignore, G->vertices[i])){
            double data = G->pagerank[i];
            int j = i-1;
            while (j >= 0 && G->pagerank[j] <= data){
                if(G->pagerank[j] < data){
                    G->pagerank[j+1] = G->pagerank[j];
                    j--;
                }else if(G->pagerank[j] == data){                   // when pagerank equals, print alphabetically
                    double temp = 0;
                    //strcmp() will compare each character of two string according to the ASCII encoding
                    if(strcmp(G->vertices[j], G->vertices[i]) < 0)  // <0, G->vertices[i] < G->vertices[j], need to swap
                    {
                        temp = G->pagerank[i];
                        G->pagerank[i] = G->pagerank[j];
                        G->pagerank[j] = temp;
                    }
                }
            }
            G->pagerank[j+1] = data;
        }
    }
}


void graph_pagerank(graph G, double damping, double delta, list ignore){
    int num = graph_vertices_count(G);
    // allocate num * sizeof(double) memory for these two arrays;
    G->oldrank = (double *)calloc(num, sizeof(double));
    G->pagerank = (double *)calloc(num, sizeof(double));
    for (int i = 0; i < num; i++){
        G->oldrank[i] = 0.0;
        double x = 1.0 / num;
        G->pagerank[i] = x;
    }
    //printf("** %d %zu\n",G->edges[0]->next->index, G->edges[0]->next->weight);
    for(int i = 0; i < num; i++){
        while(fabs(G->pagerank[i]-G->oldrank[i]) > delta){
            //1
            for (int k = 0; k < num; k++){
                //if(!list_contains(ignore, G->vertices[k])){
                G->oldrank[k] = G->pagerank[k];

            }
            double sink_rank = 0;
            //2
            for (int j = 0; j < num; j++) {
                // find all vertices in G that have no outbound edges, two situations
                if(!G->edges[j]->next){                 // when the EdgeList is null
                    sink_rank += (damping * (G->oldrank[j] / num));
                    continue;
                } else {                                // when the EdgeList is not null, but the vertex is in ignore_list
                    EdgeList edges = G->edges[j]->next;
                    int flag = -1;
                    while (edges){                // traverse all edges of a certain vertex
                        if(list_contains(ignore, G->vertices[edges->index] )){
                            edges = edges->next;
                        }else{
                            flag = 0;                   // not all vertices in ignore_list, so have outbound edges
                            break;
                        }
                    }
                    if(flag == -1){                     // only when flag not change, it has no outbound edges
                        sink_rank += (damping * (G->oldrank[j] / num));
                    }
                }
            }
            //3
            for (int t = 0; t < num; t++){
                //if(!list_contains(ignore, G->vertices[t])){
                G->pagerank[t] = sink_rank + ((1 - damping) / num);
                for (int u = 0; u < num; u++) {             // I --> u
                    EdgeList edges = G->edges[u]->next;
                    while (edges){
                        // find all vertices that have an edge to vertex with index t and this vertex not in ignore_list
                        if(edges->index == t && !list_contains(ignore, G->vertices[edges->index])){
                            G->pagerank[t] += ( (damping * G->oldrank[u]) / (double)(graph_edges_count(G, G->vertices[u])) );
                        }
                        // else{
                        edges = edges->next;
                    }
                }


            }

        }
    }
}

void graph_viewrank(graph G, FILE *file, list ignore){
//    for (int i = 1; i < G->nV; i++) {
//        if(!list_contains(ignore, G->vertices[i])){
//            double data = G->pagerank[i];
//            int j = i-1;
//            while (j >= 0 && G->pagerank[j] <= data){
//                if(G->pagerank[j] < data){
//                    G->pagerank[j+1] = G->pagerank[j];
//                    j--;
//                }else if(G->pagerank[j] == data){                   // when pagerank equals, print alphabetically
//                    double temp = 0;
//                    //strcmp() will compare each character of two string according to the ASCII encoding
//                    if(strcmp(G->vertices[j], G->vertices[i]) < 0)  // <0, G->vertices[i] < G->vertices[j], need to swap
//                    {
//                        temp = G->pagerank[i];
//                        G->pagerank[i] = G->pagerank[j];
//                        G->pagerank[j] = temp;
//                    }
//                }
//            }
//            G->pagerank[j+1] = data;
//        }
//    }
    if(!file){
        for (int i = 0; i < G->nV; i++){
            fprintf(stdout, "%s (%.3lf)\n", G->vertices[i], G->pagerank[i]);
        }
    }else{
        for (int i = 0; i < G->nV; i++){
            fprintf(file, "%s (%.3lf)\n", G->vertices[i], G->pagerank[i]);
        }
    }
}

void graph_viewrank1(graph G, list ignore){
    for (int i = 0; i < G->nV; i++){
        printf("%s (%.3lf)\n", G->vertices[i], G->pagerank[i]);
    }
}

