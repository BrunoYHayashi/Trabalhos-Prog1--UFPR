#ifndef ENTITIES
#define ENTITIES
#include "fila.h"
#include "fprio.h"
#include "environment.h"
#include "conjunto.h"
#include <stdbool.h>

struct base{
    int ID;
    int capacity;
    struct cjto_t *presents;
    struct fila_t *waitLine;
    struct coordinates location;
};

struct hero {
    int ID;
    struct cjto_t *skills;
    int pacience;
    int speed;
    int xp;
    struct base *base;
    bool alive;
};

struct mission {
    int ID;
    struct cjto_t *skillsRequired;
    struct coordinates location;
    int attempts;
    bool done;
};

struct world{
    int Nheroes;
    struct hero **heroes;

    int Nbases;
    struct base **bases;

    int Nmissions;
    struct mission **missions;

    struct fprio_t *lef;
    int Nskills;
    int NVcomposts;
    struct coordinates worldSize;
    int time;
};

struct world *initialize_world();

struct hero *initialize_hero(int id);

struct base *initialize_base(int id);

struct mission *initialize_mission(int id);

#endif