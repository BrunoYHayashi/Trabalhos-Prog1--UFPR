#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "entities.h"
#include "environment.h"
#include "events.h"

/*Inicia o mundo*/
struct world *initialize_world(){
    struct world *newWorld;

    if(!(newWorld=malloc(sizeof(struct world)))) //Aloca memória para o mundo
        return NULL;

    newWorld->lef= fprio_cria(); //Cria a fila de prioridades lef
    if (!newWorld->lef){ //verifica se fprio_cria foi bem sucedido
        free(newWorld);
        newWorld= NULL;
        return NULL;
    }

    /*Atribui as constantes à data do mundo*/
    newWorld->Nheroes=N_HEROES; 
    newWorld->Nbases=N_BASES;
    newWorld->Nmissions=N_MISSIONS;
    newWorld->Nskills=N_SKILLS;
    newWorld->NVcomposts=N_VComposts;
    newWorld->time=STARTER_TIME;
    newWorld->worldSize.x=WORLD_SIZE;
    newWorld->worldSize.y=WORLD_SIZE;

    /*Cria os vetores de heróis, bases e missões*/
    struct hero **vetHeroes;
    struct base **vetBases;
    struct mission **vetMissions;

    /*Vetores do mundo vazios*/
    newWorld->heroes= NULL;
    newWorld->bases= NULL;
    newWorld->missions= NULL;

    /*Aloca memórias para os vetores*/
    if(!(vetHeroes=malloc(sizeof(struct hero*)*(N_HEROES))))
        return NULL;
    newWorld->heroes= vetHeroes;

    if(!(vetBases=malloc(sizeof(struct base*)*(N_BASES))))
        return NULL;
    newWorld->bases= vetBases;

     if(!(vetMissions=malloc(sizeof(struct mission*)*(N_MISSIONS))))
        return NULL;
    newWorld->missions= vetMissions;

    int i;

    /*Preenche os vetores com os heróis, bases e missões*/
    for(i=0; i<N_HEROES; i++)
        newWorld->heroes[i]= initialize_hero(i);

    for(i=0; i<N_BASES;i++)
        newWorld->bases[i]= initialize_base(i);
    
    for(i=0;i<N_MISSIONS;i++)
        newWorld->missions[i]= initialize_mission(i);

    return newWorld;
}

/*Inicia o herói*/
struct hero *initialize_hero(int id){
    struct hero *newHero;

    if (!(newHero=malloc(sizeof(struct hero)))) //Aloca memória para o herói
        return NULL;

    /*Atribuições da data do herói*/
    newHero->ID= id;
    newHero->xp= 0;
    newHero->pacience= aleat(0,100);
    newHero->speed= aleat(50,5000);
    newHero->skills= cjto_aleat(aleat(1,3),N_SKILLS);
    newHero->base= NULL;
    newHero->alive= true;

    return newHero;
}

/*Inicia a base*/
struct base *initialize_base(int id){
    struct base *newBase;

    if(!(newBase=malloc(sizeof(struct base)))) //Aloca memória para a base
        return NULL;
    
    /*Atribuições da data da base*/
    newBase->location.x= aleat(0, WORLD_SIZE-1);
    newBase->location.y= aleat(0, WORLD_SIZE-1);
    newBase->ID= id;
    newBase->capacity=aleat(3,10);
    newBase->presents=cjto_cria(N_HEROES); 
    if (!newBase->presents){ //Verifica se cjto_cria foi bem sucedido
        free(newBase);
        return NULL;
    }
    newBase->waitLine= fila_cria(); 
    if(!newBase->waitLine){ //Verifica se fila_cria foi bem sucedido
        cjto_destroi(newBase->presents);
        free(newBase);
        return NULL;
    }
    return newBase;
}

/*Inicializa a missão*/
struct mission *initialize_mission(int id){
    struct mission *newMission;

    if(!(newMission=malloc(sizeof(struct mission)))) //Aloca memória para a missão
        return NULL;

    newMission->ID= id;
    newMission->skillsRequired= cjto_aleat(aleat(6, 10), N_SKILLS);
    newMission->location.x= aleat(0, WORLD_SIZE-1);
    newMission->location.y= aleat(0, WORLD_SIZE-1);
    newMission->attempts=0;
    newMission->done= false;
    
    return newMission;
};