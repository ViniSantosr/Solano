#ifndef INIMIGOS_FASE2_H
#define INIMIGOS_FASE2_H

#include <allegro5/allegro5.h>

typedef enum TIPO_INIMIGO
{
	INIMIGO_MENOR = 0,
	INIMIGO_SOLDADO,
	INIMIGO_SNIPER,
	INIMIGO_TIPO_N
} TIPO_INIMIGO;

typedef struct INIMIGO
{
	float x, y, dx, dy;
	TIPO_INIMIGO tipo;
	int tiro_timer;
	int piscar;
	int vida;
	bool ativo; // indica se o inimigo está ativo no jogo
} INIMIGO;

#define INIMIGOS_N 16
INIMIGO inimigos[INIMIGOS_N];

void inimigo_init();
void inimigo_update(float soldado_x, float soldado_y);
void inimigo_draw();

#endif
