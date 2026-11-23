//
// Created by Frede on 20-11-2026.
//

#include "graph_visualization.h"



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

