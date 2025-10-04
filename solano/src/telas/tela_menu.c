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

	al_init_font_addon();
	must_init(al_init_ttf_addon(), "ttf addon");
	ALLEGRO_FONT* font_minecraft = al_load_ttf_font("assets/fonts/Minecraft.ttf", 30, 0);
	must_init(font_minecraft,"font_minecraft");

	ALLEGRO_FONT* font_menu = al_load_ttf_font("assets/fonts/font_titulo_menu.ttf", 80, 0);
	must_init(font_menu, "font_menu");

	must_init(al_init_image_addon(), "image addon");
	ALLEGRO_BITMAP* background_menu = al_load_bitmap("assets/images/background_menu.bmp");
	must_init(background_menu, "background_menu");


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

			al_draw_scaled_bitmap(background_menu,
				0, 0, al_get_bitmap_width(background_menu), al_get_bitmap_height(background_menu),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			al_draw_text(
				ctx->font,
				al_map_rgb_f(255, 255, 255),
				CANVAS_W / 2, CANVAS_H / 3.1,
				ALLEGRO_ALIGN_CENTER,
				"SOLANO"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb(255, 255, 255),
				CANVAS_W / 3.5, CANVAS_H / 1.9,
				ALLEGRO_ALIGN_CENTER,
				"Novo Jogo"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb(255, 255, 255),
				CANVAS_W / 4.1, CANVAS_H / 1.72,
				ALLEGRO_ALIGN_CENTER,
				"Opcoes"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb_f(255, 255, 255),
				CANVAS_W / 4.6, CANVAS_H / 1.55,
				ALLEGRO_ALIGN_CENTER,
				"Sair"
			);

			al_draw_text(
				ctx->font,
				al_map_rgb_f(255, 255, 255),
				CANVAS_W / 1.2, CANVAS_H / 1.15,
				ALLEGRO_ALIGN_CENTER,
				"Creditos"
			);

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}


	al_destroy_font(font_minecraft);
	al_destroy_font(font_menu);

	return 0;
}