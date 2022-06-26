#include <stdio.h>
#include "Graph.h"
#include "string.h"
#include "stdlib.h"

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
void clique(Graph *graph, int n){
    int con_v[n];

    for(int i=0;i<n;i++){
        for(int x=0;x<n;x++){
            con_v[x]=-1;
        }
        for(int j=0;j<n;j++){
            if(j!=i&& adjacent(*graph,i,j)){
                con_v[j]=1;
            }
        }
        for(int k=i+1;k<n;k++){
            if(con_v[k]==1){
                for(int r=k+1;r<n;r++){
                    if(con_v[r]==1){
                        if(adjacent(*graph,k,r)){
                            printf("%d-%d-%d\n",i,k,r);
                        }
                    }
                }
            }
        }
    }
}
int main() {
    int n;
    char ch1[BUFSIZ], ch2[BUFSIZ];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    //Graph graph = newGraph(n);
    struct GraphRep *graph  = newGraph(n);
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
    printf("Show the graph:\n");
    showGraph(graph);
    int degree;
    int d[n];
    int max = -1, min = 1000;
    for(int i=0;i<n;i++){
        degree = 0;
        for(int j=0;j<n;j++){
            if(j!=i&& adjacent(graph,i,j)){
                degree++;
            }
        }
        d[i]=degree;
        if(d[i]>max){
            max = d[i];
        }
        if(d[i]<min){
            min = d[i];
        }
    }
    printf("Minimum degree: %d\n",min);
    printf("Maximum degree: %d\n",max);
    printf("Nodes of minimum degree:\n");
    for(int i=0;i<n;i++){
        if(d[i]==min){
            printf("%d\n",i);
        }
    }
    printf("Nodes of maximum degree:\n");
    for(int i=0;i<n;i++){
        if(d[i]==max){
            printf("%d\n",i);
        }
    }
    printf("Triangles:\n");
    clique(&graph,n);
    freeGraph(graph);
    return 0;
}
