#include "cpp.h"
#include "limits.h"

// IN HERE WILL BE THE ALGORITHM FOR THE UNDIRECTED CHINESE POSTMAN PROBLEM

int yaxiong(){
    
}



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
            if (arrayOfNodes[i].edgesFromNode[j].length == 0 && j % 2 == 0) {
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

// Prototype
int dijkstra(node_t *arrayOfNodes, int amountOfNodes, node_t srcNode, node_t destNode) {
    // Create array of all unvisited nodes. +1 to allow space to remove nodes later.
    node_t unvisitedNodes[amountOfNodes + 1];
    node_t tempNode;
    unvisitedNodes[amountOfNodes + 1] = tempNode;
    int unvisitedNodesSize = amountOfNodes;
    for (int i = 0; i < amountOfNodes; i++){
        unvisitedNodes[i] = arrayOfNodes[i];
    }
    // Set length to all nodes to max
    for (int i = 0; i < amountOfNodes ; i++){
        unvisitedNodes[i].distanceFromSrc = INT_MAX;
    }

    // srcNode setup
    srcNode.distanceFromSrc = 0;
    node_t currNode = srcNode;
    int currNodeIndex;
    for (int i = 0; i < amountOfNodes; i++){
        if (unvisitedNodes[i].id == currNode.id){
            currNodeIndex = i;
        }
    }

    int foundDest = 0;
    while (unvisitedNodesSize != 0 && !foundDest){
        // Get node with lowest distance from src.
        for (int i = 0; i < unvisitedNodesSize; i++){
            if (unvisitedNodes[i].distanceFromSrc < currNode.distanceFromSrc){
                currNode = unvisitedNodes[i];
                currNodeIndex = i;
            }
        }
        if (currNode.id == destNode.id){
            foundDest = 1;
            break;
        }

        // Compare neighbouring nodes' distanceFromSrc to the current nodes' distance plus the length to the neighbour
        // If new length is lower, update its distanceFromSrc and assign it currNode as parent
        node_t *neighbourNode;
        for (int i = 0; i < currNode.amountOfEdges; i++){
            neighbourNode = currNode.edgesFromNode[i].nodeTo;
            int distanceThroughCurrNode = currNode.distanceFromSrc + currNode.edgesFromNode[i].length;
            if (neighbourNode->distanceFromSrc > distanceThroughCurrNode){
                neighbourNode->distanceFromSrc = distanceThroughCurrNode;
                neighbourNode->parentNode = &currNode;
            }
        }

        // Remove currNode from unvisitedNodes
        for (int i = currNodeIndex; i < unvisitedNodesSize; i++){
            unvisitedNodes[i] = unvisitedNodes[i + 1];
        }
        unvisitedNodesSize--;
    }

    // If destination was found, the path can now be traced by going through the parents of each node, starting at dest.

    return foundDest;

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
            currentOddNodePath = dijkstra(arrayOfNodes, amountOfNodes, arrayOfNodes[arrayOfOddNodesIndexes[i]], arrayOfNodes[arrayOfOddNodesIndexes[j]]);
            if (currentOddNodePath < shortestOddNodePath) {
                shortestOddNodePath = currentOddNodePath;
            }
        }
    }

    //



    return totalLength;
}
