
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#pragma endregion

#pragma region Headers Game
#include "core/tela_utils.h"
#include "core/teclado.h"
#include "core/funcoes_auxiliares.h"
#include "telas/telas_gameplay.h"
#include "main.h"
#pragma endregion

#include "telas/tela_menu.h"

MenuContext menu_ctx;

BotoesConfig botoes_configs[BOTOES_N] = // Array que armazena todos os botões e as suas específicações
{
	{ "->Novo Jogo",  CANVAS_W / 3.375, CANVAS_H / 1.9 },
	{ "->Continuar",  CANVAS_W / 3.375, CANVAS_H / 1.745 },
	{ "->Opções",     CANVAS_W / 3.55, CANVAS_H / 1.62 },
	{ "->Créditos",   CANVAS_W / 3.4, CANVAS_H / 1.5 },
	{ "->Sair",       CANVAS_W / 3.7, CANVAS_H / 1.35 }
};

void inicializar_menu(GameContext* ctx);
void desenhar_botoes(GameContext* ctx, BotoesConfig botao, bool selecionado, int frames, ALLEGRO_COLOR cor);
void botoes(GameContext* ctx, int selected, int frames, bool continuar_enable);
void titulo(GameContext* ctx);

void tela_menu(GameContext* ctx)
{
	inicializar_menu(ctx);

	bool exit_tela = false;
	bool desenhar = false;
	bool continuar_enable = false;
	bool opcoes_enable = false;

	long frames = 0;
	int selected = 0;    // 0 = New Game, 1 = Options, 2 = Exit

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);
		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			if (ctx->proxima_fase != 0)
			{
				continuar_enable = true;
			}			

			frames++;
			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			if (ctx->options) // Teclas na tela de opções
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_M:
					al_play_sample_instance(ctx->sons.click);
					ctx->play_music = ctx->play_music ? false : true;
					al_set_audio_stream_playing(ctx->sons.music, ctx->play_music);
					break;

				case ALLEGRO_KEY_ESCAPE:
					ctx->options = false;
					break;

				case ALLEGRO_KEY_DOWN:	
					al_play_sample_instance(ctx->sons.click);
					if (ctx->sons.volume_general > 0.01)
					{
						ctx->sons.volume_general -= 0.01f;
						al_set_mixer_gain(ctx->sons.mixer, ctx->sons.volume_general);
					}
					break;

				case ALLEGRO_KEY_UP:	
					al_play_sample_instance(ctx->sons.click);
					if (ctx->sons.volume_general < 0.99)
					{
						ctx->sons.volume_general += 0.01f;
						al_set_mixer_gain(ctx->sons.mixer, ctx->sons.volume_general);
					}
					break;
				}					
			}
			else
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:// seta para baixo
					al_play_sample_instance(ctx->sons.click);
					selected++;
					if (selected >= BOTOES_N) selected = 0; // volta para o início
					break;

				case ALLEGRO_KEY_UP: // seta para cima
				case ALLEGRO_KEY_W:
					al_play_sample_instance(ctx->sons.click);
					if (selected == 0) // Deixa parado no 'Novo Jogo'
						break;

					selected--;
					break;

				case ALLEGRO_KEY_ENTER: // confirma a seleção											

					switch (selected)
					{
					case NOVO_JOGO:
						ctx->proxima_fase = 5;
						ctx->cena_atual = 2;
						ctx->estado_tela = CUTSCENE;
						exit_tela = true;
						break;
					case CONTINUAR:
						if (continuar_enable)
						{
							ctx->proxima_fase = ctx->proxima_fase;
							ctx->cena_atual = ctx->cena_atual;
							ctx->estado_tela = CUTSCENE;
							exit_tela = true;
						}
						break;
					case OPCOES:
						ctx->options = true;
						break;
					case SAIR:
						ctx->exit_program = true;
						break;
					}

					break;
				}
			}

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx->exit_program = true;
			break;
		}

		if (desenhar && al_is_event_queue_empty(ctx->queue))
		{
			tela_pre_draw(ctx->canvas);
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_scaled_bitmap(ctx->background,
				0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			if (!ctx->options)
			{
				titulo(ctx); // Função que desenhar os titulos
				botoes(ctx, selected, frames, continuar_enable); // Função que desenha os botões
			}
			else
			{
				tela_opcoes(ctx);
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}
}

void inicializar_menu(GameContext* ctx)
{
	menu_ctx.titulo = "SOLANO";
	menu_ctx.subtitulo = "A Guerra do Paraguai";

	ctx->sons.music = switch_music(ctx, ctx->sons.music, "assets/sounds/menu_trilha.ogg");
	/*ctx->background = switch_background(ctx, ctx->background, "assets/images/background_menu.bmp");*/
}

void titulo(GameContext* ctx)
{
	al_draw_text(ctx->fonts.font_titulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 7 + 2, ALLEGRO_ALIGN_CENTER, menu_ctx.titulo);
	al_draw_text(ctx->fonts.font_titulo, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 7, ALLEGRO_ALIGN_CENTER, menu_ctx.titulo);

	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2.45 + 2, ALLEGRO_ALIGN_CENTER, menu_ctx.subtitulo);
	al_draw_text(ctx->fonts.font_subtitulo, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 2.45, ALLEGRO_ALIGN_CENTER, menu_ctx.subtitulo);
}

void botoes(GameContext* ctx, int selected, int frames, bool continuar_enable)
{
	ALLEGRO_COLOR cor;
	for (int i = 0; i < BOTOES_N; i++)
	{
		cor = (selected == i) ? ctx->cores.verde : ctx->cores.amarelo;

		if ((selected == i) && i == CONTINUAR && !continuar_enable)
			cor = ctx->cores.verde_opaco;

		desenhar_botoes(ctx, botoes_configs[i], (selected == i), frames, cor);
	}
}

void desenhar_botoes(GameContext* ctx, BotoesConfig botao, bool selecionado, int frames, ALLEGRO_COLOR cor)
{
	int sombra_x = selecionado ? botao.x + 3 : botao.x + 2;
	int sombra_y = botao.y + 3;
	const char* texto_sem_seta = botao.texto + 2;

	if (selecionado && ((frames / 25) % 2 == 0))
		return;

	al_draw_text(ctx->fonts.font_small, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, selecionado ? botao.texto : texto_sem_seta);
	al_draw_text(ctx->fonts.font_small, cor, botao.x, botao.y, ALLEGRO_ALIGN_CENTER, selecionado ? botao.texto : texto_sem_seta);

}