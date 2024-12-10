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
  NO *no = (NO *)malloc(sizeof(NO)); // Alocar memória para a estrutura nó
  if (no != NULL)                    // e associar com o ponteiro
  {
    no->chave = chave; // Atualização dos valores
    no->fesq = NULL;
    no->fdir = NULL;
    no->altura = 0;
    return no;
  }
  return NULL;
}

/* A função a seguir calcula a altura de um nó*/
int avl_altura_no(NO *raiz)
{
  if (raiz == NULL) // Se for nó NULL então a altura é -1
    return -1;
  else
    return raiz->altura; // Retorna a altura do nó, que é armazenado na estrutura
}

/* A função a seguir calcula a altura da árvore*/
int altura(NO *raiz)
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

/* A função a seguir insere um nó na árvore */
NO *avl_inserir_no(NO *raiz, int chave)
{
  if (raiz == NULL)                                 // Caso tenha atingido uma folha
    raiz = avl_cria_no(chave);                      // Cria o nó
  else if (chave < raiz->chave)                     // Caso a chave seja menor, chama a função para a subárvore esquerda
    raiz->fesq = avl_inserir_no(raiz->fesq, chave); // Chama a função para a subárvore esquerda
  else if (chave > raiz->chave)                     // Caso o elemento seja maior, chama a função para inserir na subárvore à direita
    raiz->fdir = avl_inserir_no(raiz->fdir, chave); // Chama a função para a subárvore direita
  // As comparações do elemento a ser inserido com as chaves do nó atual garantem
  // uma busca mais eficiente (busca binária)

  // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
  raiz->altura = max(avl_altura_no(raiz->fesq), avl_altura_no(raiz->fdir)) + 1;

  raiz = avl_balancear(raiz);
  return raiz;
}

/* A função a seguir é a função principal para inserir um elemento (chave) na árvore */
bool avl_inserir(AVL *T, int chave)
{
  if (T != NULL) // Verificação inicial
  {
    T->raiz = avl_inserir_no(T->raiz, chave); // Chama a função auxiliar para inserir
    return (T->raiz != NULL);                 // Se a inserção for bem sucedida, true
  } // Se não for bem sucedida, retorna false
}

/* A função a seguir implementa a rotação direita, auxiliando no rebalanceamento da árvore */
NO *rotacaoDir(NO *a)
{
  NO *b; // Declaração de ponteiro para nó auxiliar

  /* Trocas para realizar a rotação para direita */
  b = a->fesq;
  a->fesq = b->fdir;
  b->fdir = a;
  a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
  b->altura = max(avl_altura_no(b->fesq), avl_altura_no(b->fdir)) + 1;

  return b;
}

/* A função a seguir implementa a rotação esquerda, auxiliando no rebalanceamento da árvore */
NO *rotacaoEsq(NO *a)
{
  NO *b; // Declaração de ponteiro para nó auxiliar

  /* Trocas para realizar a rotação para direita */
  b = a->fdir;
  a->fdir = b->fesq;
  b->fesq = a;
  a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
  b->altura = max(avl_altura_no(b->fesq), avl_altura_no(b->fdir)) + 1;

  return b;
}

/* A função a seguir implementa a rotação dupla esquerda direita, auxiliando no rebalanceamento da árvore */
NO *rotacaoEsqDir(NO *a)
{
  a->fesq = rotacaoEsq(a->fesq);
  return rotacaoDir(a);
}

/* A função a seguir implementa a rotação dupla */
NO *rotacaoDirEsq(NO *a)
{
  a->fdir = rotacaoDir(a->fdir);
  return rotacaoEsq(a);
}

/* A função a seguir calcula o fator de balanceamento de um nó como parâmetro */
int fator_balanceamento(NO *raiz)
{
  if (raiz)
    return (avl_altura_no(raiz->fesq) - avl_altura_no(raiz->fdir)); // Calcula o fator de balanceamento através
  else                                                              // da diferença das alturas da subárvore esquerda
    return 0;                                                       // e direita do nó
}

/* A função a seguir é responsável por balancear a árvore */
NO *avl_balancear(NO *raiz)
{
  int FB = fator_balanceamento(raiz); // Cálculo do fator de balanceamento

  /* Analise dos casos onde a árvore está desbalanceada a seguir para decidir o tipo de rotação */
  if (FB < -1 && fator_balanceamento(raiz->fdir) <= 0) // Fator de balanceamento de mesmo sinal e negativos
    raiz = rotacaoEsq(raiz);                           // Rotação simples para esquerda

  else if (FB > 1 && fator_balanceamento(raiz->fesq) >= 0) // Fator de balanceamento de mesmo sinal e positivos
    raiz = rotacaoDir(raiz);                               // Rotação simples para direita

  else if (FB > 1 && fator_balanceamento(raiz->fesq) < 0) // Fator de balanceamento de sinais diferentes e o do nó pai é positivo
    raiz = rotacaoEsqDir(raiz);                           // Rotação dupla esquerda direita

  else if (FB < -1 && fator_balanceamento(raiz->fdir) > 0) // Fator de balanceamento de sinais diferentes e o do nó pai é negativo
    raiz = rotacaoDirEsq(raiz);                            // Rotação dupla direita esquerda

  return raiz; // Retorna a raiz após realizar o rebalanceamento
}

