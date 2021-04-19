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

    //Inicia o grafo, alocando memoria para a lista de ponteiro.
    m_plist = new Adjac*[nVertices+1]();
    nArestas = 0;

    //Leitura das arestas do aquivo
    string l;
    while (getline(myFile, l)){
        if (l.empty() == false){
            istringstream tmp(l);
            int v1,v2;
            tmp >> v1 >> v2;
            cout << v1;
            this->addAresta(v1,v2);
            this->addAresta(v2,v1);
            nArestas++ ;
        };
    };
    //salvando no output
    ofstream myInfoFile;
    myInfoFile.open(m_savePath + "/info.txt");
    myInfoFile << "V =" << nVertices << endl << "A =" << nArestas << endl;
};

void Lista::addAresta(int orig, int dest){
    Adjac *no = new Adjac;
    no->vertice = dest;

    if(m_plist[orig] != NULL) m_plist[orig]->anterior = no;
    no->proximo = m_plist[orig];
    no->anterior = NULL;
    this->m_plist[orig] = no;
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