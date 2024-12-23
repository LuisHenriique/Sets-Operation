#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <stdbool.h>
#include "avl.h"
#include "llrb.h"
#define AVL_TREE 1
#define LLRBT 0

typedef struct conjunto CONJUNTO;

CONJUNTO *conjunto_criar(int estrutura);
void conjunto_apagar(CONJUNTO **conjunto);
bool conjunto_remover_elemento(CONJUNTO *conjunto, int chave);
bool conjunto_inserir_elemento(CONJUNTO *conjunto, int chave);
void conjunto_imprimir(CONJUNTO *conjuntO);
bool conjunto_pertence(CONJUNTO *conjunto, int chave);
CONJUNTO *conjunto_uniao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB);
CONJUNTO *conjunto_interseccao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB);

#endif