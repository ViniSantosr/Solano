
#include "fases/fase2/hud_fase2.h"

#include <allegro5/allegro_image.h>
#include "core/must_init.h"

ALLEGRO_FONT* font;
long score_display;

void hud_init()
{
	font = al_create_builtin_font();
	must_init(font, "font");

	score_display = 0;
}

void hud_deinit()
{
	al_destroy_font(font);
}

void hud_update(long frames)
{
	if (frames % 2)
		return;
	/*
		for (long i = 5; i > 0; i--)
		{
			long diff = 1 << i;
			if (score_display <= (score - diff))
				score_display += diff;
		}
	*/
}

void hud_draw()
{
	/*
		al_draw_textf(
			font,
			al_map_rgb_f(1, 1, 1),
			1, 1,
			0,
			"%06ld",
			score_display
		);

		int spacing = LIFE_W + 1;
		for (int i = 0; i < ship.lives; i++)
			al_draw_bitmap(sprites.life, 1 + (i * spacing), 10, 0);

		if (ship.lives < 0)
			al_draw_text(
				font,
				al_map_rgb_f(1, 1, 1),
				CANVAS_W / 2, CANVAS_H / 2,
				ALLEGRO_ALIGN_CENTER,
				"G A M E  O V E R"
		);
	*/
}