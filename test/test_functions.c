#include <assert.h>
#include "functions.h"
#include "cpp.h"

int main(void)
{
    // Test Dijkstras
    const int amountOfNodes = 5;
    node_t nodeGraph[amountOfNodes];
    node_t srcNode = nodeGraph[0];
    node_t destNode = nodeGraph[amountOfNodes-1];
    dijkstra(nodeGraph, amountOfNodes, srcNode, destNode);
    return 0;
}
