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
    srand (0); /* use assim, com zero */
        for (int i = 0; i < 5; i++) {
                int r = rand();        // gera número aleatório
                printf("%d\n", r);     // imprime
            }
    return (0) ;
}
