// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// A COMPLETAR

struct fprio_t *fprio_cria (){
  struct fprio_t *fprioCriada;
  if (!(fprioCriada=malloc (sizeof(struct fprio_t)))) //tenta alocar de forma dinâmica uma memória para a fila. 
    return NULL; //Caso falhe, retorna NULL

  fprioCriada->prim = NULL; //Primeiro nodo da fila é NULL
  fprioCriada->num = 0; //Número de ítens da fila é 0
  
  return fprioCriada;
}

struct fprio_t *fprio_destroi (struct fprio_t *f){

  if (!f) //verifica se f é válido
    return NULL; //se não for, retorna NULL

  struct fpnodo_t *atual, *prox;

  atual = f->prim;
  
  while (atual != NULL){ //da free para todos os nodos da fila até que atual (nodo atual) seja NULL, nesse caso, não existe mais nodos na fila
    prox = atual->prox;
    free (atual->item); //da free no item do nodo
    free (atual); //da free no atual
    atual = prox;
  }

  free(f); //da free na fila
  return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){

}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){

}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f){

}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f){

}
