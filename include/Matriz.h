#include <Grafo.h>
#include <string>



class Matriz : public Grafo{
public:
    Matriz(string path);
    ~Matriz();

protected:
    bool **arestas;
    int *graus;
    void addAresta(int,int);
};