/* A função a seguir é auxiliar da função para apagar a avl */
/* Essa função é responsável por apagar os nós da árvore */
void avl_apagar_nos(NO *raiz)
{
  if (raiz != NULL)
  { // Realiza-se um percurso pós-ordem
    // onde a visita é equivalente à apagar o nó através do free
    avl_apagar_nos(raiz->fesq); // Chama a função apagar auxiliar para a subárvore esquerda
    avl_apagar_nos(raiz->fdir); // Chama a função apagar auxiliar para a subárvore direita
    free(raiz);                 // Libera o nó
    raiz = NULL;                // Medida preventiva
  }
}

/* A função a seguir apaga a arvore */
void avl_apagar(AVL **T)
{
  if (T == NULL || *T == NULL)
    return;

  avl_apagar_nos((*T)->raiz); // Chama a função auxiliar para apagar os nós da árvore
  free(*T);
  *T = NULL;
}

/* Função auxiliar da remoção */
/* A função a seguir é utilizada para o caso em que deseja-se remover um nó
que contém duas subárvores
Nesse caso, escolhe-se a maior chave à esquerda ou a menor chave à direita para substituir
o nó a ser removido. Assim, a função a seguir implementa a troca em que a escolha de substituição
é para a maior chave à esquerda
*/
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

/* A função a seguir é responsável por eliminar um nó da árvore com base na chave */
NO *avl_remover_no(NO **raiz, int chave)
{
  /* Caso em que achou-se um nó nulo */
  if ((*raiz) == NULL)
    return NULL;

  /* Caso contrário, analisa-se os casos da remoção, ou seja, se é um nó folha,
  nó com 1 subárvore (esquerda ou direita), ou nó com 2 subárvores (esquerda e direita)
  */
  else if ((*raiz)->chave == chave) // Caso em que achou-se a chave para eliminar o nó
  {
    if ((*raiz)->fesq == NULL || (*raiz)->fdir == NULL) // pega o 1 e 2 caso, 1 filho ou é folha
    {
      /* Realiza a remoção propriamente dita através das trocas de ponteiros e free */
      NO *p = (*raiz);
      if ((*raiz)->fesq == NULL)
        (*raiz) = (*raiz)->fdir;
      else
        (*raiz) = (*raiz)->fesq;

      free(p); // Libera o ponteiro para o nó a ser removido
      p = NULL;
    }
    else                                               // Caso 3, no qual há 2 filhos
      troca_left_max((*raiz)->fesq, (*raiz), (*raiz)); // Realiza-se a troca com o maior elemento
  } // da subárvore esquerda
  /* Caso não tenha achado a chave, realiza-se a busca através de comparações */
  else if (chave < (*raiz)->chave)
    (*raiz)->fesq = avl_remover_no(&(*raiz)->fesq, chave); // Seja menor que a chave do nó atual
  else if (chave > (*raiz)->chave)
    (*raiz)->fdir = avl_remover_no(&(*raiz)->fdir, chave); // Caso seja maior que a chave do nó atual

  if (*raiz != NULL)
  {
    /* Recalcula a altura do nó após as alterações */
    (*raiz)->altura = max(avl_altura_no((*raiz)->fesq), avl_altura_no((*raiz)->fdir)) + 1;

    /* Rebalanceamento após a remoção */
    *raiz = avl_balancear(*raiz);
  }
  return *raiz;
}

/* A função a seguir remove um elemento da árvore */
void avl_remover(AVL *T, int chave)
{
  (T->raiz = avl_remover_no(&T->raiz, chave));
}

/* A função a seguir é auxiliar da busca */
bool avl_busca_no(NO *raiz, int chave)
{
  while (raiz != NULL)
  {
    /* Através do while é possível repetir a análise para os filhos esquerdo e direito */
    if (chave < raiz->chave) // Caso seja menor que a chave, realiza a atualização para a subárvore à esquerda
      raiz = raiz->fesq;
    else if (chave > raiz->chave) // Caso seja maior que a chave, realiza a atualização para a subárvore à direita
      raiz = raiz->fdir;
    else
      return true; // Caso tenha entrado no loop while, o nó não é nulo. Além disso, se passou
  } // pelos casos em que é menor e maior, então é igual a chave (retorna true)
  return false; // Caso tenha passado por todos os casos e não achou, então não está presente na árvore (retorna false)
}

