#include <Grafo.h>
#include <string>



class Matriz : public Grafo{
public:
    Matriz(string path);
    ~Matriz();
    void DFS(int inic);
    int *pais, *nivel;

protected:
    bool **arestas;
    int *graus;
    void addAresta(int,int);
};