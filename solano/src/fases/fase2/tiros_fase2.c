#include "fases/fase2/tiros_fase2.h"

#include <allegro5/allegro5.h>
#include <math.h>
#include "core/must_init.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "configs/config_tela.h"
#include "core/sprites/sprites_soldados.h"
#include "fases/fase2/coisas_gerais_fase2.h"

TIRO tiros[TIROS_N];

void tiro_init()
{
	for (int i = 0; i < TIROS_N; i++) {
		tiros[i].usado = false;
	}
}

bool disparar(bool soldado, bool reto, float x, float y, float mira_x, float mira_y)
{
	for (int i = 0; i < TIROS_N; i++)
	{
		if (tiros[i].usado)
			continue;;

		tiros[i].soldado = soldado; // indica de quem é o tiro

		if (soldado)
		{
			float dirx = x - mira_x;
			float diry = y - mira_y;
			float dist = sqrt(dirx * dirx + diry * diry);

			if (dist == 0) return;

			dirx /= dist;
			diry /= dist;

			float vel = 3.0f;

			tiros[i].x = x;
			tiros[i].y = y;
			tiros[i].dx = dirx * vel;
			tiros[i].dy = diry * vel;
		}
		else
		{
			tiros[i].x = x - (INIMIGO_TIRO_W / 2);
			tiros[i].y = y - (INIMIGO_TIRO_H / 2);

			if (reto) // indica que o tiro vai ser reto
			{
				tiros[i].dx = 0; // o tiro não desloca para o lado
				tiros[i].dy = 2; // o tiro se desloca para cima
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

bool tiros_collide(bool soldado, int x, int y, int w, int h)
{
	for (int i = 0; i < TIROS_N; i++)
	{
		// Se o tiro não foi usado 'false'
		if (!tiros[i].usado)
			continue;

		// Não colidir com a própria nave
		if (tiros[i].soldado == soldado)
			continue;

		int sw, sh;
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

		if (tiros[i].soldado)
		{
			float angle = atan2f(tiros[i].dy, tiros[i].dx);

			al_draw_rotated_bitmap(sprites.soldado_tiros[frame_tela],
				SOLDADO_TIRO_W / 2, SOLDADO_TIRO_H / 2,
				tiros[i].x, tiros[i].y,
				angle + ALLEGRO_PI / 2,
				0);
		}
		else
		{
			/*
				ALLEGRO_COLOR tint =
					frame_tela
					? al_map_rgb_f(1, 1, 1)
					: al_map_rgb_f(0.5, 0.5, 0.5)
					;
				al_draw_tinted_bitmap(sprites.alien_shot, tint, tiros[i].x, tiros[i].y, 0);
			*/
		}
	}
}
