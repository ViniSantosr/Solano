#ifndef INIMIGOS_FASE1_H
#define INIMIGOS_FASE1_H

#include <stdbool.h> 

// BUG
#define BUG_START_X 343
#define BUG_START_Y 1
#define BUG_W 31
#define BUG_H 55
#define BUG_FRAMES 8
#define BUG_SPACING 8

// ARROW
#define ARROW_START_X 0
#define ARROW_START_Y 188
#define ARROW_W 31
#define ARROW_H 89
#define ARROW_FRAMES 8
#define ARROW_SPACING 6

// THICC BOI
#define THICC_START_X 2
#define THICC_START_Y 385
#define THICC_W 43
#define THICC_H 129
#define THICC_FRAMES 8
#define THICC_SPACING 10


typedef enum ALIEN_TYPE // enumera os tipos de aliens
{
    ALIEN_TYPE_BUG = 0,
    ALIEN_TYPE_ARROW,
    ALIEN_TYPE_THICCBOI,
    ALIEN_TYPE_N
} ALIEN_TYPE;

typedef struct animar_alien {
    int frame;
    int frame_count;
    int frame_w;
    int frame_h;
    int frame_spacing;
    int start_x;
    int start_y;
    int frame_time;
    int frame_timer;
} animar_alien;

typedef struct ALIEN //elementos do alien
{
    int x, y;
    int movimento;
    ALIEN_TYPE type;//tipo referente ao enum acima
    int shot_timer;
    int blink;//pisca pisca após danos
    int life;
    //double morte;
    int anim_frame;      // frame atual (0..7)
    int anim_timer;      // contador para controlar velocidade
	animar_alien anim;
    bool volta;
    bool used;
} ALIEN;



void alien_anim_init(animar_alien* anim,
    int start_x, int start_y,
    int w, int h,
    int frame_count,
    int frame_spacing);

void alien_anim_update(animar_alien* anim);



void aliens_init();
void navios_update();
void navios_draw();

#define ALIENS_N 18//define a quantidade máxima de aliens na tela
ALIEN aliens[ALIENS_N];

#endif