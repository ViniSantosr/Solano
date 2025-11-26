
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
#include "telas/tela_menu.h"
#include "telas/cutscenes.h"
#include "fases/fase1/fase1.h"
#include "fases/fase2/fase2.h"
#include "fases/fase3/fase3.h"
#include "fases/fase4/fase4.h"
#include "fases/fase5/fase5.h"
#include "telas/intro_fase.h"
#include "core/funcoes_auxiliares.h"
#include "core/sprites/sprites_util.h"
#include "core/tela_utils.h"
#include "core/sprites/soldados_sprites.h"
#pragma endregion

#include "main.h"

GameContext ctx;

void inicializar_game();
void finalizar_game();
void tela_init();



int main()
{
	inicializar_game();

	while (!ctx.exit_program)
	{
		switch (ctx.estado_tela)
		{
		case TELA_MENU:
			ctx.background = switch_background(&ctx, ctx.background, "assets/images/background_menu.bmp");
			tela_menu(&ctx);
			break;
		case CUTSCENE:
			
			cutscene(&ctx, ctx.cena_atual);
			break;
		case INTRO_FASE:
			intro_fase(&ctx, ctx.proxima_fase);
			break;
		case FASE1:
			fase1(&ctx);
			//ctx.proxima_fase++;	
			//ctx.cena_atual++;
			//ctx.estado_tela = CUTSCENE;

			break;
		case FASE2:
			//fase2(&ctx);
			break;
		case FASE3:
			//fase3(&ctx);
			break;
		case FASE4:
			//fase4(&ctx);
			break;
		case FASE5:
			//fase5(&ctx);
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
	must_init(al_install_audio(), "audio");
	must_init(al_init_acodec_addon(), "audio codecs");
	must_init(al_reserve_samples(16), "reserve samples");


	ctx.timer = al_create_timer(1.0 / 60.0);
	must_init(ctx.timer, "timer");

	ctx.queue = al_create_event_queue();
	must_init(ctx.queue, "queue");

	tela_init();

	al_set_window_title(ctx.tela, "Solano: A guerra do Paraguai");	
	
	ctx.fonts.font_small = al_load_ttf_font("assets/fonts/upheavtt.ttf", 15, 0);
	must_init(ctx.fonts.font_small, "font");

	ctx.fonts.font_medium = al_load_ttf_font("assets/fonts/upheavtt.ttf", 25, 0);
	must_init(ctx.fonts.font_medium, "font_size2");

	ctx.fonts.font_big = al_load_ttf_font("assets/fonts/Cinzel-ExtraBold.ttf", 30, 0);
	must_init(ctx.fonts.font_big, "font_size2");
	
	ctx.fonts.font_subtitulo = al_load_ttf_font("assets/fonts/Cinzel-ExtraBold.ttf", 30, 0);
	must_init(ctx.fonts.font_subtitulo, "font_subtitulo");

	ctx.fonts.font_titulo = al_load_ttf_font("assets/fonts/CinzelDecorative-Black.ttf", 100, 0);
	must_init(ctx.fonts.font_titulo, "font_titulo");

	ctx.background = al_load_bitmap("assets/images/background_menu.bmp");
	must_init(ctx.background, "background_menu");

	ctx.sons.volume_general = 1.0f;
	ctx.sons.volume_music = 0.7f;
	ctx.sons.volume_effects = 0.7f;

	ctx.sons.mixer = al_get_default_mixer();
	must_init(ctx.sons.mixer, "mixer");
	al_set_mixer_gain(ctx.sons.mixer, ctx.sons.volume_general); // tente 0.7 ou até 0.5
	al_set_mixer_quality(ctx.sons.mixer, ALLEGRO_MIXER_QUALITY_LINEAR);

	ctx.play_music = true;

	ctx.sons.music = al_load_audio_stream("assets/sounds/menu_trilha.ogg", 4, 2048);	
	must_init(ctx.sons.music, "music");

	ctx.sons.gun_shot = al_load_sample("assets/sounds/gun_shot.mp3");
	must_init(ctx.sons.gun_shot, "gun_shot");

	// Voice
	ALLEGRO_SAMPLE* sample = al_load_sample("assets/sounds/voice.wav");
	must_init(sample, "voice.wav");

	ctx.sons.voice = al_create_sample_instance(sample);
	must_init(ctx.sons.voice, "voice");

	al_attach_sample_instance_to_mixer(ctx.sons.voice, ctx.sons.mixer);
	al_set_sample_instance_gain(ctx.sons.voice, 0.1);     // volume
	al_set_sample_instance_speed(ctx.sons.voice, 1.0);    // pitch
	al_set_sample_instance_pan(ctx.sons.voice, 0.0);      // centro
	al_set_sample_instance_playmode(ctx.sons.voice, ALLEGRO_PLAYMODE_ONCE);

	// Text
	sample = al_load_sample("assets/sounds/text_bip.wav");
	must_init(sample, "text_bip.wav");

	ctx.sons.text_bip = al_create_sample_instance(sample);
	must_init(ctx.sons.text_bip, "text_bip");

	al_attach_sample_instance_to_mixer(ctx.sons.text_bip, ctx.sons.mixer);
	al_set_sample_instance_gain(ctx.sons.text_bip, 0.1);     // volume
	al_set_sample_instance_speed(ctx.sons.text_bip, 0.7);    // pitch
	al_set_sample_instance_pan(ctx.sons.text_bip, 0.0);      // centro
	al_set_sample_instance_playmode(ctx.sons.text_bip, ALLEGRO_PLAYMODE_ONCE);

	// Typing
	sample = al_load_sample("assets/sounds/typing.flac");
	must_init(sample, "typing.flac");

	ctx.sons.typing = al_create_sample_instance(sample);
	must_init(ctx.sons.typing, "typing");

	al_attach_sample_instance_to_mixer(ctx.sons.typing, ctx.sons.mixer);
	al_set_sample_instance_gain(ctx.sons.typing, 1.0);     // volume
	al_set_sample_instance_speed(ctx.sons.typing, 1.0);    // pitch
	al_set_sample_instance_pan(ctx.sons.typing, 0.0);      // centro
	al_set_sample_instance_playmode(ctx.sons.typing, ALLEGRO_PLAYMODE_ONCE);

	// Click
	sample = al_load_sample("assets/sounds/click.wav");
	must_init(sample, "click.wav");

	ctx.sons.click = al_create_sample_instance(sample);
	must_init(ctx.sons.click, "click");

	al_attach_sample_instance_to_mixer(ctx.sons.click, ctx.sons.mixer);
	al_set_sample_instance_gain(ctx.sons.click, 0.5);     // volume
	al_set_sample_instance_speed(ctx.sons.click, 1.0);    // pitch
	al_set_sample_instance_pan(ctx.sons.click, 0.0);      // centro
	al_set_sample_instance_playmode(ctx.sons.click, ALLEGRO_PLAYMODE_ONCE);


	must_init(al_init_primitives_addon(), "primitives");

	sprites_soldados_init();
	sprites_util_init();

	al_register_event_source(ctx.queue, al_get_keyboard_event_source());
	al_register_event_source(ctx.queue, al_get_mouse_event_source());
	al_register_event_source(ctx.queue, al_get_display_event_source(ctx.tela));
	al_register_event_source(ctx.queue, al_get_timer_event_source(ctx.timer));

	al_start_timer(ctx.timer);

	ctx.estado_tela = TELA_MENU;

	ctx.exit_program = false;
	
	ctx.pause = false;
	ctx.options = false;

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	ctx.cores.preto = al_map_rgb(0, 0, 0);
	ctx.cores.cinza_opaco = al_map_rgba(0, 0, 0, 90);
	ctx.cores.cinza_medium = al_map_rgb(120, 120, 120);
	ctx.cores.branco = al_map_rgb(255, 255, 255);
	ctx.cores.verde = al_map_rgb(100, 200, 80);
	ctx.cores.verde_opaco = al_map_rgba_f(0.39, 0.78, 0.31, 0.5);
	ctx.cores.amarelo = al_map_rgb(255, 200, 50);
	ctx.cores.vermelho = al_map_rgb_f(1, 0.2, 0.2);
	ctx.cores.azul = al_map_rgb(0, 0, 255);
	ctx.cores.azul_claro = al_map_rgb(80, 80, 255);
	ctx.cores.azul_escuro = al_map_rgb(20, 20, 160);
}

void finalizar_game()
{
	al_destroy_font(ctx.fonts.font_small);
	al_destroy_font(ctx.fonts.font_medium);
	al_destroy_font(ctx.fonts.font_big);
	al_destroy_font(ctx.fonts.font_titulo);
	al_destroy_font(ctx.fonts.font_subtitulo);
	al_destroy_bitmap(ctx.canvas);
	al_destroy_display(ctx.tela);
	al_destroy_timer(ctx.timer);
	al_destroy_event_queue(ctx.queue);	
	al_destroy_bitmap(ctx.background);
	al_destroy_sample(ctx.sons.gun_shot);
	al_destroy_sample_instance(ctx.sons.voice);
	al_destroy_sample_instance(ctx.sons.text_bip);
	al_destroy_sample_instance(ctx.sons.typing);
	al_destroy_sample_instance(ctx.sons.click);
	al_destroy_audio_stream(ctx.sons.music);
	al_uninstall_audio();
	sprites_util_deinit();
	sprites_soldados_deinit();
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



