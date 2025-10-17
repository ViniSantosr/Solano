#ifndef FASE2_H
#define FASE2_H

#pragma region Biblitotecas Externas
	#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
	#include "core/sprites/soldados_sprites.h"
	#include "soldado_fase2.h"
	#include "tiros_fase2.h"
	#include "main.h"
#pragma endregion

typedef struct {
	const char* texto;
	float x;
	float y;
	ALLEGRO_COLOR cor;
} TextosConfigs;


typedef struct Fase2Context
{
	long frames;
	int frames_iniciais;

	long score;

	// Condições da fase
	bool game_over;
	bool pause;
	bool concluido;
	bool exit_tela;	

	ALLEGRO_BITMAP* background;
} Fase2Context;

extern Fase2Context f2_ctx;

void fase2(GameContext* ctx);

#endif
