#include "sudoku.h"

void criar_sudoku(vector<bloquinho> &sudoku, int tipo) {
    sudoku.clear();
    sudoku.resize(81);
    vector<bloquinho> ord_adj;

    for (unsigned i = 0; i < sudoku.size(); i++) {
        sudoku[i].id = i;
        sudoku[i].cores_ativas = 0;
        sudoku[i].ultimo = 0;
    }

    if (tipo == 0) {
        sudoku[0].cor = 8;
        sudoku[3].cor = 1;
        sudoku[4].cor = 5;
        sudoku[6].cor = 6;
        sudoku[12].cor = 3;
        sudoku[16].cor = 4;
        sudoku[17].cor = 1;
        sudoku[18].cor = 5;
        sudoku[24].cor = 7;
        sudoku[32].cor = 9;
        sudoku[34].cor = 6;
        sudoku[35].cor = 2;
        sudoku[40].cor = 3;
        sudoku[45].cor = 1;
        sudoku[46].cor = 4;
        sudoku[48].cor = 8;
        sudoku[56].cor = 8;
        sudoku[62].cor = 9;
        sudoku[63].cor = 2;
        sudoku[64].cor = 9;
        sudoku[68].cor = 1;
        sudoku[74].cor = 5;
        sudoku[76].cor = 9;
        sudoku[77].cor = 7;
        sudoku[80].cor = 6;

    } else if (tipo == 1) {
        bool stop = false;
        int quantidade = 0;
        int pos_x = 0;
        int pos_y = 0;
        bool flag = false;
        int contador = 0;
        vector<int> visitados;

        preencher_adjacencia(sudoku);
        //ordenar_adjacencia(sudoku, ord_adj);

        while (!stop) {
            cout << "> Voce deseja iniciar o tabuleiro com quantos numeros? (10 - 25)" << endl;
            scanf("%d%*c", &quantidade);

            if (10 <= quantidade && quantidade <= 25)
                stop = true;
        }

        do {
            flag = false;
            //contador = 0;
            pos_x = rand() % 9;
            pos_y = rand() % 9;

            do {
                if (sudoku[pos_y * 9 + pos_x].cor == 0) {
                    if (atribuir_cor(sudoku, sudoku[pos_y * 9 + pos_x], sudoku[pos_y * 9 + pos_x].ultimo + 1)) {
                        flag = true;
                        visitados.push_back(sudoku[pos_y * 9 + pos_x].id);
                        contador++;
                    } else {
                        if (!visitados.empty()) {
                                sudoku[visitados[0]].cor = 0;
                                visitados.pop_back();

                                pos_y = sudoku[visitados[0]].id / 9;
                                pos_x = sudoku[visitados[0]].id % 9;
                                flag = false;
                                contador--;
                          
                        } else { // nao eh para acontecer (nao tem saida)
                            flag = true;
                            contador--;
                        }
                    }
                } else {    // procura outra posicao
                    flag = true;
                }

            } while (!flag);
        } while (contador < quantidade);

        for (unsigned i = 1; i < sudoku.size(); i++) {
            sudoku[i].ultimo = 0;
        }

        //printar_sudoku(sudoku);
    } else {
        return;
    }

    return;
}

void printar_sudoku(vector<bloquinho> &sudoku) {
    // system(CLEAR);

    cout << "-------------------------" << '\n';
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 0) {
                cout << "| ";
            }
            cout << sudoku[j + i * 9].cor << ' ';
            if ((j + 1) % 3 == 0) {
                cout << "| ";
            }
        }
        cout << '\n';
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << " ----------------------- " << '\n';
        }
    }
    cout << "-------------------------" << '\n';
    cout << "Pressione ENTER para continuar!";
    getchar();
}

