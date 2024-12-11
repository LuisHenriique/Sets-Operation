/* Bibliotecas utilizadas */
#include <stdio.h>
#include <stdbool.h>

#include "llrb.h"

/* Definição das estruturas */
typedef struct no no_t;
struct no
{
    no_t *esq; // No esquerdo (representa a subarvore a esquerda)
    no_t *dir; // No direito (representa a subarvore a direita)
    int cor;   // Cor do nó (0 - preto; 1 - vermelho)
    int info;  // Valor do elemento do nó
};

struct llrb_
{
    no_t *raiz; // A estrutura para a árvore contem um nó para a raiz
};
typedef struct llrb_ LLRB;

/* Protótipos das funções */
void inverte(no_t *r);
no_t *rotacaoDireita(no_t *c);
no_t *rotacaoEsquerda(no_t *a);
int Vermelho(no_t *h);
no_t *propagaEsquerda(no_t *h);
no_t *propagaDireita(no_t *h);

/* Funções auxiliares */
no_t *min(no_t *raiz);
no_t *removeMin(no_t *raiz);
no_t *restaura(no_t *h);
no_t *criarNo(int data);
void llrb_destruir_aux(no_t **raiz);
no_t *apaga(no_t *raiz, int chave);
void llrb_imprimir_aux(no_t *raiz);
void llrb_transferir_elementos_auxiliar(no_t *raizA, no_t **raizB);
void llrb_interseccao_elementos_auxiliar(no_t *raizA, no_t *raizB, no_t **raizC);
bool busca_no(no_t *raiz, int chave);

/* Implementação das funções */

/* A função a seguir implementa a criação da árvore */
LLRB *llrb_criar(void)
{
    LLRB *T = (LLRB *)malloc(sizeof(LLRB));
    if (T != NULL)
    {
        T->raiz = NULL;
        return (T);
    }
    return (NULL);
}

/* A função a seguir verifica se o nó é vermelho */
/* Retorna 1 se for vermelho e 0 se não for vermelho */
int Vermelho(no_t *no)
{
    if (no == NULL)
        return (0);
    return (no->cor == 1);
}

/* A função a seguir auxilia no balanceamento */
void inverte(no_t *no)
{
    no->cor = !no->cor;
    if (no->esq)
        no->esq->cor = !no->esq->cor;
    if (no->dir)
        no->dir->cor = !no->dir->cor;
}

/* A função a seguir auxilia no balanceamento através da rotação para direita */
no_t *rotacaoDireita(no_t *c)
{
    no_t *b = c->esq;
    c->esq = b->dir;
    b->dir = c;
    b->cor = c->cor;
    c->cor = 1;
    return b;
}

/* A função a seguir auxilia no balanceamento através da rotação para esquerda */
no_t *rotacaoEsquerda(no_t *a)
{
    no_t *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = 1;
    return (b);
}

/* A função a seguir implementa a inserção do no na arvore */
no_t *llrb_inserir_no(no_t *no, int data)
{
    if (no == NULL)
        return criarNo(data);
    if (data < no->info)
        no->esq = llrb_inserir_no(no->esq, data);
    else if (data > no->info)
        no->dir = llrb_inserir_no(no->dir, data);

    /* Apos inserir, realiza o rebalanceamento */
    if (Vermelho(no->dir) && !Vermelho(no->esq))
        no = rotacaoEsquerda(no);
    if (Vermelho(no->esq) && Vermelho(no->esq->esq))
        no = rotacaoDireita(no);
    if (Vermelho(no->esq) && Vermelho(no->dir))
        inverte(no);

    return no;
}

/* Função para inserir no na arvore */
bool llrb_inserir(LLRB *T, int data)
{
    return ((T->raiz = llrb_inserir_no(T->raiz, data)) != NULL);
}

/* Funcao auxiliar para rebalancear a arvore */
no_t *propagaEsquerda(no_t *no)
{
    if (!Vermelho(no->esq) && !Vermelho(no->esq->esq))
    {
        inverte(no);
        if (Vermelho(no->dir->esq))
        {
            no->dir = rotacaoDireita(no->dir);
            no = rotacaoEsquerda(no);
            inverte(no);
        }
    }
    return (no);
}

/* Funcao auxiliar para rebalancear a arvore */
no_t *propagaDireita(no_t *no)
{
    if (Vermelho(no->esq))
        no = rotacaoDireita(no);
    if (!(Vermelho(no->dir)) && !Vermelho(no->dir->esq))
    {
        inverte(no);
        if (Vermelho(no->esq->esq))
        {
            no = rotacaoDireita(no);
            inverte(no);
        }
    }
    return (no);
}

/* Funcao para remover um nó da arvore */
bool llrb_remover(LLRB *T, int data)
{
    T->raiz = apaga(T->raiz, data);
    if (T->raiz != NULL)
        return (true);
    else
        return (false);
}

/* Funcao auxiliar para remover um nó da árvore a partir dos casos de remoção */
no_t *apaga(no_t *raiz, int chave)
{
    if (raiz == NULL)
    {
        // O nó não existe na árvore
        return NULL;
    }

    if (chave < raiz->info)
    {
        raiz = propagaEsquerda(raiz);
        raiz->esq = apaga(raiz->esq, chave);
    }
    else if (chave > raiz->info)
    {
        raiz = propagaDireita(raiz);
        raiz->dir = apaga(raiz->dir, chave);
    }
    else
    {
        // Encontramos o nó a ser removido
        if (raiz->esq == NULL || raiz->dir == NULL)
        {
            // Caso em que o nó tem no máximo um filho
            no_t *p = raiz;
            raiz = (raiz->esq != NULL) ? raiz->esq : raiz->dir; // Substitui pelo filho não nulo
            free(p);
        }
        else
        {
            // Caso em que o nó tem dois filhos
            // Substituir pelo menor valor da subárvore direita
            no_t *x = min(raiz->dir);
            raiz->info = x->info;             // Copia o valor do sucessor
            raiz->dir = removeMin(raiz->dir); // Remove o nó substituído
            raiz = restaura(raiz);            // Ajusta as propriedades rubro-negras
        }
    }

    if (raiz != NULL)
        raiz = restaura(raiz); // Restaura a árvore após a remoção

    return raiz;
}

