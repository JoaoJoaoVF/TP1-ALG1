#include "odd.hpp"

void TAD::adicionaAresta(int aresta_1, int aresta_2)
{
    aresta[aresta_1].push_back(aresta_2);
}

void TAD::adicionaAresta_Inversa(int aresta_1, int aresta_2)
{
    aresta_Inversa[aresta_2].push_back(aresta_1);
}

void TAD::dfs1(int u)
{
    if (visitado[u])
        return;

    visitado[u] = 1;

    for (int i = 0; i < aresta[u].size(); i++)
        dfs1(aresta[u][i]);

    pilha_elementos.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void TAD::dfs2(int u)
{
    if (visitado_Inverso[u])
        return;

    visitado_Inverso[u] = 1;

    for (int i = 0; i < aresta_Inversa[u].size(); i++)
        dfs2(aresta_Inversa[u][i]);

    comp_Conexa[u] = contador;
}
// function to check 2-Satisfiability
void TAD::is2Satisfiable(int n, int m, int a[], int b[])
{
    // adding edges to the graph
    for (int i = 0; i < m; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], adicionaAresta -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            adicionaAresta(a[i] + n, b[i]);
            adicionaAresta_Inversa(a[i] + n, b[i]);
            adicionaAresta(b[i] + n, a[i]);
            adicionaAresta_Inversa(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            adicionaAresta(a[i] + n, n - b[i]);
            adicionaAresta_Inversa(a[i] + n, n - b[i]);
            adicionaAresta(-b[i], a[i]);
            adicionaAresta_Inversa(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            adicionaAresta(-a[i], b[i]);
            adicionaAresta_Inversa(-a[i], b[i]);
            adicionaAresta(b[i] + n, n - a[i]);
            adicionaAresta_Inversa(b[i] + n, n - a[i]);
        }

        else
        {
            adicionaAresta(-a[i], n - b[i]);
            adicionaAresta_Inversa(-a[i], n - b[i]);
            adicionaAresta(-b[i], n - a[i]);
            adicionaAresta_Inversa(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visitado[i])
            dfs1(i);

    // STEP 2 of Kosaraju's Algorithm which
    // traverses the inverse graph. After this,
    // array comp_Conexa[] stores the corresponding value
    while (!pilha_elementos.empty())
    {
        int n = pilha_elementos.top();
        pilha_elementos.pop();

        if (!visitado_Inverso[n])
        {
            dfs2(n);
            contador++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same comp_Conexa
        if (comp_Conexa[i] == comp_Conexa[i + n])
        {
            // cout << "The given expression is unsatisfiable." << endl;
            cout << "sim" << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same comp_Conexa
    // cout << "The given expression is satisfiable." << endl;
    cout << "nao" << endl;
    return;
}