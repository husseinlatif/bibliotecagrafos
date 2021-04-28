#include <iostream>
#include <Lista.h>
#include <Matriz.h>

using namespace std;

int main(){
    Lista input = Lista("grafo_5.txt");
    //Matriz inputmat = Matriz("grafo_0.txt");
    //input.BFS(1000022);
    input.Conex();
};
