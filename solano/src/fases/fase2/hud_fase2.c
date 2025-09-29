
#include "fases/fase2/hud_fase2.h"

#include <allegro5/allegro_image.h>

#include "configs/config_tela.h"
#include "configs/sprites/config_sprites_soldados.h"

long score_display;

void hud_init()
{
	score_display = 0;
}

void hud_update(Fase2Context* f2_ctx)
{
	if (f2_ctx->frames % 2)
		return;

	for (long i = 5; i > 0; i--)
	{
		long diff = 1 << i;
		if (score_display <= (f2_ctx->score - diff))
			score_display += diff;
	}

}

void hud_draw(ALLEGRO_FONT* font, Fase2Context* f2_ctx)
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
	for (int i = 0; i < f2_ctx->soldado->vidas; i++)
		al_draw_bitmap(f2_ctx->sprites->vida, 1 + (i * spacing), 10, 0);

	// Tela de Game Over
	if (f2_ctx->game_over)
	{
		al_draw_text(
			font,
			al_map_rgb_f(1, 0.2, 0.2),
			CANVAS_W / 2, CANVAS_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"G A M E  O V E R"
		);
	}

	// Tela de Fase Concluida
	if (f2_ctx->concluido)
	{
		al_draw_text(
			font,
			al_map_rgb_f(0, 1, 0),
			CANVAS_W / 2, CANVAS_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"FASE 1 CONCLUIDA!!!!"
		);
	}

	// Tela de Pause
	if (f2_ctx->pause)
	{

		

		al_draw_text(
			font,
			al_map_rgb_f(0, 0, 1),
			CANVAS_W / 2, CANVAS_H / 3,
			ALLEGRO_ALIGN_CENTER,
			"JOGO PAUSADO"
		);

		al_draw_text(
			font,
			al_map_rgb_f(0, 0, 1),
			CANVAS_W / 2, CANVAS_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"Space -> Retomar"
		);

		al_draw_text(
			font,
			al_map_rgb_f(0, 0, 1),
			CANVAS_W / 2, CANVAS_H / 1.8,
			ALLEGRO_ALIGN_CENTER,
			"Esc -> Volta a tela de menu"
		);
	}

	// Objetivo da fase
	if (f2_ctx->frames <= 120)
	{
		al_draw_text(
			font,
			al_map_rgb_f(0, 0, 1),
			CANVAS_W / 2, CANVAS_H / 2.5,
			ALLEGRO_ALIGN_CENTER,
			"META: 10.000 pontos"
		);
	}
}