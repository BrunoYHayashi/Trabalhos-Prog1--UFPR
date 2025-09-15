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

  struct racional vetor[100], vetorValido[100]; //define um vetor para até 100 números racionais, e um vetor que posteriormente conterá apenas os válidos

  scanf ("%ld", &n); //ler n
        if ((n<1)||(n>99))
            return(1); //inválido
    
  for (i=1; i<=n; i++){ //preenche valores de 1 até n no vetor
    scanf("%ld", &vetor[i].num); //lê numerador
    scanf("%ld", &vetor[i].den); //lê denominador
  }          

  printf("VETOR= "); //imprime vetor e o conteúdo do vetor lido
  for (i=1; i<=n; i++){
    imprime_r(vetor[i]);
  }

  printf("VETOR VALIDO= ");
  i=1; //inicializa o contador do vetor inteiro em 1
  j=1; //inicializa o contador do vetor válido em 1
  while(i<=n){ //inclui todos os valores do vetor
    while ((!valido_r(vetor[i])) && (i<=n)){ //verifica se vetor[i] é válido ou se i>n, visto que no loop ocorre o incremento de i
      i=i+1;
    }

    if (i<=n){ //verifica novamente se i>n, visto que o i pode ter saído do loop acima sendo maior que n
      vetorValido[j]=vetor[i]; //vetor válido recebe apenas os números racionais do vetor original
      i++; //incremento de i, nota-se que nem sempre i e j serão os mesmos, visto que na verificação anterior i pode ter sido incrementado múltiplas vezes, indicando multiplos números inválidos consecutivos
      j++; //incremento de j
    }
  }
  for (i=1; i<=j-1; i++){ //imprime os números do vetor válido, usa-se j-1 pois após a inserção do último elemento no vetor, j recebe j++
    imprime_r(vetorValido[i]);
  }

  selectSort (vetorValido, j-1); //ordena o vetorValido
  printf("VETOR= "); //imprime o vetor ordenado
  for (i=1; i<=j-1; i++){
    imprime_r(vetorValido[i]);
  }


    
  return (0) ;
}
