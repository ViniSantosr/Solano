
#pragma region Biblitotecas Externas
// Bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
// Headers que não fazem parte exclusivamente da fase 2
#include "configs/config_tela.h"
#include "configs/sprites/soldados_dimensions.h"
#include "core/draw_tela.h"
#include "core/teclado.h"
#include "core/sprites/soldados_sprites.h"
#include "telas/telas_gameplay.h"

// Headers exclusivamente da fase 2
#include "fases/fase2/mouse_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "fases/fase2/inimigos_fase2.h"
#include "fases/fase2/hud_fase2.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "fases/fase2/fase2.h"

// Declaração das funções
void fase2_init(GameContext* ctx); // Função de inicialização da fase 2

void fase2(GameContext* ctx)
{
	fase2_init(ctx);	

	long frames = 0;
	long score = 0;

	// Condições da fase
	bool game_over = false;
	bool pause = false;
	bool concluido = false;
	bool exit_tela = false;
	bool desenhar = false;

	ALLEGRO_EVENT event;
	while (!ctx->exit_program && !exit_tela)  // Lógica do jogo
	{
		al_wait_for_event(ctx->queue, &event);
	
		mouse_update(&event);
		teclado_update(&event);

		// Update (lógica/ movimentaçao do jogo)
		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:

			// Se o jogador perder
			if (soldado.vidas <= 0) {
				game_over = true;
			}

			// Se o jogador vencer
			if (score >= 10100) {
				concluido = true;
			}

			// Se o jogo não estiver em pausa ou acabado			
			if (!concluido && !game_over && !pause) {
				al_set_audio_stream_playing(ctx->sons.music, true);
				mouse_apply(ctx->tela);
				tiros_update();
				soldado_update();			
				hud_update(ctx, &frames, &score);
				inimigo_update(&frames, &score);
			}
			else 
			{
				al_set_audio_stream_playing(ctx->sons.music, false);
			}


			desenhar = true;
			frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			if (tecla[ALLEGRO_KEY_SPACE])
			{
				if (concluido) // A fase foi concluída 
				{
					exit_tela = true;
					ctx->estado_tela = FASE3;
				}
			}

			if (tecla[ALLEGRO_KEY_ESCAPE])
			{
				// Se o jogo não estiver em pausa
				if (pause)
				{
					pause = false;
				}
				else
				{					
					pause = true; // Coloca o jogo em pausa
				}

				if (concluido || game_over)
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}
			}

			if (tecla[ALLEGRO_KEY_R]) // Reinicia a fase
			{
				if (pause || game_over || concluido)
				{
					exit_tela = true;
					ctx->estado_tela = FASE2;
				}
			}

			if (tecla[ALLEGRO_KEY_Q])
			{
				if (pause) // Se o jogo já estiver em pausa
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}
			}

			break;
		}

		// Draw (desenhar na tela)
		if (desenhar && al_is_event_queue_empty(ctx->queue))
		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_scaled_bitmap(ctx->background,
				0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
				0, 0, CANVAS_W, CANVAS_H,
				0);


			tiros_draw();			
			soldado_draw();
			inimigo_draw();			
			mouse_draw();
			hud_draw(ctx);

			if (pause) // Se o jogo estiver em pausa
			{			
				tela_pause(ctx);
			}

			if (concluido) // Se a fase foi concluída
			{				
				tela_concluido(ctx);
			}

			if (game_over) // Se o jogador perdeu
			{				
				tela_game_over(ctx);
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

	sprites_soldados_deinit();
}

void fase2_init(GameContext* ctx)
{
	sprites_soldados_init();
	hud_init();

	tiro_init();
	mouse_init(ctx->tela);
	teclado_init();
	soldado_init();
	inimigo_init();

	mira_x = CANVAS_W / 2;
	mira_y = (CANVAS_H / 2) - SOLDADO_H * 2;

	ctx->background = switch_background(ctx, ctx->background, "assets/images/campo_background.png");
	if (!ctx->background) {
		ctx->estado_tela = TELA_MENU;
		return;
	}

	ctx->sons.music = switch_music(ctx, ctx->sons.music, "assets/sounds/fase_battle_trilha.ogg");
	if (!ctx->sons.music) {
		ctx->estado_tela = TELA_MENU;
		return;
	}
}
