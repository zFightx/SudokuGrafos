
#ifndef __SUDOKU_H__

#define __SUDOKU_H__

#include <iostream>
#include <vector>
#include <ctime>
//#include <cstdlib>

#ifdef _WIN32
    #define CLEAR   "cls"
#else
    #define CLEAR   "clear"
#endif

using namespace std;

struct bloquinho{
    int id;
    int cor;
    vector <bloquinho*> adj_linha, adj_coluna, adj_bloco;
    int cores_ativas;
    int ultimo;
};

void criar_sudoku(vector<bloquinho> &sudoku, int tipo);
void printar_sudoku(vector<bloquinho> &sudoku);
void preencher_adjacencia(vector<bloquinho> &sudoku);
void ordenar_adjacencia(vector<bloquinho> sudoku, vector<bloquinho> &ord_adj);
bool cor_repetida2(bloquinho &colorir, int cor);
bool criar_solucao(vector<bloquinho> &sudoku, vector<bloquinho> &ord_adj);
int possibilidade_colorir(bloquinho &colorir);
bool atribuir_cor(vector<bloquinho> &sudoku, bloquinho colorir, int inicio);
bool atribuir_cor_rand(vector<bloquinho> &sudoku, bloquinho colorir, int inicio);
void Menu (int &opcao);
void Instrucoes();
#endif