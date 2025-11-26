
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
#include "fases/fase2/coisas_gerais_fase2.h"
#pragma endregion

#include <stdio.h>
#include "telas/cutscenes.h"

void quebra_linhas(char* texto, char caracter);
void draw_text(GameContext* ctx, char* buffer, int max_linha, float x, float y, PERSONAGEM personagem);


#pragma region TEXTOS

#pragma region INICIAL

DIALOGO inicial[] =
{
	{"Caramba, minha avó precisava limpar esse porão um pouco.", LEITOR},
	{"pfff!", LEITOR },
	{"Que susto, o que é isso?", LEITOR },
	{"Caramba, parece ser um livro antigo.", LEITOR},
	{"SOLANO: Um diário sobre a Guerra do Paraguai, por Rogerinho.", LEITOR},
	{"Ué, Rogerinho, esse não é o nome do meu bisavô?", LEITOR },
	{"Acho que vou ler.", LEITOR }
};

DIALOGO livro[] =
{
	{"Narrador: Caro leitor, vou te contar o que está acontecendo agora, antes da guerra começar. O Paraguai quer crescer e precisa de uma saída para o mar, porque sem isso eles ficam isolados.", NARRADOR},
	{"Por que eles não querem ficar isolados?", LEITOR},
	{"Sem um porto para o comércio eles não conseguem vender seus produtos nem comprar o que precisam. Ficam presos sem sair dali, dependendo dos outros.", NARRADOR},
	{"Além disso, o Brasil e a Argentina estão preocupados com os rios que cortam a região. Eles querem proteger esses rios para usar no transporte e comércio.", NARRADOR},
	{"No Uruguai, há uma briga entre dois grupos políticos. O Brasil apoia os colorados, e o Paraguai e a Argentina apoiam os blancos. Isso está causando muita confusão e tensionando ainda mais a situação.", NARRADOR},
	{"O Paraguai até prendeu um navio brasileiro no rio Paraguai, e isso deixou tudo mais difícil. Todos estão se preparando para a possível guerra, mas ninguém sabe como vai acabar.", NARRADOR}
};

#pragma endregion

#pragma region FASE1

DIALOGO pre_fase1[] =
{
	{"Capitão: Atenção! O Paraguai quer dominar o rio Riachuelo para cortar nossa ligação com os aliados.", CAPITAO},
	{"Rogerinho: Por que o rio é tão importante?", PRINCIPAL},
	{"Porque ele é a principal estrada para transportar soldados e suprimentos entre Brasil, Argentina e Uruguai.", CAPITAO},
	{"O que pode acontecer se perdermos o controle do rio?", PRINCIPAL},
	{"Misericórdia! Sem o rio, ficamos isolados e não recebemos reforços nem comida.", CAPITAO},
	{"Qual o objetivo do Paraguai?", PRINCIPAL},
	{"Eles querem impedir que a Tríplice Aliança se ajude e, assim, tentar vencer a guerra.", CAPITAO},
	{"O que precisamos fazer agora?", PRINCIPAL},
	{"Defender o rio, impedir que eles bloqueiem o caminho e garantir a passagem dos nossos aliados.", CAPITAO},
	{"E se vencermos essa batalha?", PRINCIPAL},
	{"Se vencermos, mostramos força, mantemos nossos aliados unidos e enfraquecemos o Paraguai.", CAPITAO},
	{"E qual é o destino do Paraguai se perderem?", PRINCIPAL},
	{"Eles ficam isolados e perdem poder para continuar a guerra.", CAPITAO},
	{"Estamos prontos, então?", PRINCIPAL},
	{"Sim! Agora é a nossa hora. Que o Riachuelo veja nossa coragem. Que essa luta traga esperança!", CAPITAO}
};

DIALOGO pos_fase1[] =
{
	{"A Marinha paraguaia está destruída!", CAPITAO},
	{"Controlamos os rios! Agora, temos vantagem para seguir avançando!", PRINCIPAL},
	{"Conseguimos!!!", PRINCIPAL}
};

#pragma endregion

#pragma region FASE2

DIALOGO pre_fase2[] =
{
	{"Em Uruguaiana, 1865, o Cerco começou: paraguaios cercados pelos aliados.", NARRADOR},
	{"Por que será que eles atacaram o Brasil?", LEITOR},
	{"Eles queriam avançar no sul para vencer a guerra.", NARRADOR},
	{"Como estava a situação deles agora?", LEITOR},
	{"Eles estavam cercados há semanas, com fome e cansaço.", NARRADOR},
	{"Caramba, eles vão lutar de qualquer jeito?", LEITOR},
	{"A tensão aumenta, a luta podia começar a qualquer momento.", NARRADOR}
};

