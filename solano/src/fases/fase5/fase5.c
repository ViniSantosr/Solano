
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
#include "core/tela_utils.h"
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
#include "main.h"
#include "fases/fase5/solano.h"
#pragma endregion

#include "fases/fase5/fase5.h"

// Declaração das funções
bool fase5_init(GameContext* ctx); // Função de inicialização da fase 2

void fase5(GameContext* ctx)
{
	if (!fase5_init(ctx))
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

			// Se o jogo não estiver em pausa ou acabado			
			if (!concluido && !game_over && !pause) {
				mouse_apply(ctx->tela);
				tiros_update();
				soldado_update();
				solano_update(&concluido);
				inimigo_update(ctx, &frames, &score);
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
					exit_tela = true;
					ctx->proxima_fase++;
					ctx->cena_atual++;
					ctx->estado_tela = CUTSCENE;
				}
			}


			if (pause || game_over || concluido)
			{
				if (tecla[ALLEGRO_KEY_R])
				{
					exit_tela = true;
					ctx->estado_tela = FASE4;
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
				tiros_draw();
				soldado_draw();
				inimigo_draw();
				solano_draw(ctx);
				mouse_draw();
			}

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

			hud_draw(ctx);

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}
}

bool fase5_init(GameContext* ctx)
{
	tiro_init();
	mouse_init(ctx->tela);
	teclado_init();
	soldado_init();
	solano_init();
	inimigo_init();

	mira_x = CANVAS_W / 2;
	mira_y = (CANVAS_H / 2) - SOLDADOS_H * 2;

	ctx->background = switch_background(ctx, ctx->background, "assets/images/fase5_fundo.png");
	if (!ctx->background)
		return false;


	ctx->sons.music = switch_music(ctx, ctx->sons.music, "assets/sounds/fase_battle_trilha.ogg");

	return true;
}
