#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
    struct lista *listaNova;
    if (!(listaNova=malloc (sizeof(struct lista))))
        return NULL;
    return listaNova;
}

void lista_destroi (struct lista **lista){
    
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *inicio;

    if (!(inicio=malloc(sizeof(struct nodo))))
        return 0;

    inicio->chave= chave;
    inicio->prox= lista->ini;

    lista->ini= inicio;
    lista->tamanho= lista->tamanho+1;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *fim;

    if (!(fim=malloc(sizeof(struct nodo))))
        return 0;

    fim->chave=chave;
    fim->prox=NULL;

    lista->ptr = lista->ini;

    while (lista->ptr->prox != NULL)
        lista->ptr = lista->ptr->prox;

    lista->ptr->prox = fim;
    lista->tamanho= lista->tamanho +1;

    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *novoNodo;
    int *i;

    if (!(novoNodo = malloc(sizeof(struct nodo))))
        return 0;

    novoNodo->chave = chave; 
    lista->ptr = lista->ini;   
    
    while (chave < lista->ptr->chave)
        lista->ptr = lista->ptr->prox;

    novoNodo->prox = lista->ptr->prox;
    lista->ptr->prox = novoNodo;

    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *nodoRemovido;

    nodoRemovido = lista->ini;
    lista->ini = lista->ini->prox;

    free(nodoRemovido);
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
