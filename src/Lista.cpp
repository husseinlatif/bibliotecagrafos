#include <Lista.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <iterator>
#include <unordered_set>
#include <vector>
#include <utility>
#include <algorithm>
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
    vector<int> graos(nVertices+1);
    /*Inicia o grafo, alocando memoria para a lista de ponteiro
    iniciando a contegem de arestas e o vértice de graus com 0 */ 
    m_plist = new Adjac*[nVertices+1]();;
    /*graus = new int[nVertices+1]();
    for (int j = 0; j < nVertices+1; ++j)
        {
        graus[j] = 0;
        };
    nArestas = 0;
    */
    
    //Montando o grafo
    string l;
    while (getline(myFile, l)){
        if (l.empty() == false){
            istringstream tmp(l);
            int v1,v2;
            tmp >> v1 >> v2;
            this->addAresta(v1,v2);
            this->addAresta(v2,v1);
            graos[v1]++;
            graos[v2]++;
            nArestas++;
        };
    };
    double grauMedio = 2.0*nArestas/nVertices;
    sort(graos.begin(), graos.end());
    //salvando no output
    ofstream myInfoFile;
    myInfoFile.open(m_savePath + "/info.txt");
    myInfoFile << "Vertices= " << nVertices << "  Arestas= " << nArestas << endl << "Grau medio = " << grauMedio << "   Grau maximo = " << graos[nVertices];
};

void Lista::addAresta(int orig, int dest){
    Adjac *no = new Adjac;
    no->vertice = dest;
    no->proximo = m_plist[orig];
    this->m_plist[orig] = no;
};

void Lista::BFS(int inic){
    //Inicia vetores de pais e niveis
    pais = new int[this->nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)pais[i] = 0;
    nivel = new int[this->nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)nivel[i] = 0;
    queue<int> fila;
    fila.push(inic); //inicia a fila com a raiz
    pais[inic] = inic; // pai da raiz e ela propria para realizar o algoritmo
    Adjac *vert;
    while (!fila.empty()){
        vert = this->m_plist[fila.front()];
        while (vert){ //O ultimo vizinho na lista encadeada aponta para NULL.
            /* O pai do vertice vai ser o menor entre os vertices pais presentes na camada que descobriu.
               De resto, o algoritmo opera de maneira similiar ao mostrado na aula 5   */
            if (nivel[vert->vertice] == nivel[fila.front()]+1)
            {
                pais[vert->vertice] = min(pais[vert->vertice],fila.front());
            };
            //Realiza a bfs
            if (pais[vert->vertice] == 0){          
                pais[vert->vertice] = fila.front();
                nivel[vert->vertice] = nivel[fila.front()] + 1; 
                fila.push(vert->vertice);     
            };
            vert=vert->proximo; //Coloca o proximo vizinho para ser avaliado        
        };
        fila.pop(); 
    };
    pais[inic] = 0; //seta o pai da raiz como 0, para aderir convencoes 
    

    ofstream ladjbfs;
    ladjbfs.open(m_savePath + "/bfs_adjac.txt");
    ladjbfs << "vertice,pai,nivel" << endl;
    for(int p=1; p<this->nVertices+1; p++)ladjbfs << p << "," << pais[p] << "," << nivel[p] << endl;

};

int Lista::DIST(int inic, int fim){
    nivel = new int[this->nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)nivel[i] = 0;
    queue<int> fila;
    int last;
    fila.push(inic); //inicia a fila com a raiz
    Adjac *vert;
    while (!fila.empty()){
        vert = this->m_plist[fila.front()];
        while (vert){ //O ultimo vizinho na lista encadeada aponta para NULL.
            //encontrou o destino
            if (vert->vertice == fim && fim != inic)return nivel[fila.front()] + 1;
            //Realiza a bfs
            if (nivel[vert->vertice] == 0 && vert->vertice != inic){          
                nivel[vert->vertice] = nivel[fila.front()] + 1; 
                fila.push(vert->vertice);     
            };
            vert=vert->proximo; //Coloca o proximo vizinho para ser avaliado        
        };
        last= fila.front();
        fila.pop(); 
    };
    if(inic == fim)return nivel[last];
    return -1;
};


int Lista::DIAM(){
    int maxim = 0;
    for (int i = 0; i < this->nVertices+1; i++)
    {
        int temp = this->DIST(i,i);
        if(temp > maxim)maxim=temp;
    };
    return maxim;
};






void Lista::Conex(){
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
        Adjac *vert;
        queue<int> complemento;
        pair_vec.emplace_back(make_pair(0,complemento)); //inicia novo elemento com contador no 0 e nova lista
        while (!fila.empty()){
            vert = this->m_plist[fila.front()]; 
            if(!vert){
                //solucao naive para lidar com vertices sozinhos e raiz.   
                pair_vec[conexId].second.push(fila.front()); //adiciona vertice sendo explorado no complemento
                pair_vec[conexId].first++;
                dicio.erase(fila.front());
            };
            fila.pop();
            while (vert){                                      
                //Realiza a bfs;
                unordered_set<int>::iterator got = dicio.find(vert->vertice);
                if ((got != dicio.end())){ // dicio.end aponta para depois do fim                         
                    fila.push(vert->vertice);
                    pair_vec[conexId].second.push(vert->vertice); //adiciona vertice sendo explorado no complemento
                    pair_vec[conexId].first++; //incrementa o primeiro elemento (numero de vertices na componente)
                    dicio.erase(got); //remove vert dos nao descobertos
                };               
                vert=vert->proximo; //Coloca o proximo vizinho para ser avaliado                    
            };       
        };
        conexId++;    
    };
    sort(pair_vec.begin(), pair_vec.end());
    ofstream ladjbfs;
    ladjbfs.open(m_savePath + "/conex.txt");
    
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