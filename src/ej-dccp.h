//
// Created by jako8 on 18/11/2026.
//

#ifndef P1_EJ_DCCP_H
#define P1_EJ_DCCP_H
#include "functions.h"

void ej_dccp_main(node_t *graph, int amountOfNodes);
int symmetric_graph_check(node_t *graph);
char* eulerian_tour(node_t *graph);
void print_eulerian_tour(char* eulerianTour);
void balance_calculation(node_t *graph, int amountOfNodes);
node_t* circulation_problem(node_t *graph);
void copy_arc(node_t *graph);

#endif //P1_EJ_DCCP_H
