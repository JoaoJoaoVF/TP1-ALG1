#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "../include/2_sat.hpp"
#include "../include/msgassert.hpp"

int main()
{
  Grafo eleicao(500);

  // Leitura dos dados do arquivo

  /*
    S representa o numero de seguidores
    P o numero de propostas
  */
  int S, P, voto;

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

    for (int i = 0; i < S; i++)
    {
      // Leitura do nome do seguidor
      string nome;

      nome = "Seguidor " + to_string(i + 1);

      // Erros garantindo a integridade dos dados
      // erroAssert(nome.size() >= 1, "O nome do seguidor não pode ser vazio");
      // erroAssert(nome.size() <= 20, "O nome do seguidor não pode ter mais de 20 caracteres");

      // Adiciona o nome do seguidor no map
      eleicao.adicionaSeguidor(nome, i * 4);

      // Leitura dos votos do seguidor
      for (int j = 0; j < 4; j++)
      {
        cin >> voto;

        // Erros garantindo a integridade dos dados
        erroAssert(voto >= 0, "O voto não pode ser menor que 0");
        erroAssert(voto <= P, "O voto não pode ser maior que o número de propostas");
        erroAssert(voto >= 0 || voto >= P, "O voto não pode ser menor ao número de propostas");
        erroAssert(voto <= P, "O voto não pode ser maior ao número de propostas");

        // Adiciona o voto do seguidor no vetor de votos
        eleicao.adicionaVoto(voto);
      }
    }
    map<string, int>::iterator it;

    int a[] = {1, -2, -1, 3, -3, -4, -3};
    int b[] = {2, 3, -2, 4, 5, -5, 4};
    int n = 5, m = 7;

    eleicao.is2Satisfiable(n, m, a, b); //, eleicao.seguidores, eleicao.votos);
    eleicao.k_Sat(n, m, a, b);          //, eleicao.seguidores, eleicao.votos);

    eleicao.seguidores.clear();
    eleicao.votos.clear();
    cout << endl;
  } while (S != 0 && P != 0);

  return (0);
}
