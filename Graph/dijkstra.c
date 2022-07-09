#include <stdio.h>
#include <stdbool.h>
#include "pack/PQueue.h"

#define VERY_HIGH_VALUE 999999

void dijkstraSSSP(Graph g, Vertex source) {
    int  dist[MAX_NODES];
    int  pred[MAX_NODES];
    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
    int s;

    PQueueInit();
    int nV = numOfVertices(g);
    for (s = 0; s < nV; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        pred[s] = -1;
        vSet[s] = true;
    }
    dist[source] = 0;
    /* --------- */
    while(!PQueueIsEmpty()){
        Vertex min = leavePQueue(dist);
        for(int t=0;t<nV;t++){
            if(t!=min && adjacent(g,min,t)){
                if(dist[min]+adjacent(g,min,t)<dist[t]){ //??adjacent(g,s,t)==weight
                    dist[t]=dist[min]+adjacent(g,min,t);
                    pred[t]=min;
                }
            }
        }
        vSet[min]=false;
    }
    for (int i = 0; i < nV; ++i) {
        if(vSet[i]==true){
            printf("ERROR!");
        }
    }
    int  path[MAX_NODES];
    for(int i=0;i<nV;i++){
        if(pred[i]==-1 && i!=source){
            printf("%d: no path", i);
        }else if(pred[i]==-1 && i==source){
            printf("%d: distance = %d, shortest path: %d", i,dist[i],source);
        }else{
            printf("%d: distance = %d, shortest path: ", i,dist[i]);
            path[0] =i;
            Vertex last =pred[i];
            path[1] =last;
            int j;
            for (j=2; last!=source; j++) {
                last = pred[last];
                path[j]=last;
            }
            j--;
            while (j>=0){
                if(j==0){
                    printf("%d", path[j]);
                } else{
                    printf("%d-", path[j]);
                }
                j--;
            }

        }
        printf("\n");
    }
    /* --------- */
}

void reverseEdge(Edge *e) {
    Vertex temp = e->v;
    e->v = e->w;
    e->w = temp;
}

int main(void) {
    Edge e;
    int  n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        reverseEdge(&e);               // ensure to add edge in both directions
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");

    dijkstraSSSP(g, source);
    freeGraph(g);
    return 0;
}