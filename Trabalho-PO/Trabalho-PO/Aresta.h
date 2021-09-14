#pragma once

#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <limits>
#include "No.h"


using namespace std;

class No;

class Aresta
{
public:
	
	Aresta();
	~Aresta();

	int getId();
	No* getNoInicio();
	No* getNoDestino();
	double getPeso();
	double getPesoVolta();
	string getDescricao();

	void setId(int id);
	void setNoInicio(No *no);
	void setNoDestino(No* no);
	void setPeso(double peso);
	void setPesoVolta(double peso);
	void setDescricao(string des);

private:
	int id;
	No* noInicio;
	No* noDestino;
	double peso;
	double pesoVolta;
	string descricao;
	
};

#endif