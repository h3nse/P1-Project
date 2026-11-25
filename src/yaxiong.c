#include "yaxiong.h"
#include <limits.h>

int yaxiong(node_t *arrayOfNodes, edge_t *arrayOfArcs, int amountOfNodes, int amountOfEdges){
    // Create residual arcs, i.e. reverse arcs
    edge_t *residualArcs = (edge_t*)calloc(amountOfEdges, sizeof(edge_t));
    for (int i = 0; i < amountOfEdges; i++){
        arrayOfArcs[i].residualArc = residualArcs[i];
        residualArcs[i].nodeFrom = arrayOfArcs[i].nodeTo;
        residualArcs[i].nodeTo = arrayOfArcs[i].nodeFrom;
        residualArcs[i].yaxWeight = INT_MAX; // Initally the weight is infinite, since it cannot reverse an edge that has no flow
    }

    // Step 1: Set initial solution
    for (int i = 0; i < amountOfEdges; i++){
        arrayOfArcs[i].yaxIsFeasible = 0;
        arrayOfArcs[i].yaxFlow = 0;
        arrayOfArcs[i].yaxArcDual = arrayOfArcs[i].length;
        arrayOfArcs[i].yaxWeight = 0;
    }
    for (int i = 0; i < amountOfNodes; i++){
        arrayOfNodes[i].yaxNodeDual = 0;
    }

    edge_t currArc = arrayOfArcs[0];

    // Step 2: Check status of arcs (The while loop condition). At the end of the loop, an unfeasible arc is selected if available. 
    while (!currArc.yaxIsFeasible){
        // Step 3: Form a cycle
        // Run dijkstra's from the end node of the arc to the start node of the arc
        yaxDijkstra(arrayOfNodes, amountOfNodes, *currArc.nodeTo);

        // Assign flow to arcs in cycle according to their direction

        // Step 4: Update all arc values
        
        
        // Assign an unfeasible arc to currArc (Part of step 2)
        for (int i = 0; i < amountOfEdges; i++){
            if (!arrayOfArcs[i].yaxIsFeasible){
                currArc = arrayOfArcs[i];
                break;
            }
        }
    }
}

void yaxDijkstra(node_t *arrayOfNodes, int amountOfNodes, node_t srcNode) {
    // Create array of all unvisited nodes. +1 to allow space to remove nodes later.
    node_t *unvisitedNodes = (node_t *) malloc(sizeof(node_t) * amountOfNodes);
    if (unvisitedNodes == NULL) {
        printf("Memory allocation failed! Not enough memory.");
        exit(EXIT_FAILURE);
    }
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

    while (unvisitedNodesSize != 0){
        // Get node with lowest distance from src.
        for (int i = 0; i < unvisitedNodesSize; i++){
            if (unvisitedNodes[i].distanceFromSrc < currNode.distanceFromSrc){
                currNode = unvisitedNodes[i];
                currNodeIndex = i;
            }
        }

        // Compare neighbouring nodes' distanceFromSrc to the current nodes' distance plus the length to the neighbour
        // If new length is lower, update its distanceFromSrc and assign it currNode as parent
        node_t *neighbourNode;
        for (int i = 0; i < currNode.amountOfEdgesFromNode; i++){
            neighbourNode = currNode.edgesFromNode[i].nodeTo;
            int distanceThroughCurrNode = currNode.distanceFromSrc + currNode.edgesFromNode[i].yaxWeight;
            if (neighbourNode->distanceFromSrc > distanceThroughCurrNode){
                neighbourNode->distanceFromSrc = distanceThroughCurrNode;
                neighbourNode->parentNode = &currNode;
            }
        }
        // Do this for residual arcs too
        for (int i = 0; i < currNode.amountOfEdgesToNode; i++){
            edge_t currArc = currNode.edgesToNode[i].residualArc; 
            neighbourNode = currArc.nodeTo;
            int distanceThroughCurrNode = currNode.distanceFromSrc + currArc.yaxWeight;
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

    free(unvisitedNodes);
}