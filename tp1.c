/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"
#include <stdlib.h>

/* programa principal */
int main ()
{
    long n, max, i;
    struct racional r1, r2, 
                    soma, subtr, multip, divisao;

    srand (0);

    scanf ("%ld", &n); //descobrir se pede para inserir número de novo ou deixo como está abaixo:
      

    scanf ("%ld", &max);
    
    
    for (i=1; i<n; i++){
        printf("%ld: ", i);
        r1=sorteia_r(-max, max);
        r2=sorteia_r(-max, max);

        if ((valido_r(r1)==0) || (valido_r(r2)==0)){
            printf("NUMERO INVALIDO");
            return(1);
        }   
        else
            printf("%ld/%ld %ld/%ld ", r1.num, r1.den, r2.num, r2.den);
    
        soma= soma_r(r1, r2);
        subtr= subtrai_r(r1,r2);
        multip= multiplica_r(r1, r2);
        divisao= divide_r(r1, r2);
        if (divisao.den==0){
            printf("DIVISAO INVALIDA");
            return(1);
        }
        else {
            printf("%ld/%ld ", soma.num, soma.den);
            printf("%ld/%ld ", subtr.num, subtr.den);
            printf("%ld/%ld ", multip.num, multip.den);
            printf("%ld/%ld \n", divisao.num, divisao.den);
        }
    }
    return(0);
}
