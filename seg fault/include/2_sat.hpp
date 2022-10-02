#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "../include/msgassert.hpp"

using namespace std;

class Grafo
{ // Classe que representa o grafo
private:
    int qtd_Vertices;              // Número de Vértices
    vector<int> *arestas;          // Ponteiro para vbetor com a lista de arestas
    vector<int> *aresta_Inversa;   // Ponteiro para vbetor com a lista de arestas Inversas
    vector<bool> visitado;         // Marca se a aresta ja foi visitada
    vector<bool> visitado_Inverso; // Marca se a aresta ja foi visitada
    vector<int> vertices;          // vetor contendo os vértices nas rotas
    stack<int> pilha_elementos;    // pilha de elementos
    vector<int> comp_Conexa;       // guarda a qual componente conexa pertence cada no
    int contador = 1;              // contador mantém o número da Componetes Conexas

public:
    Grafo(int qtd_Vertices); // Construtor do grafo

    void adicionaAresta(int a, int b); // Função que adiciona arestas ao grafo
    void adicionaArestaInversa(int a, int b);
    void adicionaSeguidor(string nome, int i); // Adiciona um seguidor e a posicao de seus votos no grafo
    void adicionaVoto(int i);                  // adiciona um voto no grafo
    void primeira_DFS(int v);                  //, Grafo Graph[]);            // Travessia nos vértices a partir de v
    void segunda_DFS(int v);
    void k_Sat(int Propostas, int Seguidores); //, map<string, int> seguidores, vector<int> votos);

    void imprimeSeguidores();
    void imprimeVotos();

    map<string, int> seguidores; // map com um nome para os seguidores e o posicao no vetor de votos
    vector<int> votos;           // vetor de inteiros contendo os votos dos seguidores dos candidatos

    void test();
};
