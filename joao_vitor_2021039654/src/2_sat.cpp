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
void Grafo::primeira_DFS(int u)
{
    if (visitado[u])
        return;

    visitado[u] = 1;

    for (long unsigned int i = 0; i < aresta[u].size(); i++)
        primeira_DFS(aresta[u][i]);

    pilha_elementos.push(u);
}

// DFS dos elementos do grafo inverso
void Grafo::segunda_DFS(int u)
{
    if (visitado_Inverso[u])
        return;

    visitado_Inverso[u] = 1;

    for (long unsigned int i = 0; i < aresta_Inversa[u].size(); i++)
        segunda_DFS(aresta_Inversa[u][i]);

    comp_Conexa[u] = contador;
}

// função para verificar a satisfabilidade
void Grafo::k_Sat(int n, int m, vector<int> a, vector<int> b)
{
    // laco que percorre as clausulas e adiciona as arestas ao grafo
    for (int i = 0; i < n * 2; i++)
    {
        if (a[i] > 0 && b[i] > 0) // veridica se ambas as arestas sao positivas
        {
            adicionaAresta(a[i] + m, b[i]);
            adicionaArestaInversa(a[i] + m, b[i]);
            adicionaAresta(b[i] + m, a[i]);
            adicionaArestaInversa(b[i] + m, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0) // verifica se a primeira aresta é positiva e a segunda negada
        {
            adicionaAresta(a[i] + m, m - b[i]);
            adicionaArestaInversa(a[i] + m, m - b[i]);
            adicionaAresta(-b[i], a[i]);
            adicionaArestaInversa(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0) // verifica se a segunda aresta é positiva e a primeira negada
        {
            adicionaAresta(-a[i], b[i]);
            adicionaArestaInversa(-a[i], b[i]);
            adicionaAresta(b[i] + m, m - a[i]);
            adicionaArestaInversa(b[i] + m, m - a[i]);
        }

        else // caso em que ambas as arestas sao negadas
        {
            adicionaAresta(-a[i], m - b[i]);
            adicionaArestaInversa(-a[i], m - b[i]);
            adicionaAresta(-b[i], m - a[i]);
            adicionaArestaInversa(-b[i], m - a[i]);
        }
    }

    // laco que percorre os elementos do grafo original e realiza a DFS neles
    for (int i = 1; i <= 2 * m; i++)
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
    for (int i = 1; i <= m; i++)
    {
        if (comp_Conexa[i] == comp_Conexa[i + m])
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
    for (int i = 0; i < MAX; i++)
    {
        this->aresta[i].clear();
        this->aresta_Inversa[i].clear();
        this->visitado[i] = false;
        this->visitado_Inverso[i] = false;
    }
    this->pilha_elementos = stack<int>();
}