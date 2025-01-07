#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

// Estrutura do nó da árvore
struct Node {
  int numero;
  int altura;
  Node *esquerda;
  Node *direita;

  Node(int value)
      : numero(value), altura(1), esquerda(nullptr), direita(nullptr) {}
};

// Classe ArvoreAVL que encapsula as operações da árvore
class ArvoreAVL {
private:
  Node *raiz;

  int altura(Node *node);
  int balanceamento(Node *node);
  Node *rotacionaDireita(Node *y);
  Node *rotacionaEsquerda(Node *x);
  Node *inserir(Node *node, int numero);
  Node *remover(Node *node, int numero);
  Node *menorValor(Node *node);
  bool pesquisar(Node *node, int numero);
  void mostrar(Node *node);

public:
  ArvoreAVL();
  void inserir(int numero);
  void remover(int numero);
  bool pesquisar(int numero);
  void mostrar();
};

#endif

