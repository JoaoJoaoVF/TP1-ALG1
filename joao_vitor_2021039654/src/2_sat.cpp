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

void Grafo::primeira_DFS(int v)
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

void Grafo::k_Sat(int n) //, map<string, int> seguidores, vector<int> votos)
{
    vector<int> a;
    vector<int> b;
    for (int x = 0; x < 4; x++)
    {
        a.push_back(votos[x]);
        b.push_back(votos[x + 4]);
    }
    for (int x = 0; x < 4; x++)
    {
        cout << "a " << votos[x] << endl;
        cout << "b " << votos[x + 4] << endl;
        // b.push_back(votos[x + 4]);
    }

    for (int i = 0; i < 5; i++)
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
