
#pragma region Biblitotecas Externas
#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#pragma endregion

#pragma region Headers Game
#include "configs/config_tela.h"
#include "telas/tela_menu.h"
#include "fases/fase2/fase2.h"
#pragma endregion

#include "main.h"

GameContext ctx;

void inicializar_game();
void finalizar_game();
void tela_init();
void must_init(bool test, const char* description);
ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);

int main()
{
	inicializar_game();

	while (!ctx.exit_program)
	{
		if (ctx.timer > 2147483) { // evita overflow do contador
			al_set_timer_count(ctx.timer, 0);
		}

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

	finalizar_game();

	return 0;
}

void inicializar_game()
{
	setlocale(LC_ALL, "pt_BR.UTF-8");  // Linux
	setlocale(LC_ALL, "Portuguese_Brazil.1252");  // Windows
	
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "teclado");
	must_init(al_install_mouse(), "mouse");
	must_init(al_init_font_addon(), "font addon");
	must_init(al_init_image_addon(), "image addon");
	must_init(al_init_ttf_addon(), "ttf addon");


	ctx.timer = al_create_timer(1.0 / 60.0);
	must_init(ctx.timer, "timer");

	ctx.queue = al_create_event_queue();
	must_init(ctx.queue, "queue");

	tela_init();

	al_set_window_title(ctx.tela, "Solano: A guerra do Paraguai");
	
	ctx.fonts.font = al_load_ttf_font("assets/fonts/upheavtt.ttf", 15, 0);
	must_init(ctx.fonts.font, "font");

	ctx.fonts.font_size2 = al_load_ttf_font("assets/fonts/upheavtt.ttf", 25, 0);
	must_init(ctx.fonts.font, "font_size2");	

	ctx.fonts.font_fases = al_load_ttf_font("assets/fonts/Cinzel-ExtraBold.ttf", 30, 0);
	must_init(ctx.fonts.font, "font_size2");	
	
	ctx.fonts.font_subtitulo = al_load_ttf_font("assets/fonts/Cinzel-ExtraBold.ttf", 30, 0);
	must_init(ctx.fonts.font_subtitulo, "font_subtitulo");

	ctx.fonts.font_titulo = al_load_ttf_font("assets/fonts/CinzelDecorative-Black.ttf", 100, 0);
	must_init(ctx.fonts.font_titulo, "font_titulo");

	ctx.background_menu = al_load_bitmap("assets/images/background_menu.bmp");
	must_init(ctx.background_menu, "background_menu");

	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(ctx.queue, al_get_keyboard_event_source());
	al_register_event_source(ctx.queue, al_get_mouse_event_source());
	al_register_event_source(ctx.queue, al_get_display_event_source(ctx.tela));
	al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));

	al_start_timer(ctx.timer);

	ctx.estado_tela = TELA_MENU;

	ctx.exit_program = false;

	ctx.cores.preto = al_map_rgb(0, 0, 0);
	ctx.cores.branco = al_map_rgb(255, 255, 255);
	ctx.cores.verde = al_map_rgb(100, 200, 80);
	ctx.cores.amarelo = al_map_rgb(255, 200, 50);
	ctx.cores.vermelho = al_map_rgb_f(1, 0.2, 0.2);
}

void finalizar_game()
{
	al_destroy_font(ctx.fonts.font);
	al_destroy_bitmap(ctx.canvas);
	al_destroy_display(ctx.tela);
	al_destroy_timer(ctx.timer);
	al_destroy_event_queue(ctx.queue);
	al_destroy_font(ctx.fonts.font_titulo);
	al_destroy_font(ctx.fonts.font_subtitulo);
	al_destroy_bitmap(ctx.background_menu);
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

void must_init(bool test, const char* description)
{
	if (test) return;

	fprintf(stderr, "Não pode ser inicializado: %s\n", description);
	exit(1);
}

ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
	must_init(sprite, "sprite grab");
	return sprite;
}

