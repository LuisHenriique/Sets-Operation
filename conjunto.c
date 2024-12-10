/* O programa a seguir implementa as operações do TAD CONJUNTO */
/* Dentre as operações implementadas, estão as operações básicas e as específicas */

/* Bibliotecas utilizadas*/
#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h" // Header do TAD CONJUNTO
#include "avl.h"      // Header da estrutura 1 - AVL
#include "llrb.h"     // Header da estrutura 2 - LLRB

/* Definição das estruturas*/
struct conjunto
{                      // Estrutura utilizada para acessar o conjunto
  AVL *avl_conjunto;   // Ponteiro para a AVL
  LLRB *llrb_conjunto; // Ponteiro para a LLRB
  /*
  Há apenas uma estrutura conjunto. Caso o usuário deseje utilizar a estrutura AVL
  o ponteiro llrb_conjunto será alocado dinamicamente (tamanho padrão de ponteiro),
  no entanto não será utilizado. Ao final do programa principal, a memória extra do ponteiro
  será liberada
  */
  int tipo; // Variável para identificar qual tipo de estrutura de dados é utilizado
};

/* A função a seguir cria o conjunto */
CONJUNTO *conjunto_criar(int estrutura)
{
  /*
  A função recebe a variável estrutura e aloca memória para o ponteiro para conjunto

  Parâmetros:
    estrutura: armazena o tipo de estrutura que o usuário deseja
      valores possíveis: 0 - LLRB; 1 - AVL

  Returns: retorna o ponteiro para a memória alocada para o conjunto
  */
  CONJUNTO *conjunto = (CONJUNTO *)malloc(sizeof(CONJUNTO)); // Aloca memória para o conjunto
  if (conjunto == NULL)
    return NULL;

  if (estrutura == 1)           // Caso o valor seja 1
  {                             // Cria a estrutura AVL e associa ao ponteiro
    conjunto->tipo = estrutura; // dentro da estrutura conjunto
    conjunto->avl_conjunto = avl_criar();
  }
  else
  {                                         // Caso entre no else, o valor de estrutura é 0
    conjunto->tipo = estrutura;             // Armazena a estrutura na variável tipo
    conjunto->llrb_conjunto = llrb_criar(); // Cria a estrutura da LLRB e associa ao ponteiro
  } // dentro da estrutura conjunto
  return conjunto;
}

/* A função a seguir apaga o conjunto recebido*/
void conjunto_apagar(CONJUNTO **conjunto)
{
  /*
  A função recebe um conjunto como parâmetro e apaga esse conjunto
  realizando a liberação de memória

  Parâmetros:
    conjunto: conjunto a ser apagado

  Returns:
    void
  */
  if (conjunto == NULL && *conjunto == NULL)
    return;

  if ((*conjunto)->tipo == 1)                   // Caso seja implementado com AVL
    avl_apagar(&(*conjunto)->avl_conjunto);     // chama a função que apaga AVL
  else                                          // Caso seja implementado com LLRB
    llrb_destruir(&(*conjunto)->llrb_conjunto); // Chama a função para apagar LLRB
  free(*conjunto);                              // Libera o ponteiro do conjunto
  *conjunto = NULL;
}
bool conjunto_remover_elemento(CONJUNTO *conjunto, int chave)
{
  /*
  A função remove o elemento do conjunto com base na estrutura de dados utilizada
  Caso seja AVL, chama a função responsável por remover da AVL um elemento
  Caso seja LLRB, chama a função responsável por remover da LLRB um elemento

  Parâmetros:
    conjunto: conjunto do qual irá ser removido
    chave:    elemento a ser removido

  Returns:
  */
  if (conjunto != NULL)
  {
    if (conjunto->tipo == 1) // Analisa qual estrutura está sendo implementada
      return avl_remover(conjunto->avl_conjunto, chave);
    else
      return llrb_remover(conjunto->llrb_conjunto, chave);
  }

  return false;
}
bool conjunto_inserir_elemento(CONJUNTO *conjunto, int chave)
{
  /*
  A função recebe um conjunto como parâmetro e insere um elemento nesse conjunto.
  O funcionamento segue com base na estrutura de dados sendo utilizada.
  Caso seja AVL, chama a função que insere um elemento na AVL. Caso seja LLRB, chama a função
  responsável por inserir elementos na árvore LLRB.

  Parâmetros:
    conjunto: conjunto no qual será inserido o elemento
    chave:    elemento a ser inserido
  Returns:
    true:  inserção realizada com sucesso
    false: inserção não foi realizada com sucesso
  */
  if (conjunto != NULL)
  { // Operador ternário para decidir entre as estruturas de dados
    (conjunto->tipo == 1) ? avl_inserir(conjunto->avl_conjunto, chave) : llrb_inserir(conjunto->llrb_conjunto, chave);
    return true;
  }
  return false;
}
void conjunto_imprimir(CONJUNTO *conjunto)
{
  /*
  A função recebe um conjunto e imprime os elementos desse conjunto

  Parâmetros:
    conjunto: conjunto cujos elementos serão impressos
  Returns: void
  */
  if (conjunto != NULL) // Operador ternário para decidir entre qual estrutura de dados está sendo implementada
    (conjunto->tipo == 1) ? avl_imprimir(conjunto->avl_conjunto) : llrb_imprimir(conjunto->llrb_conjunto);
}

