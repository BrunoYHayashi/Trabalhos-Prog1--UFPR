/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>

/* aqui vem a struct racional propriamente dita, nao modifique! */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b)
{
  long maior, menor, AUX;
  if (a>b) { //condição para obter o maior valor e o menor valor entre a e b
    maior= a;
    menor=b;
  }
  else {
    maior=b;
    menor=a;
  }

  while (menor!=0){ //loop para encontrar o mdc => dividendo² (maior) = divisor¹; divisor²= dividendo¹ % divisor¹
    AUX= maior % menor;
    maior= menor;
    menor= AUX;
  }

  return(maior);  //retorna o último "resto" de divisão anterior ao resto 0
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  long minMulCom;
  minMulCom= ((a*b)/(mdc(a, b))); //utiliza a fórmula para calcular o mínimo múltiplo comum e retorna esse valor
  return(minMulCom);
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r (struct racional *r)
{
  /* implemente aqui */
}

/* implemente as demais funções de racional.h aqui */
