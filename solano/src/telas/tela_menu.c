#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


#include "telas/tela_menu.h"
#include "core/draw_tela.h"
#include "core/inputs/teclado.h"
#include "configs/config_tela.h"

int tela_menu(GameContext* ctx)
{

	bool exit_tela = false;
	bool desenhar = false;

	int time = 0;            // contador de tempo (para piscar)
	int selected = 0;    // 0 = New Game, 1 = Options, 2 = Exit

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);

		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			time = al_get_timer_count(ctx->timer);

			if (time > 1000) { // evita overflow do contador
				al_set_timer_count(ctx->timer, 0);
			}

			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:// seta para baixo
					selected++;

					if (selected > 3) selected = 0; // volta para o início
					break;

				case ALLEGRO_KEY_UP: // seta para cima
				case ALLEGRO_KEY_W:
					selected--;
					if (selected < 0) selected = 3; // vai para o final
					break;

				case ALLEGRO_KEY_ENTER: // confirma a seleção
					if (selected == 0) {
						exit_tela = true;
						ctx->estado_tela = FASE2;
						printf("New Game selecionado!\n");
					}
					else if (selected == 1) {
						printf("Options selecionado!\n");
					}
					else if (selected == 2) {
						printf("Exit selecionado!\n");
						ctx->exit_program= true;
					}
					else if (selected == 3) {
						printf("Créditos selecionado!\n");
					}
					break;
			}
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;
		}


		if (desenhar && al_is_event_queue_empty(ctx->queue))
		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_scaled_bitmap(ctx->background_menu,
				0, 0, al_get_bitmap_width(ctx->background_menu), al_get_bitmap_height(ctx->background_menu),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			al_draw_text(
				ctx->font_titulo,
				al_map_rgb(255, 255, 255),
				CANVAS_W / 2, CANVAS_H / 3.1,
				ALLEGRO_ALIGN_CENTER,
				"SOLANO"
			);

			if (selected == 0) {
				if ((time / 25) % 2 == 0) {
					al_draw_text(
						ctx->font,
						al_map_rgb(255, 255, 255),
						CANVAS_W / 3.9, CANVAS_H / 1.9,
						ALLEGRO_ALIGN_CENTER,
						"->Novo Jogo");
				}
			}
			else {
				al_draw_text(
					ctx->font,
					al_map_rgb(255, 255, 255),
					CANVAS_W / 3.5, CANVAS_H / 1.9,
					ALLEGRO_ALIGN_CENTER,
					"Novo Jogo");
			}

			if (selected == 1) {
				if ((time / 25) % 2 == 0) {
					al_draw_text(
						ctx->font,
						al_map_rgb(255, 255, 255),
						CANVAS_W / 4.6, CANVAS_H / 1.72,
						ALLEGRO_ALIGN_CENTER,
						"->Opcoes");
				}
			}
			else {
				al_draw_text(
					ctx->font,
					al_map_rgb(255, 255, 255),
					CANVAS_W / 4.1, CANVAS_H / 1.72,
					ALLEGRO_ALIGN_CENTER,
					"Opcoes");
			}

			if (selected == 2) {
				if ((time / 25) % 2 == 0) {
					al_draw_text(
						ctx->font,
						al_map_rgb_f(255, 255, 255),
						CANVAS_W / 5.2, CANVAS_H / 1.55,
						ALLEGRO_ALIGN_CENTER,
						"->Sair");
				}
			}
			else {
				al_draw_text(
					ctx->font,
					al_map_rgb_f(255, 255, 255),
					CANVAS_W / 4.6, CANVAS_H / 1.55,
					ALLEGRO_ALIGN_CENTER,
					"Sair");
			}

			if (selected == 3) {
				if ((time / 25) % 2 == 0) {
					al_draw_text(
						ctx->font,
						al_map_rgb_f(255, 255, 255),
						CANVAS_W / 1.24, CANVAS_H / 1.15,
						ALLEGRO_ALIGN_CENTER,
						"->Creditos");
				}
			}
			else {
				al_draw_text(
					ctx->font,
					al_map_rgb_f(255, 255, 255),
					CANVAS_W / 1.2, CANVAS_H / 1.15,
					ALLEGRO_ALIGN_CENTER,
					"Creditos");
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

	return 0;
}