#ifndef KSAT
#define KSAT

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100000;

class Grafo
{

private:
    vector<int> aresta[MAX];         // Ponteiro para vetor com a lista de arestas
    vector<int> aresta_Inversa[MAX]; // Ponteiro para vetor com a lista de arestas Inversas
    bool visitado[MAX];              // Marca se a aresta ja foi visitada
    bool visitado_Inverso[MAX];      // Marca se a aresta Inversa ja foi visitada
    stack<int> pilha_elementos;      // pilha de elementos
    int comp_Conexa[MAX];            // guarda a qual componente conexa pertence cada no
    int contador = 1;                // contador mantém o número da Componetes Conexas

public:
    void adicionaAresta(int a, int b);                                          // adiciona aresta ao grafo
    void adicionaArestaInversa(int a, int b);                                   // adiciona aresta inversa ao grafo
    void primeira_DFS(int u);                                                   // primeira DFS
    void segunda_DFS(int u);                                                    // segunda DFS
    void k_Sat(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2); // função para verificar a satisfabilidade
    void reseta_dados();                                                        // reseta os dados para uma nova execução
};

#endif