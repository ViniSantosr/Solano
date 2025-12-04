
#pragma region Bibliotecas Externas
#include <allegro5/allegro_primitives.h>
#pragma endregion

#pragma region Headers Game

#include "fases/fase2/coisas_gerais_fase2.h"

#include "core/tela_utils.h"

#include "core/sprites/soldados_sprites.h"

#include "fases/fase2/tiros_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "main.h"
#pragma endregion

#include "fases/fase5/solano.h"

SOLANO solano;
bool moveu;
short frame_move;
short direcao;
float solano_cx;
float solano_cy;
int vida_y;
int vida_x;
int count_frames;
bool atirar;

void solano_init()
{
	solano.sprite = BAIXO;
	solano.x = round_float((CANVAS_W / 2) - (SOLDADOS_W / 2), 1); // Mudar
	solano.y = 50; // Mudar
	solano.max_y = (CANVAS_H / 2) - 100;
	solano.max_x = (CANVAS_W - SOLDADOS_W);
	solano.tiro_timer = 0;
	solano.atirar_timer = between(120, 180);
	solano.frame = 0;
	solano.vidas = 5;
	solano.dano = 3;
	solano.respawn_timer = 0;
	solano.parado = 120;
	solano.move_timer = between(120, 241); // Quanto tem ele vai poder de mover	
	solano.invencivel_timer = 120;
	moveu = false;
	solano_cx = 0.0f;
	solano_cy = 0.0f;
	vida_y = solano.y - 10;
	vida_x = solano.x;
	direcao = between(0, 4);
	atirar = false;
	count_frames = 0;
}

void solano_update(bool* concluido)
{	
	if (solano.vidas <= 0)
		return;

	if (solano.respawn_timer)
	{
		solano.respawn_timer--;
		if (solano.respawn_timer == 1)
			solano.x = between(25, CANVAS_W);
		return;
	}

	// Vai calcular qual é o sprite	
	calcular_sprite(solano.x, solano.y, soldado.x, soldado.y, &solano.sprite);

	if (solano.parado)
	{
		solano.parado--;
	}
	else if (solano.move_timer)
	{
		solano.move_timer--;

		switch (direcao)
		{
		case 0: // Para cima

			if (solano.y < 10)
			{
				solano.y = 10;
				do
				{
					direcao = between(0, 4);
				} while (direcao == 0);
				break;
			}

			solano.y -= SOLDADO_SPEED;
			moveu = true;
			solano.frame++;
			break;

		case 1: // Para Baixo

			if (solano.y > solano.max_y)
			{
				solano.y = solano.max_y;

				do
				{
					direcao = between(0, 4);
				} while (direcao == 1);

				break;
			}

			solano.y += SOLDADO_SPEED;
			moveu = true;
			solano.frame++;
			break;

		case 2: // Para esquerda

			if (solano.x < 0)
			{
				solano.y = 1;

				do
				{
					direcao = between(0, 4);
				} while (direcao == 2);

				break;
			}

			solano.x -= SOLDADO_SPEED;
			moveu = true;
			solano.frame++;
			break;

		case 3: // Para direita

			if (solano.x > solano.max_x)
			{
				solano.x = solano.max_x;

				do
				{
					direcao = between(0, 4);
				} while (direcao == 3);

				break;
			}

			solano.x += SOLDADO_SPEED;
			moveu = true;
			solano.frame++;
			break;
		}
	}
	else
	{
		direcao = between(0, 4);
		solano.move_timer = between(120, 241);
	}

	if (solano.invencivel_timer)
		solano.invencivel_timer--;
	else
	{
		if (tiros_collide(false, solano.x, solano.y, SOLDADOS_W, SOLDADOS_H))
		{			
			solano.dano--;						
		}

		if (!solano.dano)
		{
			solano.vidas--;
			solano.respawn_timer = 600;
			solano.invencivel_timer = 180;
			solano.parado = 120;
			solano.dano = 3;
		}
	}

	// Se o soldado estiver inativo, ele não pode causar dano a ele
	if (soldado.respawn_timer == 0 && soldado.invencivel_timer == 0)
	{
		if (collide(soldado.x, soldado.y, soldado.x + SOLDADOS_W, soldado.y + SOLDADOS_H, solano.x, solano.y, solano.x + SOLDADOS_W, solano.y + SOLDADOS_H))
		{
			soldado.vidas--;
			soldado.respawn_timer = 90;
			soldado.invencivel_timer = 180;
			soldado.frame = 0;		
		}
	}

	// Se o inimigo morreu
	if (solano.vidas <= 0)
	{
		*concluido = true;
		return;
	}

	switch (solano.sprite)
	{
	case CIMA:
		solano_cx = solano.x + 3.5;
		solano_cy = solano.y + 9;
		break;
	case BAIXO:
		solano_cx = (solano.x + SOLDADOS_W) - 9;
		solano_cy = solano.y + SOLDADOS_H;
		break;
	case DIREITA:
		solano_cx = solano.x + SOLDADOS_W + 2;
		solano_cy = solano.y + (SOLDADOS_H / 1.6);
		break;
	case ESQUERDA:
		solano_cx = solano.x;
		solano_cy = solano.y + (SOLDADOS_H / 1.6);
		break;
	}

	if (count_frames >= 120)
	{
		atirar = false;
		count_frames = 0;
		solano.atirar_timer = between(120, 180);
	}	
	else if (!atirar)
	{
		solano.atirar_timer--;
		if (!solano.atirar_timer) atirar = true;
	}
	else
	{				
		count_frames++;
		// Diminui o tempo do tiro, se estiver zerado, ele tem que disparar
		solano.tiro_timer--;
		if (solano.tiro_timer <= 0)
		{
			disparar(false, 1, solano_cx, solano_cy, soldado.x, soldado.y, 1.9);
			solano.tiro_timer = 20;
		}
	}
	

}

void solano_draw(GameContext* ctx)
{
	if (solano.vidas < 0)
		return;
	if (solano.respawn_timer)
		return;

	int spacing = 7 + 1;
	vida_y = solano.y - 10;
	vida_x = solano.x;
	for (int i = 0; i < solano.vidas; i++)
	{
		al_draw_tinted_bitmap(sprites_soldado.vida_boss, ctx->cores.preto, (vida_x + (i * spacing)) + 1, vida_y + 1, 0);
		al_draw_tinted_bitmap(sprites_soldado.vida_boss, ctx->cores.branco, vida_x + (i * spacing), vida_y, 0);
	}

	if (((solano.invencivel_timer / 2) % 3) == 1)
		return;

	if (moveu)
	{
		frame_move = (solano.frame / 2) % 2;
		al_draw_bitmap(sprites_soldado.solano[solano.sprite][frame_move], solano.x, solano.y, 0);

	}
	else
	{
		al_draw_bitmap(sprites_soldado.solano[solano.sprite][0], solano.x, solano.y, 0);
		solano.frame = 0;
	}

	moveu = false;

}