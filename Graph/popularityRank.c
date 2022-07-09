#include <stdio.h>
#include "pack/WGraph.h"
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
void insertionSort(float array[],int index[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        float element = array[i];
        int t = index[i];
        int j = i-1;
        while (j >= 0 && array[j] < element) {
            array[j+1] = array[j];
            index[j+1] = index[j];
            j--;
        }
        array[j+1] = element;
        index[j+1] = t;
    }
}

int main() {
    int n;
    char ch1[BUFSIZ], ch2[BUFSIZ];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    int degree[n][2], index[n];
    float rank[n];
    for(int i=0;i<n;i++){
        degree[i][0]=degree[i][1]= 0;
    }
    //struct GraphRep *graph  = newGraph(n);
    Graph graph = newGraph(n);
    while(1){
        printf("Enter an edge (from):");
        scanf("%s", ch1);
        if(isDigit(ch1)){
            printf("Enter an edge (to):");
            scanf("%s", ch2);
            if(!isDigit(ch2)){
                printf("Done.\n");
                break;
            }else{
                Edge edge = {atoi(ch1), atoi(ch2)};
                degree[edge.v][0]++;
                degree[edge.w][1]++;
                insertEdge(graph, edge);
            }
        }else{
            printf("Done.\n");
            break;
        }
    }
    for(int i=0;i<n;i++){
        if(degree[i][0]){
            rank[i] = degree[i][1] * 1.0 /degree[i][0];
        } else{
            rank[i] = degree[i][1] * 1.0 /0.5;
        }
        index[i] = i;
    }

    insertionSort(rank, index, n);
    printf("\nPopularity ranking:\n");
    for(int i=0;i<n;i++){
        printf("%d %.1f\n", index[i], rank[i]);
    }

    freeGraph(graph);
    return 0;
}