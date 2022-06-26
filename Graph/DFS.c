#include <stdio.h>
#include <stdlib.h>
//#include "Graph.h"
#include "Graph.c"
#include "string.h"

int isDigit(char *ch){
    int i=0;
    if(ch[0]=='-'){
        i++;
    }
    for(;i< strlen(ch);i++){
        if(ch[i]>'9'||ch[i]<'0')
            return 0;
    }
    return 1;
}
int visited[1000];
void depthFirstSearch(Graph g, int src) {
    // TODO
    Vertex v;
    visited[src] = 1;
    printf("%d ",src);
    for(v=0;v<g->nV;v++){
        if(adjacent(g,src,v)&&visited[v]==0){
            visited[v] = 1;
            depthFirstSearch(g,v);
        }
    }
    return;
}
int main(void) {
    int n;
    char ch1[BUFSIZ], ch2[BUFSIZ];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph *graph = newGraph(n);

    //struct GraphRep graphRep  = newGraph(n);
    while(1){
        printf("Enter an edge (from):");
        scanf("%s", ch1);
        if(isDigit(ch1)){
            printf("Enter an edge (to):");
            scanf("%s", ch2);
            if(!isDigit(ch2)){
                printf("Done.");
                break;
            }else{
                Edge edge = {atoi(ch1), atoi(ch2)};
                insertEdge(graph, edge);
            }
        }else{
            printf("Done.\n");
            break;
        }
    }

    printf("Enter src: ");
    int src;
    scanf("%d", &src);

    printf("Depth first search starting at vertex %d: \n", src);
    depthFirstSearch(graph, src);
    printf("\n");

}