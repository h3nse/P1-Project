#include "graphGenerator.h"

// IMPORTANT FUNCTIONS NOT RELATED TO THE OTHER .C FILES

void run_program() {

    srand(time(NULL)); // Random seed based on computers time.

    // INSERT ALL SORTS OF FUNCTIONS MY G

    int amountOfNodes; // debug
    printf("\nEnter the amount of nodes: ");
    scanf("%d", &amountOfNodes);

    node_t* arrayOfNodes = spanning_tree(amountOfNodes);

    int* arrayOfIndexesOfOddNodes = odd_nodes_array(arrayOfNodes, amountOfNodes);

    //printf("%d", arrayOfNodes[0].edgesFromNodeArray[0].length); // print test

    free(arrayOfNodes);
    free(arrayOfIndexesOfOddNodes);

}


/**
 *
 * @param amountOfNodes
 * @return An array of nodes, whose fields are arrays of edges going from said nodes.
 */
node_t* generate_graph(int amountOfNodes) {

    node_t* arrayOfNodes = (node_t*)malloc(sizeof(node_t)*amountOfNodes);
    if (arrayOfNodes == NULL) {
        printf("Memory allocation failed! Not enough memory.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < amountOfNodes; i++) {
        for (int j = 0; j < MAX_EDGES_PER_NODE; j++) {
            if (rand() % 3 <= 1 && j != 0) { // Chooses to randomly skip some edges in the node.
                //arrayOfNodes[i].edgesFromNodeArray[j].length = 0; // Assigns a length of zero to signify, that this edge does not exist.
                continue;
            }
            edge_t currentEdge; // Simplifies, assigns a temporary edge.

            currentEdge.length = rand() % 6 + 1; // Accesses the length of the i'th nodes j'th edge.
            currentEdge.priority = rand() % 2 + 1;
            currentEdge.nodeA = i;
            currentEdge.nodeB = i; // This must be assigned to a node with a free slot, not yet implemented.
            currentEdge.isCleared = 0;

            printf("\nNode: %d, Edge: %d, Length: %d, Priority: %d, NodeA: %d, NodeB: %d, isCleared: %d\n",
                i, j, currentEdge.length, currentEdge.priority, currentEdge.nodeA, currentEdge.nodeB, currentEdge.isCleared);

            arrayOfNodes[i].edgesFromNodeArray[j] = currentEdge; // Assigns the current edge to the temporary current edge.
        }
    }

    return arrayOfNodes;

}






