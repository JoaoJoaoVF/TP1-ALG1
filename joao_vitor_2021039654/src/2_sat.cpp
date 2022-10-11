#include "../include/2_sat.hpp"
using namespace std;

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

// DFS recursiva dos elementos do grafo original
void Grafo::DFS(int v)
{
    if (visitado[v])
        return;

    visitado[v] = true;

    for (long unsigned int i = 0; i < aresta[v].size(); i++)
    {
        DFS(aresta[v][i]);
    }

    lista_elementos.emplace_back(v);
}

// DFS recursiva dos elementos do grafo inverso
void Grafo::DFSi(int v)
{
    if (visitado_Inverso[v])
    {
        return;
    }

    visitado_Inverso[v] = true;
    componente_Conexa[v] = contador_Componentes_Conexas;

    for (long unsigned int i = 0; i < aresta_Inversa[v].size(); i++)
    {
        DFSi(aresta_Inversa[v][i]);
    }
}

// função que verifica se existe um ciclo no grafo e da a resposta do algoritmo
void Grafo::verificaCiclo(int *componente_Conexa)
{
    int i = 1;

    // laco que percorre as clausulas e verifica se existe algum elemento e sua negação
    // que pertence a mesma componente conexa
    do
    {
        while (componente_Conexa[i] == componente_Conexa[i + P])
        {
            printf("nao\n");
            return;
        }

        i++;
    } while (i <= P);

    // Caso nao exista uma aresta que liga a mesma componente, o grafo é satisfazivel
    printf("sim\n");
    return;
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
    return 4;
}

// Função que realiza a inserção da proposta no grafo de acordo com a logicas de inserção
void Grafo::preencheArestas(vector<int> Propostas_1, vector<int> Propostas_2)
{
    for (int i = 0; i < Get_S() * 2; i++)
    {
        // verifica o tipo de aresta e realiza a inserção
        verificaTipoAresta(Propostas_1[i], Propostas_2[i]);
    }
}

// Função que econtra o tipo de aresta e realiza a inserção
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

// Função que realiza a inserção das arestas do tipo a AND b
void Grafo::insereAresta_aANDb(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 + Get_P(), Propostas_2);
    adicionaAresta(Propostas_2 + Get_P(), Propostas_1);
    adicionaArestaInversa(Propostas_1 + Get_P(), Propostas_2);
    adicionaArestaInversa(Propostas_2 + Get_P(), Propostas_1);
}

// Função que realiza a inserção das arestas do tipo a AND not b
void Grafo::insereAresta_aAND_not_b(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 + Get_P(), Get_P() - Propostas_2);
    adicionaAresta(Propostas_2 * (-1), Propostas_1);
    adicionaArestaInversa(Propostas_1 + Get_P(), Get_P() - Propostas_2);
    adicionaArestaInversa(Propostas_2 * (-1), Propostas_1);
}

// Função que realiza a inserção das arestas do tipo not a AND b
void Grafo::insereAresta__not_aANDb(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 * (-1), Propostas_2);
    adicionaAresta(Propostas_2 + Get_P(), Get_P() - Propostas_1);
    adicionaArestaInversa(Propostas_1 * (-1), Propostas_2);
    adicionaArestaInversa(Propostas_2 + Get_P(), Get_P() - Propostas_1);
}

// Função que realiza a inserção das arestas do tipo not a AND not b
void Grafo::insereAresta__not_aAND_not_b(int Propostas_1, int Propostas_2)
{
    adicionaAresta(Propostas_1 * (-1), Get_P() - Propostas_2);
    adicionaAresta(Propostas_2 * (-1), Get_P() - Propostas_1);
    adicionaArestaInversa(Propostas_1 * (-1), Get_P() - Propostas_2);
    adicionaArestaInversa(Propostas_2 * (-1), Get_P() - Propostas_1);
}

// função para verificar a satisfabilidade
void Grafo::k_Sat(vector<int> Propostas_1, vector<int> Propostas_2)
{
    // laco que percorre as clausulas e adiciona as arestas ao grafo
    preencheArestas(Propostas_1, Propostas_2);

    // laco que percorre os elementos do grafo original e realiza a DFS neles
    for (int i = 1; i <= 2 * Get_P(); i++)
        while (!visitado[i])
            DFS(i);

    // laco que percorre os elementos do inverso. A cada elemento visitado, ele é adicionado a uma componente conexa
    for (auto i = lista_elementos.end(); i != lista_elementos.begin(); i--)
    {
        while (!visitado_Inverso[*i])
        {
            DFSi(*i);
            contador_Componentes_Conexas++;
        }
    }

    verificaCiclo(componente_Conexa);
}

// Função que limpa os dados dos vetores e variaveis
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
    for (auto &m : componente_Conexa)
    {
        m = 0;
    }
    for (auto &n : lista_elementos)
    {
        n = 0;
    }
}