/* Funcao auxiliar para criar nó com base em um valor */
no_t *criarNo(int data)
{
    no_t *novo = (no_t *)malloc(sizeof(no_t));
    if (novo != NULL)
    {
        novo->info = data;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->cor = 1; // Nós recém-inseridos são vermelhos
    }
    return novo;
}

/* Funcao que retorna o menor nó da árvore */
no_t *min(no_t *raiz)
{
    no_t *t = raiz;
    while (t->esq != NULL)
        t = t->esq;
    if (t == NULL)
        return NULL;
    else
        return t;
}

/* Funcao para remover o menor nó que tem na árvore */
no_t *removeMin(no_t *raiz) // Recebe a subárvore
{
    if (raiz->esq == NULL)
        return (NULL);

    if (!Vermelho(raiz->esq) && !Vermelho(raiz->esq->esq))
        raiz = propagaEsquerda(raiz);

    raiz->esq = removeMin(raiz->esq);
    raiz = restaura(raiz);

    if (Vermelho(raiz->dir))
        raiz = rotacaoEsquerda(raiz);

    return (raiz);
}

/* Funcao para realizar o rebalanceamento */
no_t *restaura(no_t *h) // Precisa analisar se ta dando certo
{
    if (Vermelho(h->dir))
        h = rotacaoEsquerda(h);
    if (Vermelho(h->esq) && Vermelho(h->esq->esq))
        h = rotacaoDireita(h);
    if (Vermelho(h->esq) && Vermelho(h->dir))
        inverte(h);
    return h;
}

/* Funcao para liberar a memória da árvore */
void llrb_destruir(LLRB **T)
{
    if (*T == NULL)
        return;
    else
        llrb_destruir_aux(&(*T)->raiz);
}

/* Funcao auxiliar para liberar a memória da árvore */
void llrb_destruir_aux(no_t **raiz)
{
    if ((*raiz) == NULL)
        return;
    llrb_destruir_aux(&(*raiz)->esq);
    llrb_destruir_aux(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

/* Funcao para imprimir os elementos da árvore */
void llrb_imprimir(LLRB *T)
{
    if (T != NULL)
        llrb_imprimir_aux(T->raiz);

    return;
}

/* Funcao auxiliar para imprimir os elementos da árvore */
void llrb_imprimir_aux(no_t *raiz)
{
    if (raiz != NULL)
    {
        llrb_imprimir_aux(raiz->esq);
        printf("%d, ", raiz->info);
        llrb_imprimir_aux(raiz->dir);
    }
    return;
}

/* Funcao que auxilia a uniao de duas árvores */
/* O funcionamento da função se baseia no fato de que as inserções em árvore
não acontecem com elementos repetidos
*/
void llrb_transferir_elementos(LLRB *T1, LLRB *T2)
{
    if (T1 == NULL && T2 == NULL)
        return;
    llrb_transferir_elementos_auxiliar(T1->raiz, &(T2)->raiz);
}
void llrb_transferir_elementos_auxiliar(no_t *raizA, no_t **raizB) // Pega a árvore A e percorre em ordem e transfere para B inserindo
{
    if (raizA != NULL)
    {
        llrb_transferir_elementos_auxiliar(raizA->esq, raizB);
        *raizB = llrb_inserir_no((*raizB), raizA->info); // insere os nos de uma arvora na outra
        llrb_transferir_elementos_auxiliar(raizA->dir, raizB);
    }
    return;
}

/* A funcao a seguir implementa a intersecção entre duas árvores */
void llrb_interseccao_elementos(LLRB *T1, LLRB *T2, LLRB *T3)
{
    if ((T1 == NULL || T2 == NULL) && T3 == NULL)
        return; // Se qualquer um dos dois conjuntos (A ou B) for vazio, então a interseção é vazia

    llrb_interseccao_elementos_auxiliar(T1->raiz, T2->raiz, &T3->raiz);
}

/* A funcao a seguir implementa a intersecção auxiliar entre duas árvores */
void llrb_interseccao_elementos_auxiliar(no_t *raizA, no_t *raizB, no_t **raizC)
{
    if (raizA == NULL || raizB == NULL)
        return; // Se qualquer uma for nula a interseção é vazia

    llrb_interseccao_elementos_auxiliar(raizA->esq, raizB, raizC);
    if (busca_no(raizB, raizA->info)) // 1.44 log n
        (*raizC) = llrb_inserir_no((*raizC), raizA->info);
    llrb_interseccao_elementos_auxiliar(raizA->dir, raizB, raizC);
}

/* Funcao que implementa a busca de um elemento na árvore */
bool busca_no(no_t *raiz, int chave)
{
    while (raiz != NULL)
    {
        if (chave < raiz->info)
            raiz = raiz->esq;
        else if (chave > raiz->info)
            raiz = raiz->dir;
        else
            return true;
    }
    return false;
}

/* Funcao para a busca de um elemento na árvore*/
bool llrb_busca(LLRB *T, int chave)
{
    return (busca_no(T->raiz, chave));
}