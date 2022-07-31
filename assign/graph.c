#include "graph.h"
#include <stdlib.h>
#include "string.h"
#include "math.h"
//#include "dijkstra.h"
//#include "pagerank.h"

// define a very large number
#define HIGH_VALUE 999999
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

typedef struct Graph_Repr {
    EdgeList *edges;       // an array which store linked list of adjacency vertices
    Vertex *vertices;      // an array which store all vertices
    double *oldrank;
    double *pagerank;      // two double arrays for calculation of pagerank
    int  *numE;           // array of number of edges of the shortest path from source
    int  *pred;           // array of predecessor in the shortest path from source
    int    nV;             // #vertices
    int    nE;             // #edges
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
                fprintf(stdout, "%s\n", G->vertices[i]);
            }
        }
        // output edges
        for (int i = 0; i < len; i++) {
            //ListNode *node = G->edges[i];
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
    int num = graph_vertices_count(G);   // get the number of vertexes
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

    int num = graph_vertices_count(G);
    // when add a new vertex, allocate memory for G->vertexes
    //G->vertices = realloc(G->vertices, (num+1) * sizeof(string));
    if(num == 0){
        G->vertices = malloc(sizeof(string *));
        G->vertices[0] = malloc(size);
        G->edges = malloc(sizeof(ListNode *));
        G->edges[0] = calloc(1,sizeof(ListNode));
        G->edges[0]->next = NULL;
    }else{
        G->vertices = realloc(G->vertices,  (num+1) * sizeof(string *));
        G->vertices[num] = malloc(size);
        G->edges = realloc(G->edges, (num+1) * sizeof(ListNode *));
        G->edges[num] = calloc(1, sizeof(ListNode));       // every new list have a null head node
        G->edges[num]->next = NULL;
    }
    if(!G->vertices|| !G->edges ){
        return;
    }
    strcpy(G->vertices[num],  vertex);
    G->nV++;
}

