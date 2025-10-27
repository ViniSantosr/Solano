
#include "fases/fase2/hud_fase2.h"

#include <allegro5/allegro_image.h>

#include "configs/config_tela.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "core/sprites/sprites_fase2.h"
#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "core/must_init.h"
#include <core/sprites/sprites_soldados.h>

//SPRITES sprites;

long score_display;

void hud_init()
{
	score_display = 0;
}

void hud_update()
{
	if (frames % 2)
		return;

	for (long i = 5; i > 0; i--)
	{
		long diff = 1 << i;
		if (score_display <= (score - diff))
			score_display += diff;
	}

}

void hud_draw(ALLEGRO_FONT* font)
{

	al_draw_textf(
		font,
		al_map_rgb_f(1, 1, 1),
		1, 1,
		0,
		"%06ld",
		score_display
	);

	int spacing = VIDA_W + 1;
	for (int i = 0; i < soldado.vidas; i++)
		al_draw_bitmap(sprites.vida, 1 + (i * spacing), 10, 0);

	if (soldado.vidas <= 0)
	{
		al_draw_text(
			font,
			al_map_rgb_f(1, 0.2, 0.2),
			CANVAS_W / 2, CANVAS_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"G A M E  O V E R"
		);
	}


	if (score >= 10000)
		al_draw_text(
			font,
			al_map_rgb_f(0.5, 1, 0.5),
			CANVAS_W / 2, CANVAS_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"FASE 1 CONCLUIDA!!!!"
		);

	if (frames <= 120)
		al_draw_text(
			font,
			al_map_rgb_f(0, 0, 1),
			CANVAS_W / 2, CANVAS_H / 2.5,
			ALLEGRO_ALIGN_CENTER,
			"META: 10.000 pontos"
		);

}