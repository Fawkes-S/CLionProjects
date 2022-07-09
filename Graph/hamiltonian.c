// Check existence of Hamiltonian path ... COMP9024 22T2
#include <stdio.h>
#include <stdbool.h>
#include "pack/Graph.h"

#define NODES 10

bool visited[NODES];

bool hamiltonR(Graph g, Vertex v, Vertex dest, int d) {
// v = current vertex considered
// dest = destination vertex
// d = distance "remaining" until path found

    Vertex w;
    if (v == dest) {
        return (d == 0);
    } else {
        visited[v] = true;
        for (w = 0; w < numOfVertices(g); w++) {
            if (adjacent(g, v, w) && !visited[w]) {
                if (hamiltonR(g, w, dest, d-1)) {
                    return true;
                }
            }
        }
    }
    visited[v] = false;
    return false;
}

bool hasHamiltonianPath(Graph g, Vertex src, Vertex dest) {
    Vertex v;
    int nV = numOfVertices(g);
    for (v = 0; v < nV; v++)
        visited[v] = false;
    return hamiltonR(g, src, dest, nV-1);
}

int main(void) {
    Graph g = newGraph(NODES);
    Edge e;

    e.v = 0; e.w = 1; insertEdge(g, e);
    e.v = 0; e.w = 2; insertEdge(g, e);
    e.v = 0; e.w = 5; insertEdge(g, e);
    e.v = 1; e.w = 5; insertEdge(g, e);
    e.v = 2; e.w = 3; insertEdge(g, e);
    e.v = 3; e.w = 4; insertEdge(g, e);
    e.v = 3; e.w = 5; insertEdge(g, e);
    e.v = 3; e.w = 8; insertEdge(g, e);
    e.v = 4; e.w = 5; insertEdge(g, e);
    e.v = 4; e.w = 7; insertEdge(g, e);
    e.v = 4; e.w = 8; insertEdge(g, e);
    e.v = 5; e.w = 6; insertEdge(g, e);
    e.v = 5; e.w = 7; insertEdge(g, e);
    e.v = 7; e.w = 8; insertEdge(g, e);
    e.v = 7; e.w = 9; insertEdge(g, e);
    e.v = 8; e.w = 9; insertEdge(g, e);
    printf("---------------------\n");
    showGraph(g);

    Vertex src, dest;
    printf("\nEnter source node: ");
    scanf("%d", &src);
    printf("Enter destination node: ");
    scanf("%d", &dest);

    printf("The graph has ");
    if (hasHamiltonianPath(g, src, dest))
        printf("a");
    else
        printf("no");
    printf(" Hamiltonian path from %d to %d.\n", src, dest);

    freeGraph(g);
    return 0;
}