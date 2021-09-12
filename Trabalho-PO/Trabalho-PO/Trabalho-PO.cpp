// Trabalho-PO.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "ilcplex/ilocplex.h"
#include "Grafo.h"
#include <cmath>

typedef IloArray<IloNumVarArray> NumVar2D; //Variável de decisão 2D
typedef IloArray<NumVar2D> NumVar3D;

bool verificaTodasAsRotas(int** matriz, int numNos) {
    for (int i = 0; i < numNos; i++)
    {
        for (int j = 0; j < numNos; j++)
        {
            if (matriz[i][j] > 0) {
                return false;
            }
        }
    }
    return true;
}

void imprimeRota(int** matriz, int numNos) {
    int atual = 0;
    cout << "Rota:" << endl;
   // cout << "0->";
    vector <int> rota;
    rota.push_back(0);
    while (!verificaTodasAsRotas(matriz, numNos)) {
        for (int j = 0; j < numNos; j++) {
            if (matriz[atual][j] > 0) {
                matriz[atual][j] -= 1;
                rota.push_back(j);
                atual = j;
                j = -1;
            }
        }
        if (verificaTodasAsRotas(matriz, numNos)) {
            break;
        }
        vector <int> path;
        int pai = atual;
        vector <int> filhos;

        for (int i = 1; i < rota.size(); i++)
        {
            if (rota.at(i - 1) == pai) {
                filhos.push_back(rota.at(i));
            }
        }

        for  (int i = 0;i< filhos.size();i++)
        {

            for (int j = 0; j < numNos; j++) {
                if (matriz[filhos.at(i)][j] > 0) {
                    atual = filhos.at(i);
                    rota.push_back(atual);
                    break;
                }
            }
            if (atual != pai) {
                break;
            }
        }

        if (atual == pai) {
            bool proxEncontrado = false;
            for (int i = 0; i < rota.size(); i++) {
                int index = rota.at(i);
                for (int j = 0; j < numNos; j++) {
                    if (matriz[index][j] > 0) {
                        atual = index;
                        proxEncontrado = true;
                        break;
                    }
                }
                if (proxEncontrado) {
                    break;
                }
            }

            proxEncontrado = false;
            for (int i = 0; i < rota.size(); i++) {
                if (rota.at(i) == pai) {
                    path.clear();
                    proxEncontrado = true;
                }
                else if (proxEncontrado) {
                    path.push_back(rota.at(i));
                }
                if (rota.at(i) == atual) {
                    break;
                }
            }
            bool evitaLongoCaminho = false;
            while (!evitaLongoCaminho)
            {
                int no1, no2;
                int pos1, pos2;
                for (int i = 0; i < path.size(); i++)
                {
                    no1 = path.at(i);
                    pos1 = i;
                    evitaLongoCaminho = true;
                    for (int j = 0; j < path.size(); j++)
                    {
                        no2 = path.at(j);
                        pos2 = j;
                        if (i != j) {
                            if (no1 == no2) {
                                evitaLongoCaminho = false;
                                break;
                            }
                        }
                    }
                    if (!evitaLongoCaminho) {
                        break;
                    }
                }
                if (path.size() == 0) {
                    break;
                }
                if (!evitaLongoCaminho) {
                    path.erase(path.begin() + pos1, path.begin() + pos2);
                }
               


            }
            

            rota.insert(rota.end(), path.begin(), path.end());

            /*
            bool proxEncontrado = false;
            for (int i = 0; i < numNos;i++) {
                for (int j=0; j < numNos; j++) {
                    if (matriz[i][j] > 0) {
                        atual = j;
                        proxEncontrado = true;
                        break;
                    }
                }
                if (proxEncontrado) {
                    break;
                }
            }

            proxEncontrado = false;
            for (int i = 0; i < rota.size();i++) {
                if (rota.at(i)==pai) {
                    path.clear();
                    proxEncontrado = true;
                } 
                else if (proxEncontrado) {
                    path.push_back(i);
                } 
                if (rota.at(i) == atual) {
                    break;
                }
            }
            rota.insert(rota.end(), path.begin(), path.end());
            */
        }


        /*
        vector <int> path;
        int pai = i;
        vector <int> filhos;
        for (int i = 0; i < length; i++)
        {

        }
            for e in range(len(E)) :
                if E[e] == 0 :
                    continue
                    if E[e][1] == v :
                        pai.append(E[e][0])
                        break

                        if not pai :
                            for i in range(len(rota)) :
                                if i != 0 :
                                    pai.append(rota[i])
                                    if rota[i] == v :
                                        break

                                        #print("List is empty")
                                        for i in rota :
        if i != atual :
            path.append(i)
            if i == pai[0] :
                break
                return v, path

                for i in rota :
        if i != atual :
            if i == pai[0] :
                break
            else :
                path.append(i)
                */

    }
    for (int i : rota) {
        cout << i << " -> ";
    }
    cout << endl;

}




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
    double** matriz = grafo->retornaMatrizDistancia();
    //Teste cplex
    
#pragma endregion

    IloEnv env;
    IloModel Model(env);
#pragma region Variaveis de decisao

    NumVar2D X(env, numNos);

    for (int s = 0; s < numNos; s++) {
        X[s] = IloNumVarArray(env, numNos, 0, IloInfinity, ILOFLOAT);
    }
#pragma endregion

#pragma region Funcao Objetivo
    IloExpr exp0(env);

    for (int s = 0; s < numNos; s++) {
        for (int d = 0; d < numNos; d++) {
            exp0 += (matriz[s][d] * X[s][d]);
        }
    }
    Model.add(IloMinimize(env, exp0));
#pragma endregion

