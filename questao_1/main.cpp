// // Alunos: Carolina de Lima Alves e Gabriel Lemos da Silva Mastub

#include "ArvoreAVL.h"

int main() {
  ArvoreAVL tree;
  int opcao, valor;

  do {
    cout << "\nMenu:\n";
    cout << "1. Inserir elemento na arvore\n";
    cout << "2. Remover elemento na arvore\n";
    cout << "3. Pesquisar elemento na arvore\n";
    cout << "4. Mostrar árvore balanceada\n";
    cout << "5. Sair\n";
    cout << "\nEscolha uma opcao: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      cout << "\nDigite o valor a ser inserido: ";
      cin >> valor;
      tree.inserir(valor);
      break;
    case 2:
      cout << "\nDigite o valor a ser removido: ";
      cin >> valor;
      tree.remover(valor);
      break;
    case 3:
      cout << "\nDigite o valor a ser pesquisado: ";
      cin >> valor;
      if (tree.pesquisar(valor))
        cout << "\nElemento encontrado.\n";
      else
        cout << "Elemento não encontrado.\n";
      break;
    case 4:
      cout << "\nÁrvore AVL em ordem:\n";
      tree.mostrar();
      break;
    case 5:
      cout << "Saindo...\n";
      break;
    default:
      cout << "Opcao invalida! Tente novamente.\n";
    }
  } while (opcao != 5);

  return 0;
}
