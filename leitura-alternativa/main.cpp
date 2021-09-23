#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<map<int, string>>::iterator it;

string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Não foi possivel abrir o arquivo - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{
    string file_path("../arquivos/tabela-emparelhamento-sorted-by-cost.csv"); // caminho do arquivo a ser lido
    string file_contents;
    map<int, vector<string>> csv_contents; // conteudo lido
    char delimiter = ';'; // separador utilizado no arquivo CSV

    file_contents = readFileIntoString(file_path);

    istringstream sstream(file_contents);
    vector<string> items;
    string record;

    int counter = 0;
    while (getline(sstream, record)) {
        istringstream line(record);
        while (getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
    // Imprime o que foi lido no arquivo de entrada
    if(counter > 0){ // somente imprime se o arquivo nao for vazio
        for(auto it = csv_contents.cbegin(); it != csv_contents.cend(); ++it)
        {
            cout << (*it).first << " "; // imprime o numero da linha
            vector <string> inVect = (*it).second; // prepara a leitura do vetor com os dados de cada linha
            for (unsigned j=0; j<inVect.size(); j++){
                cout << inVect[j]; // imprime o conteudo das linhas lidas
            }
            cout << endl;
        }
        cout << endl << "A leitura de " << counter << " linhas foi realizada com sucesso!" << endl; // imprime o status final da leitura
    }

    exit(EXIT_SUCCESS);
}
