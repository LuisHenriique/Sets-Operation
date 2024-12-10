#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "avl.h"

int main()
{

  CONJUNTO *conjuntoA;
  CONJUNTO *conjuntoB;
  CONJUNTO *conjuntoUniao;
  CONJUNTO *conjuntoInterseccao;
  int numA, numB, elemento;
  int operacao, tipo;

  scanf("%d", &tipo); /*0 -> LLRBT, 1 -> AVL_TREE*/
  conjuntoA = conjunto_criar(tipo);
  conjuntoB = conjunto_criar(tipo);

  printf("\nIndique a quantidade de elementos de A e B\n");
  scanf("%d %d", &numA, &numB);

  printf("\nConjuntoA\n");
  for (int i = 0; i < numA; i++)
  {
    scanf("%d", &elemento);
    conjunto_inserir_elemento(conjuntoA, elemento);
  }

  printf("\nConjuntoB\n");
  for (int j = 0; j < numB; j++)
  {
    scanf("%d", &elemento);
    conjunto_inserir_elemento(conjuntoB, elemento);
  }

  printf("\nOPERACAO\n");
  scanf("%d", &operacao);

  switch (operacao)
  {
  case 1:
  {
    // pertence
    scanf("%d", elemento); // Elemento para verificar se está contido no conjunto
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
    printf("\nCONJUNTO UNIAO\n");
    conjunto_imprimir(conjuntoUniao);
    break;
  }
  case 3:
  {
    // intersecção
    conjuntoInterseccao = conjunto_interseccao(conjuntoA, conjuntoB);
    printf("\nCONJUNTO INTERSECCAO\n");
    conjunto_imprimir(conjuntoInterseccao);
    break;
  }
  case 4:
  {
    // remoção
    scanf("%d", elemento); // Elemento que será removido
    conjunto_remover_elemento(conjuntoA, elemento);
    conjunto_imprimir(conjuntoA);
  }
  }

  /*REMOVER COMENTS*/
  printf("\nCONJUNTO A\n");
  conjunto_imprimir(conjuntoA);

  printf("\nCONJUNTO B\n");
  conjunto_imprimir(conjuntoB);

  // Liberação de memória
  conjunto_apagar(&conjuntoA);
  conjunto_apagar(&conjuntoB);
  conjunto_apagar(&conjuntoUniao);
  conjunto_apagar(&conjuntoInterseccao);
  return 0;
}
