#include <Grafo.h>
#include <string>


struct Adjac 
{
    int vertice;
    Adjac *proximo, *anterior;

};


class Lista : public Grafo{
public:
    Lista(string path);
    ~Lista();

protected:
    Adjac **m_plist;
    void addAresta(int,int);

};