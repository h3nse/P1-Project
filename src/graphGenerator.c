//
// Created by Frede on 18-11-2026.
//

#include "graphGenerator.h"

void testing_algorithms() {

    node_t* graph = calloc(7,sizeof(node_t));

    if (graph == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    add_edge(0,1,graph);
    add_edge(1,2,graph);
    add_edge(2,3,graph);
    add_edge(3,2,graph);
    add_edge(1,6,graph);
    add_edge(1,5,graph);
    add_edge(6,0,graph);
    add_edge(6,5,graph);
    add_edge(5,4,graph);
    add_edge(4,5,graph);
    add_edge(4,2,graph);

    run_Tarjans_algorithm(graph,7);
    run_modified_Tarjans_algorithm(graph,7);
    run_Tarjans_algorithm(graph,7);

}

node_t* generate_strongly_connected(int amount_of_nodes, int minimum_amount_of_edges) {
    int current_amount_of_edges = amount_of_nodes-1; //from spanning tree since it generates 1 edge for each node

    node_t* array_of_nodes = calloc(amount_of_nodes,sizeof(node_t)); //initialize the array

    if (array_of_nodes == NULL) {
        printf("could not allocate room for nodes");
        exit(EXIT_FAILURE);
    }

    printf("creating spanning tree\n");
    spanning_tree(array_of_nodes,amount_of_nodes);

    //printf("finding scc\n");
    //run_Tarjans_algorithm(array_of_nodes,amount_of_nodes);

    printf("making strongly connected \n");
    run_modified_Tarjans_algorithm(array_of_nodes,amount_of_nodes);


    printf("testing strongly connected \n");
    run_Tarjans_algorithm(array_of_nodes,amount_of_nodes);


    printf("adding random edges \n");
    add_random_edges(array_of_nodes,amount_of_nodes,current_amount_of_edges,minimum_amount_of_edges);

    return array_of_nodes;
}

void spanning_tree(node_t* array_of_nodes,int amount_of_nodes) {

    /*
     * explanation
     * node 0 is base
     * then for each node make a path from a previous node to it
     * repeat that
     * this ensures that all nodes can be reached from node 0
     *
     */

    array_of_nodes[0].id = 0;


    for (int i = 1; i < amount_of_nodes; i++) { // loop through all nodes and add them to a previous nodes to ensure that all nodes are connected

        array_of_nodes[i].id = i;

        //see if node has a free slot
        int connect_from;
        do {
            connect_from = rand() % i;

        }while (array_of_nodes[connect_from].edgesFromNode[MAX_EDGES_PER_NODE-2].length != 0 ); //check if node has a free slot


        if (i % 1000 == 0) {
            printf("running %d \n", i );
        }

        //add the edge to node A and b
        add_edge(connect_from,i,array_of_nodes);

    }

}

int get_free_from_slot(node_t access_node ) {
    for (int i = 0; i < MAX_EDGES_PER_NODE; i++) {
        if (access_node.edgesFromNode[i].length == 0) {
            return i;
        }
    }
    return -1;
}

int get_free_to_slot(node_t access_node ) {
    for (int i = 0; i < MAX_EDGES_PER_NODE; i++) {
        if (access_node.edgesToNode[i].length == 0) {
            return i;
        }
    }

    return -1;

}

void add_random_edges(node_t* graph,int node_count, int amount_of_edges, int required_amount_of_edges) {

    int stop_counter = 0; // make sure an infinite loop doesn't happen

    while (amount_of_edges < required_amount_of_edges && stop_counter < 100) {

        int random_node_1 = rand()%node_count;
        int random_node_2 = rand()%node_count;

        int free_slot_1 = get_free_from_slot(graph[random_node_1]);
        int free_slot_2 = get_free_to_slot(graph[random_node_2]);


        if (free_slot_1 != -1 && free_slot_2 != -1) {


            add_edge(random_node_1,random_node_2, graph);
            amount_of_edges++;


            stop_counter = 0;
        }
        else {
            stop_counter++;
        }

    }

}

void add_edge(int fromNode, int toNode, node_t* graph) {
    edge_t currentEdge; // Simplifies, assigns a temporary edge.

    currentEdge.length = rand() % 6 + 1; // random length
    currentEdge.priority = rand() % 2 + 1; // random priority why not
    currentEdge.nodeFrom = &graph[fromNode]; // from this node
    currentEdge.nodeTo = &graph[toNode]; // to this node
    currentEdge.isCleared = 0;


    graph[fromNode].edgesFromNode[get_free_from_slot(graph[fromNode])] = currentEdge;
    graph[toNode].edgesToNode[get_free_to_slot(graph[toNode])] = currentEdge;

    //print for test
    //printf("\nNodeFrom: %d, NodeTo: %d, Length: %d, Priority: %d, isCleared: %d\n",
     //       fromNode,toNode, currentEdge.length, currentEdge.priority, currentEdge.isCleared);

}

void run_Tarjans_algorithm(node_t* graph, int amount_of_nodes) {
    int* discovered = calloc(amount_of_nodes+1,sizeof(int));
    int* low = calloc(amount_of_nodes+1,sizeof(int));
    int* stack = calloc(amount_of_nodes+1,sizeof(int));
    int* in_stack = calloc(amount_of_nodes+1,sizeof(int));

    int stack_index = 1;
    int start_time = 1;

    if (discovered == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (low == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (stack == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (in_stack == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    TarjansAlgorithm(graph,discovered,low,stack,&stack_index,in_stack,&start_time,0);

    free(discovered);
    free(low);
    free(stack);
    free(in_stack);

}

void TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stack_index,int* in_stack, int* start_time, int node) {

    discovered[node] = (*start_time);

    low[node] = (*start_time);
    (*start_time)++;

    stack[*stack_index] = node;
    in_stack[node] = 1;
    (*stack_index)++;


    int length = get_free_from_slot(graph[node]);

    if (length == -1) {
        length = MAX_EDGES_PER_NODE;
    }

    for (int i = 0; i < length; i++) { // get all nodes that can be accessed from the node

        int connected_node = graph[node].edgesFromNode[i].nodeTo->id;

        if (discovered[connected_node] == 0) {
            TarjansAlgorithm(graph,discovered,low,stack,stack_index,in_stack,start_time,connected_node);

            low[node] = fmin(low[node],low[connected_node]);
        }
        else if (in_stack[connected_node]) {
            low[node] = fmin(low[node],discovered[connected_node]);

        }

    }

    if (low[node] == discovered[node]) {

        //remove all nodes connected when finding a scc


        printf("these nodes are in a scc\n");

        while (1) {

            (*stack_index)--;

            int x = stack[*stack_index];
            printf("%d, ",x);

            stack[*stack_index] = 0;

            in_stack[x] = 0;

            if (x == node || *stack_index == 0) {
                printf("\n");
                break;
            }


        }

    }

}


void run_modified_Tarjans_algorithm(node_t* graph, int amount_of_nodes) {
    int* discovered = calloc(amount_of_nodes+1,sizeof(int));
    int* inverse_discovered = calloc(amount_of_nodes+1,sizeof(int));
    int* low = calloc(amount_of_nodes+1,sizeof(int));
    int* stack = calloc(amount_of_nodes+1,sizeof(int));
    int* in_stack = calloc(amount_of_nodes+1,sizeof(int));

    int stack_index = 1;
    int start_time = 1;

    if (discovered == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (inverse_discovered == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (low == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (stack == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (in_stack == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    modified_TarjansAlgorithm(graph,discovered,low,stack,&stack_index,in_stack,&start_time,0,inverse_discovered);

    free(discovered);
    free(inverse_discovered);
    free(low);
    free(stack);
    free(in_stack);

}

void modified_TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stack_index,int* in_stack, int* start_time, int node, int* inverse_discovered) {

    discovered[node] = (*start_time);
    low[node] = (*start_time);
    inverse_discovered[*start_time] = node;

    (*start_time)++;

    stack[*stack_index] = node;
    in_stack[node] = 1;
    (*stack_index)++;



    int length = get_free_from_slot(graph[node]);

    if (length == -1) {
        length = MAX_EDGES_PER_NODE;
    }

    for (int i = 0; i < length; i++) { // get all nodes that can be accessed from the node

        int connected_node = graph[node].edgesFromNode[i].nodeTo->id;

        if (discovered[connected_node] == 0) {
            modified_TarjansAlgorithm(graph,discovered,low,stack,stack_index,in_stack,start_time,connected_node,inverse_discovered);

        }
        low[node] = fmin(low[node],low[connected_node]);

    }

    if (low[node] == discovered[node] && node != 0) {

        int v_node,w_node,x,y;


        do {
            int random_value = rand() % ((*start_time) - discovered[node]);


            x = discovered[node] + random_value;

            y = (rand() % (discovered[node]-1))+1;


            v_node = inverse_discovered[x];
            w_node = inverse_discovered[y];


            //printf("stuck on %d \n", w_node);

        } while (get_free_from_slot(graph[v_node]) == -1 || get_free_to_slot(graph[w_node]) == -1);

        add_edge(v_node,w_node,graph);
        low[node] = y;

    }

}
