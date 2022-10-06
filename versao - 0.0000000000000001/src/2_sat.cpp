#include "../include/2_sat.hpp"

Grafo::Grafo(int qtd_Vertices)
{
    this->qtd_Vertices = qtd_Vertices;
    // arestas = new vector<int>[qtd_Vertices]; // iniciamos a lista de adjacencia
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

/*----------------------------------------------------------------------*/

void Grafo::adicionaAresta(int a, int b)
{
    arestas[a].push_back(b);
}

void Grafo::adicionaArestaInversa(int a, int b)
{
    aresta_Inversa[b].push_back(a);
}

void Grafo::primeira_DFS(int v) //, Grafo Graph[])
{
    if (visitado[v])
    {
        return;
    }

    visitado[v] = 1;

    for (int i = 0; i < arestas[v].size(); i++)
    {
        primeira_DFS(arestas[v][i]);
    }

    pilha_elementos.push(v);
}

void Grafo::segunda_DFS(int v)
{
    if (visitado_Inverso[v])
    {
        return;
    }

    visitado_Inverso[v] = 1;

    for (int i = 0; i < aresta_Inversa[v].size(); i++)
    {
        segunda_DFS(aresta_Inversa[v][i]);
    }

    comp_Conexa[v] = contador;
}

void Grafo::k_Sat(int n, int m, int a[], int b[]) //, map<string, int> seguidores, vector<int> votos)
{
    for (int i = 0; i < m; i++)
    {
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
    // in same SCC
    cout << "sim" << endl;
    return;
}

/*---------------------------------------------------------------------------------------------------*/

// adds edges to form the original graph
void Grafo::addEdges(int a, int b)
{
    adj[a].push_back(b);
}

// add edges to form the inverse graph
void Grafo::addEdgesInverse(int a, int b)
{
    adjInv[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void Grafo::dfsFirst(int u)
{
    if (visited[u])
        return;

    visited[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        dfsFirst(adj[u][i]);

    s.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void Grafo::dfsSecond(int u)
{
    if (visitedInv[u])
        return;

    visitedInv[u] = 1;

    for (int i = 0; i < adjInv[u].size(); i++)
        dfsSecond(adjInv[u][i]);

    scc[u] = counter;
}

// function to check 2-Satisfiability
void Grafo::is2Satisfiable(int n, int m, int a[], int b[])
{
    // adding edges to the graph
    for (int i = 0; i < m; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], addEdges -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            addEdges(a[i] + n, b[i]);
            addEdgesInverse(a[i] + n, b[i]);
            addEdges(b[i] + n, a[i]);
            addEdgesInverse(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            addEdges(a[i] + n, n - b[i]);
            addEdgesInverse(a[i] + n, n - b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i] + n, n - a[i]);
            addEdgesInverse(b[i] + n, n - a[i]);
        }

        else
        {
            addEdges(-a[i], n - b[i]);
            addEdgesInverse(-a[i], n - b[i]);
            addEdges(-b[i], n - a[i]);
            addEdgesInverse(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visited[i])
            dfsFirst(i);

    // STEP 2 of Kosaraju's Algorithm which
    // traverses the inverse graph. After this,
    // array scc[] stores the corresponding value
    while (!s.empty())
    {
        int n = s.top();
        s.pop();

        if (!visitedInv[n])
        {
            dfsSecond(n);
            counter++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same SCC
        if (scc[i] == scc[i + n])
        {
            cout << "nao" << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same SCC
    cout << "sim" << endl;
    return;
}
