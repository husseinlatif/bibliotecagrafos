#include <iostream>
#include <Lista.h>
#include <Matriz.h>

using namespace std;

int main(){
    Lista input = Lista("grafo_6.txt");
    Matriz inputmat = Matriz("grafo_4.txt");
    inputmat.DFS(2);
    inputmat.BFS(2);
    input.Conex();
    input.BFS(2);
    input.DFS(2);
};