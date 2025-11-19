#ifndef NAVIO_FASE1_H
#define NAVIO_FASE1_H

#include <stdbool.h>       // Para usar bool se precisar futuramente
//#include "configs/config_tela.h"          // Para BUFFER_W e BUFFER_H
//#include "core/draw_tela.h"
#include "core/tela_utils.h"

#define SHIP_SPEED 3 //define a velocidade da nave baseada nos frames que ela percorerá por segundo
#define SHIP_MAX_X (CANVAS_W - SHIP_W)//define a posição maxima que a nave pode alcançar, definida pela largura menos o tamanho da nave
#define SHIP_MAX_Y (CANVAS_H - SHIP_H)

typedef struct SHIP// define o struct da nave com seus elementos
{
    int x, y;
    int shot_timer;// tempo de delay entre os tiros
    int lives;
    int respawn_timer;
    int invincible_timer;
} SHIP;
SHIP ship;

void ship_init();
void ship_update();
void ship_draw();

#endif