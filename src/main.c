#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "main.h"
#include "configs/config_tela.h"
#include "telas/tela_menu.h"
#include "fases/fase2/fase2.h"
#include "core/must_init.h"

GameContext ctx;

void inicializar_game();
void tela_init();

int main()
{
	inicializar_game();

	while (!ctx.exit_program)
	{
		switch (ctx.estado_tela)
		{
		case TELA_MENU:
			tela_menu(&ctx);
			break;
		/*case FASE1:
			fase1(&ctx);
			break;*/
		case FASE2:
			fase2(&ctx);
			break;
		}
	}

	al_destroy_font(ctx.font);
	al_destroy_bitmap(ctx.canvas);
	al_destroy_display(ctx.tela);
	al_destroy_timer(ctx.timer);
	al_destroy_event_queue(ctx.queue);

	return 0;
}

void inicializar_game()

{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "teclado");
	must_init(al_install_mouse(), "mouse");

	ctx.timer = al_create_timer(1.0 / 60.0);
	must_init(ctx.timer, "timer");

	ctx.queue = al_create_event_queue();
	must_init(ctx.queue, "queue");

	ctx.font = al_create_builtin_font();
	must_init(ctx.font, "font");

	tela_init();

	al_set_window_title(ctx.tela, "Solano: A guerra do Paraguai");

	must_init(al_init_image_addon(), "image");
	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(ctx.queue, al_get_keyboard_event_source());
	al_register_event_source(ctx.queue, al_get_mouse_event_source());
	al_register_event_source(ctx.queue, al_get_display_event_source(ctx.tela));
	al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));

	al_start_timer(ctx.timer);

	ctx.estado_tela = TELA_MENU;

	ctx.exit_program = false;
}

void tela_init()
{
	if (TELA_FULLSCREEN)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	ctx.tela = al_create_display(TELA_WINDOW_W, TELA_WINDOW_H);
	must_init(ctx.tela, "tela");

	ctx.canvas = al_create_bitmap(CANVAS_W, CANVAS_H);
	must_init(ctx.canvas, "bitmap buffer (canvas do jogo)");


	al_identity_transform(&ctx.transform);
	al_scale_transform(&ctx.transform,
		TELA_FULLSCREEN ? TELA_FULLSCREEN_SCALE_X : TELA_WINDOW_SCALE_X,
		TELA_FULLSCREEN ? TELA_FULLSCREEN_SCALE_Y : TELA_WINDOW_SCALE_Y);
	al_use_transform(&ctx.transform);
}

