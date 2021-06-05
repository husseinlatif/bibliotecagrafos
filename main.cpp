#include <iostream>
#include <Lista.h>
#include <Matriz.h>
#include <Timer.h>

using namespace std;

int main(){
    double start, finish, elapsed;
    int nums[100];
    srand(4); //seed
    Lista input = Lista("grafo_W_5.txt");
    for(int i=0;i<100;i++){
        nums[i]=rand()%4999998 + 1;
    };
    GET_TIME(start);
    for (int i = 0; i < 100; i++)
    {
        input.GenerateDij(nums[i]);
        input.Excentricidade();
    };
    GET_TIME(finish);
    elapsed = finish - start;
    cout << "tempo = " << elapsed;


};
