#ifndef TELA_UTILS_H
#define TELA_UTILS_H

#include "main.h"

#pragma region Dimensions

#define CANVAS_W		800		// Largura do canvas(desenho) / tela virtual
#define CANVAS_H		450		// Altura do canvas(desenho) / tela virtual

#define TELA_WINDOW_SCALE_X		1.5		// (Modo Janela) Ajusta a largura do 'canvas' para o monitor
#define TELA_WINDOW_SCALE_Y		1		// (Modo Janela) Ajusta a altura do 'canvas' para o monitor

#define TELA_WINDOW_W	((int)(CANVAS_W * TELA_WINDOW_SCALE_X))		// Largura do monitor do soldado
#define TELA_WINDOW_H	((int)(CANVAS_H * TELA_WINDOW_SCALE_Y))		// Altura do monitor do soldado

#define TELA_FULLSCREEN		0		// Indica se a tela é fullscreen
#define TELA_FULLSCREEN_SCALE_X ((float)al_get_display_width(ctx.tela)) / CANVAS_W		// (Tela Cheia) Ajusta a largura do 'canvas' para o monitor
#define TELA_FULLSCREEN_SCALE_Y ((float)al_get_display_height(ctx.tela)) / CANVAS_H		// (Tela Cheia) Ajusta a largura do 'canvas' para o monitor

#pragma endregion

void tela_pre_draw(ALLEGRO_BITMAP* canvas);

void tela_pos_draw(ALLEGRO_BITMAP* canvas, ALLEGRO_DISPLAY* tela);

#endif
