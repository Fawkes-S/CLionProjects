// Floyd-Warshall algorithm
// to compute all-pair shortest paths ... COMP9024 22T2
#include <stdio.h>
#include "pack/WGraph.h"

#define NODES 6
#define VERY_HIGH_VALUE 999999

int dist[NODES][NODES];
int path[NODES][NODES];

void floyd(Graph g) {
    Vertex i, s, t;
    for (s = 0; s < NODES; s++) {
        for (t = 0; t < NODES; t++) {
            if (s == t) {
                dist[s][t] = 0;
                path[s][t] = -1;
            } else {
                int w = adjacent(g,s,t);
                if (w != 0) {
                    dist[s][t] = w;
                    path[s][t] = t;
                } else {
                    dist[s][t] = VERY_HIGH_VALUE;
                    path[s][t] = -1;
                }
            }
        }
    }

    for (i = 0; i < NODES; i++)
        for (s = 0; s < NODES; s++)
            for (t = 0; t < NODES; t++)
                if (dist[s][i] + dist[i][t] < dist[s][t]) {
                    dist[s][t] = dist[s][i] + dist[i][t];
                    path[s][t] = path[s][i];
                }
}

int main(void) {
    int nE = 9;
    Graph g = newGraph(NODES);

    Edge edges[nE];
    edges[0].v = 0; edges[0].w = 1; edges[0].weight = 14;
    edges[1].v = 0; edges[1].w = 2; edges[1].weight = 9;
    edges[2].v = 0; edges[2].w = 3; edges[2].weight = 7;
    edges[3].v = 1; edges[3].w = 4; edges[3].weight = 5;
    edges[4].v = 2; edges[4].w = 1; edges[4].weight = 4;
    edges[5].v = 2; edges[5].w = 5; edges[5].weight = 3;
    edges[6].v = 3; edges[6].w = 2; edges[6].weight = 10;
    edges[7].v = 3; edges[7].w = 5; edges[7].weight = 15;
    edges[8].v = 5; edges[8].w = 4; edges[8].weight = 2;

    int i, j;
    for (i = 0; i < nE; i++) {
        insertEdge(g, edges[i]);
    }
    showGraph(g);

    floyd(g);
    printf("\ndist[][]:\n");
    for (i = 0; i < NODES; i++) {
        for (j = 0; j < NODES; j++)
            if (dist[i][j] < VERY_HIGH_VALUE)
                printf("%4d", dist[i][j]);
            else
                printf(" inf");
        putchar('\n');
    }
    printf("\npath[][]:\n");
    for (i = 0; i < NODES; i++) {
        for (j = 0; j < NODES; j++)
            printf("%4d", path[i][j]);
        putchar('\n');
    }
    freeGraph(g);

    return 0;
}