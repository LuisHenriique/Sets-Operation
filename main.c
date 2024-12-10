/*
Este é o programa principal do projeto de implementação de sets utilizando 2 estruturas de dados.
O seguinte programa coordena as operações do usuário através de variáveis auxiliares

Autores:
  Luis Henrique Ponciano dos Santos (Nusp: )
  Gabriel de Araujo Lima            (Nusp: )
*/

/* Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h" // Header contendo as operações do TAD CONJUNTO

/* Função principal */
/*
A função principal declara os ponteiros para os conjuntos do usuário (conjuntos A e B)
Além disso, coordena as entradas do usuário, na seguinte ordem:
  Entrada 1: estrutura de dados utilizada (0 para árvore rubro negra, 1 para AVL)
  Entrada 2: tamanho do primeiro conjunto
  Entrada 3: tamanho do segundo conjunto
  Entrada 4: elementos do primeiro conjunto
  Entrada 5: elementos do segundo conjunto
  Entrada 6: operação a ser utilizada (existem 4 operações possíveis)

Após isso, o código analisa a entrada 6 e chama as funções adequadas para
fazer a operação correspondente à solicitação do usuário
*/
int main()
{

  CONJUNTO *conjuntoA;                  // Declaração do ponteiro para o conjunto A
  CONJUNTO *conjuntoB;                  // Declaração do ponteiro para o conjunto B
  CONJUNTO *conjuntoUniao = NULL;       // Declaração do ponteiro para o conjunto uniao
  CONJUNTO *conjuntoInterseccao = NULL; // Declaração do ponteiro para o conjunto interseccao
  int numA, numB, elemento;             // Declaração de variáveis auxiliares
  // numA     - variável para armazenar a quantidade de elementos do conjunto A
  // numB     - variável para armazenar a quantidade de elementos do conjunto B
  // elemento - variável para armazenar temporariamente o elemento lido

  int operacao, tipo; // Declaração de variáveis auxiliares
  // operacao - variável que armazena a operação do usuário
  // Valores adequados para 'operacao':
  // 1 - Pertence
  // 2 - Uniao
  // 3 - Interseccao
  // 4 - Remocao

  // tipo - variável para armazenar o tipo de estrutura de dados que o usuário deseja
  // Valores adequados para 'tipo':
  // 0 - Estrutura Árvore rubro-negra (LLRBT)
  // 1 - Estrutura AVL

  scanf("%d", &tipo);               // Leitura do tipo
  conjuntoA = conjunto_criar(tipo); // Cria o conjunto A com base no tipo
  conjuntoB = conjunto_criar(tipo); // Cria o conjunto B com base no tipo

  scanf("%d %d", &numA, &numB); // Leitura da quantidade de elementos de cada conjunto

  /* O loop a seguir é utilizado para preencher o conjunto A com os valores lidos */
  for (int i = 0; i < numA; i++)
  {
    scanf("%d", &elemento);                         // Leitura do elemento
    conjunto_inserir_elemento(conjuntoA, elemento); // Armazena o elemento no conjunto A
  }

  /* De forma analoga, o loop a seguir é utilizado para preencher o conjunto B com os valores lidos*/
  for (int j = 0; j < numB; j++)
  {
    scanf("%d", &elemento);                         // Leitura do elemento
    conjunto_inserir_elemento(conjuntoB, elemento); // Armazena o elemento no conjunto B
  }

  scanf("%d", &operacao); // Leitura da operação do usuário

  /* O switch case a seguir é utilizado para chamar as funções específicas com base na operação */
  switch (operacao)
  {
  case 1: // Operação 'pertence'
  {
    scanf("%d", &elemento); // Elemento para verificar se está contido no conjunto
    if (conjunto_pertence(conjuntoA, elemento))
      printf("Pertence.\n");
    else
      printf("Nao pertence.\n");

    break;
  }
  case 2: // Operação 'uniao'
  {
    conjuntoUniao = conjunto_uniao(conjuntoA, conjuntoB);
    conjunto_imprimir(conjuntoUniao);
    conjunto_apagar(&conjuntoUniao);
    break;
  }
  case 3: // Operação 'interseccao'
  {
    conjuntoInterseccao = conjunto_interseccao(conjuntoA, conjuntoB);
    conjunto_imprimir(conjuntoInterseccao);
    conjunto_apagar(&conjuntoInterseccao);
    break;
  }
  case 4:                                           // Operação 'remoção'
  {                                                 // Por padrão, o elemento será removido do conjunto A
    scanf("%d", &elemento);                         // Leitura do elemento a ser removido
    conjunto_remover_elemento(conjuntoA, elemento); // Chama a função para remover o elemento do conjunto A
    conjunto_imprimir(conjuntoA);                   // Imprime o conjunto
  } // Sendo esperado todos os elementos anteriores
  } // exceto o elemento removido

  // Liberação de memória
  conjunto_apagar(&conjuntoA);
  conjunto_apagar(&conjuntoB);

  return 0;
}
