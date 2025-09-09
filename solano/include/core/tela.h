#ifndef TELA_H
#define TELA_H

#include <allegro5/allegro.h>

extern ALLEGRO_DISPLAY* tela;
extern ALLEGRO_BITMAP* canvas;

void tela_init();

void tela_destroy();

void tela_pre_draw();

void tela_pos_draw();

#endif
