/*
Nome: Johannes Peter Schulte
Matricula: 150132662
Disciplina: TAG 2018/2
Projeto 3
g++ proj3.cpp -o proj3
*/
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int teachers[100][6], schools[50][2];

// prints matched vertices
void printMatching(){
    for(int i = 0; i < 50; i++){
        cout << "School " << i + 1;
        if(schools[i][0] > 100){
            cout << "--> " << schools[i][0] - 100;
        }
        if(schools[i][1] > 100){
            cout << "--> " << schools[i][1] - 100 << endl;
        }else{
            cout << endl;
        }
    }
}

// function that matches schools and teachers
void createMatches(){
    int i, j, k;

    for(i = 0; i < 50; i++){ // checks the first school requirement
        for(k = 0; k < 100; k++){
            for(j = 0; j < 5; j++){
                if((i + 1 == teachers[100-k][j+1]) && (schools[i][0] == teachers[100-k][0])){
                    schools[i][0] = (100-k) + 101;
                    teachers[100-k][1] = 120;
                    teachers[100-k][2] = 120;
                    teachers[100-k][3] = 120;
                    teachers[100-k][4] = 120;
                    teachers[100-k][5] = 120;
                    k = 100;
                    break;
                }
            }
        }
    }

    for(i = 0; i < 50; i++){ // checks the second school requirement
        for(k = 0; k < 100; k++){
            for(j = 0; j < 5; j++){
                if((i + 1 == teachers[k][j+1]) && (schools[i][1] == teachers[k][0])){
                    schools[i][1] = (k) + 101;
                    teachers[k][1] = 120;
                    teachers[k][2] = 120;
                    teachers[k][3] = 120;
                    teachers[k][4] = 120;
                    teachers[k][5] = 120;
                    k = 100;
                    break;
                }
            }
        }
    }
    
    for(i = 0; i < 50; i++){ // distributes the teachers that did  not fulfill any requirement
        if((schools[i][0] < 100) && (schools[i][1] < 100)){
            for(k = 0; k < 100; k++){
                if(teachers[k][1] < 100){
                    schools[i][1] = k +101;
                }
            }
        }
    }
}

void readFiles(){ // reads text files and inserts the content into matrixes
    int teacher_id, preference_1, preference_2, preference_3, preference_4, preference_5;
    int qualifications;

    FILE *fp = fopen("teachers.txt", "r");

    while(fscanf(fp, "%d | %d | %d | %d | %d | %d | %d ", &teacher_id, &qualifications, &preference_1, &preference_2, &preference_3, &preference_4, &preference_5) != EOF){
        cout << "P" << teacher_id << " " << qualifications << " " << "E" << preference_1 << " E" << preference_2 << " E" << preference_3 << " E" << preference_4 << " E" << preference_5 << endl;
        teachers[i][0] = qualifications;
        teachers[i][1] = preference_1;
        teachers[i][2] = preference_2;
        teachers[i][3] = preference_3;
        teachers[i][4] = preference_4;
        teachers[i][5] = preference_5;
    }
    fclose(fp);

    FILE *fp2 = fopen("schools.txt", "r");

    int school;
    int hab_1, hab_2;

    while(fscanf(fp2, "%d | %d | %d ", &school, &hab_1, &hab_2) != EOF){
        cout << "E" << school << " " << hab_1 << " " << hab_2 << endl;
        schools[i][0] = hab_1;
        schools[i][1] = hab_2;
        schools[i][2] = 0;
    }
    fclose(fp2);

}

int main(){
    readFiles();
    createMatches();
    printMatching();

    return 0;
}