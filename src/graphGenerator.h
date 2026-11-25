#ifndef P1_GRAPHGENERATOR_H
#define P1_GRAPHGENERATOR_H

#include "project.h"
#include <math.h>

node_t* generate_strongly_connected(int amountOfNodes, int addExtraEdges);

int get_free_from_slot(node_t accessNode);

int get_free_to_slot(node_t accessNode);

void spanning_tree(node_t* arrayOfNodes,int amountOfNodes);

void add_edge(int fromNode, int toNode, node_t* graph);

void add_random_edges(node_t* graph,int nodeCount, int amountOfEdges);

void TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stack_index,int* inStack, int* start_time, int node);

void run_Tarjans_algorithm(node_t* graph, int amountOfNodes);

void run_modified_Tarjans_algorithm(node_t* graph, int amount_of_nodes);

void modified_TarjansAlgorithm(node_t* graph,int* discovered,int* inverseDiscovered,int* low, int* startTime, int node);


#endif //P1_GRAPHGENERATOR_H