bool conjunto_pertence(CONJUNTO *conjunto, int chave)
{
  /*
  A função recebe um conjunto como parâmetro e verifica se um elemento está presente nesse conjunto
  O funcionamento ocorre com base na estrutura de dados utilizada. Caso seja AVL, chama a funcao
  de busca da AVL com o elemento a ser analisado. Por outro lado, caso seja LLRB, chama a funcao
  de busca da LLRB com o elemento analisado.

  Parâmetros:
    conjunto: conjunto no qual o elemento pertence ou não
    chave:    elemento analisado
  Returns:
    true - o elemento pertence ao conjunto
    false - o elemento não pertence ao conjunto
  */
  if (conjunto != NULL)
  {

    if (conjunto->tipo == 1)                                            // Analise da estrutura de dados
      return (avl_busca(conjunto->avl_conjunto, chave)) ? true : false; // AVL
    else
      return (llrb_busca(conjunto->llrb_conjunto, chave)) ? true : false; // LLRB
  }

  return false;
}

/* A função a seguir implementa a operação de uniao de 2 conjuntos */
CONJUNTO *conjunto_uniao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB)
{
  /*
  A funçao recebe dois conjuntos e realiza a união entre eles, chamando a operação
  com base na estrutura de dados utilizada
  Caso a estrutura seja AVL, chama a função avl_transferir_elementos
  A função avl_transferir_elementos realiza a união propriamente dita. Ela pega o conjunto
  A e insere todos os elementos dele no conjunto C. Após isso, chamamos novamente
  para o conjunto B, onde ela pega todos os elementos do conjunto B e insere eles no conjunto C.

  A grande vantagem dessa função é a propriedade da inserção em árvores, já que não há inserção
  de elementos repetidos. Dessa forma, caso um elemento de B esteja sendo inserido no conjunto C
  e esse elemento já tenha sido inserido, não haverá inserção, já que elementos repetidos não
  são inseridos em árvore

  A função llrb_transferir_elementos é análoga

  Parâmetros:
    conjuntoA: primeiro conjunto da uniao
    conjuntoB: segundo conjunto da uniao
  Returns:
    conjuntoC: conjunto resultante da união dos conjuntos A e B
  */
  if (conjuntoA == NULL && conjuntoB == NULL) // União de conjuntos vazios é vazia
    return NULL;

  if (conjuntoA != NULL && conjuntoB == NULL) // União de conjunto A com vazio é conjunto A
    return conjuntoA;

  if (conjuntoA == NULL && conjuntoB != NULL) // União de conjunto B com vazio é conjunto B
    return conjuntoB;

  CONJUNTO *conjuntoC;                              // Definição do conjunto da união
  if (conjuntoA->tipo == 1 && conjuntoB->tipo == 1) // Caso a estrutura seja AVL, realiza a inserção
  {                                                 // chamando a função da AVL
    // AVL
    conjuntoC = conjunto_criar(1); // Cria o conjunto C
    /* Chama as funções para enviar os elementos de A para C e depois B para C, sem repetir
    os elementos que já foram inseridos */
    avl_transferir_elementos(conjuntoA->avl_conjunto, conjuntoC->avl_conjunto);
    avl_transferir_elementos(conjuntoB->avl_conjunto, conjuntoC->avl_conjunto);
  }
  else // Caso a estrutura seja LLRB, realiza a inserção
  {    // chamando a função LLRB
    // LLRB
    conjuntoC = conjunto_criar(0); // Cria o conjunto C
    /* Chama as funções para enviar os elementos de A para C e depois B para C, sem repetir
    os elementos que já foram inseridos */
    llrb_transferir_elementos(conjuntoA->llrb_conjunto, conjuntoC->llrb_conjunto);
    llrb_transferir_elementos(conjuntoB->llrb_conjunto, conjuntoC->llrb_conjunto);
  }
  return conjuntoC;
}

