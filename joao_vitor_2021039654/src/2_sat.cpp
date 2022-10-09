#include "../include/2_sat.hpp"
using namespace std;

// adiciona arestas para formar o grafo original
void Grafo::adicionaAresta(int a, int b)
{
    aresta[a].emplace_back(b);
}

// adiciona arestas para formar o grafo inverso
void Grafo::adicionaArestaInversa(int a, int b)
{
    aresta_Inversa[b].emplace_back(a);
}

// DFS dos elementos do grafo original
void Grafo::primeira_DFS(int v)
{
    if (visitado[v])
        return;

    visitado[v] = 1;

    for (long unsigned int i = 0; i < aresta[v].size(); i++)
        primeira_DFS(aresta[v][i]);

    pilha_elementos.push(v);
}

// DFS dos elementos do grafo inverso
void Grafo::segunda_DFS(int v)
{
    if (visitado_Inverso[v])
        return;

    visitado_Inverso[v] = 1;
    comp_Conexa[v] = contador;

    for (long unsigned int i = 0; i < aresta_Inversa[v].size(); i++)
        segunda_DFS(aresta_Inversa[v][i]);
}

// função para verificar a satisfabilidade
void Grafo::k_Sat(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2)
{
    // laco que percorre as clausulas e adiciona as arestas ao grafo
    for (int i = 0; i < S * 2; i++)
    {
        if (Propostas_1[i] > 0 && Propostas_2[i] > 0) // veridica se ambas as arestas sao positivas
        {
            adicionaAresta(Propostas_1[i] + P, Propostas_2[i]);
            adicionaArestaInversa(Propostas_1[i] + P, Propostas_2[i]);
            adicionaAresta(Propostas_2[i] + P, Propostas_1[i]);
            adicionaArestaInversa(Propostas_2[i] + P, Propostas_1[i]);
        }

        else if (Propostas_1[i] > 0 && Propostas_2[i] < 0) // verifica se a primeira aresta é positiva e a segunda negada
        {
            adicionaAresta(Propostas_1[i] + P, P - Propostas_2[i]);
            adicionaArestaInversa(Propostas_1[i] + P, P - Propostas_2[i]);
            adicionaAresta(-Propostas_2[i], Propostas_1[i]);
            adicionaArestaInversa(-Propostas_2[i], Propostas_1[i]);
        }

        else if (Propostas_1[i] < 0 && Propostas_2[i] > 0) // verifica se a segunda aresta é positiva e a primeira negada
        {
            adicionaAresta(-Propostas_1[i], Propostas_2[i]);
            adicionaArestaInversa(-Propostas_1[i], Propostas_2[i]);
            adicionaAresta(Propostas_2[i] + P, P - Propostas_1[i]);
            adicionaArestaInversa(Propostas_2[i] + P, P - Propostas_1[i]);
        }

        else // caso em que ambas as arestas sao negadas
        {
            adicionaAresta(-Propostas_1[i], P - Propostas_2[i]);
            adicionaArestaInversa(-Propostas_1[i], P - Propostas_2[i]);
            adicionaAresta(-Propostas_2[i], P - Propostas_1[i]);
            adicionaArestaInversa(-Propostas_2[i], P - Propostas_1[i]);
        }
    }

    // laco que percorre os elementos do grafo original e realiza a DFS neles
    for (int i = 1; i <= 2 * P; i++)
        if (!visitado[i])
            primeira_DFS(i);

    // laco que percorre os elementos do inverso. A cada elemento visitado, ele é adicionado a uma componente conexa
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

    // laco que percorre as componentes conexas e verifica se existe uma aresta que liga a mesma componente
    for (int i = 1; i <= P; i++)
    {
        if (comp_Conexa[i] == comp_Conexa[i + P])
        {
            cout << "nao" << endl;
            return;
        }
    }

    // Caso nao exista uma aresta que liga a mesma componente, o grafo é satisfazivel
    cout << "sim" << endl;
    return;
}

// Reseta os dados do programa
void Grafo::reseta_dados()
{

    for (auto &i : aresta)
    {
        i.clear();
    }
    for (auto &j : aresta_Inversa)
    {
        j.clear();
    }
    for (auto &k : visitado)
    {
        k = 0;
    }
    for (auto &l : visitado_Inverso)
    {
        l = 0;
    }
    for (auto &m : comp_Conexa)
    {
        m = 0;
    }
    this->pilha_elementos = stack<int>();
}