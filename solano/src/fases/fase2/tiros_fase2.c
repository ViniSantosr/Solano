#include "fases/fase2/tiros_fase2.h"

#include <allegro5/allegro5.h>
#include <math.h>
#include "core/must_init.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "configs/config_tela.h"
#include "core/sprites/sprites_soldados.h"
#include "fases/fase2/coisas_gerais_fase2.h"

TIRO tiros[TIROS_N];

#pragma region PROCESSO
/*
	1. tiro_init() -> Inicializar o array de tiros na memória.
	2. disparar() -> Quando há um disparo no jogo, percorre o array procurado por um tiro que não foi usado.
		2.1. Armazena se foi o jogador ou inimigo.
		2.2. Se foi o jogador:
				dirx -> indica
*/
#pragma endregion


void tiro_init()
{
	for (int i = 0; i < TIROS_N; i++) {
		tiros[i].usado = false;
	}
}

bool disparar(bool soldado, bool reto, float x, float  y, float alvo_x, float alvo_y, float vel)
{
	for (int i = 0; i < TIROS_N; i++)
	{
		if (tiros[i].usado)
			continue;

		tiros[i].soldado = soldado; // indica de quem é o tiro

		if (soldado)
		{
			tiros[i].x = x;
			tiros[i].y = y;
			tiros[i].dx = 0;
			tiros[i].dy = 0;

			calcular_direcao(true, x, y, alvo_x, alvo_y, &tiros[i].dx, &tiros[i].dy, vel);
		}
		else
		{
			tiros[i].x = x - (INIMIGO_TIRO_W / 2);
			tiros[i].y = y - (INIMIGO_TIRO_H / 2);

			if (reto)
			{
				tiros[i].dx = 1;
				tiros[i].dy = 2;

				calcular_direcao(false, x, y, alvo_x, alvo_y, &tiros[i].dx, &tiros[i].dy, vel);
			}
			else
			{
				tiros[i].dx = between(-2, 2);
				tiros[i].dy = between(-2, 2);
			}

			// Se o tiro não tiver velocidade, não executa
			if (!tiros[i].dx && !tiros[i].dy)
				return true;
		}

		tiros[i].frame = 0;
		tiros[i].usado = true;

		return true;
	}

	return false;
}

void tiros_update()
{
	for (int i = 0; i < TIROS_N; i++)
	{
		if (!tiros[i].usado) // Se o tiro não fui usado ainda
			continue;

		if (tiros[i].soldado) // Se foi do jogador
		{
			tiros[i].y -= tiros[i].dy;
			tiros[i].x -= tiros[i].dx;

			if (tiros[i].x < -SOLDADO_TIRO_W || tiros[i].x > CANVAS_W ||
				tiros[i].y < -SOLDADO_TIRO_H || tiros[i].y > CANVAS_H) {
				tiros[i].usado = false;
				continue;
			}
		}
		else // alien
		{
			tiros[i].x += tiros[i].dx;
			tiros[i].y += tiros[i].dy;

			if ((tiros[i].x < -INIMIGO_TIRO_W) // O tiro saido por completo da tela na esquerda
				|| (tiros[i].x > CANVAS_W) // O tiro saido por completo da tela na direita
				|| (tiros[i].y < -INIMIGO_TIRO_W) // O tiro saido por completo da tela em cima
				|| (tiros[i].y > CANVAS_H) // O tiro saido por completo da tela em baixo
				) {
				tiros[i].usado = false; // indica que não está sendo mais usado
				continue;
			}
		}

		tiros[i].frame++; // Adiciona mais 1 quadro para todos os tiros
	}
}

bool tiros_collide(bool soldado, float x, float y, float w, float h)
{
	for (int i = 0; i < TIROS_N; i++)
	{
		// Se o tiro não foi usado 'false'
		if (!tiros[i].usado)
			continue;

		// Não colidir com a própria nave
		if (tiros[i].soldado == soldado)
			continue;

		float sw, sh;
		if (soldado)
		{
			sw = INIMIGO_TIRO_W;
			sh = INIMIGO_TIRO_H;
		}
		else
		{
			sw = SOLDADO_TIRO_W;
			sh = SOLDADO_TIRO_H;
		}

		if (collide(x, y, x + w, y + h, tiros[i].x, tiros[i].y, tiros[i].x + sw, tiros[i].y + sh))
		{
			//fx_add(true, tiros[i].x + (sw / 2), tiros[i].y + (sh / 2)); // adiciona o efeito de tiro
			tiros[i].usado = false; // indica que não está sendo mais usado
			return true;
		}
	}

	return false;
}

void tiros_draw()
{
	for (int i = 0; i < TIROS_N; i++)
	{
		if (!tiros[i].usado)
			continue;

		int frame_tela = (tiros[i].frame / 2) % 2;
		float angle = atan2f(tiros[i].dy, tiros[i].dx);

		if (tiros[i].soldado)
		{
			al_draw_rotated_bitmap(sprites.soldado_tiros[frame_tela],
				SOLDADO_TIRO_W / 2, SOLDADO_TIRO_H / 2,
				tiros[i].x, tiros[i].y,
				angle + ALLEGRO_PI / 2,
				0);
		}
		else
		{

			ALLEGRO_COLOR tint =
				frame_tela
				? al_map_rgb_f(1, 1, 1)
				: al_map_rgb_f(0.5, 0.5, 0.5)
				;
			al_draw_tinted_bitmap(sprites.inimigo_tiro, tint, tiros[i].x, tiros[i].y, 0);			

		}
	}
}
