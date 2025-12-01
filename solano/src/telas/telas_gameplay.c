
#pragma region Biblitotecas Externas
// Bibliotecas do Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#pragma endregion

#pragma region Headers
#include "fases/fase2/fase2.h" // Header da fase 2
#include "core/funcoes_auxiliares.h"
#include "core/tela_utils.h"
#include "core/sprites/sprites_util.h"
#include "core/sprites/soldados_sprites.h"
#include "core/sprites/navios_sprites.h"
#pragma endregion

#include "telas/telas_gameplay.h"

float tela_opcoes_x = CANVAS_W - (CANVAS_W * 0.8);
float tela_opcoes_y = CANVAS_H - (CANVAS_H * 0.8);

float tela_opcoes_w = CANVAS_W - (CANVAS_W * 0.2);
float tela_opcoes_h = CANVAS_H - (CANVAS_H * 0.2);

void tela_inicial(GameContext* ctx, TextosConfigs* textos, int quant)
{
	for (int i = 0; i < quant; i++)
	{
		int sombra_x = textos[i].x + 2;
		int sombra_y = textos[i].y + 1;

		al_draw_text(ctx->fonts.font_big, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
		al_draw_text(ctx->fonts.font_big, textos[i].cor, textos[i].x, textos[i].y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
	}
}

void tela_pause(GameContext* ctx)
{
	// Desenha um retângulo preto semi-transparente sobre a tela
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		ctx->cores.cinza_opaco
	);

	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 1.5, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "JOGO PAUSADO");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "Esc -> Retomar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "Esc -> Retomar");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 1.5, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.65 + 1.5, ALLEGRO_ALIGN_CENTER, "E -> Opções");
	al_draw_text(ctx->fonts.font_small, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.65, ALLEGRO_ALIGN_CENTER, "E -> Opções");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.52 + 1.5, ALLEGRO_ALIGN_CENTER, "T -> Tutorial");
	al_draw_text(ctx->fonts.font_small, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.52, ALLEGRO_ALIGN_CENTER, "T -> Tutorial");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.4 + 1.5, ALLEGRO_ALIGN_CENTER, "Q -> Tela de Menu");
	al_draw_text(ctx->fonts.font_small, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 1.4, ALLEGRO_ALIGN_CENTER, "Q -> Tela de Menu");

}

void tela_game_over(GameContext* ctx)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		ctx->cores.cinza_opaco
	);

	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 1.5, ALLEGRO_ALIGN_CENTER, "VOCÊ FOI ABATIDO!");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "VOCÊ FOI ABATIDO!");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 1.5, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
	al_draw_text(ctx->fonts.font_small, ctx->cores.vermelho,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
}

void tela_concluido(GameContext* ctx)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		ctx->cores.cinza_opaco
	);


	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 3 + 1.5, ALLEGRO_ALIGN_CENTER, "BATALHA VENCIDA!!!!");
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 3, ALLEGRO_ALIGN_CENTER, "BATALHA VENCIDA!!!!");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "Space -> Avançar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "Space -> Avançar");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.8 + 1.5, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 1.8, ALLEGRO_ALIGN_CENTER, "R -> Reiniciar");

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 1.6 + 1.5, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 1.6, ALLEGRO_ALIGN_CENTER, "Esc -> Tela de Menu");
}

void tela_opcoes(GameContext* ctx)
{		
	al_draw_scaled_bitmap(ctx->background,
		0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
		0, 0, CANVAS_W, CANVAS_H,
		0);

	al_draw_filled_rectangle(tela_opcoes_x, tela_opcoes_y, tela_opcoes_w, tela_opcoes_h, ctx->cores.cinza_opaco);

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.375) + 2, (tela_opcoes_y + 1.5) + 1.5, ALLEGRO_ALIGN_CENTER, "OPÇÕES");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.verde,
		 tela_opcoes_x + (tela_opcoes_w * 0.375), tela_opcoes_y + 1.5, ALLEGRO_ALIGN_CENTER, "OPÇÕES");


	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.05) + 2, (tela_opcoes_y + (tela_opcoes_h * 0.15)) + 1.5, ALLEGRO_ALIGN_CENTER, "Som:");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.05), tela_opcoes_y + (tela_opcoes_h * 0.15), ALLEGRO_ALIGN_CENTER, "Som:");

	load_mute_bitmap(ctx, tela_opcoes_x + (tela_opcoes_w * 0.1) - MUTE_W, tela_opcoes_y + (tela_opcoes_h * 0.2));

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.24) + 2, tela_opcoes_y + (tela_opcoes_h * 0.21) + 1.5, ALLEGRO_ALIGN_CENTER, "m -> mute/desmute");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.24), tela_opcoes_y + (tela_opcoes_h * 0.21), ALLEGRO_ALIGN_CENTER, "m -> mute/desmute");


	al_draw_textf(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.1) + 2, tela_opcoes_y + (tela_opcoes_h * 0.3) + 1.5, ALLEGRO_ALIGN_CENTER, "Volume: %.0f", ctx->sons.volume_general * 100);
	al_draw_textf(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.1), tela_opcoes_y + (tela_opcoes_h * 0.3), ALLEGRO_ALIGN_CENTER, "Volume: %.0f", ctx->sons.volume_general * 100);

	al_draw_textf(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.25) + 2, tela_opcoes_y + (tela_opcoes_h * 0.36) + 1.5, ALLEGRO_ALIGN_CENTER, "Aumentar -> seta para cima", ctx->sons.volume_general * 100);
	al_draw_textf(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.25), tela_opcoes_y + (tela_opcoes_h * 0.36), ALLEGRO_ALIGN_CENTER, "Aumentar -> seta para cima", ctx->sons.volume_general * 100);

	al_draw_textf(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.255) + 2, tela_opcoes_y + (tela_opcoes_h * 0.4) + 1.5, ALLEGRO_ALIGN_CENTER, "diminuir -> seta para baixo", ctx->sons.volume_general * 100);
	al_draw_textf(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.255), tela_opcoes_y + (tela_opcoes_h * 0.4), ALLEGRO_ALIGN_CENTER, "diminuir -> seta para baixo", ctx->sons.volume_general * 100);

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto,
		tela_opcoes_x + (tela_opcoes_w * 0.1) + 2, (tela_opcoes_h - 20) + 1.5, ALLEGRO_ALIGN_CENTER, "Esc -> Voltar");
	al_draw_text(ctx->fonts.font_small, ctx->cores.verde,
		tela_opcoes_x + (tela_opcoes_w * 0.1), tela_opcoes_h - 20, ALLEGRO_ALIGN_CENTER, "Esc -> Voltar");
}

