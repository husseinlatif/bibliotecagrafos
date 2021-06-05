# Bibliotecagrafos
Trabalho de disciplina de Teoria dos Grafos. Está é uma biblioteca para definição e manipulação de grafos, construída em C++.


# Como utilizar
Para utilizar nossa biblioteca, basta clonar este repositório. Tenha em vista que seus grafos deverão estar em um arquivo .txt, nos seguintes formatos exemplificados:

# Grafos com peso:

4 -> número de vértices 

1 2 3.45 -> cada linha representa uma aresta, o formato da linha é (vértice1, vértice2, peso da aresta que liga o vértice1 ao vértice2)

2 4 7.25

4 3 10.0

1 3 25.0


# Grafos sem peso:

4 -> número de vértices

1 2 -> cada linha representa uma aresta, o formato da linha é (vértice1, vértice2)

2 4

4 3

1 3


Tendo em vista o formato acima, basta declarar o componente (em main.cpp) de nossa biblioteca que se encaixa às suas necessidades e passar como argumento o caminho para o arquivo de texto contendo seu grafo. Não se esqueça de compilar! Por exemplo, a main.cpp representada abaixo executa a função GenerateMST no grafo contido em test.txt:


    
    #include <iostream>

    #include <Lista.h>

    #include <Matriz.h>

    //#include <timer.h>

    using namespace std;

    int main(){

        Lista input = Lista("test.txt");

        input.GenerateMST(2);

    };
    
Temos disponíveis as seguintes funções em cada implementação. Ao executá-las, os resultados serão salvos em uma pasta 'output', no diretório raiz do repositório:

# Representação por Matrizes de Adjacência:

* DFS(int x): Executa uma DFS em seu grafo, com início no vértice x, retornando sua arvore geradora.

* BFS(int x): Executa uma BFS em seu grafo, com início no vértice x, retornando sua arvore geradora.

* DIST(int x, int y): Retorna a distância entre os vértices x e y em seu grafo.

* DIAM(): Retorna o diâmetro de seu grafo.

* Conex(): Retorna as componentes conexas de seu grafo, assim como os vértices que compôem cada componente conexa.


# Representação por Listas de Adjacência:

* DFS(int x): Executa uma DFS em seu grafo, com início no vértice x, retornando sua arvore geradora.

* BFS(int x): Executa uma BFS em seu grafo, com início no vértice x, retornando sua arvore geradora.

* DIST(int x, int y): Retorna a distância entre os vértices x e y em seu grafo.

* DIAM(): Retorna o diâmetro de seu grafo.

* Conex(): Retorna as componentes conexas de seu grafo, assim como os vértices que compôem cada componente conexa.

* GenerateMST(int x): Retorna a MST com raiz no vértice x para seu grafo.

* GenerateDij(int x): Cria um vetor contendo a distância de x(raiz) para todos os outros vértices. Serve de suporte para o cálculo de excentricidade e distância.

* 
      
