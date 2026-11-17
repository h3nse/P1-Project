#include "functions.h"

// IN HERE WILL BE THE ALGORITHM FOR THE UNDIRECTED CHINESE POSTMAN PROBLEM





// Step 1: find all odd nodes - this function goes through the array of all nodes, and check if each are an odd node.
// The index of the node in the array of nodes will be placed in a new array if it is an odd node.
int *odd_nodes_array(node_t *arrayOfNodes, int amountOfNodes) {
    // Create the array for odd node indexes
    int *arrayOfOddNodesIndexes = (int *) malloc(sizeof(int) * amountOfNodes);
    if (arrayOfOddNodesIndexes == NULL) {
        printf("Memory allocation failed! Not enough memory.");
        exit(EXIT_FAILURE);
    }

    // Loop through the entire array of nodes, and check how many edges goes from it
    int currentAmountOfOddNodes = 0;

    for (int i = 0; i < amountOfNodes; i++) {
        for (int j = 0; j < MAX_EDGES_PER_NODE; j++) {
            if (arrayOfNodes[i].edgesFromNodeArray[j].length == 0 && j % 2 == 0) {
                arrayOfOddNodesIndexes[currentAmountOfOddNodes] = i;
                currentAmountOfOddNodes++;
                break;
            }
        }
    }

    // Test for which nodes are odd
    // for (int i = 0; i < currentAmountOfOddNodes; i++) {
    //     printf("Node %d is odd \n", oddNodes[i]);
    // }

    return arrayOfOddNodesIndexes;
}

int djikstra(node_t *arrayOfNodes, int amountOfNodes, node_t node1, node_t node2) {

}

int cpp_total_length(node_t *arrayOfNodes, int amountOfNodes, int *arrayOfOddNodesIndexes) {
    int currentOddNodePath, shortestOddNodePath = 0, totalLength;

    // Loop through arrayOfNodes, but only odd nodes which are done using indexes from oddNodes array
    // Find the shortest odd node path
    for (int i = 0; i < amountOfNodes; i++) {
        for (int j = 0; j < amountOfNodes; j++) {
            if (i == j) {
                continue;
            }
            currentOddNodePath = djikstra(arrayOfNodes, amountOfNodes, arrayOfNodes[arrayOfOddNodesIndexes[i]], arrayOfNodes[arrayOfOddNodesIndexes[j]]);
            if (currentOddNodePath < shortestOddNodePath) {
                shortestOddNodePath = currentOddNodePath;
            }
        }
    }

    //



    return totalLength;
}
