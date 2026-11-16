#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

// IN HERE WILL BE THE ALGORITHM FOR THE CHINESE POSTMAN PROBLEM

int* odd_nodes_array (node_t* arrayOfNodes, int amountOfNodes) {
    int* odd_nodes = (int*)malloc(sizeof(int) * amountOfNodes);
    int currentAmountOfOddNodes = 0;

    for (int i = 0; i < amountOfNodes; i++) {
        if ((sizeof(arrayOfNodes[i].edgesFromNodeArray) / sizeof(edge_t)) % 2 == 1) {
            printf("%lf", (double)(sizeof(arrayOfNodes[i].edgesFromNodeArray) / sizeof(edge_t)));

        }

        odd_nodes[currentAmountOfOddNodes];

    }

}