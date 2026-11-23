#include "ej-dcpp.h"

void ej_dcpp_main(node_t *graph, int amountOfNodes) {
    //Main help functions: Symmetric graph check, eulerian tour generator (algorithm 4.3.3 on page 242), in-out-degree calculate function, circulation problem, arc add to new graph

    //Step by step guide
    char* eulerianTour;

    if (symmetric_digraph_check(graph)) {
        eulerianTour = eulerian_tour(graph, amountOfNodes);
    }
    else {
        balance_calculation(graph, amountOfNodes);
        node_t* newGraph = circulation_problem(graph);
        eulerianTour = eulerian_tour(newGraph, amountOfNodes);
        free(newGraph);
    }

    print_eulerian_tour(eulerianTour);
}

// Checks if the digraph is symmetric: the indegree and outdegree of every vertex are equal.
int symmetric_digraph_check(node_t *graph) {
    return 0;
}

// Creates a eulerian tour on a eulerian digraph
char* eulerian_tour(node_t *eulerianDigraph, int amountOfNodes) {
    srand(time(NULL));

    // Might not be used
    // node_t *intree = malloc(sizeof(node_t) * amountOfNodes);
    // if (intree == NULL) {
    //     printf("Not enough memory for intree generation!");
    //     exit(EXIT_FAILURE);
    // }

    char *eulerianTour;
    node_t vertexStart = eulerianDigraph[rand()%amountOfNodes]; // Chooses an arbitrary vertex to start intree from

    // Generate intree
    recursive_intree_constructor(vertexStart);

    // For loop that labels each vertex w in the graph consecutively following this rule:
    // Label all out-arcs from w in the graph consecutively. This can be done at random: 1, 2, 3...
    // The largest label number must be placed at the arc used in the intree
    // Lastly label the out arcs from vertexStart randomly and consecutively: 1, 2, 3...


    // Trace the eulerian tour starting at vertexStart

    //free(intree); Might not be used
    return eulerianTour;
}

void recursive_intree_constructor(node_t vertexParent) {
    for (int i = 0; i < vertexParent.amountOfEdgesToNode; i++) {
        node_t *currentVertexChild = vertexParent.edgesToNode[i].nodeFrom;
        if (currentVertexChild->isUsed) {
            continue;
        }
        else {
            currentVertexChild->parentNode = &vertexParent;
            currentVertexChild->isUsed = 1;
            recursive_intree_constructor(*currentVertexChild);
        }
    }
}

// Used to print the final eulerian tour - to show the path found
void print_eulerian_tour(char* eulerianTour) {

}

// Calculates the balance of each vertex
void balance_calculation(node_t *graph, int amountOfNodes) {
    for (int k = 0; k < amountOfNodes; k++) {
        //Graph[k].bk = Graph[k].indegree - Graph[k].outdegree
    }
}

// This is the hardest part :,(
node_t* circulation_problem(node_t *graph) {

    node_t* newGraph;
    copy_arc(graph, newGraph);
    return newGraph;
}

// Used to copy an arc to make vertices balanced: the indegree and outdegree of that vertex are equal.
void copy_arc(node_t *graph, node_t *newGraph) {

}