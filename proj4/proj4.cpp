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

int vetor[1005];

void zera(){
    int i;

    for(i = 0; i < 1005; i++){
        vetor[1005] = 0;
    }
}

void conexao(){
    int menor = 1005, menorV;
    int i;

    for(i = 0; i < 1005; i++){
        if(vetor[i] < menor){
            menor = vetor[i];
            menorV = i;
        }
    }

}

void arquivos(){//Le os arquivos de texto e passa para um vetor
    int atual, visinho;
    FILE *fp = fopen("email-Eu-core.txt", "r");

    while(fscanf(fp, "%d | %d ", &atual, &visinho) != EOF){
        vetor[atual-1]++;
        cout << "O vértice " << atual << " tem ligação com " << visinho << " e tem " << vetor[atual-1] << " visinhos." << endl;
    }
    fclose(fp);

}

int main(){

    zera();
    arquivos();

    return 0;
}