/* A função a seguir implementa a interseção entre dois conjuntos */
CONJUNTO *conjunto_interseccao(CONJUNTO *conjuntoA, CONJUNTO *conjuntoB)
{
  /*
  A funçao recebe dois conjuntos e realiza a interseccao entre eles, chamando a operação
  com base na estrutura de dados utilizada
  Caso a estrutura utilizada seja AVL, chama a função avl_interseccao_elementos, que
  funciona da seguinte maneira: ela percorre em ordem todos os elementos do conjunto (AVL) A.
  A visita desse percurso equivale a uma verificação. A verificação é se o elemento de A
  está também no conjunto (AVL) B. Em outras palavras, é feita uma busca do elemento de A
  na árvore B. Caso ele esteja presente, ele é inserido no conjunto (AVL) C. Caso contrário,
  ele percorre a segunda parte do conjunto B.

  Parâmetros:
    conjuntoA: primeiro conjunto da interseccao
    conjuntoB: segundo conjunto da interseccao
  Returns:
    conjuntoC: conjunto resultante da interseccao dos conjuntos A e B
  */
  if (conjuntoA == NULL || conjuntoB == NULL) // Caso os dois conjuntos sejam vazios
    return NULL;                              // Então a interseccao é vazia

  CONJUNTO *conjuntoC; // Declaração do conjunto C

  if (conjuntoA->tipo == 1 && conjuntoB->tipo == 1) // Caso a estrutura de dados seja AVL
  {                                                 // AVL
    conjuntoC = conjunto_criar(1);                  // Cria o conjunto C com base em AVL
    /* Chama a função responsável pela inclusao de elementos comuns a duas árvores AVL em uma terceira árvore (interseccao) */
    avl_interseccao_elementos(conjuntoA->avl_conjunto, conjuntoB->avl_conjunto, conjuntoC->avl_conjunto);
  }
  else                             // Caso a estrutura de dados seja Árvore rubro-negra
  {                                // LLRBT
    conjuntoC = conjunto_criar(0); // Cria o conjunto C com base em Áarvore rubro-negra
    /* Chama a função responsável pela inclusao de elementos comuns a duas árvores rubro-negra em uma terceira árvore (interseccao) */
    llrb_interseccao_elementos(conjuntoA->llrb_conjunto, conjuntoB->llrb_conjunto, conjuntoC->llrb_conjunto);
  }
  return conjuntoC; // Retorna o conjunto com a interseccao
}