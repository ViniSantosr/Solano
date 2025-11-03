
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
#pragma endregion

#include "fases/fase2/fase2.h" // Header da fase 2

Fase2Context f2_ctx; // Struct que representa o contexto da fase 2

TextosConfigs textos_tela_inicial[3];

// Declaração das funções
void fase2_init(GameContext* ctx);					// Função de inicialização da fase 2

// Telas de informações
static void carregar_tela(GameContext* ctx, TELAS_FASE tela);

// Funções de condições do jogo
bool jogo_em_inicio();			// Enquanto o jogo está nos frames iniciais

void fase2(GameContext* ctx) // Função principal da fase 2
{
	fase2_init(ctx);

	// Variáveis de controle da fase
	f2_ctx.game_over = false;
	f2_ctx.pause = false;
	f2_ctx.concluido = false;
	f2_ctx.exit_tela = false;
	f2_ctx.frames_iniciais = 240; // Número de frames iniciais para mostrar o objetivo da fase
	bool desenhar = false;

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !f2_ctx.exit_tela)  // Lógica do jogo
	{
		al_wait_for_event(ctx->queue, &event);

		mouse_update(&event);
		teclado_update(&event);

		// Update (lógica/ movimentaçao do jogo)
		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			if (!jogo_em_inicio()) // Só vai rodar o jogo depois dos frames iniciais (jogo_em_inicio() = false)
			{
				// Se o jogador perder
				if (soldado.vidas <= 0) {
					f2_ctx.game_over = true;
				}

				// Se o jogador vencer
				if (f2_ctx.score >= 10000) {
					f2_ctx.concluido = true;
				}

				// Se o jogo não estiver em pausa ou acabado			
				if (!f2_ctx.concluido && !f2_ctx.game_over && !f2_ctx.pause) {
					mouse_apply(ctx->tela);
					tiros_update();
					soldado_update();
					hud_update(ctx, &f2_ctx);
					inimigo_update(&f2_ctx);
				}
			}

			if (ctx->timer > 2147483) { // evita overflow do contador
				al_set_timer_count(ctx->timer, 0);
			}

			desenhar = true;
			f2_ctx.frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if (!jogo_em_inicio()) // Só vai rodar o jogo depois dos frames iniciais (jogo_em_inicio() = false)
			{
				if (tecla[ALLEGRO_KEY_SPACE])
				{
					if (f2_ctx.concluido) // A fase foi concluída 
					{
						f2_ctx.exit_tela = true;
						ctx->estado_tela = FASE3;
					}
				}


				if (tecla[ALLEGRO_KEY_ESCAPE])
				{
					if (f2_ctx.pause) // Se o jogo não estiver em pausa
					{
						f2_ctx.pause = false;
					}
					else
					{
						f2_ctx.pause = true; // Coloca o jogo em pausa
					}

					if (f2_ctx.concluido || f2_ctx.game_over)
					{
						f2_ctx.exit_tela = true;
						ctx->estado_tela = TELA_MENU;
					}
				}

				if (tecla[ALLEGRO_KEY_R]) // Reinicia a fase
				{

					if (f2_ctx.pause || f2_ctx.game_over || f2_ctx.concluido)
					{
						f2_ctx.exit_tela = true;
						ctx->estado_tela = FASE2;
					}

				}

				if (tecla[ALLEGRO_KEY_Q])
				{
					if (f2_ctx.pause) // Se o jogo já estiver em pausa
					{
						f2_ctx.exit_tela = true;
						ctx->estado_tela = TELA_MENU;
					}
				}
			}
			break;
		}

		// Draw (desenhar na tela)
		if (desenhar && al_is_event_queue_empty(ctx->queue))

		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_scaled_bitmap(f2_ctx.background,
				0, 0, al_get_bitmap_width(f2_ctx.background), al_get_bitmap_height(f2_ctx.background),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			if (jogo_em_inicio()) // Enquanto o jogo está nos frames iniciais
			{
				tela_inicial(ctx, textos_tela_inicial, 3);
			}
			else
			{
				tiros_draw();
				mouse_draw();
				soldado_draw();
				inimigo_draw(&f2_ctx);
				hud_draw(ctx, &f2_ctx);

				if (f2_ctx.pause) // Se o jogo estiver em pausa
				{
					carregar_tela(ctx, TELA_PAUSE);
				}

				if (f2_ctx.concluido) // Se a fase foi concluída
				{
					carregar_tela(ctx, TELA_CONCLUIDO);
				}

				if (f2_ctx.game_over) // Se o jogador perdeu
				{
					carregar_tela(ctx, TELA_GAME_OVER);
				}
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

	f2_ctx.frames = 0;
	f2_ctx.score = 0;
	f2_ctx.background = al_load_bitmap("assets/images/fase2_background.png");
	must_init(f2_ctx.background, "fase 2 background");

	textos_tela_inicial[0] = (TextosConfigs){ "FASE 2", CANVAS_W / 2, CANVAS_H / 4, ctx->cores.amarelo };
	textos_tela_inicial[1] = (TextosConfigs){ "Cerco de Uruguaiana (1865)", CANVAS_W / 2, CANVAS_H / 2.5, ctx->cores.amarelo };
	textos_tela_inicial[2] = (TextosConfigs){ "META:  10.000 pontos", CANVAS_W / 2, CANVAS_H / 2, ctx->cores.amarelo };
}

static void carregar_tela(GameContext* ctx, TELAS_FASE tela)
{
	switch (tela)
	{	
	case TELA_PAUSE:
		tela_pause(ctx);
		break;
	case TELA_CONCLUIDO:
		tela_concluido(ctx);
		break;
	case TELA_GAME_OVER:
		tela_game_over(ctx);
		break;
	}
}



bool jogo_em_inicio()
{
	return f2_ctx.frames < f2_ctx.frames_iniciais;
}