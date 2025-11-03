#ifndef INIMIGOS_FASE2_H
#define INIMIGOS_FASE2_H

#include <allegro5/allegro5.h>
#include "fase2.h"

typedef enum TIPO_INIMIGO
{	
	INIMIGO_SOLDADO,
	SOLANO	
} TIPO_INIMIGO;

typedef struct INIMIGO
{
	float x, y, dx, dy;
	int sprite;
	int tipo;
	int tiro_timer;
	int piscar;
	int vida;
	bool ativo; // indica se o inimigo está ativo no jogo
} INIMIGO;

#define INIMIGOS_N 16
INIMIGO inimigos[INIMIGOS_N];

void inimigo_init();
void inimigo_update(Fase2Context* f2_ctx);
void inimigo_draw(Fase2Context* f2_ctx);

#endif
