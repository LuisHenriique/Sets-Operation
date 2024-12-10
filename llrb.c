#include <stdio.h>
#include <stdbool.h>

#include "llrb.h"

/* Definição das estruturas */
typedef struct no no_t;
struct no
{
    no_t *esq;
    no_t *dir;
    int cor;
    int info;
};

struct llrb_
{
    no_t *raiz;
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

int Vermelho(no_t *no)
{
    if (no == NULL)
        return (0);
    return (no->cor == 1);
}

void inverte(no_t *no)
{
    no->cor = !no->cor;
    if (no->esq)
        no->esq->cor = !no->esq->cor;
    if (no->dir)
        no->dir->cor = !no->dir->cor;
}

no_t *rotacaoDireita(no_t *c)
{
    no_t *b = c->esq;
    c->esq = b->dir;
    b->dir = c;
    b->cor = c->cor;
    c->cor = 1;
    return b;
}

no_t *rotacaoEsquerda(no_t *a)
{
    no_t *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = 1;
    return (b);
}

no_t *llrb_inserir_no(no_t *no, int data)
{
    if (no == NULL)
        return criarNo(data);
    if (data < no->info)
        no->esq = llrb_inserir_no(no->esq, data);
    else if (data > no->info)
        no->dir = llrb_inserir_no(no->dir, data);

    if (Vermelho(no->dir) && !Vermelho(no->esq))
        no = rotacaoEsquerda(no);
    if (Vermelho(no->esq) && Vermelho(no->esq->esq))
        no = rotacaoDireita(no);
    if (Vermelho(no->esq) && Vermelho(no->dir))
        inverte(no);

    return no;
}

bool llrb_inserir(LLRB *T, int data)
{
    return ((T->raiz = llrb_inserir_no(T->raiz, data)) != NULL);
}

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
bool llrb_remover(LLRB *T, int data)
{
    return ((T->raiz = apaga(T->raiz, data)) != NULL);
}
no_t *apaga(no_t *raiz, int chave)
{
    if (raiz == NULL)
        return (NULL);
    if (raiz->info == chave)
    {
        if (raiz->info == chave)
        {
            if (raiz->esq == NULL || raiz->dir == NULL)
            {
                no_t *p = raiz;
                raiz = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
                free(p);
            }
            else
            {
                // Substituição pelo menor da subárvore direita
                no_t *x = min(raiz->dir);
                raiz->info = x->info;             // Copia o valor do sucessor
                raiz->dir = removeMin(raiz->dir); // Remove o nó substituído
                raiz = restaura(raiz);            // Ajusta as propriedades rubro-negras
            }
        }
    }
    else
    {
        if (chave < raiz->info)
        {
            raiz = propagaEsquerda(raiz);
            raiz->esq = apaga(raiz->esq, chave);
        }
        else
        {
            raiz = propagaDireita(raiz);
            raiz->dir = apaga(raiz->dir, chave);
        }
    }
    if (raiz != NULL)
    {
        if (Vermelho(raiz->dir) && !Vermelho(raiz->esq))
            raiz = rotacaoEsquerda(raiz);
        if (Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
            raiz = rotacaoDireita(raiz);
        if (Vermelho(raiz->esq) && Vermelho(raiz->dir))
            inverte(raiz);
    }
    return (raiz);
}

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

void llrb_destruir(LLRB **T)
{
    if (*T == NULL)
        return;
    else
        llrb_destruir_aux(&(*T)->raiz);
}

void llrb_destruir_aux(no_t **raiz)
{
    if ((*raiz) == NULL)
        return;
    llrb_destruir_aux(&(*raiz)->esq);
    llrb_destruir_aux(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
}

void llrb_imprimir(LLRB *T)
{
    if (T != NULL)
        llrb_imprimir_aux(T->raiz);

    return;
}

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

void llrb_interseccao_elementos(LLRB *T1, LLRB *T2, LLRB *T3)
{
    if ((T1 == NULL || T2 == NULL) && T3 == NULL)
        return; // Se qualquer um dos dois conjuntos (A ou B) for vazio, então a interseção é vazia

    llrb_interseccao_elementos_auxiliar(T1->raiz, T2->raiz, &T3->raiz);
}

void llrb_interseccao_elementos_auxiliar(no_t *raizA, no_t *raizB, no_t **raizC)
{
    if (raizA == NULL || raizB == NULL)
        return; // Se qualquer uma for nula a interseção é vazia

    llrb_interseccao_elementos_auxiliar(raizA->esq, raizB, raizC);
    if (busca_no(raizB, raizA->info)) // 1.44 log n
        (*raizC) = llrb_inserir_no((*raizC), raizA->info);
    llrb_interseccao_elementos_auxiliar(raizA->dir, raizB, raizC);
}

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
bool llrb_busca(LLRB *T, int chave)
{
    return (busca_no(T->raiz, chave));
}