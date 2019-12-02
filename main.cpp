#include "sudoku.h"

int main(){
    vector<bloquinho> sudoku;                   // tabuleiro do Sudoku
    vector<bloquinho> ord_adj;                  // adjacencias ordenadas por maior grau (maior quantidade de cores vizinhas)
    int opcao = 0;
    bool stop = false;


    srand(time(NULL));

    while (!stop) {    // sair
        //setbuf(stdin, NULL);
        Menu(opcao);

        if (opcao == 3) {
            Instrucoes();
        }
        else if (opcao == 1) {
            criar_sudoku(sudoku, 0);            // gera o sudoku (0 - default; 1 - randomico)
            printar_sudoku(sudoku);             // printa o tabuleiro
            preencher_adjacencia(sudoku);       // procurar vizinhos adjacentes conforme as regras do sudoku
            //cout << "Possibilidade: " << possibilidade_colorir(sudoku[0*9 + 8]) << '\n';
            //system("PAUSE");
            ordenar_adjacencia(sudoku, ord_adj);
            criar_solucao(sudoku, ord_adj);
            
            //system(CLEAR);
            cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
            cout << ">> Sudoku final:" << endl;
            printar_sudoku(sudoku);
        }
        else if (opcao == 2) {          // opcao 2
            criar_sudoku(sudoku, 1);            // gera o sudoku (0 - default; 1 - randomico)
            //printar_sudoku(sudoku);             // printa o tabuleiro
            preencher_adjacencia(sudoku);       // procurar vizinhos adjacentes conforme as regras do sudoku
            ordenar_adjacencia(sudoku, ord_adj);
            criar_solucao(sudoku, ord_adj);
            cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
            cout << ">> Sudoku final:" << endl;
            printar_sudoku(sudoku);
        }
        else stop = true;
    }

    // system(CLEAR);
    return 0;
}