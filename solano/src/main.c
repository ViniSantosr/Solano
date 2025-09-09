#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "core/tela.h"
#include "fases/fase2/fase2.h"
#include "core/must_init.h"

int main()
{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "teclado");
	must_init(al_install_mouse(), "mouse");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	tela_init();
	
	must_init(al_init_image_addon(), "image");
	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(tela));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	fase2(tela, queue, timer);

	return 0;
}