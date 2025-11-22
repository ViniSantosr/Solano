
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

void quebra_linhas(char* texto, char caracter);
void draw_text(GameContext* ctx, char* buffer, PERSONAGEM personagem, int max_linha);


#pragma region TEXTOS

#pragma region INICIAL

DIALOGO inicial[] =
{
	{"Caramba, minha avó precisava limpar esse porão um pouco", LEITOR},
	{"pfff!", LEITOR },
	{"Que susto, o que é isso?", LEITOR },
	{"Caramba, parece ser um livro antigo.", LEITOR},
	{"SOLANO: Uma biografia sobre Rogerinho, um herói da Guerra do Paraguai.", LEITOR},
	{"Ué, Rogerinho, esse não é o nome do meu bisavô?", LEITOR },
	{"Acho que vou ler.", LEITOR }
};

DIALOGO livro[] =
{
	{"Narrador: Caro leitor, vou te contar o que está acontecendo agora, antes da guerra começar. O Paraguai quer crescer e precisa de uma saída para o mar, porque sem isso eles ficam isolados.", NARRADOR},
	{"Leitor: Por que eles não querem ficar isolados?", LEITOR},
	{"Narrador: Porque sem um porto para o comércio eles não conseguem vender seus produtos nem comprar o que precisam. Ficam presos sem sair dali, dependendo dos outros.", NARRADOR},
	{"Além disso, o Brasil e a Argentina estão preocupados com os rios que cortam a região. Eles querem proteger esses rios para usar no transporte e comércio.", NARRADOR},
	{"No Uruguai, há uma briga entre dois grupos políticos. O Brasil apoia os colorados, e o Paraguai e a Argentina apoiam os blancos. Isso está causando muita confusão e tensionando ainda mais a situação.", NARRADOR},
	{"O Paraguai até prendeu um navio brasileiro no rio Paraguai, e isso deixou tudo mais difícil. Todos estão se preparando para a possível guerra, mas ninguém sabe como vai acabar.", NARRADOR}
};

#pragma endregion

#pragma region FASE1

const char* pre_fase1[] =
{
	"Capitão: Atenção! O Paraguai quer dominar o rio Riachuelo para cortar nossa ligação com os aliados.",
	"Rogerinho: Por que o rio é tão importante?",
	"Capitão: Porque ele é a principal estrada para transportar soldados e suprimentos entre Brasil, Argentina e Uruguai.",
	"Rogerinho: O que pode acontecer se perdermos o controle do rio?",
	"Capitão: Misericórdia! Sem o rio, ficamos isolados e não recebemos reforços nem comida.",
	"Rogerinho: Qual o objetivo do Paraguai?",
	"Capitão: Eles querem impedir que a Tríplice Aliança se ajude e, assim, tentar vencer a guerra.",
	"Rogerinho: O que precisamos fazer agora?",
	"Capitão: Defender o rio, impedir que eles bloqueiem o caminho e garantir a passagem dos nossos aliados.",
	"Rogerinho: E se vencermos essa batalha?",
	"Capitão: Se vencermos, mostramos força, mantemos nossos aliados unidos e enfraquecemos o Paraguai.",
	"Rogerinho: E qual é o destino do Paraguai se perderem?",
	"Capitão: Eles ficam isolados e perdem poder para continuar a guerra.",
	"Rogerinho: Estamos prontos, então?",
	"Capitão: Sim! Agora é a nossa hora. Que o Riachuelo veja nossa coragem. Que essa luta traga esperança!"
};

