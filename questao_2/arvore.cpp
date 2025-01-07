#include "arvore.h"
#include "colors.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

No *criar_no(Arvore *arvore, int valor) {
  No *novo_no = (No *)malloc(sizeof(No));
  novo_no->valor = valor;
  novo_no->cor = 'V';
  novo_no->esq = arvore->nulo;
  novo_no->dir = arvore->nulo;
  novo_no->pai = arvore->nulo;
  return novo_no;
};

void inicializar_arvore(Arvore *arvore) {
  arvore->nulo = (No*)malloc(sizeof(No));
  arvore->nulo->cor = 'P';
  arvore->raiz = arvore->nulo;
};

void rotacao_esquerda(Arvore *arvore, No *x) {
  No *y = x->dir;  // Y é o filho da direita de X
  x->dir = y->esq; // filho da esquerda de Y passa a ser o filho da direita de X
  if (y->esq != arvore->nulo)
    y->esq->pai = x; // X passa a ser o pai de quem era filho pela esquerda de Y

  y->pai = x->pai; // o pai de X agora passa a ser o pai de Y
  if (x->pai == arvore->nulo)
    arvore->raiz = y; // verifica se X era a raiz
  else if (x == x->pai->esq)
    x->pai->esq = y; // verifica se X era filho pela esquerda
  else
    x->pai->dir = y; // verifica se X era filho pela direita

  y->esq = x; // X passa a ser o filho da esquerda de Y
  x->pai = y; // Y é pai de X
};

void rotacao_direita(Arvore *arvore, No *x) {
  No *y = x->esq;  // Y é o filho da esquerda de X
  x->esq = y->dir; // filho da direita de Y passa a ser o filho da esquerda de X
  if (y->dir != arvore->nulo)
    y->dir->pai = x; // X passa a ser o pai de quem era filho pela direita de Y

  y->pai = x->pai; // o pai de X agora passa a ser o pai de Y
  if (x->pai == arvore->nulo)
    arvore->raiz = y; // verifica se X era a raiz
  else if (x == x->pai->esq)
    x->pai->esq = y; // verifica se X era filho pela esquerda
  else
    x->pai->dir = y; // verifica se X era filho pela direita

  y->dir = x; // X passa a ser o filho da direita de Y
  x->pai = y; // Y é pai de X
};

void corrigir_insercao(Arvore *arvore, No *z) {
  while (z->pai->cor == 'V') {        // Pai é vermelho
    if (z->pai == z->pai->pai->esq) { // Pai é filho pela esquerda do avô
      No *y = z->pai->pai->dir;       // Tio é filho pela direita do avô

      // Caso 1: Tio é vermelho
      if (y->cor == 'V') { // Troca a cor do pai, avô e tio
        z->pai->cor = 'P';
        y->cor = 'P';
        z->pai->pai->cor = 'V';
        z = z->pai->pai; // Passa o problema pro avô
      // Caso 2: Tio é preto
      } else {
        // Caso 2.1: z é filho pela direita do pai
        if (z == z->pai->dir) {
          z = z->pai;                  // Passa o problema pro pai
          rotacao_esquerda(arvore, z); // Rotaciona o pai para a esquerda
        }
        // Caso 2.2: z é filho pela esquerda do pai
        z->pai->cor = 'P';      // Muda a cor do pai para preto
        z->pai->pai->cor = 'V'; // Muda a cor do avô para vermelho
        rotacao_direita(arvore, z->pai->pai); // Rotaciona o avô para a direita
      }
    } else {                    // Pai for filho pela direita do avô
      No *y = z->pai->pai->esq; // Tio é filho pela esquerda do avô

      // Caso 1: Tio é vermelho
      if (y->cor == 'V') { // Troca a cor do pai, avô e tio
        z->pai->cor = 'P';
        y->cor = 'P';
        z->pai->pai->cor = 'V';
        z = z->pai->pai; // Passa o problema pro avô
        // Caso 2: Tio é preto
      } else {
        // Caso 2.1: z é filho pela esquerda do pai
        if (z == z->pai->esq) {
          z = z->pai;                 // Passa o problema pro pai
          rotacao_direita(arvore, z); // Rotaciona o pai para a direita
        }
        // Caso 2.2: z é filho pela direita do pai
        z->pai->cor = 'P';      // Muda a cor do pai para preto
        z->pai->pai->cor = 'V'; // Muda a cor do avô para vermelho
        rotacao_esquerda(arvore, z->pai->pai); // Rotaciona o avô para a esquerda
      }
    }
  }
  arvore->raiz->cor = 'P'; // Garante que a raiz é preta
};

