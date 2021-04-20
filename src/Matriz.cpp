#include <Matriz.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

Matriz::Matriz(string path){
    ifstream myFile;
    myFile.open(path);
    if (!myFile){
        cout << "not found";
        return;
    }
    
    //Salva a primeira linha do arquivo (n de vertices)
    myFile >> nVertices;

    /*Inicia o grafo, criando uma matriz (ponteiros para arrays) e setando todos valores para false.
    Nessa implementação as linhas não são contiguas na memória. */ 
    arestas = new bool*[nVertices+1]();
    for (int p = 0; p<nVertices+1; p++){
        arestas[p] = new bool[nVertices+1];
        for (int li = 0; li<nVertices+1; li++){
            arestas[p][li] = false;
        };  
    };
    
    //Inicia o vertice de graus com 0.
    graus = new int[nVertices+1]();
    for (int j = 0; j < nVertices+1; ++j)
        {
        graus[j] = 0;
        };
    nArestas = 0;

    //Montando o grafo
    string l;
    while (getline(myFile, l)){
        if (l.empty() == false){
            istringstream tmp(l);
            int v1,v2;
            tmp >> v1 >> v2;
            this->addAresta(v1,v2);
            this->addAresta(v2,v1);
            nArestas++ ;
        };
    };
    double grauMedio = 2.0*nArestas/nVertices;
    //salvando no output
    ofstream myInfoFile;
    myInfoFile.open(m_savePath + "/info_mat.txt");
    myInfoFile << "Vertices= " << nVertices << "  Arestas= " << nArestas << endl << "Grau medio = " << grauMedio;
    /* Salva o grau de cada vértice
    for (int k = 1; k < nVertices+1; ++k)
        {
        myInfoFile << k << " tem grau: " << graus[k] << endl;
        };
    */
};

void Matriz::addAresta(int orig, int dest){
    arestas[orig][dest] = true;
    graus[orig]++;
};

Matriz::~Matriz(){
    for (int i=0; i<=nVertices+1; i++)delete arestas[i];
    delete[] arestas;
};