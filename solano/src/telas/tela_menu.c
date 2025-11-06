
#pragma region Biblitotecas Externas
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "core/draw_tela.h"
#include "core/teclado.h"
#include "configs/config_tela.h"
#include "fases/fase1/fase1.h"
#pragma endregion

#include "telas/tela_menu.h"

MenuContext menu_ctx;

BotoesConfig botoes_configs[BOTOES_N] = // Array que armazena todos os botões e as suas específicações
{
	{ "->Novo Jogo",  CANVAS_W / 3.7, CANVAS_H / 1.9 },
	{ "->Opcoes",     CANVAS_W / 3.9, CANVAS_H / 1.75 },
	{ "->Creditos",   CANVAS_W / 3.7, CANVAS_H / 1.6 },
	{ "->Sair",       CANVAS_W / 4.0, CANVAS_H / 1.45 }
};

void inicializar_menu();
void desenhar_botoes(GameContext* ctx, BotoesConfig botao, bool selecionado, int time);
void botoes(GameContext* ctx, int selected, int time);
void titulo(GameContext* ctx, int selected, int time);

int tela_menu(GameContext* ctx)
{
	inicializar_menu();

	bool exit_tela = false;
	bool desenhar = false;

	int time = 0;            // contador de tempo (para piscar)
	int selected = 0;    // 0 = New Game, 1 = Options, 2 = Exit

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);

		// DEBUG: mostrar tipo de evento
		printf("evento recebido: %d\n", event.type);
		fflush(stdout);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			printf(">> TIMER recebido (frame %d)\n", f1_ctx.frames);
			fflush(stdout);
		}

		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			time = al_get_timer_count(ctx->timer);

			if (time > 1000) { // evita overflow do contador
				al_set_timer_count(ctx->timer, 0);
			}

			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
			case ALLEGRO_KEY_S:// seta para baixo
				selected++;
				if (selected > BOTOES_N) selected = 0; // volta para o início
				break;

			case ALLEGRO_KEY_UP: // seta para cima
			case ALLEGRO_KEY_W:
				if (selected == 0) // Deixa parado no 'Novo Jogo'
					break;

				selected--;
				break;

			case ALLEGRO_KEY_ENTER: // confirma a seleção

				switch (selected)
				{
				case NOVO_JOGO:
					exit_tela = true;
					ctx->estado_tela = FASE1;
					break;
				case SAIR:
					ctx->exit_program = true;
					break;
				}

				break;
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

			al_draw_scaled_bitmap(ctx->background_menu,
				0, 0, al_get_bitmap_width(ctx->background_menu), al_get_bitmap_height(ctx->background_menu),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			titulo(ctx, selected, time); // Função que desenhar os titulos

			botoes(ctx, selected, time); // Função que desenha os botões

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

	return 0;
}

void inicializar_menu()
{
	menu_ctx.titulo = "SOLANO";
	menu_ctx.subtitulo = "A Guerra do Paraguai";	
}

void titulo(GameContext* ctx, int selected, int time)
{
	al_draw_text(ctx->font_titulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 4 + 2, ALLEGRO_ALIGN_CENTER, menu_ctx.titulo);
	al_draw_text(ctx->font_titulo, ctx->cores.amarelo,
		CANVAS_W / 2, CANVAS_H / 4, ALLEGRO_ALIGN_CENTER, menu_ctx.titulo);

	al_draw_text(ctx->font_subtitulo, ctx->cores.preto,
		CANVAS_W / 2 + 2, CANVAS_H / 2.25 + 2, ALLEGRO_ALIGN_CENTER, menu_ctx.subtitulo);
	al_draw_text(ctx->font_subtitulo, ctx->cores.verde,
		CANVAS_W / 2, CANVAS_H / 2.25, ALLEGRO_ALIGN_CENTER, menu_ctx.subtitulo);
}

void botoes(GameContext* ctx, int selected, int time)
{
	for (int i = 0; i < BOTOES_N; i++)
	{
		desenhar_botoes(ctx, botoes_configs[i], (selected == i), time);
	}
}

void desenhar_botoes(GameContext* ctx, BotoesConfig botao, bool selecionado, int time)
{
	int sombra_x = selecionado ? botao.x + 2 : botao.x + 1;
	int sombra_y = botao.y + 1;
	const char* texto_sem_seta = botao.texto + 2;
	ALLEGRO_COLOR cor = selecionado ? ctx->cores.verde : ctx->cores.amarelo;

	if (selecionado && ((time / 25) % 2 == 0))
		return;

	al_draw_text(ctx->font, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, selecionado ? botao.texto : texto_sem_seta);
	al_draw_text(ctx->font, cor, botao.x, botao.y, ALLEGRO_ALIGN_CENTER, selecionado ? botao.texto : texto_sem_seta);

}