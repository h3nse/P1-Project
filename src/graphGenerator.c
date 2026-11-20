//
// Created by Frede on 18-11-2026.
//

#include "graphGenerator.h"

node_t* generate_strongly_connected(int amountOfNodes, int addExtraEdges) {

    node_t* graph = calloc(amountOfNodes,sizeof(node_t)); //initialize the array

    if (graph == NULL) {
        printf("could not allocate room for nodes");
        exit(EXIT_FAILURE);
    }

    printf("creating spanning tree\n");
    spanning_tree(graph,amountOfNodes);

    //printf("finding scc\n");
    //run_Tarjans_algorithm(graph,amountOfNodes);

    printf("making strongly connected \n");
    run_modified_Tarjans_algorithm(graph,amountOfNodes);


    //printf("testing strongly connected \n");
    //run_Tarjans_algorithm(graph,amountOfNodes);


    printf("adding random edges \n");
    add_random_edges(graph,amountOfNodes,addExtraEdges);

    return graph;
}

void spanning_tree(node_t* graph,int amountOfNodes) {

    /*
     * explanation
     * node 0 is base
     * then for each node make a path from a previous node to it
     * repeat that
     * this ensures that all nodes can be reached from node 0
     */

    graph[0].id = 0; //sets the id of 0


    for (int i = 1; i < amountOfNodes; i++) { // loop through all nodes and add them to a previous nodes to ensure that all nodes are connected



        //see if node has a free slot
        int connect_from;
        do {
            connect_from = rand() % i;

        }while (graph[connect_from].edgesFromNode[MAX_EDGES_PER_NODE-2].length != 0 ); //check if node has a free slot


        if (i % 1000 == 0) { //test to see if running
            printf("running %d \n", i );
        }

        //add the edge from connect to the new node
        add_edge(connect_from,i,graph);

    }

}

int get_free_from_slot(node_t accessNode ) { //gets the first free from slot in a node
    for (int i = 0; i < MAX_EDGES_PER_NODE; i++) {
        if (accessNode.edgesFromNode[i].length == 0) {
            return i;
        }
    }

    return -1;
}

int get_free_to_slot(node_t accessNode ) { //gets the first free to slot in a node
    for (int i = 0; i < MAX_EDGES_PER_NODE; i++) {
        if (accessNode.edgesToNode[i].length == 0) {
            return i;
        }
    }

    return -1;

}

