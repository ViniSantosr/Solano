
#pragma region Biblitotecas Externas
	#include <math.h>
	#include <stdio.h>
#pragma endregion

#pragma region Headers Game
#include "configs/sprites/soldados_dimensions.h"
#include "configs/config_tela.h"

#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#pragma endregion

#include "fases/fase2/inimigos_fase2.h"

INIMIGO inimigos[INIMIGOS_N];

void inimigo_init()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		inimigos[i].ativo = false;
	}
}

void inimigo_update(Fase2Context* f2_ctx)
{
	int nova_onda = 0;
	if (f2_ctx->frames % 120 == 0) // A cada 120 frames, será gerado uma nova onda, dá para criar niveis de ondas?
		nova_onda = between(1, 3);

	float new_x = between_f(-60, CANVAS_W + 60); // Posição aleatória dos inimigos no eixo X	

	float vel = 0.5f; // velocidade do inimigo

	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].ativo) // Se o inimigo ainda não foi ativo
		{
			if (nova_onda > 0)
			{
				new_x += between_f(40, 80);
				if (new_x > CANVAS_W + 60)
					new_x -= CANVAS_W + 120;

				inimigos[i].x = new_x;
				inimigos[i].y = between_f(-40, -60);
				inimigos[i].tipo = between(0, INIMIGO_TIPO_N);
				inimigos[i].tiro_timer = 0;
				inimigos[i].piscar = 0;

				switch (inimigos[i].tipo)
				{
				case INIMIGO_MENOR:
					inimigos[i].vida = 4;
					break;
				case INIMIGO_SOLDADO:
					inimigos[i].vida = 2;
					break;
				case INIMIGO_SNIPER:
					inimigos[i].vida = 12;
					break;
				}

				inimigos[i].dx = 0.1;
				inimigos[i].dy = 0.1;

				inimigos[i].ativo = true;

				nova_onda--;
			}
			continue;
		}

		switch (inimigos[i].tipo)
		{
		case INIMIGO_MENOR:
			vel = 1.0f;
			break;
		case INIMIGO_SOLDADO:
			vel = 1.2f;
			break;
		case INIMIGO_SNIPER:
			vel = 0.4f;
			break;
		}

		// Atualiza a direção da qual o inimigo deve se mover
		calcular_direcao_vel(false, inimigos[i].x, inimigos[i].y, soldado.x, soldado.y, &inimigos[i].dx, &inimigos[i].dy, vel);

		// Se o inimigo já estiver ativo, atualiza a posição dele
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

		if (soldado.respawn_timer == 0 && soldado.invencivel_timer == 0)
		{
			if (collide(soldado.x, soldado.y, soldado.x + SOLDADO_W, soldado.y + SOLDADO_H, inimigos[i].x, inimigos[i].y, inimigos[i].x + (INIMIGO_W[inimigos[i].tipo]), inimigos[i].y + (INIMIGO_H[inimigos[i].tipo])))
			{
				soldado.vidas--;
				soldado.respawn_timer = 90;
				soldado.invencivel_timer = 180;
			}
		}


		float cx = inimigos[i].x + (INIMIGO_W[inimigos[i].tipo] / 2); // Posição central do inimigo no X
		float cy = inimigos[i].y + (INIMIGO_H[inimigos[i].tipo] / 2); // Posição central do inimigo no Y

		if (inimigos[i].vida <= 0)
		{
			//fx_add(false, cx, cy);

			switch (inimigos[i].tipo)
			{
			case INIMIGO_MENOR:
				f2_ctx->score += 200;
				break;

			case INIMIGO_SOLDADO:
				f2_ctx->score += 150;
				break;

			case INIMIGO_SNIPER:
				f2_ctx->score += 800;
				/*fx_add(false, cx - 10, cy - 4);
				fx_add(false, cx + 4, cy + 10);
				fx_add(false, cx + 8, cy + 8);*/
				break;
			}

			inimigos[i].ativo = false;
			continue;
		}

		inimigos[i].tiro_timer--;
		if (inimigos[i].tiro_timer <= 0)
		{
			switch (inimigos[i].tipo)
			{
			case INIMIGO_MENOR:
				disparar(false, false, cx, cy, soldado.x, soldado.y, 1.5);
				inimigos[i].tiro_timer = 150;
				break;
			case INIMIGO_SOLDADO:
				disparar(false, true, cx, inimigos[i].y, soldado.x, soldado.y, 1.5);
				inimigos[i].tiro_timer = 80;
				break;
			case INIMIGO_SNIPER:
				disparar(false, true, cx - 5, cy, soldado.x, soldado.y, 1.0);
				disparar(false, true, cx + 5, cy, soldado.x, soldado.y, 1.0);
				disparar(false, true, cx - 5, cy + 8, soldado.x, soldado.y, 1.0);
				disparar(false, true, cx + 5, cy + 8, soldado.x, soldado.y, 1.0);
				inimigos[i].tiro_timer = 200;
				break;
			}
		}
	}
}

void inimigo_draw(Fase2Context* f2_ctx)
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].ativo) // Se o inimigo não estiver ativo
			continue;
		if (inimigos[i].piscar > 2)
			continue;

		al_draw_bitmap(sprites.inimigo[inimigos[i].tipo], inimigos[i].x, inimigos[i].y, 0);
	}
}




