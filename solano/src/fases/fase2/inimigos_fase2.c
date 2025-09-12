#include "fases/fase2/inimigos_fase2.h"

#include <math.h>

#include "configs/sprites/config_sprites_soldados.h"
#include "core/sprites/sprites_soldados.h"
#include "configs/config_tela.h"
#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase2/tiros_fase2.h"

INIMIGO inimigos[INIMIGOS_N];

void inimigo_init()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		inimigos[i].ativo = false;
	}
}

void inimigo_update(float soldado_x, float soldado_y)
{
	int nova_onda = 0;
	if (frames % 120 == 0) // A cada 120 frames, será gerado uma nova onda, dá para criar niveis de ondas?
		nova_onda = between(2, 4);

	float new_x = between(-60, CANVAS_W + 60); // Posição aleatória dos inimigos no eixo X	

	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].ativo) // Se o inimigo ainda não foi ativo
		{
			float vel = 1.0f;

			if (nova_onda > 0)
			{
				new_x += between_f(40, 80);
				if (new_x > CANVAS_W + 60)
					new_x -= CANVAS_W + 120;

				inimigos[i].x = new_x;
				inimigos[i].y = between(-40, -60);
				inimigos[i].tipo = between(0, INIMIGO_TIPO_N);
				inimigos[i].tiro_timer = 0;
				inimigos[i].piscar = 0;

				switch (inimigos[i].tipo)
				{
				case INIMIGO_MENOR:
					inimigos[i].vida = 4;
					vel = 5.0f;
					break;
				case INIMIGO_SOLDADO:
					inimigos[i].vida = 2;
					vel = 3.5f;
					break;
				case INIMIGO_SNIPER:
					inimigos[i].vida = 12;
					vel = 1.5f;
					break;
				}

				inimigos[i].dx = 0;
				inimigos[i].dy = 2;

				inimigos[i].ativo = true;

				calcular_direcao(inimigos[i].x, inimigos[i].y, soldado_x, soldado_y, &inimigos[i].dx, &inimigos[i].dy, vel);

				nova_onda--;
			}
			continue;
		}

		// Se o inimigo já está sendo ativo, atualiza a posição dele
		inimigos[i].x += inimigos[i].dx;
		inimigos[i].y += inimigos[i].dy;

		if (inimigos[i].y >= CANVAS_H)
		{
			inimigos[i].ativo = false;
		}

		if (inimigos[i].piscar)
		{
			inimigos[i].piscar--;
		}

		if (tiros_collide(false, inimigos[i].x, inimigos[i].y, INIMIGO_W[inimigos[i].tipo], INIMIGO_H[inimigos[i].tipo]))
		{
			inimigos[i].vida--;
			inimigos[i].piscar = 4;
		}

		float cx = inimigos[i].x + (INIMIGO_W[inimigos[i].tipo] / 2); // Posição central do inimigo no X
		float cy = inimigos[i].y + (INIMIGO_H[inimigos[i].tipo] / 2); // Posição central do inimigo no Y

		if (inimigos[i].vida <= 0)
		{
			//fx_add(false, cx, cy);

			switch (inimigos[i].tipo)
			{
			case INIMIGO_MENOR:
				score += 200;
				break;

			case INIMIGO_SOLDADO:
				score += 150;
				break;

			case INIMIGO_SNIPER:
				score += 800;
				/*fx_add(false, cx - 10, cy - 4);
				fx_add(false, cx + 4, cy + 10);
				fx_add(false, cx + 8, cy + 8);*/
				break;
			}

			inimigos[i].ativo = false;
			continue;
		}

		inimigos[i].tiro_timer--;
		if (inimigos[i].tiro_timer == 0)
		{
			switch (inimigos[i].tipo)
			{
			case INIMIGO_MENOR:
				disparar(false, false, cx, cy, soldado_x, soldado_y, 2.0);
				inimigos[i].tiro_timer = 150;
				break;
			case INIMIGO_SOLDADO:
				disparar(false, true, cx, inimigos[i].y, soldado_x, soldado_y, 5.0);
				inimigos[i].tiro_timer = 80;
				break;
			case INIMIGO_SNIPER:
				disparar(false, true, cx - 5, cy, soldado_x, soldado_y, 5.0);
				disparar(false, true, cx + 5, cy, soldado_x, soldado_y, 5.0);
				disparar(false, true, cx - 5, cy + 8, soldado_x, soldado_y, 5.0);
				disparar(false, true, cx + 5, cy + 8, soldado_x, soldado_y, 5.0);
				inimigos[i].tiro_timer = 200;
				break;
			}
		}
	}
}

void inimigo_draw()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].ativo) // Se o inimigo não está sendo ativo
			continue;
		if (inimigos[i].piscar > 2) // 
			continue;

		al_draw_bitmap(sprites.inimigo[inimigos[i].tipo], inimigos[i].x, inimigos[i].y, 0);
	}
}




