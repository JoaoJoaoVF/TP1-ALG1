#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "campanha.hpp"
#include "msgassert.hpp"

int main()
{
  // vetores de inteiros contendo os votos dos seguidores dos candidatos
  vector<int> votos;

  // map com um nome para os seguidores e o posicao no vetor de votos
  map<string, int> seguidores;
  // call a function in another file
  // test();

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
    // cout << "S: " << S << endl;
    // cout << "P: " << P << endl;
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

      // Impressao do nome do seguidor
      // cout << "Nome: " << nome << endl;

      // Erros garantindo a integridade dos dados
      // erroAssert(nome.size() >= 1, "O nome do seguidor não pode ser vazio");
      // erroAssert(nome.size() <= 20, "O nome do seguidor não pode ter mais de 20 caracteres");

      // Adiciona o nome do seguidor no map
      seguidores[nome] = i;

      // Leitura dos votos do seguidor
      for (int j = 0; j < 4; j++)
      {
        cin >> voto;
        cout << "max proposta " << P << " voto candidato " << voto << endl;
        // Impressao do voto do seguidor
        // cout << "Voto: " << voto << endl;

        // Erros garantindo a integridade dos dados
        erroAssert(voto >= 0, "O voto não pode ser menor que 0");
        erroAssert(voto <= P, "O voto não pode ser maior que o número de propostas");
        erroAssert(voto >= 0 || voto >= P, "O voto não pode ser menor ao número de propostas");
        erroAssert(voto <= P, "O voto não pode ser maior ao número de propostas");

        // Adiciona o voto do seguidor no vetor de votos
        votos.push_back(voto);
      }
    }
    map<string, int>::iterator it;

    for (it = seguidores.begin(); it != seguidores.end(); ++it)
    {
      cout << it->first << " => ";
      for (int k = 0; k < 4; k++)
      {
        cout << votos[it->second * 4 + k] << " ";
      }
      cout << endl;
    }

    seguidores.clear();
    votos.clear();
    cout << endl;
  } while (S != 0 && P != 0);

  // cout << seguidores.size() << endl;

  return (0);
}
