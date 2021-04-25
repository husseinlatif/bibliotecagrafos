#include <Lista.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

Lista::Lista(string path){
    ifstream myFile;
    myFile.open(path);
    if (!myFile){
        cout << "not found";
        return;
    }
    
    //Salva a primeira linha do arquivo (n de vertices)
    myFile >> nVertices;

    /*Inicia o grafo, alocando memoria para a lista de ponteiro
    iniciando a contegem de arestas e o vértice de graus com 0 */ 
    m_plist = new Adjac*[nVertices+1]();
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
    myInfoFile.open(m_savePath + "/info.txt");
    myInfoFile << "Vertices= " << nVertices << "  Arestas= " << nArestas << endl << "Grau medio = " << grauMedio;
    /* Salva o grau de cada vértice
    for (int k = 1; k < nVertices+1; ++k)
        {
        myInfoFile << k << " tem grau: " << graus[k] << endl;
        };
    */
};

void Lista::addAresta(int orig, int dest){
    Adjac *no = new Adjac;
    no->vertice = dest;
    if(m_plist[orig] != NULL) m_plist[orig]->anterior = no;
    no->proximo = m_plist[orig];
    no->anterior = NULL;
    this->m_plist[orig] = no;
    graus[orig]++;
};

void Lista::BFS(int inic){
    //WIP
    for (int i=0; i < this->nVertices+1; i++)this->arestas[0][i] = false;
    pais = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)pais[i] = 0;
    nivel = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)nivel[i] = 0;
};

Lista::~Lista(){
    Adjac *temp;
    for (int i=1; i<=nVertices; i++){
        for (Adjac *viz = m_plist[i]; viz!=NULL;){
            temp = viz;
            viz=viz->proximo;
            delete temp;
        };
    };
    delete[] m_plist;
};