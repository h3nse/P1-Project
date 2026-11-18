#include "ej-dccp.h"

void ej_dccp_main(node_t *graph, int amountOfNodes) {
    //Main help functions: Symmetric graph check, eulerian tour generator (algorithm 4.3.3 on page 242), in-out-degree calculate function, circulation problem, arc add to new graph

    //Step by step guide
    char* eulerianTour;

    if (symmetric_graph_check(graph)) {
        eulerianTour = eulerian_tour(graph);
    }
    else {
        balance_calculation(graph, amountOfNodes);
        node_t* newGraph = circulation_problem(graph);
        eulerianTour = eulerian_tour(newGraph);
    }

    print_eulerian_tour(eulerianTour);
}

int symmetric_graph_check(node_t *graph) {

}

char* eulerian_tour(node_t *graph) {

}

void print_eulerian_tour(char* eulerianTour) {

}

void balance_calculation(node_t *graph, int amountOfNodes) {
    for (int k = 0; k < amountOfNodes; k++) {
        //Graph[k].bk = Graph[k].indegree - Graph[k].outdegree
    }
}

node_t* circulation_problem(node_t *graph) {

    node_t* newGraph;
    copy_arc(newGraph);
    return newGraph;
}

void copy_arc(node_t *graph) {

}
