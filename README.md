
# Trabalho 2 - Pesquisa Operacional (DCC163 / UFJF)

Problema de otimização da rota do caminhão de lixo (variação do Problema do Carteiro Chinês ou *Chinese Postman Problem*)

---

## Estrutura do repositório

- Os arquivos com os dados utilizados como base para o trabalho encontram-se na pasta `arquivos`

- Os arquivos contendo o código do programa principal desenvolvido encontram-se na pasta `Trabalho-PO`

- Um módulo alternativo de leitura de arquivos CSV foi implementado e seu código fonte encontra-se na pasta `leitura-alternativa`

**OBS:** Existem outros arquivos README dentro das pastas com informações pertinentes, favor ler os mesmos com atenção

## Requisitos mínimos

Para execução do programa principal:

- Microsoft [Visual C++ 2015-2019](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0) 14.29.30133 ou superior
- IBM [ILOG CPLEX](https://www.ibm.com/products/ilog-cplex-optimization-studio) ou IBM [CPLEX Optimizer](https://www.ibm.com/analytics/cplex-optimizer) 20.1.0 ou superior
- Microsoft Windows 10
- [Opcional] Microsoft [Visual Studio](https://visualstudio.microsoft.com/) (Community)


Para execução do módulo de leitura alternativo:

- Microsoft Windows 10 ou Linux
- Compilador [g++ (GCC)](https://www.gnu.org/software/gcc/) 11.1.0 ou superior

## Clonando o repositório

-> No linux:

```
git clone https://github.com/oliveiraleo/PO-DEMLURB.git && cd PO-DEMLURB
```

-> No windows:

Siga as instruções mostradas [aqui](https://docs.github.com/pt/github/creating-cloning-and-archiving-repositories/cloning-a-repository-from-github/cloning-a-repository) ou [aqui](https://dicasdeprogramacao.com.br/como-instalar-o-git-no-windows/)

## Arquivos de exemplo

- Arquivo de entrada: [tabela-emparelhamecom-trecho.csv](https://github.com/oliveiraleo/PO-DEMLURB/blob/master/Trabalho-PO/Trabalho-PO/ArquivoLeitura/tabela-emparelhamecom-trecho.csv)
- Arquivo de saída com uma rota calculada: [Resultado2.txt](https://raw.githubusercontent.com/oliveiraleo/PO-DEMLURB/master/Trabalho-PO/Trabalho-PO/ArquivoResultado/Resultado2.txt)

## Trabalhos relacionados

- Repositório do usuário [dilsonpereira](https://github.com/dilsonpereira/chinese-postman-problem) com código escrito em C++
- Repositório do usuário [rkistner](https://github.com/rkistner/chinese-postman) com códido escrito em Python
- G. A. Melo, L. P. N. Santos, M. G. M. Peixoto, S. B. Barbosa e T. H. Nogueira. *Otimização da Rota de Coleta de Lixo na Região do Alto Paranaíba: Uma Pesquisa Aplicada*. [Rev. FSA](www4.unifsa.com.br/revista/index.php/fsa/article/download/2113/491492589), Teresina, v. 17, n. 12, art. 12, p. 239-261, dez. 2020

## Agradecimentos

- Professor [Marcos Passini](http://lattes.cnpq.br/3319101799280232)
- [Departamento de Limpeza Urbana](https://demlurb.pjf.mg.gov.br/apresentacao.php) (DEMLURB / [PJF](https://www.pjf.mg.gov.br/))
- Departamento de Engenharia do DEMLURB
- Setor de coleta do DEMLURB

## Licença / License

O códifo deste projeto está licenciado sob a [The MIT License (MIT)](https://opensource.org/licenses/MIT).