
#pragma region Biblitotecas Externas
#include <stdio.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "core/sprites/soldados_sprites.h"
#include "fases/fase2/soldado_fase2.h"
#include "fases/fase2/fase2.h"
#include "main.h"
#pragma endregion

#include "fases/fase3/hud_fase3.h"

long score_display;

void hud_init3()
{
	score_display = 0;
}

void hud_update3(GameContext* ctx, long* frames, long* score)
{	
	if (*frames % 2)
		return;

	for (long i = 2; i > 0; i--)
	{
		long diff = 1 << i;
		if (score_display <= (*score - diff))
			score_display += diff;
	}

}

void hud_draw3(GameContext* ctx, int seg, int min)
{
	al_draw_textf(ctx->fonts.font_medium, ctx->cores.preto, 1 + 2 / 2, 1 + 2, 0, "%02d:%02d",  seg, min);
	al_draw_textf(ctx->fonts.font_medium, ctx->cores.verde, 1, 1, 0, "%02d:%02d", seg, min);

	int spacing = VIDA_W + 1;
	for (int i = 0; i < soldado.vidas; i++)
	{		
		al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.preto, (1 + (i * spacing)) + 1, 24 + 1, 0);
		al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.branco, 1 + (i * spacing), 24, 0);
	}
}