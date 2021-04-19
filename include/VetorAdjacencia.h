#include <Graph.h>
#include <string>


struct VetorVizinhos {
    int vertice;
    VetorVizinhos* Proximo;
};

class VetorAdjacencia {
    public:
        VetorAdjacencia(string path);

    protected:
        VetorVizinhos** Vetor;
        void adicionarAresta(int v1, int v2);
};