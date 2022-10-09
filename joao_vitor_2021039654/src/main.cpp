#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "../include/2_sat.hpp"
#include "../include/msgassert.hpp"
using namespace std;

int main()
{
  // inicializa a classe Grafo
  Grafo eleicoes;

  // Leitura dos dados do arquivo

  /*
    S representa o numero de seguidores
    P o numero de propostas
  */
  int S, P;

  do
  {
    // Leitura do numero de seguidores e de propostas
    cin >> S >> P;

    // Finaliza o programa caso o numero de seguidores e de propostas seja 0
    if (S == 0 && P == 0)
    {
      break;
    }

    // Erros garantindo a integridade dos dados
    erroAssert(S >= 1, "É necessário pelo menos um seguidor");
    erroAssert(P >= 1, "É necessário pelo menos uma proposta");
    erroAssert(S <= 1000, "O número de seguidores não pode ser maior que 1000");
    erroAssert(P <= 10000, "O número de propostas não pode ser maior que 10000");

    // Inicia os vetores contendo as propostas dos seguidores
    vector<int> propostas_1; // Vetor contendo as propostas X1 e Y1 dos seguidores
    vector<int> propostas_2; // Ve tor contendo as propostas X2 e Y2 dos seguidores

    // loop para leitura das propostas
    for (int i = 0; i < S; i++)
    {
      // variaveis para guardas as propostas
      int X1 = -1, X2 = -1, Y1 = -1, Y2 = -1;

      // leitura das propostas
      cin >> X1;
      cin >> X2;
      cin >> Y1;
      cin >> Y2;

      // Erros garantindo que X1, X2, Y1 E Y2 sejam valores entre 0 e P
      erroAssert(X1 >= 0, "X1 deve ser maior ou igual a 0");
      erroAssert(X1 <= P, "X1 deve ser menor ou igual a P");
      erroAssert(X2 >= 0, "X2 deve ser maior ou igual a 0");
      erroAssert(X2 <= P, "X2 deve ser menor ou igual a P");
      erroAssert(Y1 >= 0, "Y1 deve ser maior ou igual a 0");
      erroAssert(Y1 <= P, "Y1 deve ser menor ou igual a P");
      erroAssert(Y2 >= 0, "Y2 deve ser maior ou igual a 0");
      erroAssert(Y2 <= P, "Y2 deve ser menor ou igual a P");

      // Adicionando as propostas no vetor de propostas
      if (X1 != 0 && X2 != 0) // caso X1 e X2 sejam diferentes de 0
      {
        propostas_1.emplace_back(X1);
        propostas_2.emplace_back(X2);
      }
      else
      {
        if (X1 == 0) // Caso x1 seja 0
        {
          propostas_1.emplace_back(X2);
          propostas_2.emplace_back(X2);
        }
        else // Caso X2 seja 0
        {
          propostas_1.emplace_back(X1);
          propostas_2.emplace_back(X1);
        }
      }
      if (Y1 != 0 && Y2 != 0) // caso Y1 e Y2 sejam diferentes de 0
      {
        propostas_1.emplace_back(Y1 * -1);
        propostas_2.emplace_back(Y2 * -1);
      }
      else
      {
        if (Y1 == 0) // Caso Y1 seja 0
        {
          propostas_1.emplace_back(Y2 * -1);
          propostas_2.emplace_back(Y2 * -1);
        }
        else // Caso Y2 seja 0
        {
          propostas_1.emplace_back(Y1 * -1);
          propostas_2.emplace_back(Y1 * -1);
        }
      }
    }

    // realiza a verificação se é possivel satisfazer as proposições

    eleicoes.k_Sat(S, P, propostas_1, propostas_2);

    // limpa os dados armazenados nas variaveis do programa
    eleicoes.reseta_dados();

  } while (S != 0 && P != 0);

  cout << endl;
  return 0;
}