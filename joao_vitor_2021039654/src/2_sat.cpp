#include "../include/2_sat.hpp"
using namespace std;

// void Grafo::set_P(int P)
// {
//     this->P = P;
// }

// void Grafo::set_S(int S)
// {
//     this->S = S;
// }

// int get_P()
// {
//     return this->P;
// }

// int get_S()
// {
//     return this->S;
// }

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
void Grafo::DFS(int v)
{
    if (visitado[v])
        return;

    visitado[v] = true;

    for (long unsigned int i = 0; i < aresta[v].size(); i++)
        DFS(aresta[v][i]);

    pilha_elementos.push(v);
}

// DFS dos elementos do grafo inverso
void Grafo::DFSi(int v)
{
    if (visitado_Inverso[v])
        return;

    visitado_Inverso[v] = true;
    comp_Conexa[v] = contador;

    for (long unsigned int i = 0; i < aresta_Inversa[v].size(); i++)
        DFSi(aresta_Inversa[v][i]);
}

// função para verificar a satisfabilidade
void Grafo::k_Sat(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2)
{
    // laco que percorre as clausulas e adiciona as arestas ao grafo
    preencheArestas(S, P, Propostas_1, Propostas_2);

    // for (int i = 0; i < S * 2; i++)
    // {
    //     if (Propostas_1[i] > 0 && Propostas_2[i] > 0) // veridica se ambas as arestas sao positivas
    //     {
    //         adicionaAresta(Propostas_1[i] + P, Propostas_2[i]);
    //         adicionaArestaInversa(Propostas_1[i] + P, Propostas_2[i]);
    //         adicionaAresta(Propostas_2[i] + P, Propostas_1[i]);
    //         adicionaArestaInversa(Propostas_2[i] + P, Propostas_1[i]);
    //     }

    //     else if (Propostas_1[i] > 0 && Propostas_2[i] < 0) // verifica se a primeira aresta é positiva e a segunda negada
    //     {
    //         adicionaAresta(Propostas_1[i] + P, P - Propostas_2[i]);
    //         adicionaArestaInversa(Propostas_1[i] + P, P - Propostas_2[i]);
    //         adicionaAresta(-Propostas_2[i], Propostas_1[i]);
    //         adicionaArestaInversa(-Propostas_2[i], Propostas_1[i]);
    //     }

    //     else if (Propostas_1[i] < 0 && Propostas_2[i] > 0) // verifica se a segunda aresta é positiva e a primeira negada
    //     {
    //         adicionaAresta(-Propostas_1[i], Propostas_2[i]);
    //         adicionaArestaInversa(-Propostas_1[i], Propostas_2[i]);
    //         adicionaAresta(Propostas_2[i] + P, P - Propostas_1[i]);
    //         adicionaArestaInversa(Propostas_2[i] + P, P - Propostas_1[i]);
    //     }
    //     else // caso em que ambas as arestas sao negadas
    //     {
    //         adicionaAresta(-Propostas_1[i], P - Propostas_2[i]);
    //         adicionaArestaInversa(-Propostas_1[i], P - Propostas_2[i]);
    //         adicionaAresta(-Propostas_2[i], P - Propostas_1[i]);
    //         adicionaArestaInversa(-Propostas_2[i], P - Propostas_1[i]);
    //     }
    // }

    // laco que percorre os elementos do grafo original e realiza a DFS neles
    for (int i = 1; i <= 2 * P; i++)
        if (!visitado[i])
            DFS(i);

    // laco que percorre os elementos do inverso. A cada elemento visitado, ele é adicionado a uma componente conexa
    while (!pilha_elementos.empty())
    {
        int n = pilha_elementos.top();
        pilha_elementos.pop();

        if (!visitado_Inverso[n])
        {
            DFSi(n);
            contador++;
        }
    }

    // laco que percorre as componentes conexas e verifica se existe uma aresta que liga a mesma componente
    for (int i = 1; i <= P; i++)
    {
        if (comp_Conexa[i] == comp_Conexa[i + P])
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

    for (auto &i : aresta)
    {
        i.clear();
    }
    for (auto &j : aresta_Inversa)
    {
        j.clear();
    }
    for (auto &k : visitado)
    {
        k = 0;
    }
    for (auto &l : visitado_Inverso)
    {
        l = 0;
    }
    for (auto &m : comp_Conexa)
    {
        m = 0;
    }
    this->pilha_elementos = stack<int>();
}

// Atribui um tipo de inserção para o grafo	de acordo com o tipo de entrada
int Grafo::verificaTipoProposta(int dadoA, int dadoB)
{
    if (dadoA != 0 && dadoB != 0)
    {
        return 1;
    }
    else if (dadoA == 0)
    {
        return 2;
    }
    else if (dadoB == 0)
    {
        return 3;
    }
}

// Função que realiza a inserção da proposta no grafo de acordo com a logicas de inserção
void Grafo::preencheArestas(int S, int P, vector<int> Propostas_1, vector<int> Propostas_2)
{
    for (int i = 0; i < S * 2; i++)
    {
        // verifica o tipo de aresta e realiza a inserção
        verificaTipoAresta(Propostas_1[i], Propostas_2[i]);

        // switch (tipoAresta)
        // {
        // case 1:
        //     adicionaAresta(Propostas_1[i] + P, Propostas_2[i]);
        //     adicionaArestaInversa(Propostas_1[i] + P, Propostas_2[i]);
        //     adicionaAresta(Propostas_2[i] + P, Propostas_1[i]);
        //     adicionaArestaInversa(Propostas_2[i] + P, Propostas_1[i]);
        //     break;

        // case 2:
        //     adicionaAresta(Propostas_1[i] + P, P - Propostas_2[i]);
        //     adicionaArestaInversa(Propostas_1[i] + P, P - Propostas_2[i]);
        //     adicionaAresta(-Propostas_2[i], Propostas_1[i]);
        //     adicionaArestaInversa(-Propostas_2[i], Propostas_1[i]);
        //     break;

        // case 3:
        //     adicionaAresta(-Propostas_1[i], Propostas_2[i]);
        //     adicionaArestaInversa(-Propostas_1[i], Propostas_2[i]);
        //     adicionaAresta(Propostas_2[i] + P, P - Propostas_1[i]);
        //     adicionaArestaInversa(Propostas_2[i] + P, P - Propostas_1[i]);
        //     break;

        // case 4:
        //     adicionaAresta(-Propostas_1[i], P - Propostas_2[i]);
        //     adicionaArestaInversa(-Propostas_1[i], P - Propostas_2[i]);
        //     adicionaAresta(-Propostas_2[i], P - Propostas_1[i]);
        //     adicionaArestaInversa(-Propostas_2[i], P - Propostas_1[i]);
        //     break;
        // }
    }
}

void Grafo::verificaTipoAresta(int Propostas_1, int Propostas_2)
{
    if (Propostas_1 > 0 && Propostas_2 > 0) // veridica se ambas as arestas sao positivas
    {
        insereAresta_aANDb(Propostas_1, Propostas_2);
        return;
    }

    else if (Propostas_1 > 0 && Propostas_2 < 0) // verifica se a primeira aresta é positiva e a segunda negada
    {
        insereAresta_aAND_not_b(Propostas_1, Propostas_2);
        return;
    }

    else if (Propostas_1 < 0 && Propostas_2 > 0) // verifica se a segunda aresta é positiva e a primeira negada
    {
        insereAresta__not_aANDb(Propostas_1, Propostas_2);
        return;
    }
    else // caso em que ambas as arestas sao negadas
    {
        insereAresta__not_aAND_not_b(Propostas_1, Propostas_2);
        return;
    }
}

void Grafo::insereAresta_aANDb(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 + Get_P(), Propostas_2);
    adicionaArestaInversa(Propostas_1 + Get_P(), Propostas_2);
    adicionaAresta(Propostas_2 + Get_P(), Propostas_1);
    adicionaArestaInversa(Propostas_2 + Get_P(), Propostas_1);
}

void Grafo::insereAresta_aAND_not_b(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 + Get_P(), Get_P() - Propostas_2);
    adicionaArestaInversa(Propostas_1 + Get_P(), Get_P() - Propostas_2);
    adicionaAresta(Propostas_2 * (-1), Propostas_1);
    adicionaArestaInversa(Propostas_2 * (-1), Propostas_1);
}

void Grafo::insereAresta__not_aANDb(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 * (-1), Propostas_2);
    adicionaArestaInversa(Propostas_1 * (-1), Propostas_2);
    adicionaAresta(Propostas_2 + Get_P(), Get_P() - Propostas_1);
    adicionaArestaInversa(Propostas_2 + Get_P(), Get_P() - Propostas_1);
}

void Grafo::insereAresta__not_aAND_not_b(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 * (-1), Get_P() - Propostas_2);
    adicionaArestaInversa(Propostas_1 * (-1), Get_P() - Propostas_2);
    adicionaAresta(Propostas_2 * (-1), Get_P() - Propostas_1);
    adicionaArestaInversa(Propostas_2 * (-1), Get_P() - Propostas_1);
}