#include <VetorAdjacencia.h>
#include <iostream>
#include <string>
#include <ifstream>
#include <sstream>

using namespace std;


VetorAdjacencia::VetorAdjacencia(string path){
    ifstream Input;

    Input.open(path);
    cout << endl << "Lendo arquivo" << fileLocation << "... Aguarde." << endl;

    if (!Input){
        cout << "Arquivo" << fileLocation << " não encontrado." << endl;
        return;
    }

    //Leitura do número de vértices do grafo.
    Input >> nVertices;
    //Alocação de memória.
    Vetor = new VetorVizinhos*[nVertices+1]();
    //Número de arestas inicial.
    nArestas = 0;

    //Leitura de Input:
    string s;
    while (getline(Input, s)) {
        if(s.empty() == false){
            isstringstream tmp(s);
            int v1, v2;
            //Leitura dos vértices da linha:
            tmp >> v1 >> v2;
            //Adição das arestas:
            this->adicionarAresta(v1,v2);
            this->adicionarAresta(v2,v1);
        }
    }

    cout << endl << "Leitura finalizada!" << endl;

    ofstream ArquivoInfo;
    ArquivoInfo.open(savePath + "informacoes.txt");
    ArquivoInfo << "# n = " << nVertices << endl << "# m = " << nArestas << endl;
    cout << "Informações salvas em " << savePath << "/informacoes.txt" <<endl;

};

void VetorAdjacencia::adicionarAresta(int de, int para){

    VetorAdjacencia* no = new VetorAdjacencia;
    no->vertice = para;

    

};
