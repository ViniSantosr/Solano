#ifndef FASE2_H
#define FASE2_H

#include <allegro5/allegro5.h>

#include "main.h"

#include "core/sprites/sprites_soldados.h"
#include "soldado_fase2.h"
#include "tiros_fase2.h"

typedef struct Fase2Context
{
	long frames;
	long score;
	SOLDADO* soldado;
	SPRITES* sprites;
	TIRO* tiros;
	bool game_over;
	bool pause;
	bool concluido;
} Fase2Context;

extern Fase2Context f2_ctx;

int fase2(GameContext* ctx);

#endif
