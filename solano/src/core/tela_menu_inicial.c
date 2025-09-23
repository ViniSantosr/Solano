#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "tela_menu_inicial.h"

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int width = 1280, height = 720;

int tela_menu_inicial()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // 60 FPS
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(width, height);
    must_init(disp, "display");

    must_init(al_init_ttf_addon(), "ttf addon");
    ALLEGRO_FONT* font = al_load_ttf_font("assets/fonts/Minecraft.ttf", 30, 0);
    must_init(font, "font");
    ALLEGRO_FONT* font_titulo_menu = al_load_ttf_font("assets/fonts/font_titulo_menu.ttf", 80, 0);
    must_init(font_titulo_menu, "font_titulo");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* background_menu = al_load_bitmap("assets/images/background_menu.bmp");
    must_init(background_menu, "background_menu");

    // registra as fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;

    int time = 0;            // contador de tempo (para piscar)
    int selected = 0;    // 0 = New Game, 1 = Options, 2 = Exit

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            time = al_get_timer_count(timer);

            if (time > 1000) { // evita overflow do contador
                al_set_timer_count(timer, 0);
            }

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_DOWN: // seta para baixo
                selected++;
                if (selected > 3) selected = 0; // volta para o início
                break;

            case ALLEGRO_KEY_UP: // seta para cima
                selected--;
                if (selected < 0) selected = 3; // vai para o final
                break;

            case ALLEGRO_KEY_ENTER: // confirma a seleção
                if (selected == 0) {
                    printf("New Game selecionado!\n");
                }
                else if (selected == 1) {
                    printf("Options selecionado!\n");
                }
                else if (selected == 2) {
                    printf("Exit selecionado!\n");
                    done = true;
                }
                else if (selected == 3) {
                    printf("Créditos selecionado!\n");
                }
                break;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0)); // fundo preto

            int screen_w = al_get_display_width(disp);
            int screen_h = al_get_display_height(disp);

            // desenha o fundo
            al_draw_scaled_bitmap(background_menu,
                0, 0, al_get_bitmap_width(background_menu), al_get_bitmap_height(background_menu),
                0, 0, screen_w, screen_h,
                0);
            al_draw_text(font_titulo_menu, al_map_rgb(255, 255, 255), width / 3.1, height / 3, 0, "SOLANO");

            // desenha cada opção, piscando apenas a selecionada
            if (selected == 0) {
                if ((time / 25) % 2 == 0) { // pisca a cada ~0.25s
                    al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.9, 0, "New Game");
                }
            }
            else {
                al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.9, 0, "New Game");
            }

            if (selected == 1) {
                if ((time / 25) % 2 == 0) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.7, 0, "Options");
                }
            }
            else {
                al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.7, 0, "Options");
            }

            if (selected == 2) {
                if ((time / 25) % 2 == 0) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.55, 0, "Exit");
                }
            }
            else {
                al_draw_text(font, al_map_rgb(255, 255, 255), width / 3.5, height / 1.55, 0, "Exit");
            }

            if (selected == 3) {
                if ((time / 25) % 2 == 0) {
                    al_draw_text(font, al_map_rgb(255, 255, 255), width / 1.2, height / 1.15, 0, "Credits");
                }
            }
            else {
                al_draw_text(font, al_map_rgb(255, 255, 255), width / 1.2, height / 1.15, 0, "Credits");
            }

            al_flip_display();
            redraw = false;
        }
    }

    // libera memória
    al_destroy_bitmap(background_menu);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}