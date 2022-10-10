#include "../include/2_sat.hpp"
#include "../include/msgassert.hpp"
using namespace std;

int main()
{
  // inicializa a classe Grafo
  Grafo eleicoes;

  /*
    S representa o numero de seguidores
    P o numero de propostas
  */
  int seguidores, propostas;

  do
  {
    // Leitura do numero de seguidores e de propostas
    cin >> seguidores >> propostas;

    eleicoes.Set_S(seguidores);
    eleicoes.Set_P(propostas);

    // Finaliza o programa caso o numero de seguidores e de propostas seja 0
    if (eleicoes.Get_S() == 0 && eleicoes.Get_P() == 0)
    {
      break;
    }

    // Erros garantindo a integridade dos dados
    erroAssert(eleicoes.Get_S() >= 1, "É necessário pelo menos um seguidor");
    erroAssert(eleicoes.Get_P() >= 1, "É necessário pelo menos uma proposta");
    erroAssert(eleicoes.Get_S() <= 1000, "O número de seguidores não pode ser maior que 1000");
    erroAssert(eleicoes.Get_P() <= 10000, "O número de propostas não pode ser maior que 10000");

    // Inicia os vetores contendo as propostas dos seguidores
    vector<int> propostas_1; // Vetor contendo as propostas X1 e Y1 dos seguidores
    vector<int> propostas_2; // Ve tor contendo as propostas X2 e Y2 dos seguidores

    // loop para leitura das propostas
    for (int i = 0; i < eleicoes.Get_S(); i++)
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
      erroAssert(X1 <= eleicoes.Get_P(), "X1 deve ser menor ou igual a P");
      erroAssert(X2 >= 0, "X2 deve ser maior ou igual a 0");
      erroAssert(X2 <= eleicoes.Get_P(), "X2 deve ser menor ou igual a P");
      erroAssert(Y1 >= 0, "Y1 deve ser maior ou igual a 0");
      erroAssert(Y1 <= eleicoes.Get_P(), "Y1 deve ser menor ou igual a P");
      erroAssert(Y2 >= 0, "Y2 deve ser maior ou igual a 0");
      erroAssert(Y2 <= eleicoes.Get_P(), "Y2 deve ser menor ou igual a P");

      // Funcao que determina o tipo de proposta e como ela deve ser adiconada no vetor
      int tipo_X = eleicoes.verificaTipoProposta(X1, X2);
      int tipo_Y = eleicoes.verificaTipoProposta(Y1, Y2);

      // Adicionando as propostas X no vetor de propostas
      switch (tipo_X)
      {
      case 1:
        propostas_1.emplace_back(X1);
        propostas_2.emplace_back(X2);
        break;
      case 2:
        propostas_1.emplace_back(X2);
        propostas_2.emplace_back(X2);
        break;
      case 3:
        propostas_1.emplace_back(X1);
        propostas_2.emplace_back(X1);
        break;
      }

      // Adicionando as propostas Y no vetor de propostas
      switch (tipo_Y)
      {
      case 1:
        propostas_1.emplace_back(Y1 * -1);
        propostas_2.emplace_back(Y2 * -1);
        break;
      case 2:
        propostas_1.emplace_back(Y2 * -1);
        propostas_2.emplace_back(Y2 * -1);
        break;
      case 3:
        propostas_1.emplace_back(Y1 * -1);
        propostas_2.emplace_back(Y1 * -1);
        break;
      }
    }

    // realiza a verificação se é possivel satisfazer as proposições

    eleicoes.k_Sat(propostas_1, propostas_2);

    // limpa os dados armazenados nas variaveis do programa
    eleicoes.reseta_dados();

  } while (eleicoes.Get_S() != 0 && eleicoes.Get_P() != 0);

  cout << endl;

  return (0);
}