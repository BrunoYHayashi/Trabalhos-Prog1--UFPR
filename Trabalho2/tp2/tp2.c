/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"
/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main ()
{
  long n, i, j;
  struct racional r1, r2, *r3;

  struct racional vetor[100];
  scanf ("%ld", &n); //ler n
        if ((n<1)||(n>99))
            return(1); //inválido
    
  for (i=1; i<=n; i++){
    vetor[i].num= scanf("%ld");
    vetor[i].den= scanf("%ld");
  }          

  printf("VETOR= ");
  for (i=1; i<=n; i++){
    imprime_r(vetor[i]);
  }

  printf("VETOR= ");
  for (i=1; i<=n; i++){
    if (!valido_r(vetor[i])){
      j=i+1;
      while (j<=n){
        if (valido_r(vetor[j])){
          vetor[i]=vetor[j];
          vetor[j].den=0;
        }
      }
    }
  }

  return (0) ;
}
