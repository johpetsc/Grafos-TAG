/* Universidade de Brasília
   Teoria e Aplicação de Grafos 2018/2
   Projeto 1

   Johannes Peter Schulte 15/0132662
*/

#include <stdio.h>
#include <stdlib.h>
#include "readgml.h"

int main(){
    NETWORK *network; // network.h
    FILE *fp; // read karate.gml file
    int i = 0, j = 0, l = 0, h = 0; // loop variables
    int matrix[34][17]; // matrix that stores neighbors
    int clustering = 0, neighbor;
    float dividend, divisor;
    float clustering_average = 0;
    float clustering_print;

    for(i = 0; i < 34; i++){ // fills matrix with 0s
        for(j = 0; j < 17; j++){
            matrix[i][j] = 0;
        }
    }

    fp = fopen("karate.gml", "r"); // open file

    network = (NETWORK *)malloc(sizeof(NETWORK)); // graph network memory allocation

    read_network(network, fp); // creates karate network

    fclose(fp);

    printf("===========GRAPH SIZE============\n");
    printf("Graph has %d vertices \n", network->nvertices);
    printf("\nPress ENTER to print each vertex degree and neighbors...\n");
    getchar();

    for (i = 0; i < network->nvertices; i++) {// loop that goes through every vertex
        printf("Vertex %d, degree: %d \n", network->vertex[i].id, network->vertex[i].degree);
	 	printf("Neighbors: ");
	 	for(j = 0; j < network->vertex[i].degree; j++){// loop that goes through every neighbor
	 		printf("[%d] ", network->vertex[i].edge[j].target + 1);
            matrix[i][j] = network->vertex[i].edge[j].target + 1;
	 	}
        printf("\n\n");
  	}

    printf("\nPress ENTER to print the clustering coefficient of the graph...\n");
    getchar();

    // calculates the clustering coefficient
    for(i = 0; i < network->nvertices; i++){ // loop that goes through every vertex
        for(j = 0; j < network->vertex[i].degree; j++){// loop that goes through every neighbor
            neighbor = matrix[i][j];
            for(h = 0; h < network->vertex[neighbor-1].degree; h++){// loop that goes through every neighbor of a neighbor
                for(l = 0; l < network->vertex[i].degree; l++){// compares the neighbors of the vertex and its neighbors
                    if(matrix[i][l] == matrix[neighbor-1][h]){
                        clustering++;
                    }
                }
            }
        }
        dividend = clustering;
        divisor = network->vertex[i].degree*(network->vertex[i].degree-1);
        if(divisor != 0){
            clustering_average = clustering_average + (dividend/divisor);
            clustering_print = dividend/divisor;
        }else{
            clustering_print = 0;
        }

        printf("Clustering coefficient of vertex %d: %.3f\n", network->vertex[i].id, clustering_print);
    
        clustering = 0;
    }

    printf("\nPress ENTER to print the average clustering coefficient...\n");
    getchar();

    printf("Average clustering coefficient: %.5f\n", clustering_average/34);
    
    free_network(network);
    free(network);

    return 0;
}
