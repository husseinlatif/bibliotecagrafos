#include <Matriz.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <iterator>
using namespace std;

Matriz::Matriz(string path){
    ifstream inputFile;
    inputFile.open(path);
    if (!inputFile){
        cout << "arquivo invalido";
        return;
    }
    
    //Salva a primeira linha do arquivo (n de vertices)
    inputFile >> nVertices;
    vector<int> graos(nVertices+1);
    /*Inicia o grafo, criando uma matriz (ponteiros para arrays) e setando todos valores para false.
    Nessa implementação as colunas não são contiguas na memória. 
    Alocando n+1 para deixar mais simples (vertice 1 estara na posicao 1) e reserva posicao 0 para marcador*/ 
    arestas = new bool*[nVertices+1]();
    for (int p = 0; p<nVertices+1; p++){
        arestas[p] = new bool[nVertices+1];
        for (int li = 1; li<nVertices+1; li++){
            arestas[p][li] = false;
        };  
    };
    


    //Montando o grafo
    string l;
    while (getline(inputFile, l)){
        if (l.empty() == false){
            istringstream tmp(l);
            int v1,v2;
            tmp >> v1 >> v2;
            this->addAresta(v1,v2);
            this->addAresta(v2,v1);
            graos[v1]++;
            graos[v2]++;
            nArestas++ ;
        };
    };
    double grauMedio = 2.0*nArestas/nVertices;
    //salvando no output
    ofstream infomat;
    infomat.open(m_savePath + "/info_mat.txt");
    infomat << "Vertices= " << nVertices << "  Arestas= " << nArestas << endl << "Grau medio = " << grauMedio;

};

void Matriz::addAresta(int orig, int dest){
    arestas[orig][dest] = true;
};

void Matriz::DFS(int inic){
    /*  
    a posição 0 define se o vertice esta marcado ou nao,
    necessario desmarcar vertices e zerar os pais e niveis para começar a busca; 
    */    
    
    for (int i=0; i<this->nVertices+1;i++)this->arestas[0][i] = false;
    pais = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)pais[i] = 0;
    nivel = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)nivel[i] = 0;
    stack<int> pilha;
    
    //comeco do dfs
    pilha.push(inic);
    int topo;
    nivel[inic] = 0;
    while(!pilha.empty()) {
        topo = pilha.top();
        pilha.pop();
        // se o topo nao for descoberto, adiciona seus vizinhos na pilha
        this->arestas[0][topo] = true;
        // ordem inversa para que o topo seja o menor indice
        for(int j=this->nVertices+1; j>0; j--){
            if(this->arestas[topo][j] == true && this->arestas[0][j] == false){
                pilha.push(j);
                pais[j] = topo;
                nivel[j] = nivel[topo] + 1;

            };
        };  
    };
    //salvando infos em um txt compativel com csv
    ofstream matdfs;
    matdfs.open(m_savePath + "/dfs_mat.txt");
    matdfs << "vertice,pai,nivel" << endl;
    for(int p=1; p<this->nVertices+1; p++)matdfs << p << "," << pais[p] << "," << nivel[p] << endl;
};


void Matriz::BFS(int raiz){
    /*  
    a posição 0 define se o vertice esta marcado ou nao,
    necessario desmarcar vertices e zerar os pais e niveis para começar a busca; 
    */    
    for (int i=0; i<this->nVertices+1;i++)this->arestas[0][i] = false;
    pais = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)pais[i] = 0;
    nivel = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)nivel[i] = 0;
    queue<int> fila;


    //Início da BFS - Marca a raiz como descoberta e a insere na fila. Define o nível da raiz como 0.
    this->arestas[0][raiz] = true;
    fila.push(raiz);
    nivel[raiz] = 0;
    while (!fila.empty()) {
        //Retira um vértice da fila:
        int vertice = fila.front();
        fila.pop();
        //Percorre a matriz buscando pelos vizinhos do vértice
        for (int i=1; i<nVertices+1; i++){
            bool vizinho = arestas[vertice][i];
            // Caso seja vizinho do vértice e não esteja marcado:
            if (vizinho && !arestas[0][i]){
                //Marca o vizinho como descoberto, define seu pai e o insere na fila. Define o nível do vizinho como o nível do pai + 1.
                arestas[0][i] = true;
                pais[i] = vertice;
                nivel[i] = nivel[vertice] + 1;
                fila.push(i);
            };
        };
    };
    ofstream matbfs;
    matbfs.open(m_savePath + "/bfs_mat.txt");
    matbfs << "vertice,pai,nivel" << endl;
    for(int p=1; p<this->nVertices+1; p++)matbfs << p << "," << pais[p] << "," << nivel[p] << endl;
};


