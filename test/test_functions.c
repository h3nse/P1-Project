#include <assert.h>

#define node_t NODE_CONFLICT
#define edge_t EDGE_CONFLICT

#include <gvc.h>

#undef node_t
#undef edge_t

#include "project.h"
#include "cpp.h"
#include "graphGenerator.h"

void show_graph(char* file_name, node_t* graph, int amountOfNodes);

node_t* test_graph();
void test_graph_generation();

int main(void)
{

    //test procedural generation
    test_graph_generation();
    node_t* graph = generate_strongly_connected(1000,500);

    //test visualization

    show_graph("test",graph,1000);


    // Test Dijkstras
    const int amountOfNodes = 5;
    node_t nodeGraph[amountOfNodes];
    node_t srcNode = nodeGraph[0];
    node_t destNode = nodeGraph[amountOfNodes-1];
    dijkstra(nodeGraph, amountOfNodes, srcNode, destNode);

    return 0;
}

node_t* test_graph() {

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

    return graph;
}

void test_graph_generation() {

    node_t* graph = test_graph();

    run_Tarjans_algorithm(graph,7);
    run_modified_Tarjans_algorithm(graph,7);
    run_Tarjans_algorithm(graph,7);
}

void show_graph(char* file_name, node_t* graph, int amountOfNodes){
    printf("HELP MEEEE");

    GVC_t *gvc = gvContext();
    FILE* output_file = fopen(file_name,"w");

    Agraph_t *g = agopen("g",Agdirected,NULL);

    char node1Name[10];
    char node2Name[10];


    for (int i = 0; i < amountOfNodes;i++) {

        sprintf(node1Name,"%d",i);

        Agnode_t* node1 = agnode(g,node1Name,1);

        for (int j = 0; j < MAX_EDGES_PER_NODE; j++) {


            int id = graph[i].edgesFromNode[j].nodeTo->id;
            sprintf(node2Name,"%d",id);

            Agnode_t* node2 = agnode(g,node2Name,1);

            /*
             *if(id < i)
             */

            agedge(g,node1,node2,0,1);

        }
    }


    gvLayout(gvc,g,"dot");
    gvRender(gvc,g,"dot",output_file);
    gvFreeLayout(gvc,g);
    agclose(g);

}
