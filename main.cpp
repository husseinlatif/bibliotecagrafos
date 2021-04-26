#include <iostream>
#include <Lista.h>
#include <Matriz.h>

using namespace std;

int main(){
    Lista input = Lista("grafo_0.txt");
    //Matriz inputmat = Matriz("grafo_1.txt");
    input.BFS(1);
};