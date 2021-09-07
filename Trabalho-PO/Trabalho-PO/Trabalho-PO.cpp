// Trabalho-PO.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ilcplex/ilocplex.h"
#include "Grafo.h"

typedef IloArray<IloNumVarArray> NumVar2D; //Variável de decisão 2D
typedef IloArray<NumVar2D> NumVar3D;

int main()
{
    
#pragma region Criando o grafo
    //Leitura do arquivo
    Grafo* grafo = new Grafo();
    grafo->imprimir();
#pragma endregion

#pragma region Parametros
    int numArestas = grafo->quantidadeArestas();
    int numNos = grafo->quatidadeNos();
    double** M = grafo->retornaMatrizDistancia();
    //Teste cplex
#pragma region Problem Data
    int nS = numNos;
    int nD = numNos;

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
        X[s] = IloNumVarArray(env, nD, 0, IloInfinity, ILOFLOAT);
    }
#pragma endregion

#pragma region Objective function
    IloExpr exp0(env);

    for (int s = 0; s < nS; s++) {
        for (int d = 0; d < nD; d++) {
            exp0 += (M[s][d] * X[s][d]);
        }
    }
    Model.add(IloMinimize(env, exp0));
#pragma endregion

#pragma region Constraints
    
    for (int s = 0; s < nS; s++) {
        IloExpr exp1(env);
        for (int d = 0; d < nD; d++) {
            if (M[s][d] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    exp1 += X[s][d];
                    Model.add(exp1 >= 1);
                }
            }
        }
    }


    for (int d = 0; d < nD; d++) {
        IloExpr exp3(env);
        for (int s = 0; s < nS; s++) {
            if (M[s][d] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    exp3 += X[s][d];
                    Model.add(exp3 >= 1);
                }
            }
        }
    }




    /*
    for (int d = 0; d < nD; d++) {
        IloExpr exp2(env);
        for (int s = 0; s < nS; s++) {
            if (s != d) {
                exp2 += X[s][d];
                Model.add(exp2 >= 1);
            }
        }
    }
    
    for (int d = 0; d < nD; d++) {
        IloExpr exp3(env);
        for (int s = 0; s < nS; s++) {
            if (M[s][d]!= numeric_limits<double>::infinity() ) {
                if (s != d) {
                    exp3 += X[s][d];
                    Model.add(exp3 >= 1);
                }
            }
        }
    }
    */
#pragma endregion
    IloCplex cplex(Model);
    cplex.setOut(env.getNullStream());
    cplex.solve();

    if (!cplex.solve()) {
        env.error() << "Não foi possivel obter o resultado!" << endl;
        throw(-1);
    }

    double obj = cplex.getObjValue();

    cout << "O caminho otimizado percorrido foi: " << obj << endl;
    int cont = 0;
    for (int i = 0; i < nS; i++)
    {
        for (int j = 0; j < nD; j++)
        {
            if (cplex.isExtracted(X[i][j])) {
                double Xval = cplex.getValue(X[i][j]);
                if (Xval > 0) {
                    cont++;
                    cout << "\t X[" << i << "][" << j << "] = " << Xval << endl;
                } 
            }
        }
    }
    cout << "Ha " << cont << " ruas, era para ser: " <<numArestas<<  endl;
    /*
#pragma region Criando o grafo
    //Leitura do arquivo
    Grafo* grafo = new Grafo();
    grafo->imprimir();
#pragma endregion

#pragma region Parametros
    int numArestas = grafo->quantidadeArestas();
    int numNos = grafo->quatidadeNos();
    double** matriz = grafo->retornaMatrizDistancia();
#pragma endregion

#pragma region Pre-processamento
    IloEnv ambiente;
    IloModel Modelo(ambiente);

#pragma endregion

#pragma region Variaveis de decisao
    NumVar2D X(ambiente, numNos);

    for (int i = 0; i < numNos; i++) {
        X[i] = IloNumVarArray(ambiente, numNos, 0, IloInfinity, ILOFLOAT);
    }

#pragma endregion
    
#pragma region Expressao

#pragma endregion

#pragma region Funcao Objetivo
    IloExpr exp0(ambiente);

    for (int i = 0; i < numNos; i++) {
        for (int j = 0; j < numNos; j++) {
            if (i != j) {
                double teste = matriz[i][j];//
               // teste = teste *X[i][j];
                exp0 += (teste * X[i][j]);
            }
        }     
    }
    Modelo.add(IloMinimize(ambiente, exp0));
#pragma endregion

#pragma region Restricoes
    
    /*
    for (int i = 0; i < numNos; i++) {
        IloExpr exp1(ambiente);
        for (int j = 0; j < numNos; j++) {
            exp1 += X[i][j];
            Modelo.add(exp1 <= matriz[i][j]);
        }
    }

    for (int j = 0; j < numNos; j++) {
        IloExpr exp2(ambiente);
        for (int i = 0; i < numNos; i++) {
            exp2 += X[i][j];
            Modelo.add(exp2 >= matriz[j][i]);
        }
    }
    
    
#pragma endregion

#pragma region Pos-processamento

    IloCplex cplex(Modelo);
    cplex.setOut(ambiente.getNullStream());
    cplex.solve();
    
    if (!cplex.solve()) {
        ambiente.error() << "Não foi possivel obter o resultado!" << endl;
        throw(-1);
    }

    double obj = cplex.getObjValue();

    cout << "O caminho otimizado percorrido foi: " << obj << endl;

    for (int i = 0; i < numNos; i++)
    {
        for (int j = 0; j < numNos; j++)
        {
            if (cplex.isExtracted((X[0][0]))) {
                double Xval = cplex.getValue(X[0][0]);
                cout << "\t X[" << i << "][" << j << "] = " << Xval << endl;
            }
           
        }
    }

    delete grafo;
#pragma endregion
    */

    
    /*
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
    cplex.setOut(env.getNullStream());
    cplex.solve();

    if (!cplex.solve()) {
        env.error() << "Não foi possivel obter o resultado!" << endl;
        throw(-1);
    }

    double obj = cplex.getObjValue();

    cout << "O caminho otimizado percorrido foi: " << obj << endl;

    for (int i = 0; i < nS; i++)
    {
        for (int j = 0; j < nD; j++)
        {
            double Xval = cplex.getValue(X[i][j]);
            cout << "\t X[" << i << "][" << j << "] = " << Xval << endl;
        }
    }
    */
   // cplex.solve();

   
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