DIALOGO pos_fase2[] =
{
	{"A resistência terminou. Eles estão se rendendo!", CAPITAO},
	{"Finalmente! Conseguimos cercar e fazer eles desistirem!", PRINCIPAL},
	{"Essa rendição é uma vitória importante para a gente. Foi a fome e as doenças que os enfraqueceram.", CAPITAO},
	{"Muitos deles estão fracos e descalços. Mas agora a guerra avança a nosso favor.", CAPITAO},
	{"Conseguimos!!!", PRINCIPAL}
};

#pragma endregion

#pragma region FASE3

DIALOGO pre_fase3[] =
{
	{"Estamos numa região de pântanos, lama e vegetação densa, chamada Tuiuti, às margens de um lago.", NARRADOR},
	{"Por que o Paraguai quer lutar aqui?", LEITOR},
	{"Porque controlar esse lugar impede nosso avanço pela estrada que leva à fortaleza inimiga, em Humaitá.", NARRADOR},
	{"E como estão os nossos soldados?", LEITOR},
	{"Eles estão apertados, cansados, enfrentam o calor intenso e a falta de água limpa, mas firmes na defesa.", NARRADOR},
	{"E o inimigo?", LEITOR},
	{"Eles estão bem posicionados numa fortificação com muitos canhões e soldados preparados para atacar.", NARRADOR},
	{"Qual o plano deles?", LEITOR},
	{"Atacar de vários lados com a cavalaria para tentar romper nossa linha.", NARRADOR},
	{"E a gente?", LEITOR},
	{"Construímos fossos sob camuflagem e preparamos a artilharia para barrar qualquer investida.", NARRADOR},
	{"O terreno ajuda ou atrapalha?", LEITOR},
	{"O terreno é traiçoeiro, com muita lama e plantas que escondem o inimigo, dificultando o movimento.", NARRADOR},
	{"Estamos prontos pra esse desafio?", LEITOR},
	{"Estamos prontos! Cada soldado precisa mostrar coragem, porque esta batalha vai determinar muito do que vem pelo caminho.", NARRADOR},
	{"Então é hora de fazer história!", LEITOR},
};

DIALOGO pos_fase3[] =
{
	{"Apesar do grande ataque paraguaio, seguramos a linha!", CAPITAO},
	{"Foi a maior batalha até agora, e resistimos firmes!", PRINCIPAL},
	{"Conseguimos!!!", PRINCIPAL}
};

#pragma endregion

#pragma region FASE4

DIALOGO pre_fase4[] =
{
	{"Estamos quase na capital deles, Assunção. A gente vai entrar e tomar essa cidade!", CAPITAO},
	{"É a hora decisiva, precisamos estar preparados para tudo.", CAPITAO},
	{"Essa vitória será importante para a guerra. Se tomarmos Assunção, enfraquecemos o Paraguai.", CAPITAO},
	{"Mas eles ainda vão resistir muito, né?", PRINCIPAL},
	{"É, vão lutar com tudo que têm, não será fácil. Precisamos manter a calma e trabalhar juntos.", PRINCIPAL},
	{"Então vamos mostrar nossa força e não deixar eles pararem a gente!", PRINCIPAL},
	{"Vamos lá!", PRINCIPAL}
};

DIALOGO pos_fase4[] =
{
	{"Conseguimos! Entramos na capital do Paraguai, Assunção!", CAPITAO},
	{"Depois de tanta luta, tomamos o controle da cidade principal deles.", PRINCIPAL},
	{"Essa vitória é um golpe forte para o Paraguai, mas a guerra ainda não acabou.", CAPITAO},
	{"Temos que ficar firmes, porque eles ainda tentam resistir em outros lugares.", CAPITAO},
	{"Conseguimos!!!", PRINCIPAL}
};

#pragma endregion

#pragma endregion


CENA_DIALOGO cenas[] =
{
	{ inicial, sizeof(inicial) / sizeof(inicial[0]), 500 },
	{ livro, sizeof(livro) / sizeof(livro[0]), 600 },

	{ pre_fase1, sizeof(pre_fase1) / sizeof(pre_fase1[0]), 600 },
	{ pos_fase1, sizeof(pos_fase1) / sizeof(pos_fase1[0]), 600 },

	{ pre_fase2, sizeof(pre_fase2) / sizeof(pre_fase2[0]), 600 },
	{ pos_fase2, sizeof(pos_fase2) / sizeof(pos_fase2[0]), 400 },

	{ pre_fase3, sizeof(pre_fase3) / sizeof(pre_fase3[0]), 600 },
	{ pos_fase3, sizeof(pos_fase3) / sizeof(pos_fase3[0]), 400 },

	{ pre_fase4, sizeof(pre_fase4) / sizeof(pre_fase4[0]), 400 },
	{ pos_fase4, sizeof(pos_fase4) / sizeof(pos_fase4[0]), 400 },
};

