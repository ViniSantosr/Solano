#pragma region Biblitotecas Externas
//Bibliotecas de C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Bibliotecas do Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#pragma endregion

#pragma region Headers Game
//Headers que não fazem parte exclusivamente da fase 1
#include "core/tela_utils.h"
#include "core/teclado.h"
#include "main.h"
#include "core/efeitos/efeito_gerais.h"
#include "fases/fase2/fase2.h"
#include "telas/telas_gameplay.h"
#include "telas/intro_fase.h"
#include "core/funcoes_auxiliares.h"

//Headers exclusivamente da fase 1
#include "fases/fase1/tiros_fase1.h"
#include "fases/fase1/navio_fase1.h"
#include "fases/fase1/inimigos_fase1.h"
#include "fases/fase1/hud_fase1.h"
#include "fases/fase1/coisas_gerais_fase1.h"
#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase1/fase1.h"
#pragma endregion

//Declaração das funções de Game Context que serão utilizadas na Fase 1
Fase1Context f1_ctx;
//GameContext ctx;

bool fase1_init(GameContext* ctx); // Função de inicialização da fase 2

void fase1(GameContext* ctx)
{
	if (!fase1_init(ctx))
	{
		ctx->estado_tela = TELA_MENU;
		return;
	}

	long frames = 0;
	long score = 0;

	// Condições da fase
	bool game_over = false;
	bool pause = false;
	bool tutorial = false;
	bool concluido = false;
	bool exit_tela = false;
	bool desenhar = false;


	ALLEGRO_EVENT event;
	while (!ctx->exit_program && !exit_tela)  // Lógica do jogo
	{
		al_wait_for_event(ctx->queue, &event);

		//mouse_update(&event);
		teclado_update(&event);

		// Update (lógica/ movimentaçao do jogo)
		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:

			// Se o jogador perder
			if (ship.lives <= 0) {
				game_over = true;
			}

			// Se o jogador vencer
			if (score >= 25500) {
				concluido = true;
			}

			// Se o jogo não estiver em pausa ou acabado			
			if (!concluido && !game_over && !pause) {
				//mouse_apply(ctx->tela);
				shots_update();
			    navios_update(ctx, &frames, &score);
				//hud_update(ctx, &frames, &score);  
				atualizar_hud();
				
				ship_update();

				//inimigo_update(ctx, &frames, &score);
				fx_update();
			}

			desenhar = true;
			frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			if (ctx->options) // Teclas para o tela de opções.
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_M:
					ctx->play_music = ctx->play_music ? false : true;
					al_set_audio_stream_playing(ctx->sons.music, ctx->play_music);
					break;

				case ALLEGRO_KEY_ESCAPE:
					ctx->options = false;
					pause = true;
					break;

				case ALLEGRO_KEY_DOWN:
					al_play_sample_instance(ctx->sons.click);
					if (ctx->sons.volume_general > 0.01)
					{
						ctx->sons.volume_general -= 0.01f;
						al_set_mixer_gain(ctx->sons.mixer, ctx->sons.volume_general);
					}
					break;

				case ALLEGRO_KEY_UP:
					al_play_sample_instance(ctx->sons.click);
					if (ctx->sons.volume_general < 0.99)
					{
						ctx->sons.volume_general += 0.01f;
						al_set_mixer_gain(ctx->sons.mixer, ctx->sons.volume_general);
					}
					break;
				}
			}
			else if (tutorial)
			{
				if (tecla[ALLEGRO_KEY_ESCAPE])
				{
					tutorial = false;
					pause = true;
				}
			}
			else if (pause)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					if (!ctx->options)
					{
						pause = false;
					}
					break;

				case ALLEGRO_KEY_Q:
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
					break;

				case ALLEGRO_KEY_E:
					ctx->options = true;
					break;

				case ALLEGRO_KEY_T:
					tutorial = true;
					break;
				}
			}
			else
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					pause = true;
					break;
				}
			}

			if (concluido || game_over)
			{
				if (tecla[ALLEGRO_KEY_ESCAPE])
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}

			}

			if (concluido) // A fase foi concluída 
			{
				if (tecla[ALLEGRO_KEY_SPACE])
				{
					ctx->proxima_fase++;
					ctx->cena_atual++;
					ctx->estado_tela = CUTSCENE;
					exit_tela = true;
				}
			}


			if (pause || game_over || concluido)
			{
				if (tecla[ALLEGRO_KEY_R])
				{
					exit_tela = true;
					ctx->estado_tela = FASE1;
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

			if (concluido) // Se a fase foi concluída
			{
				tela_concluido(ctx);
			}
			else
			{
				shots_draw();
				ship_draw();
				navios_draw();
				fx_draw(&frames);
				//mouse_draw();
			}

			desenhar_hud(ctx);//desenhar_hud(ctx);

			if (pause) // Se o jogo estiver em pausa
			{
				tela_pause(ctx);
			}

			if (game_over) // Se o jogador perdeu
			{
				tela_game_over(ctx);
			}

			if (ctx->options)
			{
				tela_opcoes(ctx);
			}

			if (tutorial)
			{
				tela_tutorial_combate_campo(ctx);
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}


	sprites_navios_deinit();
}

bool fase1_init(GameContext* ctx)
{
	
	//iniciar_hud();
	sprites_navios_init();
	//iniciar_sprites();
	shots_init();
	//mouse_init(ctx->tela);
	teclado_init();
	ship_init();
	aliens_init();
	fx_init();

	//mira_x = CANVAS_W / 2;
	//mira_y = (CANVAS_H / 2) - SOLDADOS_H * 2;

	ctx->background = switch_background(ctx, ctx->background, "assets/images/fase1_fundo.png");
	if (!ctx->background)
		return false;


	ctx->sons.music = switch_music(ctx, ctx->sons.music, "assets/sounds/fase_battle_trilha.ogg");

	return true;
}


