#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "../include/msgassert.hpp"

const int MAX = 100000;

using namespace std;

class Grafo
{ // Classe que representa o grafo
public:
    int qtd_Vertices;                 // Número de Vértices
    vector<int> arestas[5000];        // Ponteiro para vbetor com a lista de arestas
    vector<int> aresta_Inversa[5000]; // Ponteiro para vbetor com a lista de arestas Inversas
    bool visitado[5000];              // Marca se a aresta ja foi visitada
    bool visitado_Inverso[5000];      // Marca se a aresta ja foi visitada
    vector<int> vertices[5000];       // vetor contendo os vértices nas rotas
    stack<int> pilha_elementos;       // pilha de elementos
    int comp_Conexa[5000];            // guarda a qual componente conexa pertence cada no
    int contador = 1;                 // contador mantém o número da Componetes Conexas

    Grafo(int qtd_Vertices); // Construtor do grafo

    void adicionaAresta(int a, int b); // Função que adiciona arestas ao grafo
    void adicionaArestaInversa(int a, int b);
    void adicionaSeguidor(string nome, int i); // Adiciona um seguidor e a posicao de seus votos no grafo
    void adicionaVoto(int i);                  // adiciona um voto no grafo
    void primeira_DFS(int v);                  //, Grafo Graph[]);            // Travessia nos vértices a partir de v
    void segunda_DFS(int v);
    void k_Sat(int n); //, map<string, int> seguidores, vector<int> votos);

    void imprimeSeguidores();
    void imprimeVotos();

    map<string, int> seguidores; // map com um nome para os seguidores e o posicao no vetor de votos
    vector<int> votos;           // vetor de inteiros contendo os votos dos seguidores dos candidatos
};