void preencher_adjacencia(vector<bloquinho> &sudoku) {
    int modx, mody;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            /* Linha */
            for (int k = 0; k < 9; k++) {
                if ((j + i * 9) != (k + i * 9)) {
                    sudoku[j + i * 9].adj_linha.push_back(&sudoku[k + i * 9]);
                    if (sudoku[k + i * 9].cor != 0)
                        sudoku[j + i * 9].cores_ativas++;
                }
                //cout << "Meu *" << j+i*9 << "* vizinho na linha eh: " << sudoku[k+i*9].cor << '\n';
            }
            /* Coluna */
            for (int k = 0; k < 9; k++) {
                if ((j + i * 9) != (j + k * 9)) {
                    sudoku[j + i * 9].adj_coluna.push_back(&sudoku[j + k * 9]);
                    if (sudoku[j + k * 9].cor != 0) {
                        sudoku[j + i * 9].cores_ativas++;
                        // cout << sudoku[j + i*9].cor << " : " << j+k*9 << " : " << sudoku[j + k*9].cor << endl;
                    }
                }
            }

            /* Deslocamento para Bloco, obviamente tem jeitos melhores de se fazer isso, mas foi o que pensamos na hora :c */
            modx = (j % 3);		/* Isso servirá para descobrir em qual bloco 3x3 ele pertence */
            mody = (i % 3);
            int deslocado = 0;

            modx = j - modx;
            mody = i - mody;

            deslocado = (modx + mody * 9);

            for (int k = 0; k < 9; k++) {
                if (deslocado != (j + i * 9)) {
                    bool existente = false;
                    for (unsigned m = 0; m < sudoku[j + i * 9].adj_linha.size() && !existente; m++) {
                        if (sudoku[j + i * 9].adj_linha[m]->id == sudoku[deslocado].id) {
                            existente = true;
                        }
                    }
                    for (unsigned m = 0; m < sudoku[j + i * 9].adj_coluna.size() && !existente; m++) {
                        if (sudoku[j + i * 9].adj_coluna[m]->id == sudoku[deslocado].id) {
                            existente = true;
                        }
                    }
                    if (!existente) {
                        sudoku[j + i * 9].adj_bloco.push_back(&sudoku[deslocado]);
                        if (sudoku[deslocado].cor != 0)
                            sudoku[j + i * 9].cores_ativas++;
                    }

                    //   cout << "Meu *" << j+i*9 << "* vizinho no bloco eh: " << sudoku[deslocado].cor << '\n';
                    //   cout << "Deslocado: " << deslocado << '\n';
                }
                if ((deslocado + 1) % 3 == 0) {
                    deslocado += 9;
                    deslocado -= 2;
                } else {
                    deslocado++;
                }
            }
            // cout << sudoku[j+i*9].cor << " : " << sudoku[j+i*9].cores_ativas << " : " << j << ',' << i << endl;
        }
    }
}

int possibilidade_colorir(bloquinho &colorir) {
    int possibilidades = 0;
    for (int i = 1; i < 10; i++) {
        if (!cor_repetida2(colorir, i)) {
            possibilidades++;
        }
    }

    return possibilidades;
}

void ordenar_adjacencia(vector<bloquinho> sudoku, vector<bloquinho> &ord_adj) {
    ord_adj.clear();
    while (!sudoku.empty()) {
        int maior = 0;
        int maior_possibilidade = possibilidade_colorir(sudoku[maior]);

        for (unsigned i = 1; i < sudoku.size(); i++) {
            int possibilidade = possibilidade_colorir(sudoku[i]);
            if (possibilidade < maior_possibilidade) {
                maior = i;
                maior_possibilidade = possibilidade;
            }
        }

        if(sudoku[maior].cor == 0)
            ord_adj.push_back(sudoku[maior]);

        sudoku.erase(sudoku.begin() + maior);

        // cout << sudoku.size() << endl;
        // system("pause");
    }

    //printar_sudoku(ord_adj);
}

bool cor_repetida2(bloquinho &colorir, int cor) {
    if (colorir.cor != 0) {
        //cout << "Bloquinho ja colorido: " << colorir.id << endl;
        return true;
    }

    /* verifica cores na linha */
    for (unsigned i = 0; i < colorir.adj_linha.size(); i++) {
        if (colorir.adj_linha[i]->cor == cor) {
            return true;
        }
    }

    /* verifica cores na coluna */
    for (unsigned i = 0; i < colorir.adj_coluna.size(); i++) {
        if (colorir.adj_coluna[i]->cor == cor) {
            return true;
        }
    }

    /* verifica cores no bloco */
    for (unsigned i = 0; i < colorir.adj_bloco.size(); i++) {
        if (colorir.adj_bloco[i]->cor == cor) {
            return true;
        }
    }

    return false;
}

bool criar_solucao(vector<bloquinho> &sudoku, vector<bloquinho> &ord_adj) {
    vector<int> visitados;
    int contador = 1;
    bool tem_solucao = true;

    while (!ord_adj.empty() && tem_solucao) {
        contador++;
        tem_solucao = true;

        cout << "> Etapa (" << contador << "):" << endl;

        if (ord_adj[0].cor == 0) {
            if (atribuir_cor(sudoku, ord_adj[0], ord_adj[0].ultimo + 1)) {
                cout << "> Colorindo na posicao (" << (ord_adj[0].id % 9) << ", " << (ord_adj[0].id / 9) << ")";
                cout << " - (cor " << sudoku[ord_adj[0].id].cor << ")" << endl;

                visitados.push_back(ord_adj[0].id);
                ord_adj.erase(ord_adj.begin());
            } else {
                if (!visitados.empty()) {
                    /* XXX Tomar cuidado, visitados pode causar seg fault aqui XXX */
                    ord_adj.insert(ord_adj.begin(), sudoku[visitados[visitados.size() - 1]]);
                    visitados.pop_back();
                    ord_adj[0].cor = 0;
                    sudoku[ord_adj[0].id].cor = 0;

                    cout << "> Descolorindo na posicao (" << (ord_adj[0].id % 9) << ", " << (ord_adj[0].id / 9) << ")";
                    cout << endl;
                } else { // nao tem nenhuma opcao disponivel
                    tem_solucao = false;

                    cout << "Nao foi possivel resolver o sudoku!" << endl;
                    getchar();
                }

                for (unsigned int i = 1; i < ord_adj.size(); i++) {
                    ord_adj[i].ultimo = 0;
                }
            }
        } else { // bloquinho pintado previamente
            ord_adj.erase(ord_adj.begin());

            cout << "> Posicao (" << (ord_adj[0].id % 9) << ", " << (ord_adj[0].id / 9) << ") jah colorida ";
            cout << "(cor " << ord_adj[0].cor << ")" << endl;
        }

        ordenar_adjacencia(ord_adj, ord_adj); // reordenar por grau de adjacencia (cores)

        printar_sudoku(sudoku); // mostrar cada etapa
    }

    if (tem_solucao)
        return true;
    else
        return false;
}

