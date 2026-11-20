#include <assert.h>
#include "project.h"
#include "cpp.h"
#include "graphGenerator.h"

node_t* test_graph();
void test_graph_generation();


int main(void)
{
    test_graph_generation();


    // Test Dijkstras
    const int amountOfNodes = 5;
    node_t nodeGraph[amountOfNodes];
    node_t srcNode = nodeGraph[0];
    node_t destNode = nodeGraph[amountOfNodes-1];
    dijkstra(nodeGraph, amountOfNodes, srcNode, destNode);
    return 0;
}

node_t* test_graph() {

    node_t* graph = calloc(7,sizeof(node_t));

    if (graph == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    add_edge(0,1,graph);
    add_edge(1,2,graph);
    add_edge(2,3,graph);
    add_edge(3,2,graph);
    add_edge(1,6,graph);
    add_edge(1,5,graph);
    add_edge(6,0,graph);
    add_edge(6,5,graph);
    add_edge(5,4,graph);
    add_edge(4,5,graph);
    add_edge(4,2,graph);

    graph[0].id = 0;
    graph[1].id = 1;
    graph[2].id = 2;
    graph[3].id = 3;
    graph[4].id = 4;
    graph[5].id = 5;
    graph[6].id = 6;

    return graph;
}

void test_graph_generation() {

    node_t* graph = test_graph();

    run_Tarjans_algorithm(graph,7);
    run_modified_Tarjans_algorithm(graph,7);
    run_Tarjans_algorithm(graph,7);
}

