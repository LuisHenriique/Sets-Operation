#ifndef LLRB_H
#define LLRB_H
#define max(a, b) ((a > b) ? a : b)

#include <stdbool.h>
#include <stdlib.h>

typedef struct llrb_ LLRB;
/*
LLRB *avl_criar(void);
bool avl_inserir(LLRB *T, int chave);
void avl_imprimir(LLRB *T);
void avl_apagar(LLRB **T);
bool avl_remover(LLRB *T, int chave);
bool avl_busca(LLRB *T, int chave);
bool avl_vazia(LLRB *T);
*/
LLRB *llrb_criar(void);
bool llrb_inserir(LLRB *T, int data);
bool llrb_remover(LLRB *T, int data);
void llrb_destruir(LLRB **T);
void llrb_transferir_elementos(LLRB *T1, LLRB *T2);
void llrb_interseccao_elementos(LLRB *T1, LLRB *T2, LLRB *T3);
bool llrb_busca(LLRB *T, int chave);
void llrb_imprimir(LLRB *T);

#endif