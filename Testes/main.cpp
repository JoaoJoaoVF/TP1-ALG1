#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int n;
vector<int> g[2 * N + 1];
vector<int> rg[2 * N + 1];
vector<int> topo;
int component[2 * N + 1];
bool visit[2 * N + 1];

void dfs(int u)
{
    visit[u] = true;
    for (auto v : g[u])
    {
        if (!visit[v])
        {
            dfs(v);
        }
    }
    topo.emplace_back(u);
}

void rdfs(int u, int cur)
{
    visit[u] = true;
    component[u] = cur;
    for (auto v : rg[u])
    {
        if (!visit[v])
        {
            rdfs(v, cur);
        }
    }
}

void kosaraju()
{
    for (int i = 1; i <= n; ++i)
    {
        if (!visit[i])
        {
            dfs(i);
        }
    }
    reverse(topo.begin(), topo.end());
    memset(visit, false, sizeof visit);
    int cur = 0;
    for (auto u : topo)
    {
        if (!visit[u])
        {
            ++cur;
            rdfs(u, cur);
        }
    }
}

int getVertexId(int literal)
{
    // every odd index is the positive literal
    // and the very next even index is the corresponding negative literal
    if (literal < 0)
        return 2 * abs(literal);
    else
        return 2 * literal - 1;
}

int getComplementVertex(int vertex)
{
    if (vertex & 1)
        return vertex + 1;
    else
        return vertex - 1;
}

bool is2Sat(int var_count, vector<vector<int>> cnf)
{
    // construction of implication graph (g)
    n = 2 * var_count;
    for (int i = 0; i < cnf.size(); ++i)
    {
        int u = getVertexId(cnf[i][0]);
        int v = getVertexId(cnf[i][1]);
        g[getComplementVertex(u)].emplace_back(v);
        g[getComplementVertex(v)].emplace_back(u);
        // reverse graph for kosaraju's algorithm
        rg[v].emplace_back(getComplementVertex(u));
        rg[u].emplace_back(getComplementVertex(v));
    }
    kosaraju();
    // satisfiability criteria check for all literals
    for (int i = 1; i <= n; i += 2)
    {
        if (component[i] == component[i + 1])
        {
            // violation
            return false;
        }
    }
    return true;
}

vector<bool> getAssignment(int var_count)
{
    int lit_count = 2 * var_count;
    vector<bool> assignment(var_count + 1, false);
    for (int i = 1; i <= lit_count; i += 2)
    {
        assignment[i / 2 + 1] = component[i + 1] < component[i];
    }
    return assignment;
}

int main()
{
    int var_count, clause_count;
    cin >> var_count >> clause_count;
    vector<vector<int>> cnf(clause_count);
    for (int i = 0; i < clause_count; ++i)
    {
        int u, v;
        cin >> u >> v;
        cnf[i] = {u, v};
    }
    if (is2Sat(var_count, cnf))
    {
        vector<bool> assignment = getAssignment(var_count);
        // for (int i = 1; i <= var_count; ++i)
        // {
        cout << "sim" << endl;
    }
    else
    {
        cout << "UNSATISFIABLE" << endl;
    }
    return 0;
}
