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

vector<int> Grafo::retornaRota(int** matriz, int numNos)
{
	vector<int> rota;
	rota.push_back(0);
	int atual = 0;
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

		for (int i = 0; i < filhos.size(); i++)
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
		}
	}
	double valor = 0;
	double** m = retornaMatrizDistancia();
	for (int i = 1; i < rota.size(); i++) {
		matriz[rota.at(i - 1)][rota.at(i)] += 1;
		valor = valor + m[rota.at(i - 1)][rota.at(i)];
	}
	cout << "Distancia gasta considerando retornos " << valor <<"m" << endl;


	gravaRota(rota);

	return rota;
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
		escolha = 0;
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
	nomeArquivo = nomeArquivos.at(escolha);
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

	if (res.size() == 0) {
		delimiter = ",";
		while ((pos_end = linha.find(delimiter, pos_start)) != string::npos) {
			token = linha.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}
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
		aresta->setDescricao(res.at(3));
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



void Grafo::gravaRota(vector<int> rota)
{
	string path = "ArquivoResultado/";
	ofstream out(path+"Resultado.txt");
	Aresta* a;

	out << "Resultado do arquivo: " << nomeArquivo << endl;

	out << "Caminho formado por ruas:" << endl;

	double distancia = 0;
	for (int i = 1; i < rota.size();i++) {
		a = getAresta(rota.at(i - 1), rota.at(i));
		out << a->getDescricao() << "-> ";
		distancia = distancia + a->getPeso();
	}
	out << endl;
	out << "Caminho formado por pontos: " << endl;

	for (int i = 1; i < rota.size(); i++) {
		out << "(" << rota.at(i - 1) << "," << rota.at(i) << ") ";
	}
	out << endl;
	out << "Distância percorrida: " << distancia << "m" << endl;

	cout << endl;
	//out << input;
	out.close();

	out= ofstream(path + "Resultado2.txt");

	out << "Resultado do arquivo: " << nomeArquivo << endl;
	out << "Distância percorrida: " << distancia << "m" << endl;
	out << "Caminho formado por ruas:" << endl;

	string anterior="";
	for (int i = 1; i < rota.size(); i++) {
		a = getAresta(rota.at(i - 1), rota.at(i));

		out << anterior << "-> "<< a->getDescricao()<<endl ;
		anterior = a->getDescricao();
	}
	out << endl;
	out << "Caminho formado por pontos: " << endl;

	for (int i = 1; i < rota.size(); i++) {
		out << "(" << rota.at(i - 1) << "," << rota.at(i) << ") ";
	}
	out << endl;


	cout << endl;
	//out << input;
	out.close();
}