void inserir_no(Arvore *arvore, int valor) {
  No *z = criar_no(arvore, valor); // nó que será inseido
  No *y = arvore->nulo;            // nó nulo
  No *x = arvore->raiz;            // raiz da subárvore

  // loop roda até encontrar a posição do nó a ser inserido
  while (x != arvore->nulo) {
    y = x;
    if (z->valor < x->valor)
      x = x->esq; // se o valor for menor que a raiz da subárvore, vai para a
                  // esquerda
    else if (z->valor > x->valor)
      x = x->dir; // se o valor for maior que a raiz da subárvore, vai para a
                  // direita
    else{
      cout << "Valor já existe na árvore" << endl;
      return;
    }
  }

  z->pai = y; // o pai do nó a ser inseido é o último nó antes dele
  if (y == arvore->nulo)
    arvore->raiz = z; // se o Y for nulo, o nó inserido é a raiz
  else if (z->valor < y->valor)
    y->esq = z; // se o nó inserido for menor que o pai, ele é filho pela esquerda
  else
    y->dir = z; // se o nó inserido for maior que o pai, ele é filho pela direita

  corrigir_insercao(arvore, z);
};

void mover_subsarvore(Arvore *arvore, No *u, No *v) {
  if (u->pai == arvore->nulo) // U era a raiz
    arvore->raiz = v;
  else if (u == u->pai->esq) // U era filho pela esquerda
    u->pai->esq = v;
  else // U era filho pela direita
    u->pai->dir = v;

  v->pai = u->pai; // pai de V passa a ser quem era pai de U
};

No *encontrar_sucessor(Arvore *arvore, No *x) {
  while (x->esq != arvore->nulo) {
    x = x->esq;
  }
  return x;
};

void corrigir_remocao(Arvore *arvore, No *x) {
  while (x != arvore->raiz && x->cor == 'P') {
    No *w;                  // Irmão de X
    if (x == x->pai->esq) { // X é filho pela esquerda
      w = x->pai->dir;      // W é filho pela direita

      // Caso 1: irmão vermlho
      if (w->cor == 'V') { // troca a cor de X e W
        w->cor = 'P';
        x->pai->cor = 'V';
        rotacao_esquerda(arvore, x->pai); // Rotaciona o pai para a esquerda
        w = x->pai->dir;                  // Ajusta o filho pela direita do pai
      }

      // Caso 2: irmão preto e filho da direita preto
      if (w->esq->cor == 'P' && w->dir->cor == 'P') {
        w->cor = 'V'; // Muda a cor de W para vermelho
        x = x->pai;   // Passa o problema pro pai
      } else {
        // Caso 3: irmão preto e filho da direita vermelho
        if (w->dir->cor == 'V') {
          w->esq->cor =
              'P';      // Muda a cor do filho pela esquerda de W para preto
          w->cor = 'V'; // Muda a cor de W para vermelho
          rotacao_direita(arvore, w); // Rotaciona o irmão para a direita
          w = x->pai->dir;            // Ajusta o filho pela direita do pai
        }

        // Caso 4: irmão preto e filho da esquerda preto
        w->cor = x->pai->cor; // Muda a cor de W para a cor do pai de X
        x->pai->cor = 'P';    // Muda a cor do pai de X para preto
        w->dir->cor = 'P'; // Muda a cor do filho pela direita de W para preto
        rotacao_esquerda(arvore, x->pai); // Rotaciona o pai para a esquerda
        x = arvore->raiz;                 // Passa o problema para raiz
      }
    } else {           // X é filho pela direita
      w = x->pai->esq; // W é filho pela esquerda

      // Caso 1: irmão vermelho
      if (w->cor == 'V') {
        w->cor = 'P'; // troca a cor de X e W
        x->pai->cor = 'V';
        rotacao_direita(arvore, x->pai); // Rotaciona o pai para a direita
        w = x->pai->dir;                 // Ajusta o filho pela direita do pai
      }

      // Caso 2: irmão preto e filho da esquerda preto
      if (w->cor == 'P' && w->esq->cor == 'P') {
        w->cor = 'V'; // Muda a cor de W para vermelho
        x = x->pai;   // Passa o problema pro pai
      } else {
        // Caso 3: irmão preto e filho da esquerda vermelho
        if (w->esq->cor == 'V') {
          w->dir->cor = 'P'; // Muda a cor do filho pela direita de W para preto
          w->cor = 'V';      // Muda a cor de W para vermelho
          rotacao_esquerda(arvore, w); // Rotaciona o irmão para a esquerda
          w = x->pai->esq;             // Ajusta o filho pela esquerda do pai
        }

        // Caso 4: irmão preto e filho da direita preto
        w->cor = x->pai->cor; // Muda a cor de W para a cor do pai de X
        x->pai->cor = 'P';    // Muda a cor do pai de X para preto
        w->esq->cor = 'P'; // Muda a cor do filho pela esquerda de W para preto
        rotacao_direita(arvore, x->pai); // Rotaciona o pai para a direita
        x = arvore->raiz;                // Passa o problema para a raiz
      }
    }
  }
  x->cor = 'P';
};

