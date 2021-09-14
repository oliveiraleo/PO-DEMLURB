#include "Aresta.h"


Aresta::Aresta()
{
    pesoVolta = numeric_limits<double>::infinity();
}

Aresta::~Aresta()
{

}


int Aresta::getId()
{
    return id;
}

No* Aresta::getNoInicio()
{
    return noInicio;
}

No* Aresta::getNoDestino()
{
    return noDestino;
}

double Aresta::getPeso()
{
    return peso;
}

double Aresta::getPesoVolta()
{
    return pesoVolta;
}

string Aresta::getDescricao()
{
    return descricao;
}

void Aresta::setId(int id)
{
    this->id = id;
}

void Aresta::setNoInicio(No* no)
{
    noInicio = no;
}

void Aresta::setNoDestino(No* no)
{
    noDestino = no;
}

void Aresta::setPeso(double peso)
{
    this->peso = peso;
}

void Aresta::setPesoVolta(double peso)
{
    pesoVolta = peso;
}

void Aresta::setDescricao(string des)
{
    descricao = des;
}
