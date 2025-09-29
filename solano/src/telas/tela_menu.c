#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
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

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);

		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			desenhar = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (tecla[ALLEGRO_KEY_ESCAPE])
			{
				ctx->exit_program = true;
			}

			if (tecla[ALLEGRO_KEY_SPACE])
			{
				exit_tela = true;
				ctx->estado_tela = FASE2;
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

			al_draw_text(
				ctx->font,
				al_map_rgb_f(1, 1, 1),
				CANVAS_W / 2, CANVAS_H / 2.5,
				ALLEGRO_ALIGN_CENTER,
				"TELA DE MENU"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb_f(1, 1, 1),
				CANVAS_W / 2, CANVAS_H / 2,
				ALLEGRO_ALIGN_CENTER,
				"Press Space"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb_f(1, 1, 1),
				CANVAS_W / 2, CANVAS_H / 1.8,
				ALLEGRO_ALIGN_CENTER,
				"Esc -> Sair do jogo"
			);

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

}