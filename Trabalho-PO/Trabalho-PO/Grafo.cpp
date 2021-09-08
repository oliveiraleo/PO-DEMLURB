#include "Grafo.h"

using namespace std;
Grafo::Grafo()
{
	lerArquivo();
}

Grafo::~Grafo()
{

}

void Grafo::imprimir()
{
	for (int i = 0; i < listaArestas.size(); i++) {
		cout << listaArestas.at(i)->getId() <<": " << listaArestas.at(i)->getNoInicio()->getId() <<"->"<< listaArestas.at(i)->getNoDestino()->getId() << " "<< listaArestas.at(i)->getPeso() << "  " << listaArestas.at(i)->getPesoVolta()<<endl;
	}
	cout << endl;
}

double** Grafo::retornaMatrizDistancia()
{
	double** matriz = new double*[listaNos.size()];
	for (int i = 0; i < listaNos.size(); i++) {
		matriz[i] = new double[listaNos.size()];
	}

	//preencher a matriz com valores 0 ou infinito
	for (int i = 0; i < listaNos.size(); i++) {
		for (int j = 0; j < listaNos.size(); j++) {
			if (i == j) {
				matriz[i][j] = 0;
			}
			else {
				matriz[i][j] = numeric_limits<double>::infinity();
			}
		}
	}

	for (Aresta* a : listaArestas) {
		matriz[a->getNoInicio()->getId()][a->getNoDestino()->getId()] = a->getPeso();
		if (a->getPesoVolta() !=200000) {
		//if (a->getPesoVolta() != numeric_limits<double>::infinity()) {
			matriz[a->getNoDestino()->getId()][a->getNoInicio()->getId()] = a->getPesoVolta();
		}
	}

	/*
	for (int i = 0; i < listaNos.size(); i++) {
		for (int j = 0; j < listaNos.size(); j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}*/
	
	return matriz;
}

int Grafo::quantidadeArestas()
{
	return listaArestas.size();
}

int Grafo::quatidadeNos()
{
	return listaNos.size();
}

bool Grafo::vericaAresta(int noInicio, int noDestino)
{
	for (Aresta *a :listaArestas)
	{
		if ((a->getNoInicio()->getId() ==noInicio) && (a->getNoDestino()->getId()==noDestino)) {
			return true;
		}
	}
	return false;
}

void Grafo::lerArquivo()
{
	string path = "ArquivoLeitura";
	int index = 0;
	vector <string> nomeArquivos;
	cout << "Escolha um número correspondente ao arquivo ou -1 para sair " << endl;
	for (const auto& entry : fs::directory_iterator(path)) {
		cout << index << " - " << entry.path() << endl;
		string caminhoArquivo = entry.path().string();
		nomeArquivos.push_back(caminhoArquivo);
		index++;
	}

	/*
	for (int i = 0; i < nomeArquivos.size(); i++) {
		cout << nomeArquivos.at(i) << endl;
	}*/

	int escolha = -2;
	if (nomeArquivos.size() == 0) {
		cout << "Não há arquivos para selecao, saindo do programa" << endl;
		exit(1);
	}

	while (true) {
		//cout << "Digite um valor correspondente ao arquivo ou -1 para sair"<<endl;
		//escolha = 0;
		cin >> escolha;
		if (escolha >= 0 && escolha < nomeArquivos.size()) {

			break;
		}
		else if (escolha == -1) {
			exit(0);
		}
	}

	ifstream arquivo;
	arquivo.open(nomeArquivos.at(escolha));
	//arquivo.open("ArquivoLeitura/tabela-emparelhamento-sorted-by-cost.csv");
	string linha;

	if (arquivo.is_open()) {
		while (getline(arquivo, linha)) {
			//cout << linha << endl;
			auxAdicionaElemento(linha);
		}
		/*
		while (!arquivo.eof()) //enquanto end of file for false continua
		{
			arquivo >> linha; // como foi aberto em modo texto(padrão)
							   //e não binário(ios::bin) pega cada linha
			cout << linha << endl;
			//auxAdicionaElemento(linha);
		}*/
		arquivo.close();
	}
	else {
		cout << "Nao foi possivel abrir o arquivo.\n";
	}
}

void Grafo::auxAdicionaElemento(string linha)
{
	string delimiter = ";";
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = linha.find(delimiter, pos_start)) != string::npos) {
		token = linha.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(linha.substr(pos_start));

	if (res.at(0)=="no_inicial") {
		return;
	}


	bool existeNoInicio = verificaNo(stoi(res.at(0)));
	bool existeNoDestino = verificaNo(stoi(res.at(1)));

	No* noInicio;
	No* noDestino;

	if (!existeNoInicio) {
		noInicio = new No();
		noInicio->setId(stoi(res.at(0)));
		listaNos.push_back(noInicio);
	}
	else {
		noInicio = getNo(stoi(res.at(0)));
	}

	if (!existeNoDestino) {
		noDestino = new No();
		noDestino->setId(stoi(res.at(1)));
		listaNos.push_back(noDestino);
	}
	else {
		noDestino = getNo(stoi(res.at(1)));
	}

	Aresta* aresta = getAresta(stoi(res.at(0)), stoi(res.at(1)));
	if (aresta == nullptr) {
		aresta = new Aresta();
		aresta->setNoDestino(noDestino);
		aresta->setNoInicio(noInicio);
		aresta->setPeso(stod(res.at(2)));
		aresta->setId(listaArestas.size());
		listaArestas.push_back(aresta);
		noInicio->adicionaAresta(aresta);
		noDestino->adicionaAresta(aresta);
	}
	else {
		aresta->setPesoVolta(stod(res.at(2)));
	}

}


bool Grafo::verificaNo(int id)
{
	for (No* i : listaNos)
	{
		if (i->getId() == id) {
			return true;
		}
	}
	return false;
}

No* Grafo::getNo(int id)
{
	for (No* i : listaNos)
	{
		if (i->getId() == id) {
			return i;
		}
	}
	return nullptr;
}

Aresta* Grafo::getAresta(int idInicio, int idDestino)
{
	for (Aresta* a : listaArestas)
	{
		if ((a->getNoInicio()->getId() == idInicio) && (a->getNoDestino()->getId() == idDestino)) {
			return a;
		}
	}
	return nullptr;
}


