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
void fase2_gameplay_draw(GameContext* ctx);				// Função de desenhar os objetos na tela da fase 2

// Telas de informações
void tela_inicial(ALLEGRO_FONT* font);
void tela_pause(ALLEGRO_FONT* font);
void tela_game_over(ALLEGRO_FONT* font);
void tela_concluido(ALLEGRO_FONT* font);

// Funções de condições do jogo
bool jogo_em_inicio();			// Enquanto o jogo está nos frames iniciais

int fase2(GameContext* ctx) // Função principal da fase 2
{
	fase2_init(ctx->tela);

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
					fase2_gameplay_update(ctx->tela);
				}
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
					if (f2_ctx.pause) // Se o jogo já estiver em pausa
					{
						f2_ctx.exit_tela = true;
						ctx->estado_tela = TELA_MENU;
					}
					else // Se o jogo não estiver em pausa
					{
						f2_ctx.pause = true; // Coloca o jogo em pausa
					}

					if (f2_ctx.concluido || f2_ctx.game_over)
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

			if (jogo_em_inicio()) // Enquanto o jogo está nos frames iniciais
			{
				tela_inicial(ctx->font);
			}
			else
			{
				fase2_gameplay_draw(ctx);

				if (f2_ctx.pause) // Se o jogo estiver em pausa
				{
					tela_pause(ctx->font);
				}

				if (f2_ctx.concluido) // Se a fase foi concluída
				{
					tela_concluido(ctx->font);
				}

				if (f2_ctx.game_over) // Se o jogador perdeu
				{
					tela_game_over(ctx->font);
				}				
			}

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

void fase2_gameplay_draw(GameContext* ctx)
{
	tiros_draw();
	soldado_draw();
	inimigo_draw(&f2_ctx);
	mouse_draw();
	hud_draw(ctx->font, &f2_ctx);
}

void tela_inicial(ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgb(0, 0, 0)
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 0, 1),
		CANVAS_W / 2, CANVAS_H / 3.5,
		ALLEGRO_ALIGN_CENTER,
		"Fase 2: Cerco de Uruguaiana (1865)"
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 0, 1),
		CANVAS_W / 2, CANVAS_H / 2,
		ALLEGRO_ALIGN_CENTER,
		"META: 10.000 pontos"
	);
}

void tela_pause(ALLEGRO_FONT* font)
{
	// Desenha um retângulo preto semi-transparente sobre a tela
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgba(0, 0, 0, 150) // RGBA → A = transparência (0 = invisível, 255 = opaco)
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 0, 1),
		CANVAS_W / 2, CANVAS_H / 3,
		ALLEGRO_ALIGN_CENTER,
		"JOGO PAUSADO"
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 0, 1),
		CANVAS_W / 2, CANVAS_H / 2,
		ALLEGRO_ALIGN_CENTER,
		"Space -> Retomar"
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 0, 1),
		CANVAS_W / 2, CANVAS_H / 1.8,
		ALLEGRO_ALIGN_CENTER,
		"Esc -> Volta a tela de menu"
	);
}

void tela_game_over(ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgb(0, 0, 0)
	);

	al_draw_text(
		font,
		al_map_rgb_f(1, 0.2, 0.2),
		CANVAS_W / 2, CANVAS_H / 3,
		ALLEGRO_ALIGN_CENTER,
		"G A M E  O V E R"
	);

	al_draw_text(
		font,
		al_map_rgb_f(1, 0.2, 0.2),
		CANVAS_W / 2, CANVAS_H / 2,
		ALLEGRO_ALIGN_CENTER,
		"Space -> Reiniciar"
	);

	al_draw_text(
		font,
		al_map_rgb_f(1, 0.2, 0.2),
		CANVAS_W / 2, CANVAS_H / 1.8,
		ALLEGRO_ALIGN_CENTER,
		"Esc -> Volta a tela de menu"
	);
}

void tela_concluido(ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(
		0, 0, CANVAS_W, CANVAS_H,
		al_map_rgb(0, 0, 0)
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 1, 0),
		CANVAS_W / 2, CANVAS_H / 3,
		ALLEGRO_ALIGN_CENTER,
		"FASE 2 CONCLUIDA!!!!"
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 1, 0),
		CANVAS_W / 2, CANVAS_H / 2,
		ALLEGRO_ALIGN_CENTER,
		"Space -> Ir para a fase 3"
	);

	al_draw_text(
		font,
		al_map_rgb_f(0, 1, 0),
		CANVAS_W / 2, CANVAS_H / 1.8,
		ALLEGRO_ALIGN_CENTER,
		"Esc -> Volta a tela de menu"
	);
}

bool jogo_em_inicio()
{
	return f2_ctx.frames < f2_ctx.frames_iniciais;
}