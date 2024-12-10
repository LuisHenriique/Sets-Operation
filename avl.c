/* O programa a seguir implementa as operações da AVL */

/* Bibliotecas utilizadas */
#include "avl.h" // Incluir o header da AVL

/* Definição das estruturas */
typedef struct no NO;
struct no // Estrutura do nó da árvore
{
  int chave;  // Variável para armazenar o valor do elemento do nó (Nesse caso a chave é o valor)
  NO *fesq;   // Ponteiro para o nó filho esquerdo do nó
  NO *fdir;   // Ponteiro para o nó filho direito do nó
  int altura; // Variável para armazenar a altura do nó
};

struct avl
{                   // Estrutura da AVL
  NO *raiz;         // Ponteiro para a raiz da árvore
  int profundidade; // Armazena a profundidade da árvore
};

/* Protótipos das funções auxiliares */
NO *avl_balancear(NO *raiz);
NO *rotacaoDir(NO *a);
NO *rotacaoEsq(NO *a);
int fator_balanceamento(NO *raiz);
void avl_transferir_elementos_auxiliar(NO *raizA, NO **raizB);
void avl_interseccao_elementos_auxiliar(NO *raizA, NO *raizB, NO **raizC);

/* A função a seguir cria a árvore */
AVL *avl_criar(void)
{
  /*
  A função aloca memória da estrutura AVL e associa essa memória
  ao ponteiro T

  Parâmetros: void
  Returns: retorna o ponteiro para o espaço alocado
  */
  AVL *T = (AVL *)malloc(sizeof(AVL)); // Aloca memória para a árvore
  if (T != NULL)
  { // Atualiza os valores
    T->profundidade = -1;
    T->raiz = NULL;

    return T; // Retorna o ponteiro para a memória alocada
  }
  return NULL;
}

/* A função a seguir cria o nó da árvore*/
NO *avl_cria_no(int chave)
{
  NO *no = (NO *)malloc(sizeof(NO));
  if (no != NULL)
  {
    no->chave = chave;
    no->fesq = NULL;
    no->fdir = NULL;
    no->altura = 0;
    return no;
  }
  return NULL;
}

int avl_altura_no(NO *raiz) // altura do nó
{
  if (raiz == NULL)
    return -1;
  else
    return raiz->altura;
}
int altura(NO *raiz) // calcula a altura da árvore
{
  if (raiz == NULL)
    return -1;
  else
  {
    int left = altura(raiz->fesq);
    int right = altura(raiz->fdir);
    return (left > right) ? left + 1 : right + 1;
  }
}

NO *avl_inserir_no(NO *raiz, int chave)
{
  if (raiz == NULL)
    raiz = avl_cria_no(chave);
  else if (chave < raiz->chave)
    raiz->fesq = avl_inserir_no(raiz->fesq, chave);
  else if (chave > raiz->chave)
    raiz->fdir = avl_inserir_no(raiz->fdir, chave);

  // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
  raiz->altura = max(avl_altura_no(raiz->fesq), avl_altura_no(raiz->fdir)) + 1;

  raiz = avl_balancear(raiz);
  return raiz;
}
bool avl_inserir(AVL *T, int chave)
{
  if (T != NULL)
  {
    T->raiz = avl_inserir_no(T->raiz, chave);
    return (T->raiz != NULL);
  }
}
NO *rotacaoDir(NO *a)
{
  NO *b;

  b = a->fesq;
  a->fesq = b->fdir;
  b->fdir = a;
  a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
  b->altura = max(avl_altura_no(b->fesq), avl_altura_no(b->fdir)) + 1;

  return b;
}
NO *rotacaoEsq(NO *a)
{
  NO *b;

  b = a->fdir;
  a->fdir = b->fesq;
  b->fesq = a;
  a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
  b->altura = max(avl_altura_no(b->fesq), avl_altura_no(b->fdir)) + 1;

  return b;
}
NO *rotacaoEsqDir(NO *a)
{
  a->fesq = rotacaoEsq(a->fesq);
  return rotacaoDir(a);
}
NO *rotacaoDirEsq(NO *a)
{
  a->fdir = rotacaoDir(a->fdir);
  return rotacaoEsq(a);
}

int fator_balanceamento(NO *raiz)
{
  if (raiz)
    return (avl_altura_no(raiz->fesq) - avl_altura_no(raiz->fdir));
  else
    return 0;
}
NO *avl_balancear(NO *raiz)
{

  int FB = fator_balanceamento(raiz);

  // Rotação à esquerda
  if (FB < -1 && fator_balanceamento(raiz->fdir) <= 0)
    raiz = rotacaoEsq(raiz);

  // Rotação à direita
  else if (FB > 1 && fator_balanceamento(raiz->fesq) >= 0)
    raiz = rotacaoDir(raiz);

  // Rotação dupla à esquerda
  else if (FB > 1 && fator_balanceamento(raiz->fesq) < 0)
    raiz = rotacaoEsqDir(raiz);

  // Rotação dupla à direita
  else if (FB < -1 && fator_balanceamento(raiz->fdir) > 0)
    raiz = rotacaoDirEsq(raiz);

  return raiz;
}

