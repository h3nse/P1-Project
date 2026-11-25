#ifndef P1_EJ_DCCP_H
#define P1_EJ_DCCP_H
#include "project.h"

node_t* test_graph();
void ej_dcpp_main(node_t *graph, int amountOfNodes);
int symmetric_digraph_check(node_t *graph);
char* eulerian_tour(node_t *eulerianDigraph, int amountOfNodes, int *totalLength);
void recursive_intree_constructor(node_t *vertexParent);
char* recursive_eulerian_tour_constructor(node_t *vertexStart, int* totalLength);
void print_eulerian_tour(char* eulerianTour, int totalLength);
void balance_calculation(node_t *graph, int amountOfNodes);
node_t* circulation_problem(node_t *graph);
void copy_arc(node_t *graph, node_t *newGraph);

#endif //P1_EJ_DCCP_H
