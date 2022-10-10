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
    int S;
    int P;

    // void set_S(int S);
    // int get_S() const;
    // void set_P(int P);
    // int get_P() const;

    const int &Get_P() { return P; }
    void Set_P(int p) { P = p; }
    const int &Get_S() { return S; }
    void Set_S(int s) { S = s; }

    void adicionaAresta(int a, int b);                                                    // adiciona aresta ao grafo
    void adicionaArestaInversa(int a, int b);                                             // adiciona aresta inversa ao grafo
    void DFS(int u);                                                                      // primeira DFS
    void DFSi(int u);                                                                     // segunda DFS
    void k_Sat(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2);           // função para verificar a satisfabilidade
    void reseta_dados();                                                                  // reseta os dados para uma nova execução
    int temCiclo(vector<int> proposta);                                                   // imprime a resposta
    int verificaTipoProposta(int dadoA, int dadoB);                                       // Atribui um tipo de inserção para o grafo	de acordo com o tipo de entrada
    void preencheArestas(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2); // Realiza o preenchimento das arestas seguindo a logica do problema -> (x OR !y) AND (!x OR y)
    void verificaTipoAresta(int Propostas_1, int Propostas_2);                            // Atribui um tipo de inserção para o grafo	de acordo com o tipo de entrada
    void insereAresta_aANDb(int Propostas_1, int Propostas_2);                            // Realiza a inserção da aresta no grafo
    void insereAresta_aAND_not_b(int Propostas_1, int Propostas_2);                       // Realiza a inserção da aresta no grafo
    void insereAresta__not_aANDb(int Propostas_1, int Propostas_2);                       // Realiza a inserção da aresta no grafo
    void insereAresta__not_aAND_not_b(int Propostas_1, int Propostas_2);                  // Realiza a inserção da aresta no grafo
};

#endif