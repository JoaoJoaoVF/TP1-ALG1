#ifndef KSAT
#define KSAT

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;

class Grafo
{
public:
    // data structures used to implement Kosaraju's
    // Algorithm. Please refer
    // https://www.geeksforgeeks.org/strongly-connected-components/
    vector<int> aresta[MAX];
    vector<int> aresta_Inversa[MAX];
    bool visitado[MAX];
    bool visitado_Inverso[MAX];
    stack<int> pilha_elementos;

    // this array will store the comp_Conexa that the
    // particular node belongs to
    int comp_Conexa[MAX];

    // contador maintains the number of the comp_Conexa
    int contador = 1;

    void limpa();
    void adicionaAresta(int a, int b);
    void adicionaArestaInversa(int a, int b);
    void primeira_DFS(int u);
    void segunda_DFS(int u);
    void k_Sat(int n, int m, vector<int> a, vector<int> b);
    void imprime(vector<int> a);
};

#endif