void add_random_edges(node_t* graph,int nodeCount, int amountOfEdges) {

    int stopCounter = 0; // make sure an infinite loop doesn't happen
    int maxAttempts = 20;

    int randomNode1,freeSlot1,randomNode2,freeSlot2;

    for (int i = 0; i < amountOfEdges; i++) {


        while (stopCounter < maxAttempts) {
            stopCounter++;

            randomNode1 = rand()%nodeCount;
            freeSlot1 = get_free_from_slot(graph[randomNode1]);

            if (freeSlot1 != -1) { //if there is a free from slot add edge from here
                break;
            }
        }

        stopCounter = 0;

        while (stopCounter < maxAttempts) {
            stopCounter++;

            randomNode2 = rand()%nodeCount;
            freeSlot2 = get_free_from_slot(graph[randomNode2]);

            if (freeSlot2 != -1 && randomNode1 != randomNode2) { //if there is a free to slot add edge from here unless it tries adding to itself
                break;
            }
        }

        add_edge(randomNode1,randomNode2, graph); //add the found edge
        stopCounter = 0; //reset


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
    graph[fromNode].amountOfEdgesFromNode++;
    graph[toNode].amountOfEdgesToNode++;

    graph[fromNode].id = fromNode; //set id for later use
    graph[toNode].id = toNode; //set id for later use

    //print for test
    //printf("\nNodeFrom: %d, NodeTo: %d, Length: %d, Priority: %d, isCleared: %d\n",
     //       fromNode,toNode, currentEdge.length, currentEdge.priority, currentEdge.isCleared);

}

void run_Tarjans_algorithm(node_t* graph, int amountOfNodes) {

    //initialize all the arrays and add +1 to the length since C 0 is used as empty
    int* discovered = calloc(amountOfNodes+1,sizeof(int));
    int* low = calloc(amountOfNodes+1,sizeof(int));
    int* stack = calloc(amountOfNodes+1,sizeof(int));
    int* inStack = calloc(amountOfNodes+1,sizeof(int));


    //same reason as +1 we start at 1 instead of 0
    int stackIndex = 1;
    int startTime = 1;

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

    if (inStack == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }


    //run algorithm
    TarjansAlgorithm(graph,discovered,low,stack,&stackIndex,inStack,&startTime,0);


    //remember to free
    free(discovered);
    free(low);
    free(stack);
    free(inStack);

}

void TarjansAlgorithm(node_t* graph,int* discovered,int* low,int* stack,int* stackIndex,int* inStack, int* startTime, int node) {

    //set each value for the node depending on what it is
    discovered[node] = (*startTime); //when the node is discovered
    low[node] = (*startTime); //originally set to the same as discovered but is changed later on
    (*startTime)++; //increment the global variable by one

    stack[*stackIndex] = node; //set up the stack, ie. add node to the stack
    inStack[node] = 1; //look up table
    (*stackIndex)++; //increment global stack index by one


    int amountOfEdgesFromNode = get_free_from_slot(graph[node]); // get how many edges go from node

    if (amountOfEdgesFromNode == -1) {
        amountOfEdgesFromNode = MAX_EDGES_PER_NODE;
    }

    for (int i = 0; i < amountOfEdgesFromNode; i++) { // get all nodes that can be accessed from the node

        int connectedNode = graph[node].edgesFromNode[i].nodeTo->id; //find the id of the next node

        if (discovered[connectedNode] == 0) {
            //repeats the previous steps for the next node until you've reached the end of a branch then run the rest
            TarjansAlgorithm(graph,discovered,low,stack,stackIndex,inStack,startTime,connectedNode);

            low[node] = fmin(low[node],low[connectedNode]); // update low value
        }
        else if (inStack[connectedNode]) {
            low[node] = fmin(low[node],low[connectedNode]); // if not in a scc then update low value
        }


    }



    if (low[node] == discovered[node]) {   //remove all nodes connected in the scc


        printf("these nodes are in a scc\n");

        while (1) {
            //decrement by 1 since we added one above

            (*stackIndex)--;

            //get the node id
            int x = stack[*stackIndex];
            printf("%d, ",x);

            //pop from stack
            stack[*stackIndex] = 0;

            inStack[x] = 0;

            //if removed all from the strongly connected then break
            if (x == node || *stackIndex == 0) {
                printf("\n");
                break;
            }


        }

    }

}

void run_modified_Tarjans_algorithm(node_t* graph, int amount_of_nodes) {
    //initialize arrays again
    int* discovered = calloc(amount_of_nodes+1,sizeof(int));
    int* inverseDiscovered = calloc(amount_of_nodes+1,sizeof(int));
    int* low = calloc(amount_of_nodes+1,sizeof(int));

    int start_time = 1;

    if (discovered == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (inverseDiscovered == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    if (low == NULL) {
        printf("could not allocate");
        exit(EXIT_FAILURE);
    }

    modified_TarjansAlgorithm(graph,discovered,inverseDiscovered,low,&start_time,0);

    free(discovered);
    free(inverseDiscovered);
    free(low);

}

void modified_TarjansAlgorithm(node_t* graph,int* discovered,int* inverseDiscovered,int* low, int* startTime, int node) {
    discovered[node] = (*startTime); //when the node is discovered
    low[node] = (*startTime); //originally set to the same as discovered but is changed later on
    inverseDiscovered[*startTime] = node; //flipped version of discovered

    (*startTime)++; //increment the global variable by one

    int amountOfEdgesFromNode = get_free_from_slot(graph[node]); // get how many edges go from node

    if (amountOfEdgesFromNode == -1) {
        amountOfEdgesFromNode = MAX_EDGES_PER_NODE;
    }

    for (int i = 0; i < amountOfEdgesFromNode; i++) { // get all nodes that can be accessed from the node

        //just like regular Tarjans algorithm so see that
        int connectedNode = graph[node].edgesFromNode[i].nodeTo->id;

        if (discovered[connectedNode] == 0) {
            modified_TarjansAlgorithm(graph,discovered,inverseDiscovered,low,startTime,connectedNode);
        }
        //we want everything to be one strongly connected graph so no need for stacks anymore
        low[node] = fmin(low[node],low[connectedNode]);

    }

    if (low[node] == discovered[node] && node != 0) { // if discovering a scc, 0 is excluded since we know we can go from 0 to anything

        int vNode,wNode,x,y; //setup


        do {
            int random_value = rand() % ((*startTime) - discovered[node]);

            x = discovered[node] + random_value; // choose a value between [discovered[node], starttime]

            y = (rand() % (discovered[node]-1))+1; //choose a value from [1,discovered[node]]

            //grab the nodes associated with the discovery value
            vNode = inverseDiscovered[x];
            wNode = inverseDiscovered[y];


            //printf("stuck on %d \n", w_node); //test

        } while (get_free_from_slot(graph[vNode]) == -1 || get_free_to_slot(graph[wNode]) == -1);

        add_edge(vNode,wNode,graph); // add the edge
        low[node] = y; //update low value to make it a part of that scc

    }

}
