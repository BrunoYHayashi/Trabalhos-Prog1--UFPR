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

void event_avisa (struct world *w, int time, struct event *data){
    struct base *base = data->base;

    int occupy = cjto_card(base->presents); //atribui a "occupy" o número de presentes na base

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", time, base->ID, occupy, base->capacity);
    fila_imprime(base->waitLine);
    printf(" ]\n");

    while (occupy < base->capacity && fila_tamanho(base->waitLine) > 0){ //enquanto a base não estiver lotada e tiver gente na fila
        int *idPtr = fila_retira(base->waitLine); //tira o primeiro herói da fila
        int heroId = *idPtr;
        free(idPtr); //libera a memória criada no event_espera

        cjto_insere(base->presents, heroId); //adiciona o herói no conjunto de presentes na base
        occupy++; //atualiza contagem pro loop

        struct hero *hero = w->heroes[heroId]; //recupera o ponteiro do herói para passar no "agendador"

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", time, base->ID, heroId);

        schedule_event(w, time, EVENT_ENTRA, hero, base, NULL); //agenda o próximo evento (entrada)
    }
}

void event_entra (struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *base = data->base;

    int stayTime = 15 + hero->pacience * aleat(1,20); //Tempo de permanência do herói
    int exitTime = time +stayTime;

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", time, hero->ID, base->ID, cjto_card(base->presents), base->capacity, exitTime);

    schedule_event(w, exitTime, EVENT_SAI, hero, base, NULL); //Agenda o próximo evento (SAÍDA)
}

void event_sai (struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *base = data->base;

    cjto_retira(base->presents, hero->ID); //tira o herói da base

    int destinyId = aleat(0,w->Nbases -1); //novo destino aleatório do herói
    struct base *destiny = w->bases[destinyId]; 

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", time, hero->ID, base->ID, cjto_card(base->presents), base->capacity);

    schedule_event(w, time, EVENT_VIAJA, hero, destiny, NULL); //agenda o próximo evento (viaja)
    schedule_event(w, time, EVENT_AVISA, NULL, base, NULL); //avisa que abriu uma vaga na base
}

void event_viaja (struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *destiny = data->base; //base destino
    struct base *origin = hero->base; //base origem

    int distX = destiny->location.x - origin->location.x; //distância do destino e da origem (x2-x1)
    int distY = destiny->location.y - origin->location.y; //distância do destino e da origem (y2-y1)
    int distance = (int)sqrt((distX*distX) + (distY*distY)); //distância cartesiana = sqrt((x2-x1)² + (y2-y1)²)

    int duration = distance / hero->speed; //duração (distancia/velocidade)
    int arrivalTime = time + duration; //hora de chegada

    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", time, hero->ID, origin->ID, destiny->ID, distance, hero->speed, arrivalTime);

    schedule_event(w, arrivalTime, EVENT_CHEGA, hero, destiny, NULL); //agenda próximo evento (CHEGA na próxima base)
}

void event_morre (struct world *w, int time, struct event *data){
    struct hero *hero = data->hero;
    struct base *base = data->base;

    cjto_retira(base->presents, hero->ID); //retira o herói da base

    hero->alive = false; //coloca o estado do herói como não vivo

    hero->base = NULL; //base vira nula

    printf("%6d: MORRE HEROI %2d MISSAO %d\n", time, hero->ID, data->mission ? data->mission->ID : -1); //faz uma condicional para não dar seg fault

    schedule_event(w, time, EVENT_AVISA, NULL, base, NULL); //agenda o próximo evento (AVISA) para alertar que abriu uma vaga na base
}

void event_fim (struct world *w, int time, struct event *data){
    printf("%6d: FIM\n, time");
}