#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "configs/globals.h"
#include "core/tela.h"
#include "core/tela_menu.h"
#include "fases/fase2/fase2.h"
#include "core/must_init.h"

GameContext ctx;

void inicializar_game();

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
				fase1(&ctx);*/
			break;
		case FASE2:
			fase2(tela, &ctx);
			break;
		}
	}

	al_destroy_font(ctx.font);
	tela_destroy();
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

	al_set_window_title(tela, "Solano: A guerrra do Paraguai");

	must_init(al_init_image_addon(), "image");
	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(ctx.queue, al_get_keyboard_event_source());
	al_register_event_source(ctx.queue, al_get_mouse_event_source());
	al_register_event_source(ctx.queue, al_get_display_event_source(tela));
	al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));

	al_start_timer(ctx.timer);

	ctx.estado_tela = TELA_MENU;

	ctx.exit_program = false;
}
