
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "core/tela_utils.h"

void tela_pre_draw(ALLEGRO_BITMAP* canvas)
{
	al_set_target_bitmap(canvas);
}

void tela_pos_draw(ALLEGRO_BITMAP* canvas, ALLEGRO_DISPLAY* tela)
{
	al_set_target_backbuffer(tela);
	al_clear_to_color(al_color_name("black")); // Limpa a tela
	al_draw_bitmap(canvas, 0, 0, 0); // Desenha o 'canvas' no monitor e o 'transform' já aplica escala

	al_flip_display();
}
