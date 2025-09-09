
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "core/tela.h"
#include "configs/config_tela.h"
#include "core/must_init.h"

ALLEGRO_DISPLAY* tela;		// Monitor do soldado
ALLEGRO_BITMAP* canvas;		// Quadro/Bitmap onde o jogo vai ser desenhado
ALLEGRO_TRANSFORM transform;		// Responsável por redimensionar a tela


void tela_init()
{
	if (TELA_FULLSCREEN)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	tela = al_create_display(TELA_WINDOW_W, TELA_WINDOW_H);
	must_init(tela, "tela");

	canvas = al_create_bitmap(CANVAS_W, CANVAS_H);
	must_init(canvas, "bitmap buffer (canvas do jogo)");


	al_identity_transform(&transform);
	al_scale_transform(&transform,
		TELA_FULLSCREEN ? TELA_FULLSCREEN_SCALE_X : TELA_WINDOW_SCALE_X,
		TELA_FULLSCREEN ? TELA_FULLSCREEN_SCALE_Y : TELA_WINDOW_SCALE_Y);
	al_use_transform(&transform);
}

void tela_destroy()
{
	al_destroy_bitmap(canvas);
	al_destroy_display(tela);
}

void tela_pre_draw()
{
	al_set_target_bitmap(canvas);
}

void tela_pos_draw()
{
	al_set_target_backbuffer(tela);
	al_clear_to_color(al_color_name("black")); // Limpa a tela
	al_draw_bitmap(canvas, 0, 0, 0); // Desenha o 'canvas' no monitor e o 'transform' já aplica escala

	al_flip_display();
}
