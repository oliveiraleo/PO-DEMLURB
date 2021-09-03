#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class Grafo
{
public:
	Grafo();
	~Grafo();

private:
	void lerArquivo();
};

