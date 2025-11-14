#ifndef ENVIRONMENT
#define ENVIRONMENT

#define STARTER_TIME 0
#define ENDING_TIME 525600
#define WORLD_SIZE 20000
#define N_SKILLS 10

#define N_HEROES (N_SKILLS*5)
#define N_BASES (N_HEROES/5)
#define N_MISSIONS (ENDING_TIME/100)
#define N_VComposts (N_SKILLS*3)

struct coordinates{
    int x;
    int y;
};

#endif