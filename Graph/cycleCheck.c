#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
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
int dfsCycleCheck(Graph graph,Vertex v1,Vertex v2){
    visited[v1] = true;
    Vertex v3;
    for(v3=0;v3<numOfVertices(graph);v3++){
        if(adjacent(graph,v1,v3)){
            if(!visited[v3]){
                if(dfsCycleCheck(graph,v3,v1))
                    return true;
            }else if(v3!=v2){   //exclude
                return true;
            }
        }
    }
    return false;
}

bool hasCycle(Graph graph, int num) {
    int v;
    for(v=0;v<num;v++)
        visited[v] = false;
    for(v=0;v<num;v++)
        if(!visited[v])
            if(dfsCycleCheck(graph,v,v))
                return true;        //can find cycle
    return false;
}

int main() {
    int n;
    char ch1[BUFSIZ], ch2[BUFSIZ];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    //struct GraphRep *graph  = newGraph(n);
    Graph graph = newGraph(n);
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
    if(hasCycle(graph, n)){
        printf("The graph has a cycle.");
    }else{
        printf("The graph is acyclic.");
    }
    freeGraph(graph);
    return 0;
}