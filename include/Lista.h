#include <Grafo.h>
#include <string>
#include <vector>


struct Adjac 
{
    int vertice;
    Adjac *proximo;

};



class Lista : public Grafo{
public:
    Lista(string);
    ~Lista();
    void BFS(int inic);
    void DFS(int raiz);
    int *pais, *nivel;
    void Conex();
    int DIST(int, int);
    int DIAM();

protected:
    Adjac **m_plist;
    void addAresta(int,int);

};