#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


void run_program() {
    // INSERT ALL SORTS OF FUNCTIONS MY G
    int amountOfNodes = 6; // debug
    node_t* arrayOfNodes = generate_graph(amountOfNodes);


    //printf("%d", arrayOfNodes[0].edgesFromNodeArray[0].length); // print test

    free(arrayOfNodes);
}


/**
 *
 * @param amountOfNodes
 * @return An array of nodes, whose fields are arrays of edges going from said nodes.
 */
node_t* generate_graph(int amountOfNodes) {
    node_t* arrayOfNodes = (node_t*)malloc(sizeof(node_t)*amountOfNodes);
    for (int i = 0; i < amountOfNodes; i++) {
        for (int j = 0; j < MAX_EDGES_PER_NODE; j++) {
            if (rand() % 3 == 0) { // Chooses to randomly skip some edges in the node.
                continue;
            }
            edge_t currentEdge = arrayOfNodes[i].edgesFromNodeArray[j]; // Simplifies.

            currentEdge.length = rand() % 6 + 1; // Accesses the length of the i'th nodes j'th edge.
            currentEdge.priority = rand() % 2 + 1;
            currentEdge.nodeA = i;
            currentEdge.nodeB = i; // This must be assigned to a node with a free slot, not yet implemented.
            currentEdge.isCleared = 0;

            printf("\nNode: %d, Edge: %d, Length: %d, Priority: %d, NodeA: %d, NodeB: %d, isCleared: %d\n",
                i, j, currentEdge.length, currentEdge.priority, currentEdge.nodeA, currentEdge.nodeB, currentEdge.isCleared);
        }
    }

    return arrayOfNodes;
}