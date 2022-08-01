#include "graph.h"
#include "list.h"
#include "dijkstra.h"
#include "stdlib.h"
#include "string.h"
typedef struct Node{
    double *a;
    double *b;
    int ed;
}Node;
typedef struct Node *sss;
int main(){
    struct Graph_Repr *graph = graph_create();
//    graph_add_vertex(graph, (string)"index");
//    graph_add_vertex(graph, (string)"A");
//    graph_add_vertex(graph, (string)"B");
//    graph_add_vertex(graph, (string)"C");
//    graph_add_vertex(graph, (string)"D");
//    graph_add_vertex(graph, (string)"A/index");
//    graph_add_vertex(graph, (string)"B/index");
//    graph_add_vertex(graph, (string)"A/A1");
//    graph_add_vertex(graph, (string)"A/A2");
//    graph_add_vertex(graph, (string)"A/A3");
//    graph_add_vertex(graph, (string)"B/B1");
//    graph_add_vertex(graph, (string)"B/B2");
//    graph_add_vertex(graph, (string)"B/B3");
//    graph_add_vertex(graph, (string)"B/B4");
//    graph_add_vertex(graph, (string)"B/B5");
//    graph_add_edge(graph, "index", "A", 1);
//    graph_add_edge(graph, "index", "B", 1);
//    graph_add_edge(graph, "index", "C", 1);
//    graph_add_edge(graph, "index", "D", 1);
//    graph_add_edge(graph, "A", "A/index", 1);
//    graph_add_edge(graph, "A", "index", 1);
//    graph_add_edge(graph, "B", "B/index", 1);
//    graph_add_edge(graph, "B", "index", 1);
//    graph_add_edge(graph, "C", "A", 1);
//    graph_add_edge(graph, "C", "B", 1);
//    graph_add_edge(graph, "C", "D", 1);
//    graph_add_edge(graph, "A/index", "A/A1", 1);
//    graph_add_edge(graph, "A/index", "A/A2", 1);
//    graph_add_edge(graph, "A/index", "A/A3", 1);
//    graph_add_edge(graph, "A/index", "A", 1);
//    graph_add_edge(graph, "A/index", "index", 1);
//    graph_add_edge(graph, "B/index", "B/B1", 1);
//    graph_add_edge(graph, "B/index", "B/B2", 1);
//    graph_add_edge(graph, "B/index", "B/B3", 1);
//    graph_add_edge(graph, "B/index", "B/B4", 1);
//    graph_add_edge(graph, "B/index", "B/B5", 1);
//    graph_add_edge(graph, "B/index", "B", 1);
//    graph_add_edge(graph, "B/index", "index", 1);
//    graph_add_edge(graph, "A/A1", "A/index", 1);
//    graph_add_edge(graph, "A/A1", "A", 1);
//    graph_add_edge(graph, "A/A1", "index", 1);
//    graph_add_edge(graph, "A/A2", "A/index", 1);
//    graph_add_edge(graph, "A/A2", "A", 1);
//    graph_add_edge(graph, "A/A2", "index", 1);
//    graph_add_edge(graph, "A/A3", "A/index", 1);
//    graph_add_edge(graph, "A/A3", "A", 1);
//    graph_add_edge(graph, "A/A3", "index", 1);
//    graph_add_edge(graph, "B/B5", "B", 1);

    /**
     * situation 2
     */
//    graph_add_vertex(graph, (string)"index");
//    graph_add_vertex(graph, (string)"X");
//    graph_add_vertex(graph, (string)"Y");
//    graph_add_vertex(graph, (string)"Z");
//    graph_add_edge(graph, "index", "X", 1);
//    graph_add_edge(graph, "index", "Y", 1);
//    graph_add_edge(graph, "index", "Z", 1);
//    graph_add_edge(graph, "X", "index", 1);
//    graph_add_edge(graph, "Y", "index", 1);

    /**
     * situation 3
     */
//    graph_add_vertex(graph, (string)"x");
//    graph_add_vertex(graph, (string)"a");
//    graph_add_vertex(graph, (string)"b");
//    graph_add_vertex(graph, (string)"c");
//    graph_add_vertex(graph, (string)"d");
//    graph_add_vertex(graph, (string)"e");
//    graph_add_edge(graph, "x", "a", 1);
//    graph_add_edge(graph, "x", "c", 1);
//    graph_add_edge(graph, "a", "d", 1);
//    graph_add_edge(graph, "b", "e", 1);
//    graph_add_edge(graph, "c", "b", 1);
//    graph_add_edge(graph, "d", "e", 1);

    /**
     * situation 4
     */
    graph_add_vertex(graph, (string)"x");
    graph_add_vertex(graph, (string)"a");
    graph_add_vertex(graph, (string)"b");
    graph_add_vertex(graph, (string)"c");
    graph_add_vertex(graph, (string)"d");
    graph_add_vertex(graph, (string)"e");
    graph_add_vertex(graph, (string)"f");
    graph_add_vertex(graph, (string)"g");
    graph_add_vertex(graph, (string)"h");
    graph_add_vertex(graph, (string)"i");

    graph_add_edge(graph, "x", "a", 1);
    graph_add_edge(graph, "a", "b", 1);
    graph_add_edge(graph, "a", "c", 1);
    graph_add_edge(graph, "a", "h", 1);
    graph_add_edge(graph, "b", "e", 1);
    graph_add_edge(graph, "c", "d", 1);
    graph_add_edge(graph, "h", "i", 1);
    graph_add_edge(graph, "e", "f", 1);
    graph_add_edge(graph, "d", "f", 1);
    graph_add_edge(graph, "i", "f", 1);
    graph_add_edge(graph, "f", "g", 1);

    //graph_show1(graph);
    list ignore = list_create();
    list_add(ignore,"g");
    //list_add(ignore,"c");

//    double damping = 0.85;
//    double delta = 0.00001;
//    graph_pagerank(graph,damping,delta,ignore);
//    graph_viewrank1(graph, ignore);

    graph_shortest_path(graph, "x",ignore);
    graph_view_path(graph, "g",ignore);
}