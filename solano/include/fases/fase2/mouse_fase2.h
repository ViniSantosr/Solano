#ifndef MOUSE_FASE2_H
#define MOUSE_FASE2_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

extern ALLEGRO_MOUSE_STATE mouse_state;
// extern ALLEGRO_BITMAP* mira;

extern float mira_x;
extern float mira_y;

extern float mira_dx;
extern float mira_dy;

void mouse_init(ALLEGRO_DISPLAY* tela);

void mouse_update(ALLEGRO_EVENT* event);

void mouse_apply(ALLEGRO_DISPLAY* tela);

void mouse_draw();

#endif
