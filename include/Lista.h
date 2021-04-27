#include <Grafo.h>
#include <string>




struct Adjac 
{
    int vertice;
    Adjac *proximo;

};



class Lista : public Grafo{
public:
    Lista(string);
    ~Lista();
    void BFS(int);
    int *pais, *nivel;
    void Conex();

protected:
    Adjac **m_plist;
    int *graus;
    void addAresta(int,int);

};