bool verificar_inconsistencia(bloquinho colorir) {
    bool travou = true;
    for (unsigned i = 0; i < colorir.adj_coluna.size(); i++) {
        if (colorir.adj_coluna[i]->cor == 0) {
            travou = true;
            for (int j = 1; j < 10; j++) {
                if (!cor_repetida2(*colorir.adj_coluna[i], j)) {
                    travou = false;
                }
            }

            if (travou)
                return true;
        }
    }

    for (unsigned i = 0; i < colorir.adj_linha.size(); i++) {
        if (colorir.adj_linha[i]->cor == 0) {
            travou = true;
            for (int j = 1; j < 10; j++) {
                if (!cor_repetida2(*colorir.adj_linha[i], j)) {
                    travou = false;
                }
            }

            if (travou)
                return true;
        }
    }

    for (unsigned i = 0; i < colorir.adj_bloco.size(); i++) {
        if (colorir.adj_bloco[i]->cor == 0) {
            travou = true;
            for (int j = 1; j < 10; j++) {
                if (!cor_repetida2(*colorir.adj_bloco[i], j)) {
                    travou = false;
                }
            }

            if (travou)
                return true;
        }
    }

    return false;
}

bool atribuir_cor(vector<bloquinho> &sudoku, bloquinho colorir, int inicio) {
    for (int i = inicio; i < 10; i++) {
        if (!cor_repetida2(sudoku[colorir.id], i)) {
            sudoku[colorir.id].cor = i;
            if (!verificar_inconsistencia(sudoku[colorir.id])) {
                sudoku[colorir.id].ultimo = i;
                return true;
            } else {
                sudoku[colorir.id].cor = 0;
            }
        }
    }
    return false;
}

bool atribuir_cor_rand(vector<bloquinho> &sudoku, bloquinho colorir) {
    int cor = colorir.ultimo + 1 + (rand() % (9 - colorir.ultimo));

    if (!cor_repetida2(sudoku[colorir.id], cor)) {
        sudoku[colorir.id].cor = cor;
        if (!verificar_inconsistencia(sudoku[colorir.id])) {
            sudoku[colorir.id].ultimo = cor;
            return true;
        } else {
            sudoku[colorir.id].cor = 0;
        }
    }

    return false;
}

void Menu(int &opcao) {
    bool valido = false;

    while (!valido) {
        system(CLEAR);
        cout << "========== SUDOKU ==========" << '\n';
        cout << "1. Sudoku default" << endl;
        cout << "2. Sudoku aleatorio" << endl;
        cout << "3. Instrucoes" << endl;
        cout << "4. Sair" << endl;
        cout << "> ";
        scanf("%d%*c", &opcao);
        //cin >> opcao;
        if (1 <= opcao && opcao <= 4)
            valido = true;
    }
}

void Instrucoes() {
    system(CLEAR);
    cout << "========================= Instrucoes ===========================" << endl;
    cout << " Regras do Sudoku:" << endl;
    cout << "  - Nao pode ter numero (cor) repetida na linha;" << endl;
    cout << "  - Nao pode ter numero (cor) repetida na coluna;" << endl;
    cout << "  - Nao pode ter numero (cor) repetida no bloco (3x3)." << endl;
    cout << endl;
    cout << " Menu:" << endl;
    cout << "  - Opcao 1: Executa o tabuleiro exemplificado para o trabalho;" << endl;
    cout << "  - Opcao 2: Gera um tabuleiro aleatorio e tenta solucionar;" << endl;
    cout << "  - Opcao 3: Exibe a tela atual;" << endl;
    cout << "  - Opcao 4: Fecha o programa." << endl;
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
    cout << "Pressione ENTER para voltar!";
    getchar();
}