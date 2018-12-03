/* Universidade de Brasília
   Teoria e Aplicação de Grafos 2018/2
   Projeto 1

   Johannes Peter Schulte 15/0132662
*/

#include <stdio.h>
#include <stdlib.h>
#include "readgml.h"

int main(){
    NETWORK *network; //utilização do network.h
    FILE *fp; //leitura do arquivo karate.gml
    int i = 0, j = 0, l = 0, h = 0; //variaveis para loop
    int matriz[34][17]; //matriz que armazena todos os vizinhos
    int clustering = 0, vizinho;
    float dividendo, divisor;
    float clusteringMedio = 0;
    float clusteringPrint;

    for(i = 0; i < 34; i++){ //preenche a matriz de vizinhos com 0 para evitar lixo de memória
        for(j = 0; j < 17; j++){
            matriz[i][j] = 0;
        }
    }
    fp = fopen("karate.gml", "r"); // abre o arquivo

    network = (NETWORK *)malloc(sizeof(NETWORK)); //aloca memoria para o grafo

    read_network(network, fp); //abre o grafo com o parser

    fclose(fp); //fecha a leitura do arquivo

    printf("===========TAMANHO DO GRAFO============\n");
    printf("Grafo possui %d vértices \n", network->nvertices);
    printf("\nPressione Enter para visualizar o grau e os vizinhos de cada vértice...\n");
    getchar();

    for (i = 0; i < network->nvertices; i++) {//loop que passa por todos os vertices do grafo
        printf("Vértice %d, grau: %d \n", network->vertex[i].id, network->vertex[i].degree);
	 	printf("Vizinhos: ");
	 	for(j = 0; j < network->vertex[i].degree; j++){//loop que passa por todos os vizinhos do vertice
	 		printf("[%d] ", network->vertex[i].edge[j].target + 1);
            matriz[i][j] = network->vertex[i].edge[j].target + 1;
	 	}
        printf("\n\n");
  	}

    printf("\nPressione Enter para visualizar o coeficiente de aglomeração/agrupamento...\n");
    getchar();
    //calcula os coeficientes de agrupamento
    for(i = 0; i < network->nvertices; i++){//loop para todos os vertices
        for(j = 0; j < network->vertex[i].degree; j++){//loop para todos os vizinhos do vertice
            vizinho = matriz[i][j];
            for(h = 0; h < network->vertex[vizinho-1].degree; h++){//loop para todos os vizinhos do vizinho
                for(l = 0; l < network->vertex[i].degree; l++){//compara os vizinhos do vertice com os do seu vizinho
                    if(matriz[i][l] == matriz[vizinho-1][h]){
                        clustering++;
                    }
                }
            }
        }
        dividendo = clustering;
        divisor = network->vertex[i].degree*(network->vertex[i].degree-1);
        if(divisor != 0){
            clusteringMedio = clusteringMedio + (dividendo/divisor);
            clusteringPrint = dividendo/divisor;
        }else{
            clusteringPrint = 0;
        }

        printf("Coeficiente de aglomeração/agrupamento do vértice %d: %.3f\n", network->vertex[i].id, clusteringPrint);
    
        clustering = 0;
    }

    printf("\nPressione Enter para visualizar o coeficiente medio...\n");
    getchar();

    printf("Coeficiente de agrupamento medio: %.5f\n", clusteringMedio/34);
    

    /*for(i = 0; i < 34; i++){
        for(j = 0; j < 17; j++){
            printf("[%d]", matriz[i][j]); //visualização da matriz de vizinhos
        }
        printf("\n");
    }*/
    free_network(network);
    free(network);

    return 0;
}
