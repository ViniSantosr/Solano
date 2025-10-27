#ifndef INIMIGOS_FASE1_H
#define INIMIGOS_FASE1_H

#include <stdbool.h> 


typedef enum ALIEN_TYPE // enumera os tipos de aliens
{
    ALIEN_TYPE_BUG = 0,
    ALIEN_TYPE_ARROW,
    ALIEN_TYPE_THICCBOI,
    ALIEN_TYPE_N
} ALIEN_TYPE;

typedef struct ALIEN //elementos do alien
{
    int x, y;
    int movimento;
    ALIEN_TYPE type;//tipo referente ao enum acima
    int shot_timer;
    int blink;//pisca pisca após danos
    int life;
    //int movimento;
    bool volta;
    bool used;
} ALIEN;

void aliens_init();
void aliens_update();
void aliens_draw();

#define ALIENS_N 16//define a quantidade máxima de aliens na tela
ALIEN aliens[ALIENS_N];

#endif