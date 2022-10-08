#include <bits/stdc++.h>
#include "../include/2_sat.hpp"
using namespace std;

void Grafo::limpa()
{
    // for (int i = 0; i < MAX; i++)
    // {
    //     aresta[i].clear();
    //     pilha_elementos.pop();
    //     aresta_Inversa[i].clear();
    //     visitado[i] = false;
    //     visitado_Inverso[i] = false;
    // }
    // pilha_elementos = stack<int>();
}

// adds edges to form the original graph
void Grafo::adicionaAresta(int a, int b)
{
    aresta[a].push_back(b);
}

// add edges to form the inverse graph
void Grafo::adicionaArestaInversa(int a, int b)
{
    aresta_Inversa[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void Grafo::primeira_DFS(int u)
{
    if (visitado[u])
        return;

    visitado[u] = 1;

    for (int i = 0; i < aresta[u].size(); i++)
        primeira_DFS(aresta[u][i]);

    pilha_elementos.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void Grafo::segunda_DFS(int u)
{
    if (visitado_Inverso[u])
        return;

    visitado_Inverso[u] = 1;

    for (int i = 0; i < aresta_Inversa[u].size(); i++)
        segunda_DFS(aresta_Inversa[u][i]);

    comp_Conexa[u] = contador;
}

// function to check 2-Satisfiability
void Grafo::k_Sat(int n, int m, vector<int> a, vector<int> b)
{
    // adding edges to the graph
    for (int i = 0; i < n * 2; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], adicionaAresta -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            adicionaAresta(a[i] + n, b[i]);
            adicionaArestaInversa(a[i] + n, b[i]);
            adicionaAresta(b[i] + n, a[i]);
            adicionaArestaInversa(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            adicionaAresta(a[i] + n, n - b[i]);
            adicionaArestaInversa(a[i] + n, n - b[i]);
            adicionaAresta(-b[i], a[i]);
            adicionaArestaInversa(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            adicionaAresta(-a[i], b[i]);
            adicionaArestaInversa(-a[i], b[i]);
            adicionaAresta(b[i] + n, n - a[i]);
            adicionaArestaInversa(b[i] + n, n - a[i]);
        }

        else
        {
            adicionaAresta(-a[i], n - b[i]);
            adicionaArestaInversa(-a[i], n - b[i]);
            adicionaAresta(-b[i], n - a[i]);
            adicionaArestaInversa(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visitado[i])
            primeira_DFS(i);

    // STEP 2 of Kosaraju's Algorithm which
    // traverses the inverse graph. After this,
    // array comp_Conexa[] stores the corresponding value
    while (!pilha_elementos.empty())
    {
        int n = pilha_elementos.top();
        pilha_elementos.pop();

        if (!visitado_Inverso[n])
        {
            segunda_DFS(n);
            contador++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same comp_Conexa
        if (comp_Conexa[i] == comp_Conexa[i + n])
        {
            cout << "nao" << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same comp_Conexa
    cout << "sim" << endl;
    return;
}

void Grafo::imprime(vector<int> a)
{
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << ", ";
}
