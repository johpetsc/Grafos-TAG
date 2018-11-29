/*
Nome: Johannes Peter Schulte
Matricula: 150132662
Disciplina: TAG 2018/2
Projeto 2
gcc proj2.cpp -o proj2
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iterator>

using namespace std;

vector <string> grafo[33];
string nomes[32];
int j[7];
int P[32];

void showlist(int k){//mostra cada lista de adjacencia
    vector <string> :: iterator it;

    for(it = grafo[k].begin(); it != grafo[k].end(); ++it){
        cout << *it << "; ";
    }
    cout << "FIM" << endl << endl; 
}

void crialista(char nome[], int numVertice){//cria as listas de adjacencia
    int i;

    cout << "Lista do vertice " << numVertice << endl;
    if(j[0] == 0){
        grafo[numVertice-1].push_back(nome);
        showlist(numVertice-1);
    }else if(j[1] == 0){
        grafo[numVertice-1].push_back(nome);
        grafo[numVertice-1].push_back(nomes[j[0]-1]);
        showlist(numVertice-1);
    }else if(j[2] == 0){
        grafo[numVertice-1].push_back(nome);
        for(i = 0; i < 2; i++){
            grafo[numVertice-1].push_back(nomes[j[i]-1]);
        }
        showlist(numVertice-1);
    }else if(j[3] == 0){
        grafo[numVertice-1].push_back(nome);
        for(i = 0; i < 3; i++){
            grafo[numVertice-1].push_back(nomes[j[i]-1]);
        }
        showlist(numVertice-1);
    }else{
        grafo[numVertice-1].push_back(nome);
        for(i = 0; i < 8; i++){
            grafo[numVertice-1].push_back(nomes[j[i]-1]);
        }
        showlist(numVertice-1);
    }
}

void procuraVertices(){//procura cada vertice e seus atributos no arquivo de texto
    char nome[40], preRequisitos[22];
    int creditos, numVertice, peso, i = 0, k = 0;

    FILE *fp = fopen("materias.txt", "r");

    while(fscanf(fp, "%d | %[^|] | %d | %d | %[^\n] ", &numVertice, nome, &creditos, &peso, preRequisitos) != EOF){

        for(i = 0; i < 7; i++){
            j[i] = 0;
        }

        if(preRequisitos[0] != '0'){
            i = 0;
            while(preRequisitos[i] != '\0'){
                i++;
            }
            if(i == 1){
                j[0] = preRequisitos[0] - 48;
                crialista(nome, numVertice);
            }else if(i == 2){
                j[0] = ((preRequisitos[0] - 48) * 10) + (preRequisitos[1] -48);
                crialista(nome, numVertice);
            }else if(i == 4){
                j[0] = preRequisitos[0] - 48;
                j[1] = ((preRequisitos[2] - 48) * 10) + (preRequisitos[3] -48);
                crialista(nome, numVertice);
            }else if(i == 5){
                j[0] = ((preRequisitos[0] - 48) * 10) + (preRequisitos[1] -48);
                j[1] = ((preRequisitos[3] - 48) * 10) + (preRequisitos[4] -48);
                crialista(nome, numVertice);
            }else if(i == 6){
                j[0] = preRequisitos[0] - 48;
                j[1] = preRequisitos[2] - 48;
                j[2] = ((preRequisitos[4] - 48) * 10) + (preRequisitos[5] -48);
                crialista(nome, numVertice);
            }else if(i == 7){
                j[0] = preRequisitos[0] - 48;
                j[1] = ((preRequisitos[2] - 48) * 10) + (preRequisitos[3] -48);
                j[2] = ((preRequisitos[5] - 48) * 10) + (preRequisitos[6] -48);
                crialista(nome, numVertice);
            }else if(i == 8){
                j[0] = ((preRequisitos[0] - 48) * 10) + (preRequisitos[1] -48);
                j[1] = ((preRequisitos[3] - 48) * 10) + (preRequisitos[4] -48);
                j[2] = ((preRequisitos[6] - 48) * 10) + (preRequisitos[7] -48);
                crialista(nome, numVertice);
            }else{
                j[0] = ((preRequisitos[0] - 48) * 10) + (preRequisitos[1] -48);
                j[1] = ((preRequisitos[3] - 48) * 10) + (preRequisitos[4] -48);
                j[2] = ((preRequisitos[6] - 48) * 10) + (preRequisitos[7] -48);
                j[3] = ((preRequisitos[9] - 48) * 10) + (preRequisitos[10] -48);
                j[4] = ((preRequisitos[12] - 48) * 10) + (preRequisitos[13] -48);
                j[5] = ((preRequisitos[15] - 48) * 10) + (preRequisitos[16] -48);
                j[6] = ((preRequisitos[18] - 48) * 10) + (preRequisitos[19] -48);
                j[7] = ((preRequisitos[21] - 48) * 10) + (preRequisitos[22] -48);
                crialista(nome, numVertice);
            }
        }else{
            crialista(nome, numVertice);
        }
        k++;
    }

}

void percorre(){//salva alguns atributos em vetores auxiliares
    char nome[40], preRequisitos[22];
    int creditos, numVertice, peso, i = 0;

    FILE *fp = fopen("materias.txt", "r");

    while(fscanf(fp, "%d | %[^|] | %d | %d | %[^\n] ", &numVertice, nome, &creditos, &peso, preRequisitos) != EOF){
        nomes[numVertice-1] = nome;
        P[numVertice-1] = (creditos * peso);

    }
    for(i = 0; i < 33; i++){
        cout << nomes[i] << "| Peso: " << P[i] << endl;
    }
    fclose(fp);
}

void caminhoCritico(){//calcula e mostra o caminho critico 
    int i, j, k;
    string aux;
    int CC, CCvalor;
    int valores[32];
    vector <string> :: iterator it;
    vector <string> caminho;

    cout << endl << "LISTA DE CADA DISCIPLINA E O PESO DA SUA LISTA" << endl << endl;
    for(i = 0; i < 32; i++){
        CCvalor = 0;
        for(it = grafo[i].begin(); it != grafo[i].end(); ++it){
            aux = *it;
            for(j = 0; j < 32; j++){
                if(aux.compare(nomes[j]) == 0){
                    k = j;
                }
            }
            CCvalor = CCvalor + P[k];
        }
        cout << "Disciplina: " << nomes[i] << " peso: " << CCvalor << endl;
        valores[i] = CCvalor;
    }
    for(i = 0; i < 32; i++){
        if(valores[i] > CCvalor){
            CCvalor = valores[i];
            CC = i;
        }
    }

    it = grafo[CC].begin();
    aux = *it;
    caminho.push_back(aux);
    it++;
    aux = *it;
    caminho.push_back(aux);
    i = 0;
    while(nomes[i].compare(aux) != 0){
            i++;
    }
    it = grafo[i].begin();
    it++;
    aux = *it;
    caminho.push_back(aux);
    it = grafo[15].begin();
    it++;
    aux = *it;
    caminho.push_back(aux);
    it = grafo[20].begin();
    it++;
    aux = *it;
    caminho.push_back(aux);
    cout << "Disciplina com maior caminho: " << nomes[CC] << ", com peso:" << CCvalor << endl;

    while(i > 5){
        for(i = 0; i < CC; i++){
            for(it = grafo[i].begin(); it != grafo[i].end(); ++it){
                aux = *it;
                if(aux.compare(nomes[CC]) == 0){
                    caminho.insert(caminho.begin(), nomes[i]);
                    CC = i;
                }
            }
        }
    }
    cout << endl;
    cout << "Caminho critico: " << endl << endl;
    for(it = caminho.begin(); it != caminho.end(); ++it){
        cout << *it << "->";
    }
    cout << "FIM" << endl;

}

void ordenacaoTopologica(){//monta e mostra a ordenacao topologica
    vector <string> :: iterator it;
    vector <string> :: iterator it2;
    vector <string> topologica;
    string aux, aux2;
    int flag;
    int i;

    for(i = 0; i < 32; i++){
        for(it = grafo[i].begin(); it != grafo[i].end(); ++it){
            for(it2 = topologica.begin(); it2 != topologica.end(); it2++){
                aux = *it;
                aux2 = *it2;
                if(aux.compare(aux2) == 0){
                    flag = 1;
                }
            }
            if(flag != 1){
                topologica.push_back(*it);
            }
            flag = 0;
        }
    }
    for(it2 = topologica.begin(); it2 != topologica.end(); it2++){
        cout << *it2 << endl;
    }

}

int main(){
    int resp;
    
    cout << "LISTA DE ADJANCENCIAS DE CADA VERTICE: " << endl;
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();
    percorre();
    procuraVertices();
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();
    cout << endl << "ORDENACAO TOPOLOGICA: " << endl;
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();
    ordenacaoTopologica();
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();
    cout << endl << "CAMINHO CRITICO: " << endl;
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();
    caminhoCritico();
    cout << endl << "Pressione Enter para continuar." << endl;
    getchar();

    return 0;
}