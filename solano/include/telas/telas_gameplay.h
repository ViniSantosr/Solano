#ifndef TELA_GAMEPLAY_H
#define TELA_GAMEPLAY_H

#include "main.h"

typedef struct {
	const char* texto;
	float x;
	float y;
	ALLEGRO_COLOR cor;
} TextosConfigs;

typedef enum {
	TELA_INICIAL,
	TELA_PAUSE,
	TELA_GAME_OVER,
	TELA_CONCLUIDO
} TELAS_FASE;

void tela_pause(GameContext* ctx);
void tela_tutorial_combate_campo(GameContext* ctx);
void tela_game_over(GameContext* ctx);
void tela_concluido(GameContext* ctx);
void tela_opcoes(GameContext* ctx);

#endif