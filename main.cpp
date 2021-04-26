#include <iostream>
#include <Lista.h>
#include <Matriz.h>

using namespace std;

int main(){
    //Lista input = Lista("grafo_5.txt");
    Matriz inputmat = Matriz("grafo_0.txt");
    inputmat.DFS(2);
    inputmat.BFS(2);
};