/* A função a seguir implementa a busca de um elemento na árvore */
bool avl_busca(AVL *T, int chave)
{
  return (avl_busca_no(T->raiz, chave));
}

/* A função a seguir é reponsável por imprimir os elementos da árvore em ordem crescente */
void avl_imprimir_auxiliar(NO *raiz)
{
  if (raiz != NULL) // Verificação inicial
  {
    /* A impressão em ordem crescente é realizada por meio do percurso em ordem
    Onde a visita ao nó é a própria impressão
    */
    avl_imprimir_auxiliar(raiz->fesq); // Analisa a subárvore à esquerda
    printf("%d ", raiz->chave);        // Visita em ordem (impressao do valor da chave)
    avl_imprimir_auxiliar(raiz->fdir); // Analisa a subárvore à direita
  }
  return;
}

/* A função a seguir implementa a impressão através do parâmetro da árvore */
void avl_imprimir(AVL *T)
{
  if (T != NULL)
  {
    avl_imprimir_auxiliar(T->raiz);
  }
  return;
}

/* A função a seguir verifica se a árvore está vazia */
bool avl_vazia(AVL *T)
{
  return (T != NULL && T->raiz == NULL); // Retorna true se for vazia e false se não for vazia
}

/* A função a seguir é importante para realizar a união entre dois conjuntos
Utiliza-se a propriedade de que na inserção de um elemento em uma árvore que já possui esse elemento
não haverá a inserção do elemento de forma repetida. Dessa forma, utiliza-se uma árvore
T1 como referência.
A partir disso, a árvore T1 é percorrida em ordem, onde para cada nó visitado é inserido
na árvore T2.
Com isso, tem-se que todos os elementos de T2 já estarão presentes e os elementos de T1 serão inseridos
sem repetição. Ao final, os elementos de T1 que já estavam em T2 não serão inseridos, garantindo
a união
*/
void avl_transferir_elementos(AVL *T1, AVL *T2)
{
  if (T1 == NULL && T2 == NULL)
    return;
  avl_transferir_elementos_auxiliar(T1->raiz, &(T2)->raiz);
}

/* A função a seguir é auxiliar da avl_transferir_elementos, implementando de forma principal
o percurso em ordem explicado na função anterior
 */
void avl_transferir_elementos_auxiliar(NO *raizA, NO **raizB) // Pega a árvore A e percorre em ordem e transfere para B inserindo
{
  if (raizA != NULL)
  {
    avl_transferir_elementos_auxiliar(raizA->fesq, raizB); // Realiza para a subárvore esquerda
    *raizB = avl_inserir_no((*raizB), raizA->chave);       // Insere os nos de uma arvora na outra
    avl_transferir_elementos_auxiliar(raizA->fdir, raizB); // Realiza para a subárvore direita
  }
  return;
}

/* A função a seguir é importante para a operacao de interseccao
O funcionamento ocorre da seguinte forma: uma árvore é percorrida em ordem, onde cada nó é visitado.
A visita consiste em uma verificação se esse elemento está presente em outra árvore. Dessa forma,
a visita é representada por uma busca. Caso esse elemento esteja presente na outra árvore, ele será
inserido na segunda árvore.

A partir disso, apenas elementos que estão na árvore T1 e árvore T2 serão inseridos na árvore T3.
Portanto, será realizado a intersecao dos elementos da arvore T1 e T2.
*/
void avl_interseccao_elementos(AVL *T1, AVL *T2, AVL *T3)
{
  if ((T1 == NULL || T2 == NULL) && T3 == NULL)
    return; // Se qualquer um dos dois conjuntos (A ou B) for vazio, então a interseção é vazia

  avl_interseccao_elementos_auxiliar(T1->raiz, T2->raiz, &T3->raiz);
}

/* A função a seguir é auxiliar da avl_interseccao_elementos, implementado o percurso em ordem,
onde a visita é uma verificação através de busca para inserir na terceira árvore (T3)
*/
void avl_interseccao_elementos_auxiliar(NO *raizA, NO *raizB, NO **raizC)
{
  if (raizA == NULL || raizB == NULL)
    return; // Se qualquer uma das duas árvores for nula então a interseção é vazia

  avl_interseccao_elementos_auxiliar(raizA->fesq, raizB, raizC); // Realiza para a subárvore esquerda
  if (avl_busca_no(raizB, raizA->chave))                         // Verifica se o elemento da arvore A já esta em B
    (*raizC) = avl_inserir_no((*raizC), raizA->chave);           // se já estiver (interseccao), então insere
  avl_interseccao_elementos_auxiliar(raizA->fdir, raizB, raizC); // Realiza para a subárvore direita
}