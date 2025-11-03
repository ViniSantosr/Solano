
#pragma region Biblitotecas Externas


// Bibliotecas do Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#pragma endregion

#pragma region Headers Game

#include "configs/config_tela.h"
#include "fases/fase2/fase2.h" // Header da fase 2

#pragma endregion

#include "telas/telas_gameplay.h"

void tela_inicial(GameContext* ctx, TextosConfigs* textos, int quant)
{

	for (int i = 0; i < quant; i++)
	{
		int sombra_x = textos[i].x + 2;
		int sombra_y = textos[i].y + 1;

		al_draw_text(ctx->fonts.font_fases, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
		al_draw_text(ctx->fonts.font_fases, textos[i].cor, textos[i].x, textos[i].y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
	}
}

void tela_pause(GameContext* ctx)
{
	// Desenha um retângulo preto semi-transparente sobre a tela
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgba(0, 0, 0, 100) // RGBA → A = transparência (0 = invisível, 255 = opaco)
	);

	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 2, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 2, ALLEGRO_ALIGN_CENTER, "Esc -> Retomar");
	al_draw_text(ctx->fonts.font, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "Esc -> Retomar");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 2, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.6 + 2, ALLEGRO_ALIGN_CENTER, "Q -> Tela de Menu");
	al_draw_text(ctx->fonts.font, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.6, ALLEGRO_ALIGN_CENTER, "Q -> Tela de Menu");

}

void tela_game_over(GameContext* ctx)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgba(0, 0, 0, 100) // RGBA → A = transparência (0 = invisível, 255 = opaco)
	);

	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 2, ALLEGRO_ALIGN_CENTER, "VOCÊ FOI ABATIDO!");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "VOCÊ FOI ABATIDO!");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 2, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 2, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
	al_draw_text(ctx->fonts.font, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
}

void tela_concluido(GameContext* ctx)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgba(0, 0, 0, 100) // RGBA → A = transparência (0 = invisível, 255 = opaco)
	);


	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 2, ALLEGRO_ALIGN_CENTER, "BATALHA VENCIDA!!!!");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "BATALHA VENCIDA!!!!");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 2, ALLEGRO_ALIGN_CENTER, "Space -> Próxima Fase");
	al_draw_text(ctx->fonts.font, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "Space -> Próxima Fase");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 2, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.6 + 2, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
	al_draw_text(ctx->fonts.font, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 1.6, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
}