#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "avl.h"
#include "llrb.h"

struct conjunto
{
  AVL *avl_conjunto;
  LLRB *llrb_conjunto;

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
    conjunto->llrb_conjunto = llrb_criar();
  }
  return conjunto;
}
void conjunto_apagar(CONJUNTO **conjunto)
{
  if (conjunto == NULL && *conjunto == NULL)
    return;

  if ((*conjunto)->tipo == 1)
    avl_apagar(&(*conjunto)->avl_conjunto);
  else
    llrb_destruir(&(*conjunto)->llrb_conjunto);
  free(*conjunto);
  *conjunto = NULL;
}
bool conjunto_remover_elemento(CONJUNTO *conjunto, int chave)
{

  if (conjunto != NULL)
  {
    if (conjunto->tipo == 1)
      avl_remover(conjunto->avl_conjunto, chave);
    else
      llrb_remover(conjunto->llrb_conjunto, chave);

    return true;
  }

  return false;
}
bool conjunto_inserir_elemento(CONJUNTO *conjunto, int chave)
{
  if (conjunto != NULL)
  {
    (conjunto->tipo == 1) ? avl_inserir(conjunto->avl_conjunto, chave) : llrb_inserir(conjunto->llrb_conjunto, chave);
    return true;
  }
  return false;
}
void conjunto_imprimir(CONJUNTO *conjunto)
{
  if (conjunto != NULL)
    (conjunto->tipo == 1) ? avl_imprimir(conjunto->avl_conjunto) : llrb_imprimir(conjunto->llrb_conjunto);
}

bool conjunto_pertence(CONJUNTO *conjunto, int chave)
{
  if (conjunto != NULL)
  {

    if (conjunto->tipo == 1)
      return (avl_busca(conjunto->avl_conjunto, chave)) ? true : false; // avl
    else
      return (llrb_busca(conjunto->llrb_conjunto, chave)) ? true : false; // avl
  }

  return false;
}

CONJUNTO *conjunto_uniao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB)
{
  if (conjuntoA == NULL || conjuntoB == NULL)
    return NULL;

  CONJUNTO *conjuntoC;
  if (conjuntoA->tipo == 1 && conjuntoB->tipo == 1)
  {
    // AVL
    conjuntoC = conjunto_criar(1);
    avl_transferir_elementos(conjuntoA->avl_conjunto, conjuntoC->avl_conjunto);
    avl_transferir_elementos(conjuntoB->avl_conjunto, conjuntoC->avl_conjunto);
  }
  else
  {
    // LLRB
    conjuntoC = conjunto_criar(0);
    llrb_transferir_elementos(conjuntoA->llrb_conjunto, conjuntoC->llrb_conjunto);
    llrb_transferir_elementos(conjuntoB->llrb_conjunto, conjuntoC->llrb_conjunto);
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
    llrb_interseccao_elementos(conjuntoA->llrb_conjunto, conjuntoB->llrb_conjunto, conjuntoC->llrb_conjunto);
  }
  return conjuntoC;
}