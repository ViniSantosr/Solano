
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
	for (int i = 0; i < soldado.vidas; i++)
		al_draw_bitmap(sprites.vida, 1 + (i * spacing), 10, 0);	
}