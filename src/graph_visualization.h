//
// Created by Frede on 20-11-2026.
//

#ifndef P1_GRAPH_VISUALIZATION_H
#define P1_GRAPH_VISUALIZATION_H

#include "project.h"

#define node_t NODE_CONFLICT
#define edge_t EDGE_CONFLICT

#include <gvc.h>
#include <cgraph.h>

#undef node_t
#undef edge_t

void show_graph(char* file_name, node_t* graph, int amountOfNodes);

#endif //P1_GRAPH_VISUALIZATION_H