#pragma region Restricoes
    
    for (int s = 0; s < numNos; s++) {
        for (int d = 0; d < numNos; d++) {
            IloExpr exp1(env);
            if (matriz[s][d] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    exp1 += X[s][d];
                    Model.add(exp1 >= 1);
                }
            }
        }
    }
    
    for (int d = 0; d < numNos; d++) {
        for (int s = 0; s < numNos; s++) {
            IloExpr exp2(env);
            if (matriz[s][d] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    exp2 += X[s][d];
                    Model.add(exp2 >= 1);
                }
            }
        }
    }

    /*O conjunto de arestas
orientadas será denotado por Ed. Para a execução, a partir de agora, d(v) será a diferença entre o
número de arcos e arestas orientadas que entram em v e o número de arcos e arestas orientadas
que saem de v, ou seja, d(v) = d(v)− - d(v)+ .*/

    for (int d = 0; d < numNos; d++) {
        for (int s = 0; s < numNos; s++) {
            IloExpr exp3(env);
            int numEntrada = 0;
            int numSaida = 0;
            int numEntradaDestino = 0;
            int numSaidaDestino = 0;
            for (int j = 0; j < numNos; j++)
            {
                if (matriz[d][j]>0 && (matriz[d][j]!=numeric_limits<double>::infinity())) {
                    numSaida += 1;
                }
                if (matriz[j][d]>0 && (matriz[j][d]!=numeric_limits<double>::infinity())) {
                    numEntrada += 1;
                }
                if (matriz[s][j] > 0 && (matriz[s][j] != numeric_limits<double>::infinity())) {
                    numSaidaDestino += 1;
                }
                if (matriz[j][s] > 0 && (matriz[j][s] != numeric_limits<double>::infinity())) {
                    numEntradaDestino += 1;
                }
            }
            if (matriz[d][s] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    //exp3 += X[s][d];
                    int saldo = numEntrada - numSaida;
                    exp3 += X[d][s];
                    if (saldo > 0) {
                       // exp3 += X[d][s];
                        if (saldo == 1)
                            saldo += 1;
                    }
                    
                    else if(saldo<0) {
                       //exp3 += X[d][s];

                        //saldo = saldo *(-1);

                        //if(saldo==1)
                        //saldo += 1;
                    }
                    if (numEntradaDestino - numSaidaDestino < 0) {
                        if (numSaidaDestino != 0) {
                            if (saldo < 0) {
                                saldo = (saldo * (-1)) + numEntradaDestino - numSaidaDestino ;
                            }
                            else {
                                saldo = saldo + abs(numEntradaDestino - numSaidaDestino);
                            }
                        }
                    }
                    //saldo += 1;
                    Model.add(exp3 >= saldo);
                }
            }
        }
    }

    /*
    bool* isPercorrido = new bool[numArestas];
    int *qtdPercorrido = new int[numArestas];
    for (int i = 0; i < numArestas; i++) {
        isPercorrido[i] = false;
        qtdPercorrido[i] = 0;
    }

    while (true)
    {

        bool todosPercorrido = false;
        for (int i = 0; i < numArestas;i++) {
            if (!isPercorrido[i]) {
                todosPercorrido = false;
                break;
            }
            else {
                todosPercorrido = true;
            }
        }
        if (todosPercorrido) {
            break;
        }
    }
    */
    //Model.add(exp1 == exp2);
/*
    for (int d = 0; d < numNos; d++) {
        for (int s = 0; s < numNos; s++) {
            IloExpr exp3(env);
            if (matriz[s][d] != numeric_limits<double>::infinity()) {
                if (s != d) {
                    exp3 += X[s][d];
                    Model.add(exp3 >= 1);
                }
            }
        }
    }
*/



    /*
    for (int d = 0; d < numNos; d++) {
        IloExpr exp2(env);
        for (int s = 0; s < numNos; s++) {
            if (s != d) {
                exp2 += X[s][d];
                Model.add(exp2 >= 1);
            }
        }
    }
    
    for (int d = 0; d < numNos; d++) {
        IloExpr exp3(env);
        for (int s = 0; s < numNos; s++) {
            if (matriz[s][d]!= numeric_limits<double>::infinity() ) {
                if (s != d) {
                    exp3 += X[s][d];
                    Model.add(exp3 >= 1);
                }
            }
        }
    }
    */
#pragma endregion

#pragma region Processamento

    IloCplex cplex(Model);
    //cplex.setOut(env.getNullStream());
    cplex.solve();

    if (!cplex.solve()) {
        env.error() << "Não foi possivel obter o resultado!" << endl;
        throw(-1);
    }

    double obj = cplex.getObjValue();

    cout << "O caminho otimizado percorrido foi: " << obj << endl;
    int cont = 0;
    int* vet = new int[numNos];
    int** matrizPercorrida = new int *[numNos];

    for (int i = 0; i < numNos;i++) {
        vet[i] = 0;
        matrizPercorrida[i] = new int[numNos];
    }

    for (int i = 0; i < numNos; i++)
    {
        for (int j = 0; j < numNos; j++)
        {
            matrizPercorrida[i][j] = 0;
            if (cplex.isExtracted(X[i][j])) {
                double Xval = cplex.getValue(X[i][j]);
                if (Xval > 0) {
                    cont++;
                    cout << "\t X[" << i << "][" << j << "] = " << Xval << endl;
                    matrizPercorrida[i][j] = Xval;
                    vet[j] += Xval;
                }  
            }
            cout << matrizPercorrida[i][j] << " ";
        }
        cout << endl;
    }
   // cout << "Ha " << cont << " ruas, era para ser: " <<numArestas<<  endl;
    for (int i = 0; i < numNos; i++) {
      //  cout << vet[i] << endl;
    }
    imprimeRota(matrizPercorrida, numNos);
#pragma endregion


    delete grafo;

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
