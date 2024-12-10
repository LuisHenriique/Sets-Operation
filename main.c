#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "avl.h"

int main()
{

  int num, num2;
  int qtd;

  CONJUNTO *conjuntoA;
  CONJUNTO *conjuntoB;

  conjuntoA = conjunto_criar(1);
  conjuntoB = conjunto_criar(1);

  printf("\nIndique a quantidade de elementos\n");
  scanf("%d", &qtd);
  printf("\nConjuntoA\n");
  for (int i = 0; i < qtd; i++)
  {
    scanf("%d", &num);
    conjunto_inserir_elemento(conjuntoA, num);
  }

  printf("\nConjuntoB\n");
  for (int j = 0; j < qtd; j++)
  {
    scanf("%d", &num2);
    conjunto_inserir_elemento(conjuntoB, num2);
  }

  conjunto_pertence(conjuntoA, 6);
  conjunto_pertence(conjuntoA, 59);
  conjunto_pertence(conjuntoB, 24);
  conjunto_pertence(conjuntoA, 150);
  conjunto_pertence(conjuntoB, 3);

  CONJUNTO *conjuntoC = conjunto_uniao(conjuntoA, conjuntoB);

  printf("\nCONJUNTO A\n");
  conjunto_imprimir(conjuntoA);

  printf("\nCONJUNTO B\n");
  conjunto_imprimir(conjuntoB);

  printf("\nCONJUNTO C\n");
  conjunto_imprimir(conjuntoC);

  // Liberação de memória
  conjunto_apagar(&conjuntoA);
  conjunto_apagar(&conjuntoB);
  conjunto_apagar(&conjuntoC);
  return 0;
}
