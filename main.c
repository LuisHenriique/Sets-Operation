#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

int main()
{

  CONJUNTO *conjuntoA;
  CONJUNTO *conjuntoB;
  CONJUNTO *conjuntoUniao = NULL;
  CONJUNTO *conjuntoInterseccao = NULL;
  int numA, numB, elemento;
  int operacao, tipo;

  scanf("%d", &tipo); /*0 -> LLRBT, 1 -> AVL_TREE*/
  conjuntoA = conjunto_criar(tipo);
  conjuntoB = conjunto_criar(tipo);

  scanf("%d %d", &numA, &numB);

  for (int i = 0; i < numA; i++)
  {
    scanf("%d", &elemento);
    conjunto_inserir_elemento(conjuntoA, elemento);
  }

  for (int j = 0; j < numB; j++)
  {
    scanf("%d", &elemento);
    conjunto_inserir_elemento(conjuntoB, elemento);
  }

  scanf("%d", &operacao);

  switch (operacao)
  {
  case 1:
  {
    // pertence
    scanf("%d", &elemento); // Elemento para verificar se está contido no conjunto
    if (conjunto_pertence(conjuntoA, elemento))
      printf("Pertence.\n");
    else
      printf("Nao pertence.\n");

    break;
  }
  case 2:
  {
    // união

    conjuntoUniao = conjunto_uniao(conjuntoA, conjuntoB);
    conjunto_imprimir(conjuntoUniao);
    conjunto_apagar(&conjuntoUniao);
    break;
  }
  case 3:
  {
    // intersecção
    conjuntoInterseccao = conjunto_interseccao(conjuntoA, conjuntoB);
    conjunto_imprimir(conjuntoInterseccao);
    conjunto_apagar(&conjuntoInterseccao);
    break;
  }
  case 4:
  {
    // remoção
    scanf("%d", &elemento); // Elemento que será removido
    conjunto_remover_elemento(conjuntoA, elemento);
    conjunto_imprimir(conjuntoA);
  }
  }

  // Liberação de memória
  conjunto_apagar(&conjuntoA);
  conjunto_apagar(&conjuntoB);

  return 0;
}
