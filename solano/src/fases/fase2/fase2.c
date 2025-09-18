
#include "fases/fase2/fase2.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

#include "core/tela.h"
#include "configs/config_tela.h"
#include "core/inputs/teclado.h"
#include "fases/fase2/mouse_fase2.h"
#include "core/sprites/sprites_soldados.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "fases/fase2/tiros_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "fases/fase2/inimigos_fase2.h"
#include "fases/fase2/hud_fase2.h"
#include "fases/fase2/coisas_gerais_fase2.h"
#include "core/must_init.h"


void fase2_init(ALLEGRO_DISPLAY* tela);
void fase2_gameplay_update(ALLEGRO_DISPLAY* tela);
void fase2_gameplay_draw();

int fase2(ALLEGRO_DISPLAY* tela, GameContext* ctx)
{
	fase2_init(tela);

	bool exit_tela = false;
	bool desenhar = true;
	bool game_over = false;
	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);

		mouse_update(&event);
		teclado_update(&event);

		// Update (lógica/ movimentaçao do jogo)
		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			// Updates
			if (score >= 10000 || soldado.vidas <= 0) {
				game_over = true;
			}

			if (!game_over) {
				fase2_gameplay_update(tela);
			}
			
			desenhar = true;
			frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if (game_over)
			{
				if (tecla[ALLEGRO_KEY_ENTER])
				{
					exit_tela = true;
					ctx->estado_tela = TELA_MENU;
				}
			}

			if (tecla[ALLEGRO_KEY_ESCAPE])
			{
				ctx->exit_program = true;
			}
			break;
		}

		// Draw (desenhar na tela)
		if (desenhar && al_is_event_queue_empty(ctx->queue))
		{
			tela_pre_draw();
			al_clear_to_color(al_map_rgb(0, 0, 0));

			fase2_gameplay_draw();

			hud_draw(ctx->font);

			tela_pos_draw();
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

	frames = 0;
	score = 0;
}

void fase2_gameplay_update(ALLEGRO_DISPLAY* tela)
{
	mouse_apply(tela);
	tiros_update();
	soldado_update();
	hud_update();
	inimigo_update();
}

void fase2_gameplay_draw()
{
	tiros_draw();
	soldado_draw();
	inimigo_draw();
	mouse_draw();
}