#include "graph_visualization.h"

#include "graphGenerator.h"

void show_graph(char *file_name, node_t *graph, int amountOfNodes) {

    char extension[] = "png";

    GVC_t *gvc = gvContext();

    Agraph_t *g = agopen("g", Agdirected,NULL);

    char node1Name[10];
    char node2Name[10];

    for (int i = 0; i < amountOfNodes; i++) {
        sprintf(node1Name, "%d", i);

        Agnode_t *node1 = agnode(g, node1Name, 1);


        int node_size = get_free_from_slot(graph[i]);

        if (node_size == -1) {
            node_size = MAX_EDGES_PER_NODE;
        }

        for (int j = 0; j < node_size; j++) {
            int id = graph[i].edgesFromNode[j].nodeTo->id;
            sprintf(node2Name, "%d", id);

            Agnode_t *node2;


             if(id > i) {
                 node2 = agnode(g, node2Name, 1);
             }
            else {
                node2 = agnode(g, node2Name, 0);
            }


            agedge(g, node1, node2, 0, 1);
        }
    }


    gvLayout(gvc, g, "dot");

    char cat_file_name[50] = "graphs/";

    strcat(cat_file_name,file_name);
    strcat(cat_file_name,".");
    strcat(cat_file_name,extension);

    gvRenderFilename(gvc, g, extension, cat_file_name);
    gvFreeLayout(gvc, g);
    agclose(g);

    printf("created graph\n");
}
