#pragma once

#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
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

	void setId(int id);
	void setNoInicio(No *no);
	void setNoDestino(No* no);
	void setPeso(double peso);
	void setPesoVolta(double peso);

private:
	int id;
	No* noInicio;
	No* noDestino;
	double peso;
	double pesoVolta;
	
};

#endif