void remover_no(Arvore *arvore, int valor) {
  No *z = buscar_no(arvore, valor);
  // Verifica se o valor que será removido está na árvore
  if (z == arvore->nulo)
    cout << "O valor " << valor << " não está na árvore\n"; // Se não tiver sai da função
  else {                             // Se tiver, então prossegue
    No *y = z;
    char y_cor_original = y->cor;
    No *x = (No *)malloc(sizeof(No));

    // Caso 1: o nó a ser removido não tem filho a esquerda
    if (z->esq == arvore->nulo) {
      x = z->dir;
      mover_subsarvore(arvore, z, x);
      // Caso 2: o nó a ser removido não tem filho a direita
    } else if (z->dir == arvore->nulo) {
      x = z->esq;
      mover_subsarvore(arvore, z, x);
      // Caso 3: o nó a ser removido tem dois filhos
    } else {
      // Pegar o sucessor do nó a ser removido e salvar sua cor
      y = encontrar_sucessor(arvore, z->dir);
      y_cor_original = y->cor;
      x = y->dir; // X é o filho da direita do sucessor

      if (y->pai == z) // Se o sucessor é filho pela direita diretamente do nó a
                       // ser removido
        x->pai = y;

      // Caso não, precisa mover o filho da direita do sucessor para o lugar do
      // sucessor
      else {
        mover_subsarvore(arvore, y, x);
        // Filho da direita do nó a ser removido passa a ser filho da direita do
        // sucessor
        y->dir = z->dir;
        y->dir->pai = y;
      }

      // Mover o sucessor para o lugar do nó a ser removido
      mover_subsarvore(arvore, z, y);
      // Filho da esquerda do nó a ser removido passa a ser filho da esquerda do
      // sucessor
      y->esq = z->esq;
      y->esq->pai = y;
      y->cor = z->cor; // Sucessor passa a ter a mesma cor do nó a ser removido
    }
    // Se a cor original era preto, corrigir as cores para manter as
    // propriedades
    if (y_cor_original == 'P')
      corrigir_remocao(arvore, x);
  }
};

No *buscar_no(Arvore *arvore, int valor) {
  No *x = arvore->raiz;
  // Enquanto não chegar em nulo ou no valor buscado
  while (x != arvore->nulo && valor != x->valor) {
    if (valor < x->valor)
      x = x->esq; // Se o valor for menor, vai para a esquerda
    else
      x = x->dir; // Se o valor for maior, vai para a direita
  }
  return x;
};

void imprimir_arvore(Arvore *arvore) {
  if (arvore->raiz == arvore->nulo) {
    cout << "A árvore está vazia." << endl;
    return;
  }
  stack<No *> pilhaGlobal;
  pilhaGlobal.push(arvore->raiz);
  int nVazios = 32;
  bool linhaVazia = false;
  cout << endl;
  while (linhaVazia == false) {
    stack<No *> pilhaLocal;
    linhaVazia = true;

    for (int j = 0; j < nVazios; j++)
      cout << ' ';

    while (pilhaGlobal.empty() == false) {
      No *temp = pilhaGlobal.top();
      pilhaGlobal.pop();
      if (temp != arvore->nulo) {
        if (temp->cor ==  'V')
          cout << hey::red << temp->valor << "(V)"<< hey::off;
        else
          cout << hey::gray << temp->valor << "(P)"<< hey::off;
        // cout << temp->valor;
        pilhaLocal.push(temp->esq);
        pilhaLocal.push(temp->dir);

        if (temp->esq != arvore->nulo || temp->dir != arvore->nulo)
          linhaVazia = false;
      } else {
        cout << "--";
        pilhaLocal.push(arvore->nulo);
        pilhaLocal.push(arvore->nulo);
      }
      for (int j = 0; j < nVazios * 2 - 2; j++)
        cout << ' ';
    }
    cout << endl;
    nVazios = nVazios / 2;
    while (pilhaLocal.empty() == false) {
      pilhaGlobal.push(pilhaLocal.top());
      pilhaLocal.pop();
    }
  }
  cout << endl;
};
