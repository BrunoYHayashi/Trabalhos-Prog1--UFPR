#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "entities.h"
#include "environment.h"

struct world *initialize_world(){
    struct world *newWorld;

    if(!(newWorld=malloc(sizeof(struct world))))
        return NULL;

    newWorld->Nheroes=N_HEROES;
    newWorld->Nbases=N_BASES;
    newWorld->Nmissions=N_MISSIONS;
    newWorld->Nskills=N_SKILLS;
    newWorld->NVcomposts=N_VComposts;
    newWorld->time=STARTER_TIME;

    struct hero **vetHeroes;
    struct base **vetBases;
    struct mission **vetMissions;

    newWorld->heroes= NULL;
    newWorld->bases= NULL;
    newWorld->missions= NULL;

    if(!(vetHeroes=malloc(sizeof(struct hero*)*(N_HEROES))))
        return NULL;
    newWorld->heroes= vetHeroes;

    if(!(vetBases=malloc(sizeof(struct base*)*(N_BASES))))
        return NULL;
    newWorld->bases= vetBases;

     if(!(vetMissions=malloc(sizeof(struct mission*)*(N_MISSIONS))))
        return NULL;
    newWorld->missions= vetMissions;


    
}

struct hero *initialize_hero(int id);

struct base *initialize_base(int id);

struct mission *initialize_mission(int id);