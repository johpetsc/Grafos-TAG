/*
Nome: Johannes Peter Schulte
Matricula: 150132662
Disciplina: TAG 2018/2
Projeto 4
g++ proj4.cpp -o proj4
*/
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int vetor[1005];//Vetor com a conectividade de cada vértice

void zera(){//Zera o vetor
    int i;

    for(i = 0; i < 1005; i++){
        vetor[1005] = 0;
    }
}

void arquivos(){//Le os arquivos de texto e passa para um vetor
    int atual, visinho;
    FILE *fp = fopen("email-Eu-core.txt", "r");

    while(fscanf(fp, "%d | %d ", &atual, &visinho) != EOF){
        vetor[atual-1]++;//aumenta a conectividade do vertice
        cout << "O vértice " << atual << " tem ligação com " << visinho << " e tem " << vetor[atual-1] << " visinhos." << endl;
    }
    fclose(fp);

}

void quantidade(){
    int i, j = 0, l = 0;
    int maiores[100];

    for(i = 0; i < 1005; i++){
        if(vetor[i] < 193){
            j++;
            
        }else{
            maiores[l] = i;//vertices com maior conectividade
            l++;
        }
    }

    cout << "Foram encontradas " << l-1 << " comunidades." << endl;
    getchar();
    int atual, visinho;
    
    for(i = 0; i < l-1; i++){//printa as comunidades
        cout << maiores[i] << endl;
        FILE *fp = fopen("email-Eu-core.txt", "r");
        cout << endl << "Comunidade " << i+1 << ":" << endl;
        while(fscanf(fp, "%d | %d ", &atual, &visinho) != EOF){
            if(maiores[i]+1 == atual){
                cout << visinho << " -> ";
            }
        }
        fclose(fp);
    }
    cout << endl;
}

int main(){

    zera();
    arquivos();
    quantidade();

    return 0;
}