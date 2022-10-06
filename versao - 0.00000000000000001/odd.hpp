
#ifndef TADs
#define TADs

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>

using namespace std;
class Grafo
{
public:
    void adicionaAresta(int aresta_1, int aresta_2);
    void adicionaAresta_Inversa(int aresta_1, int aresta_2);
    void dfs1(int u);
    void dfs2(int u);
    void is2Satisfiable(int n, int m, int a[], int b[]);

    // vetor que armazena as arestas de cada elemento do grafo, e o seu inverso
    vector<int> aresta[10000];
    vector<int> aresta_Inversa[10000];

    // demarca se a aresta ja foi visitada
    bool visitado[10000];
    bool visitado_Inverso[10000];

    // pilha de elementos
    stack<int> pilha_elementos;

    int comp_Conexa[10000];

    int contador = 1;
};

#endif