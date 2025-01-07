#ifndef Arvore_H
#define Arvore_H

// Estrutura do nó
typedef struct No {
  int valor; // Valor armazenado no nó
  char cor;  // Cor do nó
  No *dir;   // Ponteiro para o filho da direita
  No *esq;   // Ponteiro para o filho da esquerda
  No *pai;   // Ponteiro para o pai
} No;

// Estrutura da árvore
typedef struct Arvore {
  No *raiz;
  No *nulo;
} Arvore;

No *criar_no(Arvore *, int);
void inicializar_arvore(Arvore *);
void rotacao_esquerda(Arvore *, No *);
void rotacao_direita(Arvore *, No *);

void corrigir_insercao(Arvore *, No *);
void inserir_no(Arvore *, int);

No *encontrar_sucessor(Arvore *, No *);
void mover_subsarvore(Arvore *, No *, No *);
void corrigir_remocao(Arvore *, No *);
void remover_no(Arvore *, int);

No *buscar_no(Arvore *, int);

void imprimir_arvore(Arvore *);

#endif
