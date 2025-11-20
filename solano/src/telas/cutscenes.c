
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

#include "telas/cutscenes.h"

const char* dialogo[] = {
    "Ola soldado. Seja bem-vindo ao campo de treinamento.",
    "Hoje voce ira aprender a movimentar, atacar e defender.",
    "Boa sorte!"
};

int linha_atual = 0;
const int total_linhas = 3;
char buffer[512];

int letras_visiveis = 0;      // quantas letras já devem aparecer
int frame_counter = 0;
int frames_por_letra = 3;     // controla a velocidade (3 frames ≈ 20 letras/s)
int text_sound_frame = 6;
bool linha_completa = false;

void cutscene(GameContext* ctx, int fase_atual)
{
	al_set_audio_stream_playing(ctx->sons.music, false);

	size_t tam;
	int frames = 0; // contador de tempo (para piscar)
	
	float pular_x = CANVAS_W - 150;
	float pular_y = CANVAS_H - 25;

    bool exit_tela = false;
    bool desenhar = false;

    ALLEGRO_EVENT event;

    while (!ctx->exit_program && !exit_tela)
    {        
		al_wait_for_event(ctx->queue, &event);
		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			if (!linha_completa) {  // Verifica se a linha foi completada
				frame_counter++; // Aumenta o frame

				if (frame_counter >= frames_por_letra) { // Se frames chegar a 3 frames					
					frame_counter = 0; // Zera o frames

					// Pega a próxima letra
					tam = strlen(dialogo[linha_atual]);

					if (letras_visiveis < tam) {
						letras_visiveis++;		
						al_play_sample(ctx->sons.text_bip, 0.2, 0.0, 0.7, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else {
						linha_completa = true;												
					}
				}
			}
			
			frames++;
			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				tam = strlen(dialogo[linha_atual]);

				if (!linha_completa) {
					// Mostra tudo instantaneamente
					letras_visiveis = (int)tam;
					linha_completa = true;
				}
				else {
					// Vai para a próxima linha
					linha_atual++;

					if (linha_atual < total_linhas) {
						// reinicia para a próxima frase
						letras_visiveis = 0;
						frame_counter = 0;
						linha_completa = false;
					}
					else {
						// acabou o diálogo
						/*ctx->proxima_fase = fase_atual;
						ctx->estado_tela = INTRO_FASE;
						exit_tela = true;
						break;*/
					}
				}
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

			strncpy_s(buffer, sizeof(buffer), dialogo[linha_atual], letras_visiveis);
			buffer[letras_visiveis] = '\0';

			al_draw_text(ctx->fonts.font_small, ctx->cores.verde, 50, 50, 0, buffer);

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

