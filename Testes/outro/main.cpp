#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100000;

bool Propostas[MAX];             // Ponteiro para vetor com a lista de arestas
vector<int> aresta[MAX];         // Ponteiro para vetor com a lista de arestas
vector<int> aresta_Inversa[MAX]; // Ponteiro para vetor com a lista de arestas Inversas
bool visitado[MAX];              // Marca se a aresta ja foi visitada
bool visitado_Inverso[MAX];      // Marca se a aresta Inversa ja foi visitada
stack<int> pilha_elementos;      // pilha de elementos
int comp_Conexa[MAX];            // guarda a qual componente conexa pertence cada no
int contador = 1;

void DFS(int v)
{ Propostas[v] = true
    for each vertex u adjacent to v do:
        if (!Propostas[u])
            DFS(u)
    pilha_elementos.push(v)
}

void DFSi(int v)
{
    Propostas[v] = true
    for each vertex u adjacent to v do:
        if not Propostas[u]:
            DFSi(u)
    comp_Conexa[v] = counter
}

for (auto &i : n)
{
    addEdge(-x[i], y[i]);
    addEdge(-y[i], x[i]);
}
for (auto &i : n)
{
    if (!Propostas[x[i]])
    {
        DFS(x[i]);
    }
    if (!Propostas[y[i]])
    {
        DFS(y[i]);
    }
    if (!Propostas[-x[i]])
    {
        DFS(not x[i]);
    }
    if (!Propostas[-y[i]])
    {
        DFS(not y[i]);
    }
}

set all Propostas values false contador = 0 flip directions of edges // change v -> u to u -> v

    while (!pilha_elementos.empty())
{
    pilha_elementos.pop();
    if (!visitado_Inverso[n])
    {
        contador = contador + 1;
        DFSi(n);
    }
}

for (auto i : n)
{
    if (comp_Conexa[x[i]] == comp_Conexa[-x[i]])
    {
        cout << "nao" << endl;
        return;
    }
    if (comp_Conexa[y[i]] == comp_Conexa[-y[i]])
    {
        cout << "nao" << endl;
        return;
    }
    else
    {
        cout << "sim" << endl;
        return;
    }
}