int Matriz::DIST(int inic, int fim){
    for (int i=0; i<this->nVertices+1;i++)this->arestas[0][i] = false;
    nivel = new int[nVertices+1]();
    for (int i = 0; i < nVertices+1; ++i)nivel[i] = 0;
    queue<int> fila;
    //Início da BFS - Marca a raiz como descoberta e a insere na fila. Define o nível da raiz como 0.
    this->arestas[0][inic] = true;
    fila.push(inic);
    nivel[inic] = 0;
    int vertice;
    while (!fila.empty()){
        //Retira um vértice da fila:
        vertice = fila.front();
        int last = fila.front();
        fila.pop();
        //Percorre a matriz buscando pelos vizinhos do vértice
        for (int i=1; i<nVertices+1; i++){
            bool vizinho = arestas[vertice][i]; 
            // achou o vertice
            if(vizinho && i == fim && inic != fim) return nivel[vertice] + 1;
            // Caso seja vizinho do vértice e não esteja marcado:
            if (vizinho && !arestas[0][i]){
                //Marca o vizinho como descoberto, define seu pai e o insere na fila. Define o nível do vizinho como o nível do pai + 1.
                arestas[0][i] = true;
                nivel[i] = nivel[vertice] + 1;
                fila.push(i);
            };
        };
    };
    if(inic == fim)return nivel[vertice];
    return -1;

};


int Matriz::DIAM(){
    int maxim = 0;
    for (int i = 0; i < this->nVertices+1; i++)
    {
        int temp = this->DIST(i,i);
        if(temp > maxim)maxim=temp;
    };
    return maxim;
};



void Matriz::Conex(){
    /*
    BFS adaptada pra descobrir componentes conexas
    pair vec é um vetor que em pair_vec[n]:
    .first é o contador de vertices na componente n
    .second é uma fila com os vertices existentes em n
    */   
    vector<pair<int,queue<int>>>pair_vec;
    unordered_set<int> dicio; //unordered_set, dicionario so com chave e nao ordenado   
    for(int i=1 ; i < this->nVertices+1; i++)dicio.insert(i);
    int conexId = 0;
    while (!dicio.empty()){ //dicio armazena os nao visitados
        queue<int> fila;
        int inic = *dicio.begin(); //pega qualquer elemento do set (primeiro)
        fila.push(inic); //inicia a fila com a raiz
        int vertice;
        bool vizinho;
        queue<int> complemento;
        pair_vec.emplace_back(make_pair(0,complemento)); //inicia novo elemento com contador no 0 e nova lista
        while (!fila.empty()){
            vertice = fila.front();
            fila.pop();
            for(int i=1; i < nVertices+1; i++){
                vizinho = this-> arestas[vertice][i];                                    
                //Realiza a bfs;
                unordered_set<int>::iterator got = dicio.find(i);
                if ((vizinho && (got != dicio.end()))){ // dicio.end aponta para depois do fim                         
                    fila.push(i);
                    pair_vec[conexId].second.push(i); //adiciona vertice sendo explorado no complemento
                    pair_vec[conexId].first++; //incrementa o primeiro elemento (numero de vertices na componente)
                    dicio.erase(got); //remove vert dos nao descobertos
                };                                   
            };
        };
        conexId++;
    };
            
    sort(pair_vec.begin(), pair_vec.end());
    ofstream ladjbfs;
    ladjbfs.open(m_savePath + "/conex_mat.txt");
    
    for (int i = pair_vec.size() - 1; i >= 0; i--)
    {
        ladjbfs << endl << "C" << i << " = " << pair_vec[i].first<< endl << "{";
        while(!pair_vec[i].second.empty()){
            ladjbfs << pair_vec[i].second.front() << ",";
            pair_vec[i].second.pop();
        };
        ladjbfs << " }" << endl;
    };
    
        
};



Matriz::~Matriz(){
    for (int i=0; i<=nVertices+1; i++)delete arestas[i];
    delete[] arestas;
};