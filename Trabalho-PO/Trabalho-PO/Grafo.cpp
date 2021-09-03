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
	for (int i = 0; i < listaNos.size(); i++) {
		cout << listaNos.at(i).getId()<<" ";
	}
	cout << endl;
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
		while (!arquivo.eof()) //enquanto end of file for false continua
		{
			arquivo >> linha; // como foi aberto em modo texto(padrão)
								   //e não binário(ios::bin) pega cada linha
			//cout << linha << endl;

		}
		arquivo.close();
	}
	else {
		cout << "Nao foi possivel abrir o arquivo.\n";
	}
}
