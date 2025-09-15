#ifndef CONFIG_TELA_H
#define CONFIG_TELA_H

#define CANVAS_W		320		// Largura do canvas(desenho) / tela virtual
#define CANVAS_H		240		// Altura do canvas(desenho) / tela virtual

#define TELA_WINDOW_SCALE_X		3.5		// (Modo Janela) Ajusta a largura do 'canvas' para o monitor
#define TELA_WINDOW_SCALE_Y		3		// (Modo Janela) Ajusta a altura do 'canvas' para o monitor

#define TELA_WINDOW_W	((int)(CANVAS_W * TELA_WINDOW_SCALE_X))		// Largura do monitor do soldado
#define TELA_WINDOW_H	((int)(CANVAS_H * TELA_WINDOW_SCALE_Y))		// Altura do monitor do soldado

#define TELA_FULLSCREEN		1		// Indica se a tela é fullscreen
#define TELA_FULLSCREEN_SCALE_X ((float)al_get_display_width(tela)) / CANVAS_W		// (Tela Cheia) Ajusta a largura do 'canvas' para o monitor
#define TELA_FULLSCREEN_SCALE_Y ((float)al_get_display_height(tela)) / CANVAS_H		// (Tela Cheia) Ajusta a largura do 'canvas' para o monitor

#endif

