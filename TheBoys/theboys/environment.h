#ifndef ENVIRONMENT
#define ENVIRONMENT

/*Define constantes do mundo de acordo com tpf_enunciado*/
#define STARTER_TIME 0
#define ENDING_TIME 525600
#define WORLD_SIZE 20000
#define N_SKILLS 10

/*Constantes relacionadas ao número de coisas*/
#define N_HEROES (N_SKILLS*5)
#define N_BASES (N_HEROES/5)
#define N_MISSIONS (ENDING_TIME/100)
#define N_VComposts (N_SKILLS*3)

/*Estrutura de coordenadas*/
struct coordinates{
    int x;
    int y;
};

#endif