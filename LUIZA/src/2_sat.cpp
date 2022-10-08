#include <bits/stdc++.h>
#include "../include/2_sat.hpp"
using namespace std;

void kSat::limpa()
{
    for (int i = 0; i < MAX; i++)
    {
        adj[i].clear();
        adjInv[i].clear();
        visited[i] = false;
        visitedInv[i] = false;
        //scc[i] = 1;
    }
    s = stack<int>();
    //counter = 1;
}

// adds edges to form the original graph
void kSat::addEdges(int a, int b)
{
    adj[a].push_back(b);
}

// add edges to form the inverse graph
void kSat::addEdgesInverse(int a, int b)
{
    adjInv[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void kSat::dfsFirst(int u)
{
    if (visited[u])
        return;

    visited[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        dfsFirst(adj[u][i]);

    s.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void kSat::dfsSecond(int u)
{
    if (visitedInv[u])
        return;

    visitedInv[u] = 1;

    for (int i = 0; i < adjInv[u].size(); i++)
        dfsSecond(adjInv[u][i]);

    scc[u] = counter;
}

// function to check 2-Satisfiability
void kSat::is2Satisfiable(int n, int m, vector<int> a, vector<int> b)
{
    //n = número de vertices/propostas, entao isso é = p
    //m = número de clausulas = 2*n 

    // adding edges to the graph
    for (int i = 0; i < n*2; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], addEdges -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i]>0 && b[i]>0)
        {
            addEdges(a[i]+m, b[i]);
            addEdgesInverse(a[i]+m, b[i]);
            addEdges(b[i]+m, a[i]);
            addEdgesInverse(b[i]+m, a[i]);
        }
  
        else if (a[i]>0 && b[i]<0)
        {
            addEdges(a[i]+m, m-b[i]);
            addEdgesInverse(a[i]+m, m-b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }
  
        else if (a[i]<0 && b[i]>0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i]+m, m-a[i]);
            addEdgesInverse(b[i]+m, m-a[i]);
        }
  
        else
        {
            addEdges(-a[i], m-b[i]);
            addEdgesInverse(-a[i], m-b[i]);
            addEdges(-b[i], m-a[i]);
            addEdgesInverse(-b[i], m-a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * m; i++)
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

    for (int i = 1; i <= m; i++)
    {
        // for any 2 variable x and -x lie in
        // same SCC
        if (scc[i] == scc[i + m])
        {
            cout << "nao"
                 << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same SCC
    cout << "sim"
         << endl;
    return;
}