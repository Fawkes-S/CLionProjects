#include "graph.h"

int main(){
    struct Graph_Repr *graph = graph_create();
    graph_add_vertex(graph, (string)"a");
    graph_add_vertex(graph, (string)"b");
    graph_add_vertex(graph, (string)"c");
    graph_add_vertex(graph, (string)"d");
    graph_add_edge(graph,(string)"a",(string)"b",10);
    size_t a = graph_get_edge(graph,(string)"a",(string)"b");

    graph_add_edge(graph,(string)"b",(string)"a",18);
    //graph_set_edge(graph,(string)"a",(string)"b",50);
    //graph_show(graph);
    graph_add_edge(graph,(string)"a",(string)"c",89);
    graph_add_edge(graph,(string)"a",(string)"d",11);
    graph_add_edge(graph,(string)"b",(string)"c",167);
    size_t count = graph_edges_count(graph, (string)"a");
    graph_show(graph);
    printf("degree : %d", count);
    graph_destroy(graph);



}