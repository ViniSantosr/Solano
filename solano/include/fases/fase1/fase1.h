#ifndef FASE1_H
#define FASE1_H

#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#pragma endregion

//extern long frames;

typedef struct
{
	long frames;
	long score;
	bool game_over;
	bool pause;
	bool concluido;
	bool exit_tela;
	int frames_iniciais;	
} Fase1Context;

extern Fase1Context f1_ctx;

void fase1(GameContext* ctx);

#endif // !FASE1_H

