#include "ej-dcpp.h"
#include "graphGenerator.h"

node_t* test_graph() {

    node_t* graph = calloc(7,sizeof(node_t));

    if (graph == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    add_edge(0,1,graph);
    add_edge(0,1,graph);
    add_edge(0,1,graph);
    add_edge(0,1,graph);
    add_edge(1,2,graph);
    add_edge(1,5,graph);
    add_edge(1,6,graph);
    add_edge(1,6,graph);
    add_edge(2,0,graph);
    add_edge(2,0,graph);
    add_edge(2,0,graph);
    add_edge(2,3,graph);
    add_edge(3,2,graph);
    add_edge(4,2,graph);
    add_edge(4,2,graph);
    add_edge(4,5,graph);
    add_edge(5,4,graph);
    add_edge(5,4,graph);
    add_edge(5,4,graph);
    add_edge(6,0,graph);
    add_edge(6,5,graph);

    run_Tarjans_algorithm(graph, 7);

    return graph;
}

void ej_dcpp_main(node_t *graph, int amountOfNodes) {
    int totalLength = 0;
    //Main help functions: Symmetric graph check, eulerian tour generator (algorithm 4.3.3 on page 242), in-out-degree calculate function, circulation problem, arc add to new graph

    //Step by step guide
    char* eulerianTour;

    if (symmetric_digraph_check(graph)) {
        eulerianTour = eulerian_tour(graph, amountOfNodes, &totalLength);
    }
    else {
        balance_calculation(graph, amountOfNodes);
        node_t* newGraph = circulation_problem(graph);
        eulerianTour = eulerian_tour(newGraph, amountOfNodes, &totalLength);
        free(newGraph);
    }


    print_eulerian_tour(eulerianTour, totalLength);
    free(eulerianTour);
}

// Checks if the digraph is symmetric: the indegree and outdegree of every vertex are equal.
int symmetric_digraph_check(node_t *graph) {
    return 1;
}

// Creates a eulerian tour on a eulerian digraph
char* eulerian_tour(node_t *eulerianDigraph, int amountOfNodes, int *totalLength) {
    srand(time(NULL));

    int labelCount;
    char *eulerianTour = malloc(sizeof(char) * 3 * amountOfNodes * MAX_EDGES_PER_NODE); // Makes space so string can have following form (v1-v2-...-vn) - can also later be done with edge id between
    node_t* vertexStart = &eulerianDigraph[rand()%amountOfNodes]; // Chooses an arbitrary vertex to start intree from

    // Generate intree
    vertexStart->isUsed = 1;
    recursive_intree_constructor(vertexStart);

    // For loop that labels each vertex w in the graph consecutively following this rule:
    // Label all out-arcs from w in the graph consecutively. This can be done at random: 1, 2, 3...
    // The largest label number must be placed at the arc used in the intree
    // Lastly label the out arcs from vertexStart randomly and consecutively: 1, 2, 3...
    for (int i = 0; i < amountOfNodes; i++) {
        node_t* currentNode = &eulerianDigraph[i];
        labelCount = 0;
        for (int j = 0; j < currentNode->amountOfEdgesFromNode; j++) {
            if (currentNode->edgesFromNode[j].usedInIntree) { // First checks if the current edge is the edge from the intree
                currentNode->edgesFromNode[j].inTreeLabels = currentNode->amountOfEdgesFromNode; // Then sets label to the largest
            }
            else {
                labelCount++;
                currentNode->edgesFromNode[j].inTreeLabels = labelCount; // If not then set it randomly (in this case based on order in edgesFromNode array)
            }
        }
    }

    // Trace the eulerian tour starting at vertexStart
    char* tourWithoutStartVertex = recursive_eulerian_tour_constructor(vertexStart, totalLength);
    // Add the start point
    snprintf(eulerianTour, sizeof(char) * 6 * amountOfNodes * MAX_EDGES_PER_NODE, "v%d-%s", vertexStart->id, tourWithoutStartVertex);

    return eulerianTour;
}

// Used in eulerian tour function to create intree connections bewteen nodes
void recursive_intree_constructor(node_t* vertexParent) {
    for (int i = 0; i < vertexParent->amountOfEdgesToNode; i++) {
        node_t *currentVertexChild = vertexParent->edgesToNode[i].nodeFrom;
        if (currentVertexChild->isUsed) {
            continue;
        }
        else {
            currentVertexChild->parentNode = vertexParent;
            currentVertexChild->isUsed = 1;
            for (int j = 0; j < currentVertexChild->amountOfEdgesFromNode; j++) {
                if (currentVertexChild->edgesFromNode[j].nodeTo == vertexParent && currentVertexChild->edgesFromNode[j].length == vertexParent->edgesToNode[j].length) {
                    currentVertexChild->edgesFromNode[j].usedInIntree = 1;
                    break;
                }
            }
            recursive_intree_constructor(currentVertexChild);
        }
    }
}

// Used in eulerian tour function to construct a string with the eulerian tour
char* recursive_eulerian_tour_constructor(node_t *vertexStart, int* totalLength) {
    edge_t* nextEdge = NULL;

    // Loop through and find the next best edge
    for (int i = 0; i < vertexStart->amountOfEdgesFromNode; i++) {
        edge_t* candidate = &vertexStart->edgesFromNode[i];
        if (candidate->isCleared == 0) {
            if (nextEdge == NULL || candidate->inTreeLabels < nextEdge->inTreeLabels) {
                nextEdge = candidate;
            }
        }
    }

    // Return the end of the string if there are no more edges
    if (nextEdge == NULL) {
        char* empty = malloc(2);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    // Update total length traversed and that this edge now is cleared
    *totalLength += nextEdge->length;
    nextEdge->isCleared = 1;

    // Do this recursively for all edges
    char* restOfTour = recursive_eulerian_tour_constructor(nextEdge->nodeTo, totalLength);

    // Make space for
    int maxDigits = (nextEdge->nodeTo->id == 0) ? 1 : (int)floor(log10(abs(nextEdge->nodeTo->id))) + 1; // To find how many digits there are in the id
    int totalSize = maxDigits + 3 + strlen(restOfTour); // add this edge as well with v and - and with space for the length of all other strings

    char* fullTour = malloc(totalSize);
    if (fullTour != NULL) {
        snprintf(fullTour, totalSize, "v%d-%s", nextEdge->nodeTo->id, restOfTour);
    }

    free(restOfTour);
    return fullTour;
}

// Used to print the final eulerian tour - to show the path found
void print_eulerian_tour(char* eulerianTour, int totalLength) {
    printf("This is the eulerian tour: %s\n It uses the total length of %d\n", eulerianTour, totalLength);
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