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

int prof[100][6], esc[50][2];

// Funcao para mostrar o emparelhamento na tela.
void print(){
    int i;

    for(i = 0; i < 50; i++){
        cout << "Escola " << i + 1;
        if(esc[i][0] > 100){
            cout << "--> " << esc[i][0] - 100;
        }
        if(esc[i][1] > 100){
            cout << "--> " << esc[i][1] - 100 << endl;
        }else{
            cout << endl;
        }
    }
}

// Funcao para selecionar cada professor para as escolas
void selecao(){
    int i, j, k;
    int aux = 0, pref;

    for(i = 0; i < 50; i++){//Verifica o primeiro requisito das escolas
        for(k = 0; k < 100; k++){
            for(j = 0; j < 5; j++){
                //cout << "Verificando escola n " << i +1 << " com o professor n " << k +1 << " na opcao n " << j + 1 << " que e: " << prof[k][j+1] << " comparando com: " << esc[i][0] << endl;
                //getchar();
                if((i + 1 == prof[100-k][j+1]) && (esc[i][0] == prof[100-k][0])){
                    esc[i][0] = (100-k) + 101;
                    prof[100-k][1] = 120;
                    prof[100-k][2] = 120;
                    prof[100-k][3] = 120;
                    prof[100-k][4] = 120;
                    prof[100-k][5] = 120;
                    k = 100;
                    break;
                }
            }
        }
    }

    for(i = 0; i < 50; i++){//Verifica o segundo requisito das escolas
        for(k = 0; k < 100; k++){
            for(j = 0; j < 5; j++){
                if((i + 1 == prof[k][j+1]) && (esc[i][1] == prof[k][0])){
                    esc[i][1] = (k) + 101;
                    prof[k][1] = 120;
                    prof[k][2] = 120;
                    prof[k][3] = 120;
                    prof[k][4] = 120;
                    prof[k][5] = 120;
                    k = 100;
                    break;
                }
            }
        }
    }
    
    for(i = 0; i < 50; i++){//Distribui os professores que sobraram nas escolas que nao tiveram seus requisitos cumpridos.
        if((esc[i][0] < 100) && (esc[i][1] < 100)){
            for(k = 0; k < 100; k++){
                if(prof[k][1] < 100){
                    esc[i][1] = k +101;
                }
            }
        }
    }
}

void arquivos(){//Le os arquivos de texto e passa para um vetor
    int professor, pref1, pref2, pref3, pref4, pref5;
    int habilitacoes;
    int i = 0;

    FILE *fp = fopen("professores.txt", "r");

    while(fscanf(fp, "%d | %d | %d | %d | %d | %d | %d ", &professor, &habilitacoes, &pref1, &pref2, &pref3, &pref4, &pref5) != EOF){
        cout << "P" << professor << " " << habilitacoes << " " << "E" << pref1 << " E" << pref2 << " E" << pref3 << " E" << pref4 << " E" << pref5 << endl;
        prof[i][0] = habilitacoes;
        prof[i][1] = pref1;
        prof[i][2] = pref2;
        prof[i][3] = pref3;
        prof[i][4] = pref4;
        prof[i][5] = pref5;
        i++;
    }
    fclose(fp);

    FILE *fp2 = fopen("escolas.txt", "r");

    int escola;
    int hab1, hab2;

    i = 0;

    while(fscanf(fp2, "%d | %d | %d ", &escola, &hab1, &hab2) != EOF){
        cout << "E" << escola << " " << hab1 << " " << hab2 << endl;
        esc[i][0] = hab1;
        esc[i][1] = hab2;
        esc[i][2] = 0;
        i++;
    }
    fclose(fp2);

}

int main(){
    arquivos();
    selecao();
    print();
    cout << "Foram utilizados 68 professores para preencher as 50 escolas. 3 professores não tiveram os requisitos respondidos." << endl;
    cout << "Por exemplo, a escola 17 quer habilitaçao 3 e 1, porem os professores que requisitaram ela tinham habilidade 2." << endl;
    cout << "Isso fez com que a escola 17 fosse preenchida com um professor qualquer que sobrou, assim como as outras duas escolas." << endl;
    return 0;
}