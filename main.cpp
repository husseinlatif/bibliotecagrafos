#include <iostream>
#include <Lista.h>
#include <Matriz.h>
//#include <timer.h>

using namespace std;

int main(){
    Lista input = Lista("test.txt");
    input.GenerateMST(2);
};
