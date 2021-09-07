// Trabalho-PO.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ilcplex/ilocplex.h"
#include "Grafo.h"

typedef IloArray<IloNumVarArray> NumVar2D; //Variável de decisão 2D
typedef IloArray<NumVar2D> NumVar3D;

int main()
{
    /*
    //Leitura do arquivo
    Grafo* grafo = new Grafo();
    grafo->imprimir();
    double** matriz = grafo->retornaMatrizDistancia();
    delete grafo;

    //Parâmetros


    //Pré processamento


    //Variáveis de decisão


    //Expressão


    //Função objetivo


    //Restrições

    */

    //Teste cplex
#pragma region Problem Data
    int nS = 4;
    int nD = 3;

    int* S = new int[nS] {10, 30, 40, 20};
    int* D = new int[nD] {20, 50, 30};

    int** C = new int* [nS];
    C[0] = new int [nD] {2, 3, 4};
    C[1] = new int [nD] {3, 2, 1};
    C[2] = new int [nD] {1, 4, 3};
    C[3] = new int [nD] {4, 5, 2};
#pragma endregion
    IloEnv env;
    IloModel Model(env);
#pragma region Decision variables


    NumVar2D X(env, nS);

    for (int s = 0; s < nS; s++) {
        X[s] = IloNumVarArray(env, nD, 0, IloInfinity, ILOINT);
    }
#pragma endregion

#pragma region Objective function
    IloExpr exp0(env);

    for (int s = 0; s < nS; s++) {
        for (int d = 0; d < nD; d++) {
            exp0 += C[s][d] * X[s][d];
        }
    }
    Model.add(IloMinimize(env, exp0));
#pragma endregion

#pragma region Constraints
    for (int s = 0; s < nS; s++) {
        IloExpr exp1(env);
        for (int d = 0; d < nD; d++) {
            exp1 += X[s][d];
        }
        Model.add(exp1 <= S[s]);
    }

    for (int d = 0; d < nD; d++) {
        IloExpr exp2(env);
        for (int s = 0; s < nS; s++) {
            exp2 += X[s][d];
        }
        Model.add(exp2 >= D[d]);
    }
#pragma endregion

    IloCplex cplex(Model);
    cplex.solve();
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
