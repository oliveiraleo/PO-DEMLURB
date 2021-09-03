#pragma once

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "Aresta.h"

using namespace std;

namespace fs = std::filesystem;

class Grafo
{
public:
	Grafo();
	~Grafo();
	void adicionaNo(No* no);
	void adicionaAresta(Aresta* aresta);
	void imprimir();

private:
	void lerArquivo();
	vector <No> listaNos;
	vector <Aresta> listaArestas;
	
};

#endif