
#pragma region Headers Game
#include "core/sprites/soldados_sprites.h"
#include "fases/fase2/soldado_fase2.h"
#include "fases/fase1/navio_fase1.h"
#include "fases/fase2/fase2.h"
#include "main.h"
#pragma endregion

#include "fases/fase2/hud_fase2.h"

long score_display;

void hud_init()
{
	score_display = 0;
}

void hud_update(GameContext* ctx, long* frames, long* score)
{
	if (*frames % 2)
		return;

	for (long i = 5; i > 0; i--)
	{
		long diff = 1 << i;
		if (score_display <= (*score - diff))
			score_display += diff;
	}

}

void hud_draw(GameContext* ctx)
{

	if (ctx->estado_tela == FASE4 || ctx->estado_tela == FASE5)
	{
		int spacing = VIDA_W + 1;
		for (int i = 0; i < soldado.vidas; i++)
		{
			al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.preto, (1 + (i * spacing)) + 1, 10 + 1, 0);
			al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.branco, 1 + (i * spacing), 10, 0);
		}
	}
	else
	{
		al_draw_textf(
			ctx->fonts.font_medium,
			ctx->cores.preto,
			1 + 2, 1 + 2,
			0,
			"%06ld",
			score_display
		);

		al_draw_textf(
			ctx->fonts.font_medium,
			ctx->cores.verde,
			1, 1,
			0,
			"%06ld",
			score_display
		);

		int spacing = VIDA_W + 1;

		if (ctx->estado_tela == FASE1)
		{

			for (int i = 0; i < navio.lives; i++)
			{
				al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.preto, (1 + (i * spacing)) + 1, 24 + 1, 0);
				al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.branco, 1 + (i * spacing), 24, 0);
			}
		}
		else
		{
			for (int i = 0; i < soldado.vidas; i++)
			{
				al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.preto, (1 + (i * spacing)) + 1, 24 + 1, 0);
				al_draw_tinted_bitmap(sprites_soldado.vida, ctx->cores.branco, 1 + (i * spacing), 24, 0);
			}
		}

	}

}