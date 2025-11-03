
#pragma region Biblitotecas Externas
#include <math.h>
#include <stdio.h>
#pragma endregion

#pragma region Headers Game
#include "configs/sprites/soldados_dimensions.h"
#include "configs/config_tela.h"

#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#include "core/sprites/soldados_sprites.h"
#include "fases/fase2/soldado_fase2.h"
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

	float new_x = round_float(between_f(-60, CANVAS_W + 60), 1); // Posição aleatória dos inimigos no eixo X	
	float new_y = round_float(between_f(-40, -60), 1);

	float vel = 0.7f; // velocidade do inimigo

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
				inimigos[i].y = new_y;
				inimigos[i].sprite = BAIXO;
				inimigos[i].tipo = INIMIGO_SOLDADO;
				inimigos[i].tiro_timer = 0;
				inimigos[i].piscar = 0;
				inimigos[i].vida = 2;
				inimigos[i].dx = 0.1;
				inimigos[i].dy = 0.1;

				inimigos[i].ativo = true;

				nova_onda--;
			}
			continue;
		}

		calcular_sprite(inimigos[i].x, inimigos[i].y, soldado.x, soldado.y, &inimigos[i].sprite);

		// Atualiza a direção da qual o inimigo deve se mover		
		calcular_direcao_vel(inimigos[i].x, inimigos[i].y, soldado.x, soldado.y, &inimigos[i].dx, &inimigos[i].dy, vel);
		inimigos[i].x -= inimigos[i].dx;
		inimigos[i].y -= inimigos[i].dy;


		// Se o piscar > 0, então diminui 
		if (inimigos[i].piscar)
			inimigos[i].piscar--;

		// Verifica se houve colisão no inimigo
		if (tiros_collide(false, inimigos[i].x, inimigos[i].y, INIMIGO_W[3], INIMIGO_H))
		{
			inimigos[i].vida--;
			inimigos[i].piscar = 4;
		}

		// Se o soldado estiver inativo, ele não pode causar dano a ele
		if (soldado.respawn_timer == 0 && soldado.invencivel_timer == 0)
		{
			if (collide(soldado.x, soldado.y, soldado.x + SOLDADO_W[soldado.sprite], soldado.y + SOLDADO_H, inimigos[i].x, inimigos[i].y, inimigos[i].x + INIMIGO_W[3], inimigos[i].y + INIMIGO_H))
			{
				soldado.vidas--;
				soldado.respawn_timer = 90;
				soldado.invencivel_timer = 180;
			}
		}

		float cx = round_float(inimigos[i].x + (INIMIGO_W[3] / 2), 1); // Posição central do inimigo no X
		float cy = round_float(inimigos[i].y + (INIMIGO_H / 2), 1); // Posição central do inimigo no Y

		// Se o inimigo morreu
		if (inimigos[i].vida <= 0)
		{
			f2_ctx->score += 150;

			/*fx_add(false, cx - 10, cy - 4);
			fx_add(false, cx + 4, cy + 10);
			fx_add(false, cx + 8, cy + 8);*/

			inimigos[i].ativo = false;
			continue;
		}

		// Diminui o tempo do tiro, se estiver zerado, ele tem que disparar
		inimigos[i].tiro_timer--;
		if (inimigos[i].tiro_timer <= 0)
		{
			disparar(false, between(0, 2), cx, inimigos[i].y, soldado.x, soldado.y, 1.9);
			inimigos[i].tiro_timer = 80;
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

		al_draw_bitmap(sprites.inimigo[inimigos[i].sprite], inimigos[i].x, inimigos[i].y, 0);
	}
}




