#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "avl.h"

struct conjunto
{
  AVL *avl_conjunto;

  int tipo;
};

CONJUNTO *conjunto_criar(int estrutura)
{
  CONJUNTO *conjunto = (CONJUNTO *)malloc(sizeof(CONJUNTO));
  if (conjunto == NULL)
    return NULL;

  if (estrutura == 1)
  {
    conjunto->tipo = estrutura;
    conjunto->avl_conjunto = avl_criar();
  }
  else
  {
    conjunto->tipo = estrutura;
    // conjunto->lista_conjunto = lista_criar();
  }
  return conjunto;
}
void conjunto_apagar(CONJUNTO **conjunto)
{
  if (conjunto == NULL && *conjunto == NULL)
    return;

  if ((*conjunto)->tipo == 1)
  {
    avl_apagar(&(*conjunto)->avl_conjunto);
  }
  free(*conjunto);
  *conjunto = NULL;
}
void conjunto_remover_elemento(CONJUNTO *conjunto, int chave)
{

  if (conjunto == NULL)
    return;

  avl_remover(conjunto->avl_conjunto, chave);
}
void conjunto_inserir_elemento(CONJUNTO *conjunto, int chave)
{
  if (conjunto == NULL)
    return;

  if (conjunto->tipo == 1)
    avl_inserir(conjunto->avl_conjunto, chave);
}
void conjunto_imprimir(CONJUNTO *conjunto)
{
  if (conjunto == NULL)
    return;

  if (conjunto->tipo == 1)
    avl_imprimir(conjunto->avl_conjunto);
  else
  {
    // LLRBT
  }
}

void conjunto_pertence(CONJUNTO *conjunto, int chave)
{
  if (conjunto == NULL)
    return;

  if (conjunto->tipo == 1)
  {
    // avl
    if (avl_busca(conjunto->avl_conjunto, chave))
      printf("\nPertence\n");
    else
      printf("\nNão pertence\n");
  }
  else
  {
    // LLRBT
  }
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB)
{
  if (conjuntoA == NULL || conjuntoB == NULL)
    return NULL;

  CONJUNTO *conjuntoC;
  if (conjuntoA->tipo == 1 && conjuntoB->tipo == 1)
  {
    // avl
    conjuntoC = conjunto_criar(1);
    avl_transferir_elementos(conjuntoA->avl_conjunto, conjuntoC->avl_conjunto);
    avl_transferir_elementos(conjuntoB->avl_conjunto, conjuntoC->avl_conjunto);
  }
  else
  {
    // LLRBT
    conjuntoC = conjunto_criar(0);
  }
  return conjuntoC;
}
CONJUNTO *conjunto_interseccao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB)
{
  if (conjuntoA == NULL || conjuntoB == NULL)
    return NULL;

  CONJUNTO *conjuntoC;

  if (conjuntoA->tipo == 1 && conjuntoB->tipo == 1)
  {
    // avl
    conjuntoC = conjunto_criar(1);
    avl_interseccao_elementos(conjuntoA->avl_conjunto, conjuntoB->avl_conjunto, conjuntoC->avl_conjunto);
  }
  else
  {
    // LLRBT
    conjuntoC = conjunto_criar(0);
  }
  return conjuntoC;
}