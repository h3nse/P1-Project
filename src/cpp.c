#include "functions.h"

// IN HERE WILL BE THE ALGORITHM FOR THE CHINESE POSTMAN PROBLEM
int* odd_nodes_array (node_t* arrayOfNodes, int amountOfNodes) {
    printf("started\n");
    int* oddNodes = (int*)malloc(sizeof(int) * amountOfNodes);
    if (oddNodes == NULL) {
        printf("Memory allocation failed! Not enough memory.");
        exit(EXIT_FAILURE);
    }

    int currentAmountOfOddNodes = 0;

    for (int i = 0; i < amountOfNodes; i++) {
        for (int j = 0; j < MAX_EDGES_PER_NODE; j++) {
            if (arrayOfNodes[i].edgesFromNodeArray[j].length == 0 && j % 2 == 0) {
                printf("odd added with %d loops\n", j);
                oddNodes[currentAmountOfOddNodes] = i;
                currentAmountOfOddNodes++;
                break;
            }
        }
    }

    for (int i = 0; i < currentAmountOfOddNodes; i++) {
        printf("Node %d is odd \n", oddNodes[i]);
    }

    return oddNodes;
}

