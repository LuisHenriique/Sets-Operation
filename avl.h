#ifndef AVL_H
#define AVL_H
#define max(a, b) ((a > b) ? a : b)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct avl AVL;

AVL *avl_criar(void);
bool avl_inserir(AVL *T, int chave);
void avl_apagar(AVL **T);
bool avl_remover(AVL *T, int chave);
bool avl_busca(AVL *T, int chave);
void avl_imprimir(AVL *T);
bool avl_vazia(AVL *T);
void avl_transferir_elementos(AVL *T1, AVL *T2);
void avl_interseccao_elementos(AVL *T1, AVL *T2, AVL *T3);
#endif