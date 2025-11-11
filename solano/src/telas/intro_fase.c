
#pragma region Biblitotecas Externas
// Bibliotecas do Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#pragma endregion

#pragma region Headers Game
#include "core/tela_utils.h"
#include "core/funcoes_auxiliares.h"
#include "core/teclado.h"
#include "core/sprites/soldados_sprites.h"
#include "telas/telas_gameplay.h"
#pragma endregion

#include "telas/intro_fase.h"

TextosConfigsIntro textos[_FASES_N][3];

void inicializar_intro(GameContext* ctx);

bool has_tutorial;

float pular_x = CANVAS_W - 150;
float pular_y = CANVAS_H - 25;

void intro_fase(GameContext* ctx, int fase_selected)
{
	inicializar_intro(ctx);

	bool has_tutorial = false;

	switch (fase_selected)
	{
	case _FASE1:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/rio_background.png");
		if (!ctx->background) {
			ctx->estado_tela = TELA_MENU;
			return;
		}
		break;

	case _FASE2:
		has_tutorial = true;
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase2_fundo.png");
		if (!ctx->background) {
			ctx->estado_tela = TELA_MENU;
			return;
		}
		break;

	case _FASE3:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase3_fundo.png");
		if (!ctx->background) {
			must_init(ctx->background, "fase3_fundo");
			ctx->estado_tela = TELA_MENU;
			return;
		}
		break;

	case _FASE4:
	case _FASE5:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase2_fundo.png");
		if (!ctx->background) {
			ctx->estado_tela = TELA_MENU;
			return;
		}
		break;
	}

	bool exit_tela = false;
	bool desenhar = false;

	int frames = 0; // contador de tempo (para piscar)
	int texto_inicial = has_tutorial ? 480 : 240;
	int tutorial = has_tutorial ? 240 : 0;

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);
		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			if (frames > texto_inicial)
			{
				ctx->estado_tela = fase_selected;
				exit_tela = true;
			}

			frames++;
			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				ctx->estado_tela = fase_selected;
				exit_tela = true;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				ctx->exit_program = true;
				break;
			}
		}

		if (desenhar && al_is_event_queue_empty(ctx->queue))
		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_scaled_bitmap(ctx->background,
				0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			if (has_tutorial)
			{
				if (frames < tutorial)
				{
					if (fase_selected == _FASE2)
					{
						tela_tutorial_combate_campo(ctx);
					}
				}
				else
				{
					if (frames < texto_inicial)
					{
						for (int fase = 0; fase < _FASES_N; fase++)
						{
							if (fase == fase_selected)
							{
								for (int i = 0; i < 3; i++)
								{
									int sombra_x = textos[fase][i].x + 2;
									int sombra_y = textos[fase][i].y + 1;

									al_draw_text(ctx->fonts.font_big, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, textos[fase][i].texto);
									al_draw_text(ctx->fonts.font_big, textos[fase][i].cor, textos[fase][i].x, textos[fase][i].y, ALLEGRO_ALIGN_CENTER, textos[fase][i].texto);
								}
							}
						}

					}

				}
			}
			else
			{
				if (frames < texto_inicial)
				{
					for (int fase = 0; fase < _FASES_N; fase++)
					{
						if (fase == fase_selected)
						{
							for (int i = 0; i < 3; i++)
							{
								int sombra_x = textos[fase][i].x + 2;
								int sombra_y = textos[fase][i].y + 1;

								al_draw_text(ctx->fonts.font_big, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, textos[fase][i].texto);
								al_draw_text(ctx->fonts.font_big, textos[fase][i].cor, textos[fase][i].x, textos[fase][i].y, ALLEGRO_ALIGN_CENTER, textos[fase][i].texto);
							}
						}
					}

				}
			}



			if ((frames / 25) % 2 == 0)
			{
				al_draw_text(ctx->fonts.font_small, ctx->cores.preto, pular_x + 2, pular_y + 2, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para pular");
				al_draw_text(ctx->fonts.font_small, ctx->cores.verde, pular_x, pular_y, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para pular");
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}
}

void inicializar_intro(GameContext* ctx)
{
	switch_music(ctx, ctx->sons.music, "assets/sounds/intro_fase_trilha.wav");
	

	textos[_FASE2][0] = (TextosConfigsIntro){ "FASE 2", CANVAS_W / 2, CANVAS_H / 4, ctx->cores.amarelo };
	textos[_FASE2][1] = (TextosConfigsIntro){ "Cerco de Uruguaiana (1865)", CANVAS_W / 2, CANVAS_H / 2.5, ctx->cores.amarelo };
	textos[_FASE2][2] = (TextosConfigsIntro){ "META:  10.000 pontos", CANVAS_W / 2, CANVAS_H / 2, ctx->cores.amarelo };

	textos[_FASE3][0] = (TextosConfigsIntro){ "FASE 3", CANVAS_W / 2, CANVAS_H / 4, ctx->cores.amarelo };
	textos[_FASE3][1] = (TextosConfigsIntro){ "Batalha de Tuiuti (1866)", CANVAS_W / 2, CANVAS_H / 2.5, ctx->cores.amarelo };
	textos[_FASE3][2] = (TextosConfigsIntro){ "META:  Sobreviva por 1 minuto", CANVAS_W / 2, CANVAS_H / 2, ctx->cores.amarelo };

	textos[_FASE4][0] = (TextosConfigsIntro){ "FASE 4", CANVAS_W / 2, CANVAS_H / 4, ctx->cores.amarelo };
	textos[_FASE4][1] = (TextosConfigsIntro){ "Tomada de Assunção (1869)", CANVAS_W / 2, CANVAS_H / 2.5, ctx->cores.amarelo };
	textos[_FASE4][2] = (TextosConfigsIntro){ "META:  15.000 pontos", CANVAS_W / 2, CANVAS_H / 2, ctx->cores.amarelo };
}