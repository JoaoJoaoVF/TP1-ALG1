#include <bits/stdc++.h>
#include "../include/2_sat.hpp"
#include "../include/msgassert.hpp"
using namespace std;

int main()
{
    kSat eleicao;
    // n is the number of variables
    // 2n is the total number of nodes
    // m is the number of clauses
    int s, p;

    while (true)
    {
        cin >> s >> p;

        if (s == 0)
            break;

        vector<int> a;
        vector<int> b;

        for (int i = 0; i < s; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            if (x1 != 0 && x2 != 0)
            {
                a.push_back(x1);
                b.push_back(x2);
            }
            else
            {
                if (x1 == 0)
                {
                    a.push_back(x2);
                    b.push_back(x2);
                }
                else
                {
                    a.push_back(x1);
                    b.push_back(x1);
                }
            }
            if (y1 != 0 && y2 != 0)
            {
                a.push_back(y1 * -1);
                b.push_back(y2 * -1);
            }
            else
            {
                if (y1 == 0)
                {
                    a.push_back(y2 * -1);
                    b.push_back(y2 * -1);
                }
                else
                {
                    a.push_back(y1 * -1);
                    b.push_back(y1 * -1);
                }
            }
        }

        eleicao.is2Satisfiable(p, s, a, b);
        eleicao.limpa();
    }
    return 0;
}