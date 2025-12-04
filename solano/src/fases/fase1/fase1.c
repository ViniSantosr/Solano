
#pragma region Biblitotecas Externas

//Bibliotecas do Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#pragma endregion

#pragma region Headers Game
//Headers que não fazem parte exclusivamente da fase 1
#include "core/tela_utils.h"
#include "core/teclado.h"
#include "main.h"
#include "telas/telas_gameplay.h"
#include "core/funcoes_auxiliares.h"

//Headers exclusivamente da fase 1
#include "fases/fase1/tiros_fase1.h"
#include "fases/fase1/navio_fase1.h"
#include "fases/fase1/inimigos_fase1.h"
#include "fases/fase2/hud_fase2.h"
#pragma endregion


#include "fases/fase1/fase1.h"

Fase1Context f1_ctx;

bool fase1_init(GameContext* ctx);

void fase1(GameContext* ctx)
{
	if (!fase1_init(ctx))
	{
		ctx->estado_tela = TELA_MENU;
		return;
	}

	long frames = 0;
	long score = 0;

	f1_ctx.frames = 0;
	f1_ctx.score = 0;


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
	
		teclado_update(&event);

		// Update (lógica/ movimentaçao do jogo)
		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:

			// Se o jogador perder
			if (navio.lives <= 0) {
				game_over = true;
			}

			// Se o jogador vencer
			if (f1_ctx.score >= 2500) {
				concluido = true;
			}

			// Se o jogo não estiver em pausa ou acabado			
			if (!concluido && !game_over && !pause) {				
				shots_update();			
				hud_update(ctx, &f1_ctx.frames, &f1_ctx.score);
				navio_update();
				inimigos_update(ctx, &f1_ctx, &frames, &score);
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

			if (pause || game_over || concluido)
			{
				if (tecla[ALLEGRO_KEY_R])
				{
					exit_tela = true;
					ctx->estado_tela = FASE1;
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
				navio_draw();
				inimigos_draw();							
			}

			hud_draw(ctx);

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
				tela_tutorial_combate_navio(ctx);
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}
}

bool fase1_init(GameContext* ctx)
{	
	hud_init();
	shots_init();
	teclado_init();
	navio_init();
	inimigos_init();

	ctx->background = switch_background(ctx, ctx->background, "assets/images/fase1_fundo.png");
	if (!ctx->background)
		return false;


	ctx->sons.music = switch_music(ctx, ctx->sons.music, "assets/sounds/fase_battle_trilha.ogg");

	return true;
}