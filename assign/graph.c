#include "graph.h"
#include <stdlib.h>
#include "string.h"
#include "math.h"

#define HIGH_VALUE 999999           // define a very large number

typedef string Vertex;              // vertices are strings

typedef struct List_Node{
    int index;                      // value
    size_t weight;
    struct List_Node *next;         // pointer
}ListNode, * EdgeList;
/* both are struct pointer type
 * generally, ListNode emphasize pointer variables of any node
 * while EdgeList emphasize the header pointer of a linked list
 */

typedef struct Graph_Repr {
    EdgeList *edges;       // an array which store linked list of adjacency vertices
    Vertex *vertices;      // an array which store all vertices
    double *oldrank;
    double *pagerank;      // two double arrays for calculation of pagerank
    int  *numE;            // array of number of edges of the shortest path from source
    int  *pred;            // array of predecessor in the shortest path from source
    int    nV;             // vertices
    int    nE;             // edges
    int inSource;          // index of source in G->vertices
} Graph_Repr;

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
    // allocate memory for a graph
    graph G = malloc(sizeof(Graph_Repr));
    if(!G){
        return NULL;
    }
    G->nV = 0;
    G->nE = 0;
    return G;
}

// free the linked list
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
    free(G->pagerank);
    free(G->oldrank);
    free(G->numE);
    free(G->pred);
    free(G);
}

