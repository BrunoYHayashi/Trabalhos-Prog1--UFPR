/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"
/* coloque aqui as funções auxiliares que precisar neste arquivo */
static void imprimeVetor (struct racional V[], long max);
static void validaVetor (struct racional V[], long *max);
static void selectSort (struct racional V[], long max);
/* programa principal */
int main ()
{
  long n, i;
  struct racional soma;

  struct racional vetor[100]; //define um vetor para até 100 números racionais, e um vetor que posteriormente conterá apenas os válidos

  scanf ("%ld", &n); //ler n
  if ((n<1)||(n>99))
    return(1); //inválido
    
  for (i=1; i<=n; i++){ //preenche valores de 1 até n no vetor
    scanf("%ld", &vetor[i].num); //lê numerador
    scanf("%ld", &vetor[i].den); //lê denominador
  }          

  imprimeVetor(vetor, n); //imprime vetor e o conteúdo do vetor lido

  validaVetor(vetor, &n);
  imprimeVetor(vetor, n); //imprime vetor válido

  selectSort(vetor, n); //ordena vetor válido
  imprimeVetor(vetor, n); //imprime vetor ordenado

  soma.num=0; //inicializa o racional 0/1 como soma, para não usar um racional que afetaria a soma
  soma.den=1;
  for (i=1; i<=n; i++)
    soma_r(soma, vetor[i], &soma); //soma todos os valores do vetorValido
  printf("SOMA = ");
  imprime_r(soma);
  printf("\n"); 

  return (0) ;
}

static void imprimeVetor (struct racional V[], long max){ //imprime o vetor e pula linha
  int i;
  printf("VETOR = ");
  for (i=1; i<=max; i++)
    imprime_r(V[i]);
  printf("\n");
}

static void validaVetor (struct racional V[], long *max){
  int i, j;
  i=1; //inicializa o contador do vetor inteiro em 1
  j=1; //inicializa o contador do vetor válido em 1

  while(i<=*max){ //enquanto i for menor ou igual que o número total de elementos do vetor inteiro faça:
    while ((i<=*max) && (!valido_r(V[i]))){ //enquanto i for menor ou igual ao n de elementos do vetor inteiro E V[i] for válido faça:
      i++; // pula inválidos
    }
    if (i<=*max){ //como i pode ter sido incrementado a ponto de ser maior que o número de elementos, pergunta de novo se ele ainda é menor ou igual a max
      V[j]=V[i]; // copia o válido mais próximo
      i++; //i continua de onde achou o válido mais próximo +1
      j++; //j avança um para preencher o próximo elemento do vetor
    }
  }

  *max = j-1; // atualiza quantidade de elementos válidos, usa-se j-1 pois após atualizar o último elemento, ele ainda incrementa 1 em j
}


static void selectSort (struct racional V[], long max){ //selectSort
  int i, j, menor;
  struct racional AUX;

  for (i=1; i<max; i++){ 
    menor= i; //supões que o menor índice é i
    for (j=i+1; j<=max; j++){ //verifica os outros elementos do vetor
      if ((compara_r(V[j], V[menor]))== -1){
        menor=j; //se existir um elemento do vetor menor do que o elemento de V[i], o menor índice vira ele (j)
      }
    }
    if (menor!=i){ //se menor não for = i, significa que achou outro menor, logo, faz as alterações
      AUX= V[i];
      V[i]= V[menor];
      V[menor]= AUX;
    }
  }
}