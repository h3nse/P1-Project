
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



#define RANDOM_SEED /*--*/ true
#define  GIVEN_SEED /*--*/ 1
#define NUMBER_OF_NODES    1000
#define MAX_EDGE_PER_NODE  8
#define MAX_EDGE_LENGTH_CM 100



#define SEED RANDOM_SEED == true ? time(NULL) : GIVEN_SEED
#define MAX_OUT_PER_NODE MAX_EDGE_PER_NODE / 2 + MAX_EDGE_PER_NODE % 2
#define MAX_IN_PER_NODE  MAX_EDGE_PER_NODE / 2 + MAX_EDGE_PER_NODE % 2


typedef unsigned int uint;

typedef struct edge {

    uint length;
    uint priority;
    uint timesVisited;
    
    uint nodeFrom;
    uint nodeTo;
    
} Edge;
typedef struct node {

    uint inEdges[MAX_IN_PER_NODE];
    uint outEdges[MAX_OUT_PER_NODE];
    
    uint inAmount;
    uint outAmount;
    
} Node;
typedef struct graph {
    
    Node *nodes;
    Edge *edges;
    uint *oddNodes;
    
    uint nodeCount;
    uint edgeCount;
    uint oddNodeCount;
    
} Graph;


Graph graph_create(uint nodeAmount);

void graph_generate(Graph *graph, uint edgeAmount);
void make_edge(Graph *graph, uint nodeFrom, uint nodeTo, uint length, uint priority);
bool edge_exists(Graph *graph, uint nodeFrom, uint nodeTo);
void find_odd_nodes(Graph *graph);

uint dijkstra(Graph *graph, uint nodeFrom, uint nodeTo);

void print_relations(Graph *graph);


int main(void) {

    
    srand(SEED);

    
    uint edgeAmount = NUMBER_OF_NODES - rand() % (NUMBER_OF_NODES / 4);
    
    Graph graph = graph_create(NUMBER_OF_NODES);
    
    graph_generate(&graph, edgeAmount);    

    
    
    find_odd_nodes(&graph);

    
    uint totalLength = 0;
    for (uint i = 0; i < graph.edgeCount; i++) {

        totalLength += graph.edges[i].length;
    }

    
    printf(" Total length: %d\n", totalLength);
    printf("  Length between Node 0 and Node 4 : %u\n", dijkstra(&graph, 0, 4));
    printf("  Length between Node 5 and Node 944 : %u\n", dijkstra(&graph, 5, 944));
    printf("  Odd nodes: %d\n", graph.oddNodeCount);

    return 0;
}


void print_relations(Graph *graph) {

    for (uint i = 0; i < graph->edgeCount; i++) {
        
        printf(" (%d, %d) : %d cm \n", graph->edges[i].nodeFrom, graph->edges[i].nodeTo, graph->edges[i].length);
    }
}

Graph graph_create(uint nodeAmount) {

    Graph graph = {
        
        .nodes = (Node *)calloc(nodeAmount, sizeof(Node)),
        .edges = (Edge *)calloc(nodeAmount * MAX_OUT_PER_NODE, sizeof(Edge)),
        .oddNodes = (uint *)calloc(nodeAmount, sizeof(uint)),
        .nodeCount = nodeAmount,
        .edgeCount = 0,
        .oddNodeCount = 0
    };
    
    if (!(graph.nodes && graph.edges && graph.oddNodes)) { printf(" Failed to allocate.\n"); exit(EXIT_FAILURE); }

    return graph;
}

void graph_generate(Graph *graph, uint edgeAmount) {
    
    uint rNodeFrom, rNodeTo, length, priority;
    
    for (uint i = 0; i < graph->nodeCount; i++) {

        length = rand() % MAX_EDGE_LENGTH_CM;
        priority = rand() % 5;
       make_edge(graph, i, i + 1 % graph->nodeCount, length, priority);
    }
    
    while (graph->edgeCount < edgeAmount) {
        
        rNodeFrom = rand() % graph->nodeCount;
        rNodeTo = rand() % graph->nodeCount;
        length = rand() % MAX_EDGE_LENGTH_CM;
        priority = rand() % 5;
        make_edge(graph, rNodeFrom, rNodeTo, length, priority);
    }
}

void make_edge(Graph *graph, uint nodeFrom, uint nodeTo, uint length, uint priority) {

    if (nodeFrom == nodeTo) return;
    if (graph->nodes[nodeFrom].outAmount >= MAX_OUT_PER_NODE) return;
    if (graph->nodes[ nodeTo ]. inAmount >= MAX_IN_PER_NODE ) return;
    if (graph->nodes[nodeFrom]. inAmount + graph->nodes[nodeFrom].outAmount >= MAX_EDGE_PER_NODE) return;
    if (graph->nodes[ nodeTo ]. inAmount + graph->nodes[ nodeTo ].outAmount >= MAX_EDGE_PER_NODE) return;
    if (edge_exists(graph, nodeFrom, nodeTo)) return;

    Edge newEdge = {
        
        .nodeFrom = nodeFrom,
        .nodeTo = nodeTo,
        .length = length,
        .priority = priority,
        .timesVisited = 0  
    };
    
    graph->nodes[nodeFrom].outEdges[graph->nodes[nodeFrom].outAmount++] = graph->edgeCount;
    graph->nodes[ nodeTo ]. inEdges[graph->nodes[ nodeTo ]. inAmount++] = graph->edgeCount;
    graph->edges[graph->edgeCount++] = newEdge;
}

bool edge_exists(Graph *graph, uint nodeFrom, uint nodeTo) {

    if (graph->nodes[nodeFrom].outAmount == 0) return false;

    for (uint i = 0; i < graph->nodes[nodeFrom].outAmount; i++) {
    
        if (graph->edges[graph->nodes[nodeFrom].outEdges[i]].nodeTo == nodeTo) return true;
    }
        
    return false;
}

void find_odd_nodes(Graph *graph) {
    
    for (uint i = 0; i < graph->nodeCount; i++) {
        
        if (graph->nodes[i].inAmount + graph->nodes[i].outAmount % 2 == 1) {

            graph->oddNodes[graph->oddNodeCount++] = i;
        }
    }
}

uint dijkstra(Graph *graph, uint nodeFrom, uint nodeTo) {

    bool nodeVisited[graph->nodeCount];
    uint distances[graph->nodeCount];
    uint maxDistance = 4294967295;

    for (uint i = 0; i < graph->nodeCount; i++) {

        nodeVisited[i] = false;
        distances[i] = maxDistance;
    }

    distances[nodeFrom] = 0;
    
    uint currentNode = nodeFrom;

    while (currentNode != nodeTo) {
        
        for (uint i = 0; i < graph->nodes[currentNode].outAmount; i++) {
            
            uint nextNode = graph->edges[graph->nodes[currentNode].outEdges[i]].nodeTo;
            uint edgeLength = graph->edges[graph->nodes[currentNode].outEdges[i]].length;
            uint possibleLength = distances[currentNode] + edgeLength;
            
            if (!nodeVisited[nextNode] && possibleLength <= distances[nextNode]) {
                
                distances[nextNode] = possibleLength;
            }
        }

        nodeVisited[currentNode] = true;

        uint minDistance = maxDistance;
        
        for (uint i = 0; i < graph->nodeCount; i++) {
            
            if (!nodeVisited[i] && distances[i] < minDistance) {

                minDistance = distances[i];
                currentNode = i;
            }
        }
    }

    return distances[nodeTo];
}
