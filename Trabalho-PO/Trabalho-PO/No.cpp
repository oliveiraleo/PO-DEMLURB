#include "No.h"

No::No()
{
}

No::~No()
{
}

int No::getId()
{
    return id;
}

void No::setId(int id)
{
    this->id = id;
}

void No::adicionaAresta(Aresta* aresta)
{
    listaAresta.push_back(aresta);
}
