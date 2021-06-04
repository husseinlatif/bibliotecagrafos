#include <Lista.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <iterator>
#include <unordered_set>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <limits>
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
    
    //Montando o grafo
    string l;
    getline(myFile, l); //Removendo o endl que ficou após a leitura do nvertice
    getline(myFile, l); //Pegar a primeira linha para ver se é com peso
    istringstream tmp(l);
    int v1,v2;
    double v3 = std::numeric_limits<double>::max(); //Valor de inf
    tmp >> v1 >> v2;
    tmp >> v3;

    this->tem_peso = false;
    this->tem_pesonegativo = false;

    if (v3 == std::numeric_limits<double>::max())
    {
        //aloca espaço para estrutras sem peso
        m_plist = new Adjac*[nVertices+1]();;
        this->addAresta(v1,v2);
        this->addAresta(v2,v1);
        while (getline(myFile, l)){
            if (l.empty() == false){
                istringstream tmp(l);
                tmp >> v1 >> v2;
                this->addAresta(v1,v2);
                this->addAresta(v2,v1);
                graos[v1]++;
                graos[v2]++;
                nArestas++;
            };
        };
    } else {
        //pesados
        w_list = new WAdjac*[nVertices+1]();;
        this->tem_peso = true;
        this->addWAresta(v1,v2,v3);
        this->addWAresta(v2,v1,v3);
        while (getline(myFile, l)){
            if (l.empty() == false){
                istringstream tmp(l);
                tmp >> v1 >> v2 >> v3;
                if(v3 < 0)this->tem_pesonegativo = true; //flag de peso negativo
                this->addWAresta(v1,v2,v3);
                this->addWAresta(v2,v1,v3);
                graos[v1]++;
                graos[v2]++;
                nArestas++;
            };
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

void Lista::addWAresta(int orig, int dest, double peso){
    WAdjac *no = new WAdjac;
    no->vertice = dest;
    no->proximo = w_list[orig];
    no->peso = peso;
    this->w_list[orig] = no;
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

void Lista::DijDist(int inic, int fim){
    double inf = std::numeric_limits<double>::infinity();
    int nv = this->nVertices+1;
    dists = new double[nv];
    visitados = new bool[nv];
    pais = new int[nv];
    for (int i = 0; i < nv; ++i){
        dists[i] = inf;
        visitados[i] = false;
        pais[i] = 0;
    };
    dists[inic] = 0.0;
    priority_queue < pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > fila_p;
    fila_p.push(make_pair(0.0, inic));

    while (!fila_p.empty())
    {
        pair<double,int> dupl = fila_p.top();
        int vert_indice = dupl.second;
        fila_p.pop();
        WAdjac *vert;
        if(visitados[vert_indice] == false){
            visitados[vert_indice] = true;
            vert = this->w_list[vert_indice];
            while (vert)
            {
                int viz_indice = vert->vertice;
                double peso_a = vert->peso;

                if (dists[viz_indice] > dists[vert_indice] + peso_a)
                {
                    dists[viz_indice] = dists[vert_indice] + peso_a;
                    pais[viz_indice] = vert_indice;
                    fila_p.push(make_pair(dists[viz_indice],viz_indice));
                };
                vert = vert->proximo;
            };
        };
    };
    int cam = pais[fim];
    cout << fim << endl;
    while (cam != inic)
    {
        cout << cam << endl;
        cam = pais[cam];

    };
    cout << inic <<endl;
    ofstream DijDist;
    DijDist.open(m_savePath + "/Dists_Dij.txt");
    DijDist << "vertice, Distancia de vertice " << inic << endl;
    for(int p=1; p<this->nVertices+1; p++)DijDist << p << "," << dists[p] << endl;
};

void Lista::GenerateMST(int origem){
    double inf = std::numeric_limits<double>::infinity();

    //Implementação do Algoritmo de Prim.
    //Declara uma fila de prioridade para os custos.
    priority_queue < pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > fila_p;
    fila_p.push(make_pair(0.0, origem));

    //Declara array para os custos, array de pais, e array de visitados.
    dists = new double[nVertices+1];
    pais = new int[nVertices+1];
    visitados = new bool[nVertices+1];

    //Percorre os arrays setando os valores iniciais.
    for (int i = 0; i < nVertices+1; ++i){
        dists[i] = inf;
        pais[i] = 0;
        visitados[i] = false;
    }

    //O custo para chegar à origem é zero.
    dists[origem] = 0;

    //Declaração de variáveis utilizadas dentro do while.
    pair<double,int> topo;
    int vert_indice;
    int vizinho_ind;
    WAdjac *vizinho;

    //Enquanto a priority queue não estiver vazia:
    while (!fila_p.empty()){
        //Seleciona o vértice de maior prioridade (com menor custo e não visitado):
        topo = fila_p.top();
        //Armazena seu índice:
        vert_indice = topo.second;
        //Marca o vértice como visitado:
        visitados[vert_indice] = true;
        //O remove da priority queue:
        fila_p.pop();
        //Seleciona seu vizinho:
        vizinho = w_list[vert_indice];
        //Enquanto não percorrer todos os vizinhos do vértice de maior prioridade:
        while (vizinho != NULL){
            vizinho_ind = vizinho->vertice;
            //Apenas executa a verificação e a inserção na fila de prioridade caso o vizinho não seja visitado e seu custo seja maior:
            if (dists[vizinho_ind] > vizinho->peso && visitados[vizinho_ind] == false){
                dists[vizinho_ind] = vizinho->peso;
                pais[vizinho_ind] = vert_indice;
                fila_p.push(make_pair(dists[vizinho_ind],vizinho_ind));
                };
            //Passa para o próximo vizinho:
            vizinho = vizinho->proximo;
        };
    };

    ofstream MSTree;
    MSTree.open(m_savePath + "/MST.txt");
    MSTree << "vertice, pai, peso" << endl;
    for(int p=1; p<this->nVertices+1; p++)MSTree << p << ", " << pais[p] << ", " << dists[p] << endl;
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

void Lista::DFS(int raiz){
    //Inicia vetores de pais, niveis e visitados:
    pais = new int[this->nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)pais[i] = 0;
    nivel = new int[this->nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)nivel[i] = 0;
    visitados = new bool[nVertices+1]();
    for (int i = 0; i < this->nVertices+1; ++i)visitados[i] = false;
    stack<int> pilha;

    //Início da DFS - Insere a raiz na pilha e define o seu nível como 0.
    pilha.push(raiz);
    nivel[raiz]=0;
    int topo;
    while (!pilha.empty()){
        topo = pilha.top();
        pilha.pop();
        
        //Define o próximo vizinho da lista ordenada
        Adjac *vizinho = this->m_plist[topo];

        //Caso o vértice no topo da pilha não tenha sido visitado:
        if(!visitados[topo]){
            //Marca o vértice como visitado e define o pai e nível de seu vizinho
            visitados[topo] = true;

            //Percorre todos os vizinhos do vértice:
            while(vizinho!=NULL){
                
                //Caso não seja um vértice visitado:
                if(!visitados[vizinho->vertice]){
                    //O insere na pilha.
                    pilha.push(vizinho->vertice);
                    pais[vizinho->vertice]=topo;
                    nivel[vizinho->vertice]=nivel[topo]+1;
                    
                    }
                vizinho = vizinho->proximo;
            }
        }
    }
    ofstream ladjdfs;
    ladjdfs.open(m_savePath + "/dfs_adjac.txt");
    ladjdfs << "vertice,pai,nivel" << endl;
    for(int p=1; p<this->nVertices+1; p++)ladjdfs << p << "," << pais[p] << "," << nivel[p] << endl;
}





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