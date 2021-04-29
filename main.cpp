#include <iostream>
#include <Lista.h>
#include <Matriz.h>
#include <Timer.h>
#include <stdlib.h>

using namespace std;

int main(){
    Lista input1 = Lista("grafo_4.txt");
    Matriz inputmat = Matriz("grafo_4.txt");
    inputmat.DFS(2);
    inputmat.BFS(2);
    input1.Conex();
    input1.BFS(2);
    input1.DFS(2);
};
