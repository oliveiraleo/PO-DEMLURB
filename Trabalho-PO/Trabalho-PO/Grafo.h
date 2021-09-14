#pragma once

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include "Aresta.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>

using namespace std;

namespace fs = std::filesystem;

class Grafo
{
public:
	Grafo();
	~Grafo();
	//void adicionaNo(No* no);
	//void adicionaAresta(Aresta* aresta);
	void imprimir();
	double** retornaMatrizDistancia();
	int quantidadeArestas();
	int quatidadeNos();
	bool vericaAresta(int noInicio, int noDestino);
	vector <int> retornaRota(int** matriz, int numNos);

private:
	void lerArquivo();
	vector <No*> listaNos;
	vector <Aresta*> listaArestas;
	void auxAdicionaElemento(string linha);
	bool verificaNo(int id);
	No* getNo(int id);
	Aresta* getAresta(int idInicio, int idDestino);
	string nomeArquivo;
	void gravaRota(vector <int> rota);
};

#endif