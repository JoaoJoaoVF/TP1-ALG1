#include <bits/stdc++.h>
#include "../include/2_sat.hpp"
#include "../include/msgassert.hpp"
using namespace std;

int main()
{
    Grafo eleicoes;
    // n is the number of variables
    // 2n is the total number of nodes
    // m is the number of clauses
    int S, P;

    do
    {
        // Leitura do numero de seguidores e de propostas
        cin >> S >> P;

        // Impressao do numero de seguidores e propostas
        if (S == 0 && P == 0)
        {
            break;
        }
        // Erros garantindo a integridade dos dados
        // erroAssert(S >= 1, "É necessário pelo menos um seguidor");
        // erroAssert(P >= 1, "É necessário pelo menos uma proposta");
        erroAssert(S <= 1000, "O número de seguidores não pode ser maior que 1000");
        erroAssert(P <= 1000, "O número de propostas não pode ser maior que 1000");

        vector<int> propostas_a;
        vector<int> propostas_b;

        for (int i = 0; i < S; i++)
        {
            int X1, X2, Y1, Y2;

            cin >> X1 >> X2 >> Y1 >> Y2;

            if (X1 != 0 && X2 != 0)
            {
                propostas_a.push_back(X1);
                propostas_b.push_back(X2);
            }
            else
            {
                if (X1 == 0)
                {
                    propostas_a.push_back(X2);
                    propostas_b.push_back(X2);
                }
                else
                {
                    propostas_a.push_back(X1);
                    propostas_b.push_back(X1);
                }
            }
            if (Y1 != 0 && Y2 != 0)
            {
                propostas_a.push_back(Y1 * -1);
                propostas_b.push_back(Y2 * -1);
            }
            else
            {
                if (Y1 == 0)
                {
                    propostas_a.push_back(Y2 * -1);
                    propostas_b.push_back(Y2 * -1);
                }
                else
                {
                    propostas_a.push_back(Y1 * -1);
                    propostas_b.push_back(Y1 * -1);
                }
            }
        }

        // eleicoes.k_Sat(S, P * 2, propostas_a, propostas_b);
        eleicoes.imprime(propostas_a);
        cout << endl;
        eleicoes.imprime(propostas_b);
        cout << endl;
        cout << endl;
        eleicoes.limpa();

    } while (S != 0 && P != 0);
    return 0;
}