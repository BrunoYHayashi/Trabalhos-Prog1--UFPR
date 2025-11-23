#include <stdio.h>  
#include <stdlib.h>

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