const char* pos_fase1[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

#pragma endregion

#pragma region FASE2

const char* pre_fase2[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

const char* pos_fase2[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

#pragma endregion

#pragma region FASE3

const char* pre_fase3[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

const char* pos_fase3[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

#pragma endregion

#pragma region FASE4

const char* pre_fase4[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

const char* pos_fase4[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

#pragma endregion

#pragma region FASE5

const char* pre_fase5[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

const char* pos_fase5[] =
{
	"Outro diálogo...",
	"Segunda linha..."
};

#pragma endregion

#pragma endregion


CENA_DIALOGO cenas[] =
{
	{ inicial, sizeof(inicial) / sizeof(inicial[0]), 500 },
	{ livro, sizeof(livro) / sizeof(livro[0]), 600 },
};

ALLEGRO_COLOR cor_texto;
PERSONAGEM personagem_atual;

void cutscene(GameContext* ctx, int cena)
{
	al_set_audio_stream_playing(ctx->sons.music, false);

	int cena_atual = cena;
	int total_linhas = cenas[cena_atual].total_linhas;

	char buffer[512];
	size_t tam = 0;
	int linha_atual = 0;
	int letras_visiveis = 0;      // quantas letras já devem aparecer
	int frame_counter = 0;
	int frames_por_letra = 3;     // controla a velocidade (3 frames ≈ 20 letras/s)
	int max_linha = cenas[cena_atual].max_linha;
	float personagem_gain = 0.0f;

	bool linha_completa = false;
	bool play_bip = false;

	bool exit_tela = false;
	bool desenhar = false;
	int frames = 0;

	float pular_x = CANVAS_W - 150;
	float pular_y = CANVAS_H - 25;

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

					// Pega a próxima linha
					tam = strlen(cenas[cena_atual].dialogos[linha_atual].texto);

					// Verifica se todas as letras já apareceram
					if (letras_visiveis < tam) {
						letras_visiveis++;
						play_bip = true;						
					}
					else {
						linha_completa = true;
					}
				}
			}

			personagem_atual = cenas[cena_atual].dialogos[linha_atual].personagem;

			frames++;
			desenhar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				tam = strlen(cenas[cena_atual].dialogos[linha_atual].texto);

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

						switch (cena_atual)
						{
						case PRE_FASE1:
							ctx->cena_atual++;
							ctx->estado_tela = FASE1;
							exit_tela = true;
							break;
						case PRE_FASE2:
							ctx->cena_atual++;
							ctx->estado_tela = FASE2;
							exit_tela = true;
							break;
						case PRE_FASE3:
							ctx->cena_atual++;
							ctx->estado_tela = FASE3;
							exit_tela = true;
							break;
						case PRE_FASE4:
							ctx->cena_atual++;
							ctx->estado_tela = FASE4;
							exit_tela = true;
							break;
						case PRE_FASE5:
							ctx->cena_atual++;
							ctx->estado_tela = FASE5;
							exit_tela = true;
							break;

						case POS_FASE5:
							ctx->estado_tela = TELA_MENU;
							exit_tela = true;
							break;

						default:
							ctx->cena_atual++;
							ctx->estado_tela = CUTSCENE;
							exit_tela = true;
							break;
						}
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

			strncpy_s(buffer, sizeof(buffer), cenas[cena_atual].dialogos[linha_atual].texto, letras_visiveis);
			buffer[letras_visiveis] = '\0';

			switch (personagem_atual)
			{
			case PRINCIPAL:
				cor_texto = ctx->cores.verde;
				personagem_gain = 0.2f;
				break;
			case LEITOR:
				cor_texto = ctx->cores.azul;
				personagem_gain = 0.2f;
				break;
			case NARRADOR:
				cor_texto = ctx->cores.branco;
				personagem_gain = 0.5f;
				break;
			case CAPITAO:
				cor_texto = ctx->cores.amarelo;
				personagem_gain = 0.5f;
				break;
			}

			if (play_bip)
			{
				al_play_sample_instance(ctx->sons.text_bip);
				play_bip = false;
			}

			switch (cena_atual) {
			case CENA_INICIAL:
				draw_text(ctx, buffer, personagem_atual, max_linha);
				break;
			case CENA_LIVRO:
				al_draw_filled_rectangle(
					0, 0, CANVAS_W, CANVAS_H,
					ctx->cores.verde_opaco
				);
				draw_text(ctx, buffer, personagem_atual, max_linha);
				break;
			}

			if ((frames / 45) % 2 == 0)
			{
				al_draw_text(ctx->fonts.font_small, ctx->cores.preto, pular_x + 2, pular_y + 2, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para avançar");
				al_draw_text(ctx->fonts.font_small, ctx->cores.verde, pular_x, pular_y, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para avançar");
			}

			tela_pos_draw(ctx->canvas, ctx->tela);
			desenhar = false;
		}
	}

}


void quebra_linhas(char* texto, char caracter)
{
	int len = (int)strlen(texto);	

	for (int i = 0; i < len; i++)
	{
		// Se for espaço, marca como ponto de quebra possível
		if (texto[i] == caracter)
		{			
			texto[i + 1] = '\n';  // substitui espaço por quebra			
		}
	}
}

void draw_text(GameContext* ctx, char* buffer, PERSONAGEM personagem, int max_linha)
{	

	quebra_linhas(buffer, '.');

	al_draw_multiline_text(
		ctx->fonts.font_small,
		ctx->cores.preto,
		50 + 2,
		50 + 2,
		max_linha,    // mesma largura do wrap
		al_get_font_line_height(ctx->fonts.font_small),
		0,
		buffer
	);

	al_draw_multiline_text(
		ctx->fonts.font_small,
		cor_texto,
		50,
		50,
		max_linha,    // mesma largura do wrap
		al_get_font_line_height(ctx->fonts.font_small),
		0,
		buffer
	);
}