void tela_tutorial_combate_campo(GameContext* ctx)
{

	al_draw_scaled_bitmap(ctx->background,
		0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
		0, 0, CANVAS_W, CANVAS_H,
		0);

	al_draw_text(ctx->fonts.font_big, ctx->cores.preto, (CANVAS_W / 2) + 2, (CANVAS_H / 6) + 1.5, ALLEGRO_ALIGN_CENTER, "Mecânica: Combate no campo");
	al_draw_text(ctx->fonts.font_big, ctx->cores.amarelo, CANVAS_W / 2, CANVAS_H / 6, ALLEGRO_ALIGN_CENTER, "Mecânica: Combate no campo");


	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2) + 2, (CANVAS_H / 3.5) + 1.5, ALLEGRO_ALIGN_CENTER, "Movimentação:");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2, CANVAS_H / 3.5, ALLEGRO_ALIGN_CENTER, "Movimentação:");


	al_draw_bitmap(sprites_soldado.soldado[BAIXO][0], (CANVAS_W / 2) - (SOLDADOS_W / 2), (CANVAS_H / 2) - (SOLDADOS_H / 2), 0);

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, CANVAS_W / 2, (CANVAS_H / 2 - 50) + 1.5, ALLEGRO_ALIGN_CENTER, "W");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2, CANVAS_H / 2 - 50, ALLEGRO_ALIGN_CENTER, "W");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2 - 40) + 2, CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "A");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2 - 40, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "A");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, CANVAS_W / 2, (CANVAS_H / 2 + 30) + 1.5, ALLEGRO_ALIGN_CENTER, "S");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2, (CANVAS_H / 2 + 30), ALLEGRO_ALIGN_CENTER, "S");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2 + 40), CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "D");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, (CANVAS_W / 2 + 40), CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "D");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, CANVAS_W / 2, CANVAS_H / 1.5 + 1.5, ALLEGRO_ALIGN_CENTER, "mira: mover com o mouse");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2, CANVAS_H / 1.5, ALLEGRO_ALIGN_CENTER, "mira: mover com o mouse");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, CANVAS_W / 2, CANVAS_H / 1.39  + 1.5, ALLEGRO_ALIGN_CENTER, "atirar: Botão direito do mouse");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.amarelo, CANVAS_W / 2, CANVAS_H / 1.39, ALLEGRO_ALIGN_CENTER, "atirar: Botão direito do mouse");
}

void tela_tutorial_combate_navio(GameContext* ctx)
{

	al_draw_scaled_bitmap(ctx->background,
		0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
		0, 0, CANVAS_W, CANVAS_H,
		0);

	al_draw_text(ctx->fonts.font_big, ctx->cores.preto, (CANVAS_W / 2) + 2, (CANVAS_H / 6) + 1.5, ALLEGRO_ALIGN_CENTER, "Mecânica: Combate no navio");
	al_draw_text(ctx->fonts.font_big, ctx->cores.azul_escuro, CANVAS_W / 2, CANVAS_H / 6, ALLEGRO_ALIGN_CENTER, "Mecânica: Combate no navio");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2) + 2, (CANVAS_H / 3.5) + 1.5, ALLEGRO_ALIGN_CENTER, "Movimentação:");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.azul_escuro, CANVAS_W / 2, CANVAS_H / 3.5, ALLEGRO_ALIGN_CENTER, "Movimentação:");

	al_draw_bitmap(sprites_navios.navio, (CANVAS_W / 2) - (NAVIOS_INIMIGO_W[1] / 2), (CANVAS_H / 2) - (NAVIOS_INIMIGO_H[1] / 2), 0);
	
	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2 - 40) + 2, CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "<-");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.azul_escuro, CANVAS_W / 2 - 40, CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "<-");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, (CANVAS_W / 2 + 40), CANVAS_H / 2 + 1.5, ALLEGRO_ALIGN_CENTER, "->");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.azul_escuro, (CANVAS_W / 2 + 40), CANVAS_H / 2, ALLEGRO_ALIGN_CENTER, "->");

	al_draw_text(ctx->fonts.font_medium, ctx->cores.preto, CANVAS_W / 2, CANVAS_H / 1.39  + 1.5, ALLEGRO_ALIGN_CENTER, "atirar: TECLA X");
	al_draw_text(ctx->fonts.font_medium, ctx->cores.azul_escuro, CANVAS_W / 2, CANVAS_H / 1.39, ALLEGRO_ALIGN_CENTER, "atirar: TECLA X");
}