
#include "fases/fase1/fase1.h"

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

#include <fases/fase1/fase1.h>
#include "core/draw_tela.h"
#include "configs/config_tela.h"
#include "core/teclado.h"
#include "main.h"
#include "fases/fase1/tiros_fase1.h"
#include "fases/fase1/navio_fase1.h"
#include "fases/fase1/inimigos_fase1.h"
#include "fases/fase1/hud_fase1.h"
#include "fases/fase1/coisas_gerais_fase1.h"
#include "fases/fase2/coisas_gerais_fase2.h"
#include "core/efeitos/efeito_gerais.h"

Fase1Context f1_ctx;
GameContext ctx;

int mainwow()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    tela_init();

    audio_init();

    must_init(al_init_image_addon(), "image");
    iniciar_sprites();

    iniciar_hud();

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(ctx.tela));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    teclado_init();
    fx_init();
    shots_init();
    ship_init();
    aliens_init();

    f1_ctx.frames = 0;
    f1_ctx.score = 0;

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            fx_update();
            shots_update();
  
            ship_update();
            aliens_update();
            atualizar_hud();

            if (tecla[ALLEGRO_KEY_ESCAPE])
                done = true;

            redraw = true;
            f1_ctx.frames++;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        teclado_update(&event);

        if (redraw && al_is_event_queue_empty(queue))
        {
            tela_pre_draw(ctx.canvas);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            
            aliens_draw();
            shots_draw();
            fx_draw();
            ship_draw();

            desenhar_hud();

            tela_pos_draw(ctx.canvas, ctx.tela);
            redraw = false;
        }
    }

    destruir_sprites();
    hud_deinit();
    audio_deinit();
    //tela_destroy();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}