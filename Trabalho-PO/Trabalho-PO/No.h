#pragma once
#ifndef NO_H
#define NO_H


#include <iostream>
#include <vector>
//#include <iostream>
#include "Aresta.h"

using namespace std;
class Aresta;
class No
{
public:
	No();
	~No();
	int getId();

	void setId(int id);

private:
	int id;
	vector <Aresta> listaAresta;
	//Aresta a;
};
#endif
