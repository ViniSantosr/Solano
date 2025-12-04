
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "core/sprites/soldados_sprites.h"
#include "core/tela_utils.h"
#pragma endregion

#include "fases/fase2/mouse_fase2.h"

ALLEGRO_MOUSE_STATE mouse_state;
//ALLEGRO_BITMAP* mira;

float mira_x;
float mira_y;

float mira_dx;
float mira_dy;

void mouse_init(ALLEGRO_DISPLAY* tela)
{
	al_grab_mouse(tela);
	al_hide_mouse_cursor(tela);	
}

void mouse_update(ALLEGRO_EVENT* event)
{
	al_get_mouse_state(&mouse_state);

	switch (event->type)
	{
	case ALLEGRO_EVENT_MOUSE_AXES:
		mira_dx += event->mouse.dx;
		mira_dy += event->mouse.dy;		

		break;
	}
}

void mouse_apply(ALLEGRO_DISPLAY* tela) 
{
	// Aplica o delta acumulado à mira
	mira_x += mira_dx * 0.3f; // multiplicador para sensibilidade
	mira_y += mira_dy * 0.3f;

	// Limita a mira ao canvas
	if (mira_x < 0) mira_x = 0;
	if (mira_x > CANVAS_W) mira_x = CANVAS_W;
	if (mira_y < 0) mira_y = 0;
	if (mira_y > CANVAS_H) mira_y = CANVAS_H;

	// Zera os deltas acumulados
	mira_dx = 0;
	mira_dy = 0;

	// Recentraliza o mouse para evitar que saia da tela
	al_set_mouse_xy(tela, CANVAS_W / 2, CANVAS_H / 2);
}

void mouse_draw()
{
	al_draw_bitmap(sprites_soldado.mira, mira_x - (MIRA_W / 2), mira_y - (MIRA_H / 2), 0);
	/*al_draw_line(mira_x - 5, mira_y, mira_x + 5, mira_y, al_map_rgb(255, 0, 0), 2);
	al_draw_line(mira_x, mira_y - 5, mira_x, mira_y + 5, al_map_rgb(255, 0, 0), 2);*/
}

