#ifndef KSAT
#define KSAT

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <list>

using namespace std;

const int QTD_MAXIMA_ELEMENTOS = 100000;

class Grafo
{

private:
    vector<int> aresta[QTD_MAXIMA_ELEMENTOS];         // Ponteiro para vetor com a lista de arestas
    vector<int> aresta_Inversa[QTD_MAXIMA_ELEMENTOS]; // Ponteiro para vetor com a lista de arestas Inversas
    bool visitado[QTD_MAXIMA_ELEMENTOS];              // Marca se a aresta ja foi visitada
    bool visitado_Inverso[QTD_MAXIMA_ELEMENTOS];      // Marca se a aresta Inversa ja foi visitada
    list<int> lista_elementos;                        // lista de elementos
    int componente_Conexa[QTD_MAXIMA_ELEMENTOS];      // guarda a qual componente conexa pertence cada no
    int contador_Componentes_Conexas = 1;             // contador mantém o número da Componetes Conexas
    int S;                                            // identificador do numero de propostas
    int P;                                            // identificador do numero de seguidores

    void adicionaAresta(int a, int b);        // adiciona aresta ao grafo
    void adicionaArestaInversa(int a, int b); // adiciona aresta inversa ao grafo

    void DFS(int u);  // DFS com o grafo na direção normal
    void DFSi(int u); // DFS com o grafo na direção inversa

    void preencheArestas(vector<int> Propostas_1, vector<int> Propostas_2); // Realiza o preenchimento das arestas seguindo a logica do problema -> (x OR !y) AND (!x OR y)

    void verificaTipoAresta(int Propostas_1, int Propostas_2); // Atribui um tipo de inserção para o grafo	de acordo com o tipo de entrada

    void verificaCiclo(int *comp_Conexa); // Verifica se há um ciclo no grafo

    void insereAresta_aANDb(int Propostas_1, int Propostas_2);           // Realiza a inserção da aresta no grafo a AND b
    void insereAresta_aAND_not_b(int Propostas_1, int Propostas_2);      // Realiza a inserção da aresta no grafo a AND !b
    void insereAresta__not_aANDb(int Propostas_1, int Propostas_2);      // Realiza a inserção da aresta no grafo !a AND b
    void insereAresta__not_aAND_not_b(int Propostas_1, int Propostas_2); // Realiza a inserção da aresta no grafo !a AND !b

public:
    void Set_P(int p) { P = p; }     // seta o numero de propostas
    void Set_S(int s) { S = s; }     // seta o numero de seguidores
    const int &Get_P() { return P; } // retorna o numero de propostas
    const int &Get_S() { return S; } // retorna o numero de seguidores

    int verificaTipoProposta(int dadoA, int dadoB); // Atribui um tipo de inserção para o grafo	de acordo com o tipo de entrada

    void k_Sat(vector<int> Propostas_1, vector<int> Propostas_2); // função para verificar a satisfabilidade

    void reseta_dados(); // reseta os dados para uma nova execução
};

#endif