void avl_apagar_nos(NO *raiz)
{
  if (raiz != NULL)
  {
    avl_apagar_nos(raiz->fesq);
    avl_apagar_nos(raiz->fdir);
    free(raiz);
    raiz = NULL;
  }
};
void avl_apagar(AVL **T)
{
  if (T == NULL || *T == NULL)
    return;

  avl_apagar_nos((*T)->raiz);
  free(*T);
  *T = NULL;
}
void troca_left_max(NO *change, NO *raiz, NO *previous)
{
  if (change->fdir != NULL)
  {
    troca_left_max(change->fdir, raiz, change);
    return;
  }
  if (raiz == previous)
    previous->fesq = change->fesq;
  else
    previous->fdir = change->fesq;

  raiz->chave = change->chave;
  free(change);
  change = NULL;
}

NO *avl_remover_no(NO **raiz, int chave)
{
  if ((*raiz) == NULL)
    return NULL;
  else if ((*raiz)->chave == chave)
  {
    if ((*raiz)->fesq == NULL || (*raiz)->fdir == NULL) // pega o 1 e 2 caso, 1 filho ou é folha
    {
      NO *p = (*raiz);
      if ((*raiz)->fesq == NULL)
        (*raiz) = (*raiz)->fdir;
      else
        (*raiz) = (*raiz)->fesq;

      free(p);
      p = NULL;
    }
    else // 3 caso, tem 2 filhos
      troca_left_max((*raiz)->fesq, (*raiz), (*raiz));
  }
  else if (chave < (*raiz)->chave)
    (*raiz)->fesq = avl_remover_no(&(*raiz)->fesq, chave);
  else if (chave > (*raiz)->chave)
    (*raiz)->fdir = avl_remover_no(&(*raiz)->fdir, chave);

  if (*raiz != NULL)
  {
    (*raiz)->altura = max(avl_altura_no((*raiz)->fesq), avl_altura_no((*raiz)->fdir)) + 1;

    *raiz = avl_balancear(*raiz);
  }
  return *raiz;
}
void avl_remover(AVL *T, int chave)
{
  (T->raiz = avl_remover_no(&T->raiz, chave));
}
bool avl_busca_no(NO *raiz, int chave)
{
  while (raiz != NULL)
  {
    if (chave < raiz->chave)
      raiz = raiz->fesq;
    else if (chave > raiz->chave)
      raiz = raiz->fdir;
    else
      return true;
  }
  return false;
}
bool avl_busca(AVL *T, int chave)
{
  return (avl_busca_no(T->raiz, chave));
}

void avl_imprimir_auxiliar(NO *raiz)
{
  if (raiz != NULL)
  {
    avl_imprimir_auxiliar(raiz->fesq);
    printf("%d ", raiz->chave);
    avl_imprimir_auxiliar(raiz->fdir);
  }
  return;
}

void avl_imprimir(AVL *T)
{
  if (T != NULL)
  {
    avl_imprimir_auxiliar(T->raiz);
  }
  return;
}
bool avl_vazia(AVL *T)
{
  return (T != NULL && T->raiz == NULL);
}

void avl_transferir_elementos(AVL *T1, AVL *T2)
{
  if (T1 == NULL && T2 == NULL)
    return;
  avl_transferir_elementos_auxiliar(T1->raiz, &(T2)->raiz);
}
void avl_transferir_elementos_auxiliar(NO *raizA, NO **raizB) // Pega a árvore A e percorre em ordem e transfere para B inserindo
{
  if (raizA != NULL)
  {

    avl_transferir_elementos_auxiliar(raizA->fesq, raizB);
    *raizB = avl_inserir_no((*raizB), raizA->chave); // insere os nos de uma arvora na outra
    avl_transferir_elementos_auxiliar(raizA->fdir, raizB);
  }
  return;
}

void avl_interseccao_elementos(AVL *T1, AVL *T2, AVL *T3)
{
  if ((T1 == NULL || T2 == NULL) && T3 == NULL)
    return; // Se qualquer um dos dois conjuntos (A ou B) for vazio, então a interseção é vazia

  avl_interseccao_elementos_auxiliar(T1->raiz, T2->raiz, &T3->raiz);
}

void avl_interseccao_elementos_auxiliar(NO *raizA, NO *raizB, NO **raizC)
{
  if (raizA == NULL || raizB == NULL)
    return; // Se qualquer uma for nula a interseção é vazia

  avl_interseccao_elementos_auxiliar(raizA->fesq, raizB, raizC);
  if (avl_busca_no(raizB, raizA->chave)) // 1.44 log n
    (*raizC) = avl_inserir_no((*raizC), raizA->chave);
  avl_interseccao_elementos_auxiliar(raizA->fdir, raizB, raizC);
}