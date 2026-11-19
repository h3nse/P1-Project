//
// Created by Frede on 18-11-2026.
//

#ifndef P1_GRAPHGENERATOR_H
#define P1_GRAPHGENERATOR_H

#include "functions.h"
#include <math.h>

void testing_algorithms();

node_t* generate_strongly_connected(int amount_of_nodes, int minimum_amount_of_edges);

int get_free_slot(node_t access_node );

void spanning_tree(node_t* array_of_nodes,int amount_of_nodes);

void add_edge(int nodeA, int nodeB, node_t* graph);

void TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stack_index,int* in_stack, int* start_time, int node);

void run_Tarjans_algorithm(node_t* graph, int amount_of_nodes);

void run_modified_Tarjans_algorithm(node_t* graph, int amount_of_nodes);

void modified_TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stack_index,int* in_stack, int* start_time, int node, int* inverse_discovered);

void add_random_edges(node_t* graph,int node_count, int amount_of_edges, int required_amount_of_edges);

#endif //P1_GRAPHGENERATOR_H