void graph_show (graph G, FILE *file, list ignore){
    if(!G){
        return;
    }
    int len = G->nV;                     // get the number of vertexes
    if(!file){                           // when file is null, print to stdout
        // output the name of each vertex which is not in ignore_list
        for (int i = 0; i < len; i++) {
            if(!list_contains(ignore, G->vertices[i])){       // G->vertices[i] not in ignore_list
                fprintf(stdout, "%s\n", G->vertices[i]);
            }
        }
        // output edges
        for (int i = 0; i < len; i++) {
            EdgeList edges = G->edges[i]->next;
            if(!list_contains(ignore, G->vertices[i])){
                while (edges){
                    int i_vertices = edges->index;
                    if(!list_contains(ignore, G->vertices[i_vertices])){
                        fprintf(file, "%s %s %zu\n", G->vertices[i], G->vertices[i_vertices], edges->weight);
                    }
                    edges = edges->next;
                }
            }
        }
    }else{                              // when file is not null, print to file
        // output the name of each vertex which is not in ignore_list
        for (int i = 0; i < len; i++) {
            if(!list_contains(ignore, G->vertices[i])){       // G->vertices[i] not in ignore_list
                fprintf(file, "%s\n", G->vertices[i]);
            }
        }
        // output edges
        for (int i = 0; i < len; i++) {
            EdgeList edges = G->edges[i]->next;
            if(!list_contains(ignore, G->vertices[i])){
                while (edges){
                    int i_vertices = edges->index;
                    if(!list_contains(ignore, G->vertices[i_vertices])){
                        fprintf(file, "%s %s %zu\n", G->vertices[i], G->vertices[i_vertices], edges->weight);
                    }
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
    int num = G->nV;   // get the number of vertexes
    // output the name of each vertex
    for (int i = 0; i < num; i++) {
        printf("\t%s\n", G->vertices[i]);
    }
    // output edges
    for (int i = 0; i < num; i++) {
        //ListNode *node = G->edges[i];
        EdgeList edges = G->edges[i]->next;
        while (edges){
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
    size_t size = strlen(vertex) + 1;
    int num = G->nV;

    // when add a new vertex, allocate memory for G->vertexes and G->edges
    if(num == 0){
        G->vertices = malloc(sizeof(string *));
        G->vertices[0] = malloc(size);                                          // allocate one size to each element so that it can be assigned a value by strcpy
        G->edges = malloc(sizeof(ListNode *));
        G->edges[0] = calloc(1,sizeof(ListNode));
        G->edges[0]->next = NULL;
    }else{
        // num > 0, allocate more enough memory for two arrays
        G->vertices = realloc(G->vertices,  (num+1) * sizeof(string *));
        G->vertices[num] = malloc(size);
        G->edges = realloc(G->edges, (num+1) * sizeof(ListNode *));
        G->edges[num] = calloc(1, sizeof(ListNode));       // every new list have a null head node
        G->edges[num]->next = NULL;
    }
    if(!G->vertices|| !G->edges ){
        return;
    }
    // string assignment. NO "="
    strcpy(G->vertices[num],  vertex);
    G->nV++;
}

bool graph_has_vertex (graph G, string vertex){
    if(!G){
        return false;
    }
    for (int i = 0; i < G->nV; i++) {
        // strcmp() = 0, two arguments are equally, which means there are vertex in G->vertices
          if(!strcmp(G->vertices[i], vertex)){
            return true;
        }
    }
    return false;
}

size_t graph_vertices_count (graph G){
    return G->nV;
}

void graph_add_edge (graph G, string vertex1, string vertex2, size_t weight){
    // firstly, determine the existence of these two vertices
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return;
    }
    int index1, index2;
    index1 = index2 = 0;
    int len = graph_vertices_count(G);         // get the number of vertexes
    for (int i = 0; i < len; i++) {            // get the index of the corresponding string vertex.
        if(!strcmp(G->vertices[i], vertex1)){
            index1 = i;
        }
        if(!strcmp(G->vertices[i], vertex2)){
            index2 = i;
        }
    }
    // determine whether this edge already exists
    if(graph_has_edge(G, vertex1, vertex2)){
        return;
    }
    // create a new List Node, and add it at the end of the list
    ListNode *listNode = makeListNode(index2, weight);
    EdgeList edges = G->edges[index1];
    EdgeList edges_cpy = G->edges[index1]->next;
    while (edges_cpy){
        edges = edges_cpy;
        edges_cpy = edges_cpy->next;
    }
    listNode->next = edges->next;
    edges->next = listNode;

    G->nE++;
}

bool graph_has_edge (graph G, string vertex1, string vertex2){
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return false;
    }
    int index1, index2;
    index1 = index2 = 0;
    for (int i = 0; i < G->nV; i++) {
        if(!strcmp(G->vertices[i], vertex1)){
            index1 = i;
        }
        if(!strcmp(G->vertices[i], vertex2)){
            index2 = i;
        }
    }
    // determine string vertex2 whether in list of G->edges[index1]
    EdgeList edges = G->edges[index1]->next;
    while (edges){
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
        if(!strcmp(G->vertices[i], vertex1)){
            index1 = i;
        }
        if(!strcmp(G->vertices[i], vertex2)){
            index2 = i;
        }
    }
    // find the node in list of G->edges[index1]
    EdgeList edges = G->edges[index1]->next;
    while (edges){
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
        if(!strcmp(G->vertices[i], vertex1)){
            index1 = i;
        }
        if(!strcmp(G->vertices[i], vertex2)){
            index2 = i;
        }
    }
    // find the node in list of G->edges[index1]
    EdgeList edges = G->edges[index1]->next;
    while (edges){
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
    // find index of this vertex in G->vertices
    for (int i = 0; i < G->nV; i++) {
        if(!strcmp(G->vertices[i], vertex)){
            index = i;
        }
    }
    EdgeList edges = G->edges[index]->next;
    // length of list is the number of edges
    while (edges){
        edges = edges->next;
        count++;
    }
    return count;
}

// remove vertices in ignore_list, then get number of edges
size_t graph_edges_count_ignore (graph G, string vertex, list ignore){
    int index = 0;
    size_t count = 0;
    // determine the existence of the vertex
    if(!graph_has_vertex(G, vertex)){
        return 0;
    }
    for (int i = 0; i < G->nV; i++) {
        if(!strcmp(G->vertices[i], vertex)){
            index = i;
        }
    }
    EdgeList edges = G->edges[index]->next;
    while (edges){
        if(!list_contains(ignore, G->vertices[edges->index])){
            count++;
        }
        edges = edges->next;
    }
    return count;
}

void graph_pagerank(graph G, double damping, double delta, list ignore){
    int num = G->nV;
    // allocate num * sizeof(double) memory for these two arrays;
    G->oldrank = (double *)calloc(num, sizeof(double));
    G->pagerank = (double *)calloc(num, sizeof(double));
    for (int i = 0; i < num; i++) {
        if(list_contains(ignore, G->vertices[i])){
            num--;
        }
    }

    for (int i = 0; i < num; i++){
        if(!list_contains(ignore, G->vertices[i])){
            G->oldrank[i] = 0.0;
            G->pagerank[i] = 1.0 / num;
        }
    }

    for(int i = 0; i < num; i++){
        while(fabs(G->pagerank[i]-G->oldrank[i]) > delta && !list_contains(ignore, G->vertices[i])){
            for (int k = 0; k < num; k++){
                if(!list_contains(ignore, G->vertices[k])) {
                    G->oldrank[k] = G->pagerank[k];
                }
            }
            double sink_rank = 0;
            for (int j = 0; j < num; j++) {
                if(!list_contains(ignore, G->vertices[j])){
                    // find all vertices in G that have no outbound edges, two situations
                    if(!G->edges[j]->next){                 // when the EdgeList is null
                        sink_rank += (damping * (G->oldrank[j] / num));
                    } else {                                // when the EdgeList is not null, but the vertex is in ignore_list
                        EdgeList edges = G->edges[j]->next;
                        int flag = -1;
                        while (edges){                     // traverse all edges of a certain vertex
                            if(list_contains(ignore, G->vertices[edges->index]) ){
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

            }
            for (int t = 0; t < num; t++){
                if(!list_contains(ignore, G->vertices[t])){
                    G->pagerank[t] = sink_rank + ((1 - damping) / num);
                    for (int u = 0; u < num; u++) {             // I --> u
                        if(!list_contains(ignore, G->vertices[u]) ){
                            if(graph_has_edge(G, G->vertices[u], G->vertices[t])){
                                G->pagerank[t] += ( (damping * G->oldrank[u]) / (double)(graph_edges_count_ignore(G, G->vertices[u],ignore)) );
                            }
                        }
                    }

                }
            }

        }
    }
}

void graph_viewrank(graph G, FILE *file, list ignore){
    int num = G->nV;
    int index[num];
    for (int i = 0; i < num; i++) {
        index[i] = i;
    }

    // bubbleSort
    for(int i=0; i < num - 1; i++){                                                                 // control rounds
        for(int j=0; j < num - i - 1; j++){
            // when two vertices have the same rank, print alphabetically (strcmp)
            if(G->pagerank[j] < G->pagerank[j+1] || (G->pagerank[j] == G->pagerank[j+1] && strcmp(G->vertices[index[j+1]], G->vertices[index[j]]) < 0) ){
                double temp = G->pagerank[j];
                G->pagerank[j] = G->pagerank[j+1];
                G->pagerank[j+1] = temp;
                int in = index[j];
                index[j] = index[j+1];
                index[j+1] = in;
            }
        }
    }

    if(!file){
        for (int i = 0; i < num; i++){
            if(!list_contains(ignore, G->vertices[index[i]])) {
                fprintf(stdout, "%s (%.3lf)\n", G->vertices[index[i]], G->pagerank[i]);
            }
        }
    }else{
        for (int i = 0; i < num; i++){
            if(!list_contains(ignore, G->vertices[index[i]])) {
                fprintf(file, "%s (%.3lf)\n", G->vertices[index[i]], G->pagerank[i]);
            }
        }
    }

}

void graph_viewrank1(graph G, list ignore){
    int num = G->nV;
    int index[num];
    for (int i = 0; i < num; i++) {
        index[i] = i;
    }
    for(int i=0; i < num - 1; i++){// control rounds
        for(int j=0; j < num - i - 1; j++){
            if(G->pagerank[j] < G->pagerank[j+1] || (G->pagerank[j] == G->pagerank[j+1] && strcmp(G->vertices[index[j+1]], G->vertices[index[j]]) < 0) ){
                double temp = G->pagerank[j];
                G->pagerank[j] = G->pagerank[j+1];
                G->pagerank[j+1] = temp;
                int in = index[j];
                index[j] = index[j+1];
                index[j+1] = in;
            }
        }
    }

    for (int i = 0; i < G->nV; i++){
        if(!list_contains(ignore, G->vertices[index[i]])) {
            printf("%s (%.3lf)\n", G->vertices[index[i]], G->pagerank[i]);
        }
    }
}

void graph_shortest_path(graph G, string source, list ignore){
    int num = G->nV;
    int inSource = 0;                   // index of source in G->vertices
    // allocate num * sizeof(int) memory, and initial value is null
    G->numE = calloc(num, sizeof(int));
    G->pred = calloc(num, sizeof(int));
    bool vSet[num];                    // vSet[v] = true <=> v has not been processed

    for (int i = 0; i < num; i++){
        G->numE[i] = HIGH_VALUE;
        G->pred[i] = -1;
        vSet[i] = true;
        if(!strcmp(G->vertices[i], source)){
            inSource = i;
        }
    }
    G->inSource = inSource;
    G->numE[inSource] = 0;

    // ignore vertices in ignore_list, mark them false in vSet in advance
    for (int i = 0; i < num; ++i) {
        if(list_contains(ignore, G->vertices[i])){
           vSet[i] = false;
        }
    }

    // only when sum = 0, all vertices in vSet has been processed, or continue the loop
    int sum;
    do {
        // Get the sum of elements of vSet. Every loop sum return to 0
        sum = 0;
        for (int j = 0; j < num; j++){
            sum += vSet[j];
        }
        // when v ∈ vSet, find the minimum numE[v]
        int min = HIGH_VALUE;
        int minIn = -1;
        for (int i = 0; i < num; i++){
            if( G->numE[i] < min && vSet[i]){
                minIn = i;
                min = G->numE[i];
            }

        }
        // cannot find the minimum value, there is no connection path.
        if(minIn == -1){
            break;
        }

        // this loop is to find excepted the shortest path when there are multiple shortest paths at the same time
        for (int i = 0; i < num; i++) {
            // pathT1 and pathT2 are to record the path form the next vertex of source to vertex which have the same num of edges
            int pathT1[num],pathT2[num];
            if( min == G->numE[i] && i != minIn && vSet[i] && min != HIGH_VALUE){
                int secMin = minIn;
                // the next vertex index to backtrack to the start of this path.
                int in1, in2;
                in1 = in2 = 1;
                pathT1[0] = secMin;
                pathT2[0] = i;
                while (inSource != G->pred[secMin]){
                    secMin =G->pred[secMin];
                    pathT1[in1] = secMin;
                    in1++;
                }
                int secI = i;
                while (inSource != G->pred[secI]){
                    secI =G->pred[secI];
                    pathT2[in2] = secI;
                    in2++;
                }

                // when index of the second vertex of this path is smaller,  choose it!
                if(secI < secMin){
                    min = G->numE[i];
                    minIn = i;
                }
                // when index of the second vertex of these two paths are equally, traverse two paths until different vertices appear.
                else if(secI == secMin){
                    in1--;
                    in2--;
                    while (pathT1[in1]==pathT2[in2] && in1 >= 0 && in2 >=0){
                        in1--;
                        in2--;
                    }
                    if(pathT1[in1] < pathT2[in2]){
                        min = G->numE[pathT1[0]];
                        minIn = pathT1[0];
                    }else{
                        min = G->numE[pathT2[0]];
                        minIn = pathT2[0];
                    }
                }
            }
        }

        for (int t = 0; t < num; t++){
            if(!list_contains(ignore, G->vertices[t])){
                if(t != minIn && graph_has_edge(G, G->vertices[minIn], G->vertices[t])){
                    if( (G->numE[minIn] + 1) < G->numE[t]){
                        G->numE[t] = G->numE[minIn] + 1;
                        G->pred[t] = minIn;
                    }
                }
            }
        }
        vSet[minIn] = false;
    } while (sum != 0);

}

void graph_view_path(graph G, string destination, list ignore){
    int inDes = 0;                    // index of destination in G->vertices
    int num = G->nV;
    int  path[num];                   // a path array to restore the shortest path by pred

    for (int i = 0; i < num; i++) {
        if(!strcmp(G->vertices[i], destination)){
            inDes = i;
        }
    }

    if(G->pred[inDes] == -1 && inDes == G->inSource){                                // no vertex between source and destination
        printf("%s\n%s", G->vertices[G->inSource], G->vertices[inDes]);
    }else if(G->pred[inDes] != -1){                                                  // some vertices between source and destination
        path[0] = inDes;
        int lastIn = G->pred[inDes];
        path[1] = lastIn;
        int j = 2;
        while(lastIn != G->inSource) {
            lastIn = G->pred[lastIn];
            path[j] = lastIn;
            j++;
        }
        j--;

        while(j >= 0){                                                              // print G->vertices[path[]], path[] includes all indexes of the correct path
            printf("%s\n", G->vertices[path[j]]);
            j--;
        }
    }
}
