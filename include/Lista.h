#include <Grafo.h>
#include <string>
#include <vector>


struct Adjac 
{
    int vertice;
    Adjac *proximo;

};

struct WAdjac 
{
    int vertice;
    double peso;
    WAdjac *proximo;

};



class Lista : public Grafo{
public:
    Lista(string);
    ~Lista();
    void BFS(int inic);
    void DFS(int raiz);
    int *pais, *nivel;
    double *dists;
    void Conex();
    int DIST(int, int);
    int DIAM();
    void DijDist(int,int);
    bool *visitados;
    bool tem_peso;
    bool tem_pesonegativo;

protected:
    Adjac **m_plist;
    WAdjac **w_list;
    void addAresta(int,int);
    void addWAresta(int,int,double);

};