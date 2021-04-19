#include <string>

using namespace std;


class Grafo {
    public:
        Grafo();
        ~Grafo();


    protected:
        int nVertices;
        int nArestas;
        string m_savePath = "output";

};