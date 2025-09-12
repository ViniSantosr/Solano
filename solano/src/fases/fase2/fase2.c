
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



int fase2(ALLEGRO_DISPLAY* tela, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer)
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

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	while (!done)
	{
		al_wait_for_event(queue, &event);

		mouse_update(&event);
		teclado_update(&event);

		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			// Updates
			mouse_apply(tela);
			tiros_update();
			soldado_update();
			hud_update(frames);
			inimigo_update(CANVAS_W / 2, CANVAS_H / 2);

			if (tecla[ALLEGRO_KEY_ESCAPE])
				done = true;

			redraw = true;
			frames++;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (redraw && al_is_event_queue_empty(queue))
		{
			tela_pre_draw();
			al_clear_to_color(al_map_rgb(0, 0, 0));

			tiros_draw();
			soldado_draw();
			inimigo_draw();
			mouse_draw();
			hud_draw();

			tela_pos_draw();
			redraw = false;
		}
	}

	sprites_deinit();
	hud_deinit();
	tela_destroy();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}