bool graph_has_vertex (graph G, string vertex){
    if(!G){
        return false;
    }
    for (int i = 0; i < G->nV; i++) {
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
    // determine the existence of these two vertices
    if(!graph_has_vertex(G, vertex1) || !graph_has_vertex(G, vertex2)){
        return;
    }
    int index1, index2;
    index1 = index2 = 0;
    int len = graph_vertices_count(G);      // get the number of vertexes
    for (int i = 0; i < len; i++) {         // get the index of the corresponding string vertex.
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
    // create a new List Node, and add it at the beginning of the list
//    ListNode *listNode = makeListNode(index2, weight);
//    EdgeList edges = G->edges[index1];
//    while (edges->next){
//        edges = edges->next;
//    }
//    edges->next = listNode;
//    G->edges[index1] = edges;
    //=====
    ListNode *listNode = makeListNode(index2, weight);
    EdgeList edges = G->edges[index1];
    EdgeList edges_cpy = G->edges[index1]->next;
    while (edges_cpy){
        edges = edges_cpy;
        edges_cpy = edges_cpy->next;
    }
    listNode->next = edges->next;
    edges->next = listNode;
    //=====

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
    for (int i = 0; i < G->nV; i++) {
        if(!strcmp(G->vertices[i], vertex)){
            index = i;
        }
    }
    EdgeList edges = G->edges[index]->next;
    while (edges){
        edges = edges->next;
        count++;
    }
    return count;
}

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
    int num = graph_vertices_count(G);
    // allocate num * sizeof(double) memory for these two arrays;
    G->oldrank = (double *)calloc(num, sizeof(double));
    G->pagerank = (double *)calloc(num, sizeof(double));
    int c = 0;
    for (int i = 0; i < num; i++) {
        if(list_contains(ignore, G->vertices[i])){
            c++;
        }
    }
    int num_af;
    num_af = num - c;
    for (int i = 0; i < num; i++){
        if(!list_contains(ignore, G->vertices[i])){
            G->oldrank[i] = 0.0;
            G->pagerank[i] = 1.0 / num_af;
        }
    }
//    for (int i = 0; i < num; ++i) {
//        printf("@@@%lf\t", G->pagerank[i]);
//    }
    //printf("** %d %zu\n",G->edges[0]->next->index, G->edges[0]->next->weight);
    for(int i = 0; i < num; i++){
        while(fabs(G->pagerank[i]-G->oldrank[i]) > delta && !list_contains(ignore, G->vertices[i])){ //&& !list_contains(ignore, G->vertices[i])
            //1
            for (int k = 0; k < num; k++){
                if(!list_contains(ignore, G->vertices[k])) {               //!!!!!!!
                    G->oldrank[k] = G->pagerank[k];
                }
            }
            double sink_rank = 0;
            //2
            for (int j = 0; j < num; j++) {
                if(!list_contains(ignore, G->vertices[j])){
                    // find all vertices in G that have no outbound edges, two situations
                    if(!G->edges[j]->next){                 // when the EdgeList is null
                        sink_rank += (damping * (G->oldrank[j] / num_af));
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
                            sink_rank += (damping * (G->oldrank[j] / num_af));
                        }
                    }
                }

            }
            //3
//            for (int j = 0; j < num; ++j) {
//                printf("~~%s\t",G->vertices[j]);
//            }
            for (int t = 0; t < num; t++){
                if(!list_contains(ignore, G->vertices[t])){
                    G->pagerank[t] = sink_rank + ((1 - damping) / num_af);
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
//        for (int i = 1; i < G->nV; i++) {
//                double data = G->pagerank[i];
//                int j = i-1;
//                while (j >= 0 && G->pagerank[j] <= data){
//                    if(G->pagerank[j] < data){
//                        G->pagerank[j+1] = G->pagerank[j];
//                        j--;
//                    }else if(G->pagerank[j] == data){                   // when pagerank equals, print alphabetically
//                        double temp = 0;
//                        //strcmp() will compare each character of two string according to the ASCII encoding
//                        if(strcmp(G->vertices[index[j]], G->vertices[index[i]]) >0)  // <0, G->vertices[j] < G->vertices[i], need to swap
//                        {
//                            temp = G->pagerank[i];
//                            G->pagerank[i] = G->pagerank[j];
//                            G->pagerank[j] = temp;
//                        }
//                        j--;
//                    }
//                }
//                G->pagerank[j+1] = data;
//
//    }
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

//    for (int i = 0; i < G->nV; ++i) {
//        printf("start: %d, " ,index[i]);
//    }
//    printf("\n");
    for (int i = 0; i < G->nV; i++){
        if(!list_contains(ignore, G->vertices[index[i]])) {
            printf("%s (%.3lf)\n", G->vertices[index[i]], G->pagerank[i]);
        }
    }
}

void graph_shortest_path(graph G, string source, list ignore){
    int num = G->nV;
    int inSource = 0;           // index of source in G->vertices
//    int  numE[num];           // array of number of edges of the shortest path from source
//    int  pred[num];           // array of predecessor in the shortest path from source
    G->numE = calloc(num, sizeof(int));
    G->pred = calloc(num, sizeof(int));

    // create a linked list to store all vertices for the following judgement and removal, function which is similar to vSet
    //list vSet = list_create();
    bool vSet[num];

    for (int i = 0; i < num; i++){
        //list_add(vSet, G->vertices[i]);           // add non-repeating vertices at the end of vSet
        G->numE[i] = HIGH_VALUE;
        G->pred[i] = -1;
        vSet[i] = true;
        if(!strcmp(G->vertices[i], source)){
            inSource = i;
        }
    }
    G->inSource = inSource;
    G->numE[inSource] = 0;
    /* --------- */

    // only when sum = 0, all vertices in vSet has been processed, or continue the loop
    int sum = 0;
    do {
        // Get the sum of elements of vSet. Every loop sum return to 0
        sum = 0;
        for (int j = 0; j < num; j++){
            sum += vSet[j];
        }
        // when v ∈ vSet, find the minimum numE[v]
        int min = HIGH_VALUE;
        int minIn = 0;
        for (int i = 0; i < num; i++){
            if( G->numE[i] < min && vSet[i]){
                minIn = i;
                min = G->numE[i];
            }
        }

        // this loop is to find excepted the shortest path when there are multiple shortest paths at the same time
        for (int i = 0; i < num; i++) {
            int pathT1[num],pathT2[num];
            if( min == G->numE[i] && i != minIn && vSet[i]){
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
                //
//                for (int j = 0; j < in1; ++j) {
//                    printf("!! %d \t!!",pathT1[j]);
//                }
//                for (int j = 0; j < in2; ++j) {
//                    printf("!! %d\n!!",pathT2[j]);
//                }

                // when index of the second vertex of this path is smaller, choose it!
                if(secI < secMin){
                    min = G->numE[i];
                    minIn = i;
                }
                else if(secI == secMin){
                    // when index of the second vertex of these two paths are equally, Traverse two paths until different vertices appear.
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
            if(t != minIn && graph_has_edge(G, G->vertices[minIn], G->vertices[t])){
                if( (G->numE[minIn] + 1) < G->numE[t]){
                    G->numE[t] = G->numE[minIn] + 1;
                    G->pred[t] = minIn;
                }
            }
        }
        vSet[minIn] = false;
    } while (sum != 0);

//    printf("output numE and pred\n");
//    for (int i = 0; i < G->nV; ++i) {
////        printf("index: %s, numE: %d, pred: %s\n", G->vertices[i], G->numE[i], G->vertices[G->pred[i]]);
//        printf("index: %d, numE: %d, pred: %d\n", i, G->numE[i], G->pred[i]);
//    }

}

void graph_view_path(graph G, string destination, list ignore){
    int  path[G->nV];
    int inDes = 0;                    // index of destination in G->vertices
    for (int i = 0; i < G->nV; i++) {
        if(!strcmp(G->vertices[i], destination)){
            inDes = i;
        }
    }

    if(G->pred[inDes] == -1 && inDes == G->inSource){
        printf("%s\n%s", G->vertices[G->inSource], G->vertices[inDes]);
    }else{
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
//        printf("j: %d\n",j);
//        for (int i = 0; i <= j; ++i) {
//            printf("path: %d\t", path[i]);
//        }
//        printf("\n");

        while(j >= 0){
            printf("%s\n", G->vertices[path[j]]);
            j--;
        }
    }
}
