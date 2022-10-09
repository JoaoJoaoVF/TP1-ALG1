#ifndef KSAT
#define KSAT

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;

class Grafo
{
private:
    vector<int> aresta[MAX];         // Ponteiro para vbetor com a lista de arestas
    vector<int> aresta_Inversa[MAX]; // Ponteiro para vbetor com a lista de arestas Inversas
    bool visitado[MAX];              // Marca se a aresta ja foi visitada
    bool visitado_Inverso[MAX];      // Marca se a aresta Inversa ja foi visitada
    stack<int> pilha_elementos;      // pilha de elementos
    int comp_Conexa[MAX];            // guarda a qual componente conexa pertence cada no
    int contador = 1;                // contador mantém o número da Componetes Conexas

public:
    Grafo();
    void limpa();
    void adicionaAresta(int a, int b);
    void adicionaArestaInversa(int a, int b);
    void primeira_DFS(int u);
    void segunda_DFS(int u);
    void k_Sat(int n, int m, vector<int> a, vector<int> b);
};

#endif