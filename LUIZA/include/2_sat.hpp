#ifndef KSAT
#define KSAT

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100001;

class kSat
{
public:
    // data structures used to implement Kosaraju's
    // Algorithm. Please refer
    // https://www.geeksforgeeks.org/strongly-connected-components/
    vector<int> adj[MAX];
    vector<int> adjInv[MAX];
    bool visited[MAX];
    bool visitedInv[MAX];
    stack<int> s;

    // this array will store the SCC that the
    // particular node belongs to
    int scc[MAX];

    // counter maintains the number of the SCC
    int counter = 1;

    void limpa();

    // adds edges to form the original graph
    void addEdges(int a, int b);

    // add edges to form the inverse graph
    void addEdgesInverse(int a, int b);

    // for STEP 1 of Kosaraju's Algorithm
    void dfsFirst(int u);

    // for STEP 2 of Kosaraju's Algorithm
    void dfsSecond(int u);

    // function to check 2-Satisfiability
    void is2Satisfiable(int n, int m, vector<int> a, vector<int> b);
};

#endif