#ifndef NAVIO_FASE1_H
#define NAVIO_FASE1_H

#include <stdbool.h>       // Para usar bool se precisar futuramente
#include "core/tela_utils.h"
#include "core/sprites/navios_sprites.h"

#define SHIP_SPEED 3 //define a velocidade da nave baseada nos frames que ela percorerá por segundo
#define SHIP_MAX_X (CANVAS_W - SHIP_W - 100)//define a posição maxima que a nave pode alcançar, definida pela largura menos o tamanho da nave
#define SHIP_MAX_Y (CANVAS_H - SHIP_H)
#define SHIP_MIN_X ((CANVAS_W - CANVAS_W) + 100)

extern int ship_anim_start_x; // X inicial do primeiro frame do ship no _navios_sheet
extern int ship_anim_start_y; // Y inicial

extern ship_animation ship_anim;

typedef struct SHIP// define o struct da nave com seus elementos
{
    int x, y;
    int dx, dy;
    int shot_timer;// tempo de delay entre os tiros
    int lives;
    int respawn_timer;
    int invincible_timer;
    ALLEGRO_BITMAP* sheet;  // spritesheet do ship

    ship_animation anim;

} SHIP;
SHIP ship;

void ship_init();
void ship_update();
void ship_draw();

#endif