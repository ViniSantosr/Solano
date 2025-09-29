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

#include "fases/fase2/fase2.h" // Header da fase 2

// Headers que não fazem parte exclusivamente da fase 2
#include "configs/config_tela.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "core/draw_tela.h"
#include "core/inputs/teclado.h"
#include "core/sprites/sprites_soldados.h"

// Headers exclusivamente da fase 2
#include "fases/fase2/mouse_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "fases/fase2/inimigos_fase2.h"
#include "fases/fase2/hud_fase2.h"

Fase2Context f2_ctx; // Struct que representa o contexto da fase 2

// Declaração das funções
void fase2_init(ALLEGRO_DISPLAY* tela);					// Função de inicialização da fase 2
void fase2_gameplay_update(ALLEGRO_DISPLAY* tela);		// Função de atualizar os objetos na tela da fase 2
void fase2_gameplay_draw();								// Função de desenhar os objetos na tela da fase 2

int fase2(GameContext* ctx) // Função principal da fase 2
{
	fase2_init(ctx->tela);

	f2_ctx.soldado = &soldado;
	f2_ctx.sprites = &sprites;
	f2_ctx.tiros = &tiros;

	// Variáveis de controle da fase
	bool exit_tela = false;
	bool desenhar = false;

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)  // Lógica do jogo
	{
		al_wait_for_event(ctx->queue, &event);

		mouse_update(&event);
		teclado_update(&event);

		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:

			// Se o jogador perder
			if (soldado.vidas <= 0) {
				f2_ctx.game_over = true;
			}

			// Se o jogador vencer
			if (f2_ctx.score >= 10000) {
				f2_ctx.concluido = true;
			}

			// Se o jogo não estiver em pausa ou acabado			
			if (!f2_ctx.game_over && !f2_ctx.pause) {
				fase2_gameplay_update(ctx->tela);
			}

			desenhar = true;
			f2_ctx.frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			if (tecla[ALLEGRO_KEY_SPACE])
			{				
				if (f2_ctx.concluido) // Se o jogo acabou 
				{
					// Avança para o próxima fase
				}

				if (f2_ctx.game_over) // Se o jogador perdeu
				{
					// Reinicia a fase
				}

				if (f2_ctx.pause) // Se o jogo estiver em pausa
				{
					f2_ctx.pause = false; // Retoma o jogo
				}
			}


			if (tecla[ALLEGRO_KEY_ESCAPE])
			{				
				if(f2_ctx.pause) // Se o jogo já estiver em pausa
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}
				else // Se o jogo não estiver em pausa
				{
					f2_ctx.pause = true; // Coloca o jogo em pausa
				}

				if (f2_ctx.concluido || f2_ctx.game_over)
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}
			}
			break;
		}


		if (desenhar && al_is_event_queue_empty(ctx->queue))  // Desenhos
		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			fase2_gameplay_draw();

			hud_draw(ctx->font, &f2_ctx);

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

	sprites_deinit();

	return 0;
}

void fase2_init(ALLEGRO_DISPLAY* tela)
{
	sprites_init();
	hud_init();

	tiro_init();
	mouse_init(tela);
	teclado_init();
	soldado_init();
	inimigo_init();

	mira_x = CANVAS_W / 2;
	mira_y = (CANVAS_H / 2) - SOLDADO_H * 2;

	f2_ctx.frames = 0;
	f2_ctx.score = 0;
}

void fase2_gameplay_update(ALLEGRO_DISPLAY* tela)
{
	mouse_apply(tela);
	tiros_update();
	soldado_update();
	hud_update(&f2_ctx);
	inimigo_update(&f2_ctx);
}

void fase2_gameplay_draw()
{
	tiros_draw();
	soldado_draw();
	inimigo_draw(&f2_ctx);
	mouse_draw();
}