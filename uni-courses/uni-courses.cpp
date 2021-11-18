/*
name: Johannes Peter Schulte
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

vector <string> graph[33];
string names[32];
int j[7];
int P[32];

void showList(int k){ // shows adjacency list
    vector <string> :: iterator it;

    for(it = graph[k].begin(); it != graph[k].end(); ++it){
        cout << *it << "; ";
    }
    cout << "END" << endl << endl; 
}

void createList(char name[], int vertex_num){ //create adjacency lists
    int i;

    cout << "List of vertex " << vertex_num << endl;
    if(j[0] == 0){
        graph[vertex_num-1].push_back(name);
        showList(vertex_num-1);
    }else if(j[1] == 0){
        graph[vertex_num-1].push_back(name);
        graph[vertex_num-1].push_back(names[j[0]-1]);
        showList(vertex_num-1);
    }else if(j[2] == 0){
        graph[vertex_num-1].push_back(name);
        for(i = 0; i < 2; i++){
            graph[vertex_num-1].push_back(names[j[i]-1]);
        }
        showList(vertex_num-1);
    }else if(j[3] == 0){
        graph[vertex_num-1].push_back(name);
        for(i = 0; i < 3; i++){
            graph[vertex_num-1].push_back(names[j[i]-1]);
        }
        showList(vertex_num-1);
    }else{
        graph[vertex_num-1].push_back(name);
        for(i = 0; i < 8; i++){
            graph[vertex_num-1].push_back(names[j[i]-1]);
        }
        showList(vertex_num-1);
    }
}

void searchVertices(){ // searches for every vertex and its attributes in the text file
    char name[40], requirements[22];
    int credits, vertex_num, weight, i = 0, k = 0;

    FILE *fp = fopen("courses.txt", "r");

    while(fscanf(fp, "%d | %[^|] | %d | %d | %[^\n] ", &vertex_num, name, &credits, &weight, requirements) != EOF){

        for(i = 0; i < 7; i++){
            j[i] = 0;
        }

        if(requirements[0] != '0'){
            i = 0;
            while(requirements[i] != '\0'){
                i++;
            }
            if(i == 1){
                j[0] = requirements[0] - 48;
                createList(name, vertex_num);
            }else if(i == 2){
                j[0] = ((requirements[0] - 48) * 10) + (requirements[1] -48);
                createList(name, vertex_num);
            }else if(i == 4){
                j[0] = requirements[0] - 48;
                j[1] = ((requirements[2] - 48) * 10) + (requirements[3] -48);
                createList(name, vertex_num);
            }else if(i == 5){
                j[0] = ((requirements[0] - 48) * 10) + (requirements[1] -48);
                j[1] = ((requirements[3] - 48) * 10) + (requirements[4] -48);
                createList(name, vertex_num);
            }else if(i == 6){
                j[0] = requirements[0] - 48;
                j[1] = requirements[2] - 48;
                j[2] = ((requirements[4] - 48) * 10) + (requirements[5] -48);
                createList(name, vertex_num);
            }else if(i == 7){
                j[0] = requirements[0] - 48;
                j[1] = ((requirements[2] - 48) * 10) + (requirements[3] -48);
                j[2] = ((requirements[5] - 48) * 10) + (requirements[6] -48);
                createList(name, vertex_num);
            }else if(i == 8){
                j[0] = ((requirements[0] - 48) * 10) + (requirements[1] -48);
                j[1] = ((requirements[3] - 48) * 10) + (requirements[4] -48);
                j[2] = ((requirements[6] - 48) * 10) + (requirements[7] -48);
                createList(name, vertex_num);
            }else{
                j[0] = ((requirements[0] - 48) * 10) + (requirements[1] -48);
                j[1] = ((requirements[3] - 48) * 10) + (requirements[4] -48);
                j[2] = ((requirements[6] - 48) * 10) + (requirements[7] -48);
                j[3] = ((requirements[9] - 48) * 10) + (requirements[10] -48);
                j[4] = ((requirements[12] - 48) * 10) + (requirements[13] -48);
                j[5] = ((requirements[15] - 48) * 10) + (requirements[16] -48);
                j[6] = ((requirements[18] - 48) * 10) + (requirements[19] -48);
                j[7] = ((requirements[21] - 48) * 10) + (requirements[22] -48);
                createList(name, vertex_num);
            }
        }else{
            createList(name, vertex_num);
        }
        k++;
    }

}

void auxFunction(){ //stores attributes in auxiliary vectors
    char name[40], requirements[22];
    int credits, vertex_num, weight, i = 0;

    FILE *fp = fopen("courses.txt", "r");

    while(fscanf(fp, "%d | %[^|] | %d | %d | %[^\n] ", &vertex_num, name, &credits, &weight, requirements) != EOF){
        names[vertex_num-1] = name;
        P[vertex_num-1] = (credits * weight);

    }
    for(i = 0; i < 33; i++){
        cout << names[i] << "| weight: " << P[i] << endl;
    }
    fclose(fp);
}

void criticalPath(){// calculates and shows the critical path
    int i, j, k;
    string aux;
    int cc, cc_value;
    int valores[32];
    vector <string> :: iterator it;
    vector <string> path;

    cout << endl << "LIST OF EVERY COURSE AND THE WEIGHT OF ITS LIST" << endl << endl;
    for(i = 0; i < 32; i++){
        cc_value = 0;
        for(it = graph[i].begin(); it != graph[i].end(); ++it){
            aux = *it;
            for(j = 0; j < 32; j++){
                if(aux.compare(names[j]) == 0){
                    k = j;
                }
            }
            cc_value = cc_value + P[k];
        }
        cout << "Course: " << names[i] << " weight: " << cc_value << endl;
        valores[i] = cc_value;
    }
    for(i = 0; i < 32; i++){
        if(valores[i] > cc_value){
            cc_value = valores[i];
            cc = i;
        }
    }

    it = graph[cc].begin();
    aux = *it;
    path.push_back(aux);
    it++;
    aux = *it;
    path.push_back(aux);
    i = 0;
    while(names[i].compare(aux) != 0){
            i++;
    }
    it = graph[i].begin();
    it++;
    aux = *it;
    path.push_back(aux);
    it = graph[15].begin();
    it++;
    aux = *it;
    path.push_back(aux);
    it = graph[20].begin();
    it++;
    aux = *it;
    path.push_back(aux);
    cout << "Course with the longest path: " << names[cc] << ", weight:" << cc_value << endl;

    while(i > 5){
        for(i = 0; i < cc; i++){
            for(it = graph[i].begin(); it != graph[i].end(); ++it){
                aux = *it;
                if(aux.compare(names[cc]) == 0){
                    path.insert(path.begin(), names[i]);
                    cc = i;
                }
            }
        }
    }
    cout << endl;
    cout << "Critical path: " << endl << endl;
    for(it = path.begin(); it != path.end(); ++it){
        cout << *it << "->";
    }
    cout << "END" << endl;

}

void topologicalSorting(){
    vector <string> :: iterator it;
    vector <string> :: iterator it2;
    vector <string> topological;
    string aux, aux2;
    int flag;
    int i;

    for(i = 0; i < 32; i++){
        for(it = graph[i].begin(); it != graph[i].end(); ++it){
            for(it2 = topological.begin(); it2 != topological.end(); it2++){
                aux = *it;
                aux2 = *it2;
                if(aux.compare(aux2) == 0){
                    flag = 1;
                }
            }
            if(flag != 1){
                topological.push_back(*it);
            }
            flag = 0;
        }
    }
    for(it2 = topological.begin(); it2 != topological.end(); it2++){
        cout << *it2 << endl;
    }

}

int main(){
    cout << "LIST OF ADJACENCY OF EACH VERTEX: " << endl;
    cout << endl << "Press ENTER to continue." << endl;
    getchar();
    auxFunction();
    searchVertices();
    cout << endl << "Press ENTER to continue." << endl;
    getchar();
    cout << endl << "TOPLOGICAL SORTING: " << endl;
    cout << endl << "Press ENTER to continue." << endl;
    getchar();
    topologicalSorting();
    cout << endl << "Press ENTER to continue." << endl;
    getchar();
    cout << endl << "CRITICAL PATH: " << endl;
    cout << endl << "Press ENTER to continue." << endl;
    getchar();
    criticalPath();
    cout << endl << "Press ENTER to continue." << endl;
    getchar();

    return 0;
}