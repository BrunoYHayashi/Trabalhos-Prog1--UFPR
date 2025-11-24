#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "events.h"
#include "fprio.h"
#include "fila.h"
#include "entities.h"
#include "conjunto.h"
#include "environment.h"

void schedule_event (struct world *w, int time, int tipo, struct hero *hero, struct base *base, struct mission *mission){
    struct event *event;

    if(!(event=malloc(sizeof(struct event)))) //Aloca memória para o evento
        return;

    /*Atribui ao evento o herói afetado, a base afetada, ou a missão*/
    event->hero= hero;
    event->base=base;
    event->mission=mission;

    fprio_insere(w->lef, event, tipo, time); //Insere na fila de prioridades o evento
}

void event_chega (struct world *w, int time, struct event *data) {
    struct hero *hero = data->hero;
    struct base *base = data->base;

    hero->base=base; //Base em que o herói está

    bool decision; //decisao do herói
    int queue = fila_tamanho(base->waitLine); //Heróis na fila
    int occupy = cjto_card(base->presents); //Heróis que estão na base

    /*Verificação da decisão do herói:
    Se a base não estiver lotada e a fila estiver vazia, ele decide ficar sem pensar
    Se não, ele fica apenas se a paciência dele for maior que 10* a fila*/
    if (occupy < base->capacity && queue == 0) 
        decision = true;
    else
        decision = (hero->pacience > (10*queue));

    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ", time, hero->ID, base->ID, occupy, base->capacity);
    printf("%s \n", decision ? "ESPERA" : "DESISTE");

    /*Define o próximo evento
    Se a decisão for ficar, ocorre o evento espera
    Se não, ocorre o evento desiste*/
    if (decision)
        schedule_event(w, time, EVENT_ESPERA, hero, base, NULL);
    else 
        schedule_event(w, time, EVENT_DESISTE, hero, base, NULL);
}

void event_espera(struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *base = data->base;

    int *idPtr; //cria um ponteiro para o id do herói
    if (!(idPtr=malloc(sizeof(int))))
        return;
    
    *idPtr = hero->ID; 
    fila_insere(base->waitLine, idPtr); //insere o ponteiro do id do herói na fila

    int queue = fila_tamanho(base->waitLine); //"queue" recebe o tamanho da fila

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", time, hero->ID, queue -1);

    schedule_event(w, time, EVENT_AVISA, NULL, base, NULL); //Agenda o próximo evento (AVISA)
}

void event_desiste (struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *base = data->base;

    int random_baseID = aleat(0, w->Nbases -1); //gera o ID de uma nova base aleatória
    struct base *newDestiny = w->bases[random_baseID]; //atribui para "newDestiny" essa nova base

    printf("%6d: DESIST HEROI %2d BASE %d\n", time, hero->ID, base->ID);

    schedule_event(w, time, EVENT_VIAJA, hero, newDestiny, NULL); //agenda o próximo evento, a viagem do herói para a nova base
}
/*Próximos passos: 
event_avisa
event_entra
event_sai
event_viaja*/