ALLEGRO_COLOR cor_texto;
PERSONAGEM personagem_atual;

int max_x_texto;

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

	bool animacao = false;

	int jovem_x = (CANVAS_W / 2) - (JOVEM_W / 2);
	int jovem_y = -60;
	int jovem_frame = 0;
	int frame_move = 0;

	int livro_x = (CANVAS_W / 2) - (LIVRO_W / 2);
	int livro_y = (CANVAS_H / 2) - (JOVEM_H / 2);

	switch (cena_atual)
	{
	case CENA_LIVRO:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/inicial_fundo.png");
		must_init(ctx->background, "background - inicial_fundo.png");
		break;
	case PRE_FASE1:
	case POS_FASE1:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase1_fundo.png");
		must_init(ctx->background, "background - pre/pos_fase1");
		break;
	case PRE_FASE2:
	case POS_FASE2:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase2_fundo.png");
		must_init(ctx->background, "background - pre/pos_fase2");
		break;
	case PRE_FASE3:
	case POS_FASE3:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase3_fundo.png");
		must_init(ctx->background, "background - pre/pos_fase3");
		break;
	case PRE_FASE4:
	case POS_FASE4:
		ctx->background = switch_background(ctx, ctx->background, "assets/images/fase4_fundo.png");
		must_init(ctx->background, "background - pre/pos_fase4");
		break;
	}

	ALLEGRO_EVENT event;

	while (!ctx->exit_program && !exit_tela)
	{
		al_wait_for_event(ctx->queue, &event);
		teclado_update(&event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			if (cena_atual == CENA_INICIAL)
			{
				if (collide(jovem_x, jovem_y, jovem_x + 24, jovem_y + 40, livro_x, livro_y, livro_x + 49, livro_y + 51))
				{
					animacao = false;
				}
				else
				{
					jovem_y += 1;
					jovem_frame++;
					animacao = true;					
				}
			}

			if (!linha_completa) {  // Verifica se a linha foi completada
				frame_counter++; // Aumenta o frame

				if (frame_counter > frames_por_letra) { // Se frames chegar a 3 frames					
					frame_counter = 0; // Zera o frames

					// Pega a próxima linha
					tam = strlen(cenas[cena_atual].dialogos[linha_atual].texto);

					// Verifica se todas as letras já apareceram
					if (letras_visiveis < tam) {
						letras_visiveis++;
						play_bip = true;
						personagem_atual = cenas[cena_atual].dialogos[linha_atual].personagem;
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
				tam = strlen(cenas[cena_atual].dialogos[linha_atual].texto);

				if (animacao)
				{
					break;
				}

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
					else
					{
						switch (cena_atual)
						{
						case PRE_FASE1:
						case PRE_FASE2:
						case PRE_FASE3:
						case PRE_FASE4:
							ctx->estado_tela = INTRO_FASE;
							exit_tela = true;
							break;

						case POS_FASE4:
							ctx->estado_tela = TELA_MENU;
							ctx->proxima_fase = 1;
							ctx->cena_atual = 0;
							exit_tela = true;
							break;

						default:
							ctx->cena_atual++;
							ctx->estado_tela = CUTSCENE;
							exit_tela = true;
							break;
						}
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

			al_draw_scaled_bitmap(ctx->background,
				0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
				0, 0, CANVAS_W, CANVAS_H,
				0);

			int max = sizeof(buffer) - 1;
			int n = (letras_visiveis < max) ? letras_visiveis : max;

			strncpy_s(buffer, sizeof(buffer), cenas[cena_atual].dialogos[linha_atual].texto, n);
			buffer[n] = '\0';

			switch (personagem_atual)
			{
			case PRINCIPAL:
				cor_texto = ctx->cores.verde;

				if (play_bip)
				{
					al_play_sample_instance(ctx->sons.text_bip);
					play_bip = false;
				}

				break;
			case LEITOR:
				cor_texto = ctx->cores.vermelho;

				if (play_bip)
				{
					al_play_sample_instance(ctx->sons.text_bip);
					play_bip = false;
				}

				break;
			case NARRADOR:
				cor_texto = ctx->cores.branco;

				if (play_bip)
				{
					al_set_sample_instance_speed(ctx->sons.typing, between_f(1.0, 1.5));
					al_set_sample_instance_gain(ctx->sons.typing, between_f(1.0, 1.3));
					al_play_sample_instance(ctx->sons.typing);
					play_bip = false;
				}

				break;
			case CAPITAO:
				cor_texto = ctx->cores.amarelo;

				if (play_bip)
				{
					al_set_sample_instance_speed(ctx->sons.voice, between_f(0.7, 1.6));
					al_play_sample_instance(ctx->sons.voice);
					play_bip = false;
				}

				break;
			}


			switch (cena_atual) {
			case CENA_INICIAL:
				al_draw_filled_rectangle(
					0, 0, CANVAS_W, CANVAS_H,
					ctx->cores.preto
				);

				if (animacao)
				{
					frame_move = (jovem_frame / 2) % 2;
					al_draw_bitmap(sprites_soldado.jovem[frame_move], jovem_x, jovem_y, 0);				
				}
				else
				{
					al_draw_bitmap(sprites_soldado.jovem[0], jovem_x, jovem_y, 0);									
				}

				al_draw_bitmap(sprites_soldado.livro, livro_x, livro_y, 0);
				draw_text(ctx, buffer, max_linha, 100 - (strlen(buffer) * 1.6), 50, personagem_atual);

				break;

			case CENA_LIVRO:
				al_draw_scaled_bitmap(ctx->background,
					0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
					0, 0, CANVAS_W, CANVAS_H,
					0);
				// Colocar fundo do livro

				switch (personagem_atual)
				{
				case NARRADOR:
					draw_text(ctx, buffer, 325, 100 - (strlen(buffer) * 1.4), 60, personagem_atual);
					break;

				case LEITOR:
					draw_text(ctx, buffer, 325, 425 - (strlen(buffer) * 1.4), 60, personagem_atual);
					break;
				}
				break;

			case PRE_FASE1:
			case POS_FASE1:
				al_draw_scaled_bitmap(ctx->background,
					0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
					0, 0, CANVAS_W, CANVAS_H,
					0);
				draw_text(ctx, buffer, max_linha, 195 - (strlen(buffer) * 1.6), CANVAS_H / 2 - 100, personagem_atual);
				// Colocar apenas o navio Brasileiro e deixar o texto emcima.
				break;

			case POS_FASE2:
			case POS_FASE3:
			case PRE_FASE4:
			case POS_FASE4:
				al_draw_scaled_bitmap(ctx->background,
					0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
					0, 0, CANVAS_W, CANVAS_H,
					0);
				draw_text(ctx, buffer, max_linha, ((CANVAS_W / 2) - 100) - (strlen(buffer) * 1.8), (CANVAS_H / 2) - 50, personagem_atual);
				al_draw_bitmap(sprites_soldado.soldado[CIMA][0], (CANVAS_W / 2) - (SOLDADOS_W / 2), (CANVAS_H / 2) + 20, 0);
				al_draw_bitmap(sprites_soldado.soldado_loiro, (CANVAS_W / 2) + 30, (CANVAS_H / 2) - 150, 0);
				al_draw_bitmap(sprites_soldado.soldado_moreno, (CANVAS_W / 2) - (SOLDADOS_W / 2), (CANVAS_H / 2) - 130, 0);
				break;

			default:
				al_draw_scaled_bitmap(ctx->background,
					0, 0, al_get_bitmap_width(ctx->background), al_get_bitmap_height(ctx->background),
					0, 0, CANVAS_W, CANVAS_H,
					0);
				draw_text(ctx, buffer, max_linha, 195 - (strlen(buffer) * 1.6), CANVAS_H / 2 - 100, personagem_atual);
				break;
			}

			if ((frames / 45) % 2 == 0)
			{
				al_draw_text(ctx->fonts.font_small, ctx->cores.preto, pular_x + 2, pular_y + 1.5, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para avançar");
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



	for (int i = 0; i < len - 1; i++)
	{
		// Se for espaço, marca como ponto de quebra possível
		if (texto[i] == caracter)
		{
			texto[i + 1] = '\n';  // substitui espaço por quebra			
		}
	}
}

void draw_text(GameContext* ctx, char* buffer, int max_linha, float x, float y, PERSONAGEM personagem)
{

	quebra_linhas(buffer, '.');

	switch (ctx->cena_atual)
	{
	case CENA_INICIAL:
		max_x_texto = 45;
		break;

	case CENA_LIVRO:

		switch (personagem)
		{
		case NARRADOR:
			max_x_texto = 60;
			break;
		case LEITOR:
			max_x_texto = 420;
			break;
		}
		break;

	case POS_FASE2:
	case POS_FASE3:
	case PRE_FASE4:
	case POS_FASE4:
		max_x_texto = (CANVAS_W / 2) - 200;
		break;

	default:
		max_x_texto = 100;
		break;
	}

	if (x < max_x_texto) x = max_x_texto;

	al_draw_multiline_text(
		ctx->fonts.font_small,
		ctx->cores.preto,
		x + 2,
		y + 1.5,
		max_linha,    // mesma largura do wrap
		al_get_font_line_height(ctx->fonts.font_small),
		0,
		buffer
	);

	al_draw_multiline_text(
		ctx->fonts.font_small,
		cor_texto,
		x,
		y,
		max_linha,    // mesma largura do wrap
		al_get_font_line_height(ctx->fonts.font_small),
		0,
		buffer
	);
}
