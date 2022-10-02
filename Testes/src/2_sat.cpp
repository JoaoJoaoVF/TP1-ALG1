#include "../include/2_sat.hpp"

Grafo::Grafo(int qtd_Vertices)
{
    this->qtd_Vertices = qtd_Vertices;
    arestas = new vector<int>[qtd_Vertices]; // iniciamos a lista de adjacencia
}

void Grafo::adicionaSeguidor(string nome, int i)
{
    seguidores[nome] = i;
}

void Grafo::adicionaVoto(int i)
{
    votos.push_back(i);
}

void Grafo::imprimeSeguidores()
{
    map<string, int>::iterator it;

    for (it = seguidores.begin(); it != seguidores.end(); ++it)
    {
        cout << it->first << " => " << it->second << endl;

        /* for (int k = 0; k < 4; k++)
        {
            cout << votos[it->second + k] << " ";
        }
        cout << endl;
        */
    }
}

void Grafo::imprimeVotos()
{
    for (long unsigned int i = 0; i < votos.size(); i++)
    {
        if (i % 4 == 0)
            cout << endl;
        cout << votos[i] << " ";
    }
    cout << endl;
}

void Grafo::primeira_DFS(int v) //, Grafo Graph[])
{
    /*
    visitado[v] = true;
    for (int i = 0; i < (int)Graph[v].retornaTamanho(); i++)
    {
        int u = Graph[v][i];
        if (!visitado[u])
        {
            DFS(u, Graph);
        }
    }
    */

    if (visitado[v])
    {
        return;
    }

    visitado[v] = 1;

    for (int i = 0; i < (int)arestas[v].size(); i++)
    {
        // int u = arestas[v][i];
        // if (!visitado[u])
        // {
        primeira_DFS(arestas[v][i]);
        // }
    }
    // for (int i = 0; i < arestas[v].size(); i++)
    //     DFS(arestas[v][i]);

    pilha_elementos.push(v);
}

void Grafo::segunda_DFS(int v)
{
    if (visitado_Inverso[v])
    {
        return;
    }

    visitado_Inverso[v] = 1;

    for (int i = 0; i < (int)aresta_Inversa[v].size(); i++)
    {
        // int u = arestas[v][i];
        // if (!visitado_Inverso[u])
        // {
        segunda_DFS(aresta_Inversa[v][i]);
        // }
    }
    // for (int i = 0; i < arestas[v].size(); i++)
    //     DFS(arestas[v][i]);

    comp_Conexa[v] = contador;
}

void Grafo::k_Sat(int Propostas, int Seguidores, map<string, int> seguidores, vector<int> votos)
{
    /* Sugestao do GitHub autopilot
    Grafo grafo(2 * Propostas);
    map<string, int>::iterator it;

    for (it = seguidores.begin(); it != seguidores.end(); ++it)
    {
        for (int k = 0; k < 4; k++)
        {
            grafo.adicionaAresta(votos[it->second + k], votos[it->second + k + 1]);
        }
    }
    */
    int n = Propostas; // Numero de variaveis
    int m = 4;         // Numero de clausulas

    for (int i = 0; i < m; i++)
    {
        /* Sugestao do GitHub autopilot

         for (int j = 0; j < n; j++)
         {
             adicionaAresta(i * n + j, i * n + (j + 1) % n);
         }
         */
    }
}
void test()
{
    cout << "Funciona!" << endl;
}
