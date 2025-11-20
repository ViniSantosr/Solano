
#pragma region Biblitotecas Externas
#include <math.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "fases/fase2/coisas_gerais_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#include "core/sprites/soldados_sprites.h"
#include "fases/fase2/soldado_fase2.h"
#include "core/tela_utils.h"
#include "main.h"
#pragma endregion

#include "fases/fase2/inimigos_fase2.h"

INIMIGO inimigos[INIMIGOS_N];


int nova_onda = 0;

float new_x = 0.0f;
float new_y = 0.0f;

float vel = 0.7f; // velocidade do inimigo

float cx = 0.0f;
float cy = 0.0f;

bool movimentou_inimigo;
int frame_movimento;

void inimigo_init()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		inimigos[i].ativo = false;
	}
}

void inimigo_update(GameContext* ctx, long* frames, long* score)
{

	/*if (*frames % 240 == 0)*/ // A cada 120 frames, será gerado uma nova onda, dá para criar niveis de ondas?
		switch (ctx->estado_tela)
		{	
		case FASE5:
		case FASE3:
			if (*frames % 160 == 0)
				nova_onda = between(1, 3);
			break;
		case FASE2:
			if (*frames % 240 == 0)
				nova_onda = between(1, 0);
			break;
		case FASE4:
			if (*frames % 160 == 0)
				nova_onda = between(2, 4);		
			break;
		}
		

	new_x = round_float(between_f(-60, CANVAS_W + 60), 1); // Posição aleatória dos inimigos no eixo X	
	new_y = round_float(between_f(-40, -60), 1);


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

		// Muda a direção do sprite
		calcular_sprite(inimigos[i].x, inimigos[i].y, soldado.x, soldado.y, &inimigos[i].sprite);

		// Atualiza a direção da qual o inimigo deve se mover		
		calcular_direcao_vel(inimigos[i].x, inimigos[i].y, soldado.x, soldado.y, &inimigos[i].dx, &inimigos[i].dy, vel);

		if (inimigos[i].dx || inimigos[i].dy)
		{
			inimigos[i].x -= inimigos[i].dx;
			inimigos[i].y -= inimigos[i].dy;
			movimentou_inimigo = true;
			inimigos[i].frame++;
		}



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
			if (collide(soldado.x, soldado.y, soldado.x + SOLDADOS_W, soldado.y + SOLDADOS_H, inimigos[i].x, inimigos[i].y, inimigos[i].x + INIMIGO_W[3], inimigos[i].y + INIMIGO_H))
			{
				soldado.vidas--;
				soldado.respawn_timer = 90;
				soldado.invencivel_timer = 180;
			}
		}


		switch (inimigos[i].sprite)
		{
		case CIMA:
			cx = inimigos[i].x + 3.5;
			cy = inimigos[i].y + 9;
			break;
		case BAIXO:
			cx = (inimigos[i].x + INIMIGO_W[3]) - 6;
			cy = (inimigos[i].y + INIMIGO_H) + 6;
			break;
		case DIREITA:
			cx = inimigos[i].x + INIMIGO_W[3] + 4;
			cy = inimigos[i].y + (INIMIGO_H / 1.2);
			break;
		case ESQUERDA:
			cx = inimigos[i].x;
			cy = inimigos[i].y + (INIMIGO_H / 1.2);
			break;
		}

		// Se o inimigo morreu
		if (inimigos[i].vida <= 0)
		{
			*score += 150;

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
			disparar(false, between(0, 2), cx, cy, soldado.x, soldado.y, 1.9);
			inimigos[i].tiro_timer = 80;
		}
	}
}

void inimigo_draw()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].ativo) // Se o inimigo não estiver ativo
			continue;
		if (inimigos[i].piscar > 2)
			continue;		


		frame_movimento = (inimigos[i].frame / 2) % 2;
		al_draw_bitmap(sprites_soldado.inimigo[inimigos[i].sprite][frame_movimento], inimigos[i].x, inimigos[i].y, 0);



	}
}




