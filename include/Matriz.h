#include <Grafo.h>
#include <string>



class Matriz : public Grafo{
public:
    Matriz(string path);
    ~Matriz();
    void DFS(int inic);
    void BFS(int raiz);
    int *pais, *nivel;
    int  DIST(int, int);
    int DIAM();
    void Conex();

protected:
    bool **arestas;
    void addAresta(int,int);
};