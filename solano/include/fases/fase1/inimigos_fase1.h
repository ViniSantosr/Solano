#ifndef INIMIGOS_FASE1_H
#define INIMIGOS_FASE1_H

#include <stdbool.h> 
#include "fases/fase1/fase1.h"

// BARCO
#define BARCO_START_X 345
#define BARCO_START_Y 59
#define BARCO_W 31
#define BARCO_H 56
#define BARCO_FRAME_COUNT 4
#define BARCO_SPACING 8

// NAVIO INIMIGO
#define NAVIO_START_X 0
#define NAVIO_START_Y 278
#define NAVIO_W 36
#define NAVIO_H 90
#define NAVIO_FRAME_COUNT 4
#define NAVIO_SPACING 0


typedef enum TIPO_INIMIGO // enumera os tipos de aliens
{
    BARCO_INIMIGO = 0,
    NAVIO_INIMIGO,
    INIMIGOS_TIPO_N
} TIPO_INIMIGO;

typedef struct animar_inimigos {
    int frame;
    int frame_count;
    int frame_w;
    int frame_h;
    int frame_spacing;
    int start_x;
    int start_y;
    int frame_time;
    int frame_timer;
} animar_inimigos;

typedef struct INIMIGO //elementos do alien
{
    int x, y;
    int movimento;
    TIPO_INIMIGO tipo;//tipo referente ao enum acima
    int shot_timer;
    int blink;//pisca pisca após danos
    int life;
    //double morte;
    int anim_frame;      // frame atual (0..7)
    int anim_timer;      // contador para controlar velocidade
	animar_inimigos anim;
    bool volta;
    bool used;
} INIMIGO;



void inimigos_anim_init(animar_inimigos* anim,
    int start_x, int start_y,
    int w, int h,
    int frame_count,
    int frame_spacing);

void inimigos_anim_update(animar_inimigos* anim);



void inimigos_init();
void inimigos_update(GameContext* ctx, Fase1Context* f1_ctx, long* frames, long* score);
void inimigos_draw();

#define INIMIGOS_N 18//define a quantidade máxima de inimigos na tela
extern INIMIGO inimigos[INIMIGOS_N];

#endif