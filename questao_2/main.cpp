// Alunos: Carolina de Lima Alves e Gabriel Lemos da Silva Mastub

#include "arvore.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void) {
  int op;
  int valor;
  Arvore arvore;
  inicializar_arvore(&arvore);
  

  while (1) {
    cout << "1 - Inserir valor\n";
    cout << "2 - Remover valor\n";
    cout << "3 - Consultar valor\n";
    cout << "4 - Mostrar a arvore\n";
    cout << "5 - Sair\n";
    cout << "Opcao? ";
    cin >> op;
    switch (op) {
    case 1: // inserir valor
    {
      cout << "Qual o valor para ser inserido na arvore? ";
      cin >> valor;
      inserir_no(&arvore, valor);
      break;
    }
    case 2: // remover valor
    {
      cout << "Qual o valor para ser removido na arvore? ";
      cin >> valor;
      remover_no(&arvore, valor);
      break;
    }
    case 3: //  consulta por valor
    {
      cout << "Qual o valor para ser buscado na arvore? ";
      cin >> valor;
      if (buscar_no(&arvore, valor))
        cout << "Valor " << valor << " encontrado na arvore\n";
      else
        cout << "Valor não encontrado na arvore\n";
      break;
    }
    case 4: // mostrar a arvore
    {
      imprimir_arvore(&arvore);
      break;
    }
    case 5: // abandonar o programa
    {
      exit(0);
    }
    }
  }
}
