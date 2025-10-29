#ifndef FASE1_H
#define FASE1_H

#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "core/sprites/navios_sprites.h"
#include "core/sprites/sprites_fase2.h"
#include "fases/fase1/navio_fase1.h"
#include "tiros_fase1.h"
#include "main.h"
#pragma endregion

typedef struct Fase1Context
{
	long frames;
	long score;
	bool game_over;
	bool pause;
	bool concluido;
	bool exit_tela;
	int frames_iniciais;
	ALLEGRO_BITMAP* background;
} Fase1Context;

extern Fase1Context f1_ctx;

#endif // !FASE1_H

