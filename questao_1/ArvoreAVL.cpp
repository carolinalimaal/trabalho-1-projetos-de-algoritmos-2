#include "ArvoreAVL.h"
#include <stack>

// Retorna a altura de um nó
int ArvoreAVL::altura(Node *node) { return node ? node->altura : 0; }

// Calcula o balanceamento de um nó
int ArvoreAVL::balanceamento(Node *node) {
  return node ? altura(node->esquerda) - altura(node->direita) : 0;
}

// Rotaciona à direita
Node *ArvoreAVL::rotacionaDireita(Node *y) {
  Node *x = y->esquerda;
  Node *T2 = x->direita;

  x->direita = y;
  y->esquerda = T2;

  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

  return x;
}

// Rotaciona à esquerda
Node *ArvoreAVL::rotacionaEsquerda(Node *x) {
  Node *y = x->direita;
  Node *T2 = y->esquerda;

  y->esquerda = x;
  x->direita = T2;

  x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
  y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

  return y;
}

// Insere um elemento na árvore
Node *ArvoreAVL::inserir(Node *node, int numero) {
  if (!node)
    return new Node(numero);

  if (numero < node->numero)
    node->esquerda = inserir(node->esquerda, numero);
  else if (numero > node->numero)
    node->direita = inserir(node->direita, numero);
  else
    return node; // Nó duplicado não é permitido

  node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

  int balance = balanceamento(node);

  // Casos de balanceamento
  if (balance > 1 && numero < node->esquerda->numero)
    return rotacionaDireita(node);

  if (balance < -1 && numero > node->direita->numero)
    return rotacionaEsquerda(node);

  if (balance > 1 && numero > node->esquerda->numero) {
    node->esquerda = rotacionaEsquerda(node->esquerda);
    return rotacionaDireita(node);
  }

  if (balance < -1 && numero < node->direita->numero) {
    node->direita = rotacionaDireita(node->direita);
    return rotacionaEsquerda(node);
  }

  return node;
}

// Remove um elemento da árvore
Node *ArvoreAVL::remover(Node *node, int numero) {
  if (!node)
    return node;

  if (numero < node->numero)
    node->esquerda = remover(node->esquerda, numero);
  else if (numero > node->numero)
    node->direita = remover(node->direita, numero);
  else {
    if (!node->esquerda || !node->direita) {
      Node *temp = node->esquerda ? node->esquerda : node->direita;
      delete node;
      return temp;
    } else {
      Node *temp = menorValor(node->direita);
      node->numero = temp->numero;
      node->direita = remover(node->direita, temp->numero);
    }
  }

  node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

  int balance = balanceamento(node);

  // Casos de balanceamento
  if (balance > 1 && balanceamento(node->esquerda) >= 0)
    return rotacionaDireita(node);

  if (balance > 1 && balanceamento(node->esquerda) < 0) {
    node->esquerda = rotacionaEsquerda(node->esquerda);
    return rotacionaDireita(node);
  }

  if (balance < -1 && balanceamento(node->direita) <= 0)
    return rotacionaEsquerda(node);

  if (balance < -1 && balanceamento(node->direita) > 0) {
    node->direita = rotacionaDireita(node->direita);
    return rotacionaEsquerda(node);
  }

  return node;
}

// Encontra o menor valor na árvore
Node *ArvoreAVL::menorValor(Node *node) {
  Node *current = node;
  current = current->esquerda;
  return current;
}

// Pesquisa um elemento na árvore
bool ArvoreAVL::pesquisar(Node *node, int numero) {
  if (!node)
    return false;
  if (node->numero == numero)
    return true;
  if (numero < node->numero)
    return pesquisar(node->esquerda, numero);
  return pesquisar(node->direita, numero);
}

// Imprime a árvore em ordem
void ArvoreAVL::mostrar(Node *node) {
  if (!node) {
    cout << "Árvore vazia." << endl;
    return;
  }
  
  stack<Node*> pilhaGlobal;
  pilhaGlobal.push(node);
  int nVazios = 32;
  bool linhaVazia = false;
  cout << endl;
  while(linhaVazia==false){
    stack<Node*> pilhaLocal;
    linhaVazia = true;
    
    for(int j=0; j<nVazios; j++)
      cout << ' ';
    
    while(pilhaGlobal.empty()==false){
      Node* temp = pilhaGlobal.top();
      pilhaGlobal.pop();
      if(temp != NULL){
        cout << temp->numero;
        pilhaLocal.push(temp->esquerda);
        pilhaLocal.push(temp->direita);
        
        if(temp->esquerda != NULL || temp->direita != NULL)
          linhaVazia = false;
      } else{
        cout << "--";
        pilhaLocal.push(NULL);
        pilhaLocal.push(NULL);
      }
      for(int j=0; j<nVazios*2-2; j++)
        cout << ' ';
    }
    cout << endl;
    nVazios = nVazios/2;
    while(pilhaLocal.empty()==false){
      pilhaGlobal.push( pilhaLocal.top() );
      pilhaLocal.pop();
    }
  }  
  cout << endl;
}

ArvoreAVL::ArvoreAVL() : raiz(nullptr) {}

void ArvoreAVL::inserir(int numero) { raiz = inserir(raiz, numero); }

void ArvoreAVL::remover(int numero) { raiz = remover(raiz, numero); }

bool ArvoreAVL::pesquisar(int numero) { return pesquisar(raiz, numero); }

void ArvoreAVL::mostrar() {
  mostrar(raiz);
  cout << endl;
}
