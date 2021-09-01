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
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{
    string file_path("../tabela-emparelhamento-sorted-by-cost.csv");
    string file_contents;
    map<int, vector<string>> csv_contents;
    char delimiter = ';';

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
    if(counter == 38){
        cout << "Leitura de " << counter << " linhas feita com sucesso!" << endl;
    }

    exit(EXIT_SUCCESS);
}
