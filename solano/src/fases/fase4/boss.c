
#pragma region Bibliotecas Externas
#include <math.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#pragma endregion

#pragma region Headers Game

#include "fases/fase2/coisas_gerais_fase2.h"

#include "core/tela_utils.h"

#include "core/sprites/soldados_sprites.h"
#include "core/teclado.h"

#include "fases/fase2/mouse_fase2.h"
#include "fases/fase2/tiros_fase2.h"
#include "fases/fase2/soldado_fase2.h"
#include "main.h"
#pragma endregion

#include "fases/fase4/boss.h"

BOSS boss;
bool boss_moveu;
short boss_frame_move;
short boss_direcao;
float boss_cx;
float boss_cy;
int boss_vida_y;
int boss_vida_x;
int boss_count_frames;
bool boss_atirar;

void boss_init()
{
	boss.sprite = BAIXO;
	boss.x = round_float((CANVAS_W / 2) - (SOLDADOS_W / 2), 1); // Mudar
	boss.y = 50; // Mudar
	boss.max_y = (CANVAS_H / 2) - 100;
	boss.max_x = (CANVAS_W - SOLDADOS_W);
	boss.tiro_timer = 0;
	boss.atirar_timer = between(120, 180);
	boss.frame = 0;
	boss.vidas = 3;
	boss.dano = 3;
	boss.respawn_timer = 0;
	boss.parado = 120;
	boss.move_timer = between(120, 241); // Quanto tem ele vai poder de mover	
	boss.invencivel_timer = 120;
	boss_moveu = false;
	boss_cx = 0.0f;
	boss_cy = 0.0f;
	boss_vida_y = boss.y - 10;
	boss_vida_x = boss.x;
	boss_direcao = between(0, 4);
	boss_atirar = false;
	boss_count_frames = 0;
}

void boss_update(bool* concluido)
{	
	if (boss.vidas <= 0)
		return;

	if (boss.respawn_timer)
	{
		boss.respawn_timer--;
		if (boss.respawn_timer == 1)
			boss.x = between(25, CANVAS_W);
		return;
	}

	// Vai calcular qual é o sprite	
	calcular_sprite(boss.x, boss.y, soldado.x, soldado.y, &boss.sprite);

	if (boss.parado)
	{
		boss.parado--;
	}
	else if (boss.move_timer)
	{
		boss.move_timer--;

		switch (boss_direcao)
		{
		case 0: // Para cima

			if (boss.y <= 10)
			{
				boss.y = 10;
				do
				{
					boss_direcao = between(0, 4);
				} while (boss_direcao == 0);
				break;
			}

			boss.y -= BOSS_SPEED;
			boss_moveu = true;
			boss.frame++;
			break;

		case 1: // Para Baixo

			if (boss.y > boss.max_y)
			{
				boss.y = boss.max_y;

				do
				{
					boss_direcao = between(0, 4);
				} while (boss_direcao == 1);

				break;
			}

			boss.y += BOSS_SPEED;
			boss_moveu = true;
			boss.frame++;
			break;

		case 2: // Para esquerda

			if (boss.x < 0)
			{
				boss.y = 1;

				do
				{
					boss_direcao = between(0, 4);
				} while (boss_direcao == 2);

				break;
			}

			boss.x -= BOSS_SPEED;
			boss_moveu = true;
			boss.frame++;
			break;

		case 3: // Para direita

			if (boss.x > boss.max_x)
			{
				boss.x = boss.max_x;

				do
				{
					boss_direcao = between(0, 4);
				} while (boss_direcao == 3);

				break;
			}

			boss.x += BOSS_SPEED;
			boss_moveu = true;
			boss.frame++;
			break;
		}
	}
	else
	{
		boss_direcao = between(0, 4);
		boss.move_timer = between(120, 241);
	}

	if (boss.invencivel_timer)
		boss.invencivel_timer--;
	else
	{
		if (tiros_collide(false, boss.x, boss.y, SOLDADOS_W, SOLDADOS_H))
		{			
			boss.dano--;						
		}

		if (!boss.dano)
		{
			boss.vidas--;
			boss.respawn_timer = 600;
			boss.invencivel_timer = 180;
			boss.parado = 120;
			boss.dano = 3;
		}
	}

	// Se o soldado estiver inativo, ele não pode causar dano a ele
	if (soldado.respawn_timer == 0 && soldado.invencivel_timer == 0)
	{
		if (collide(soldado.x, soldado.y, soldado.x + SOLDADOS_W, soldado.y + SOLDADOS_H, boss.x, boss.y, boss.x + SOLDADOS_W, boss.y + SOLDADOS_H))
		{
			soldado.vidas--;
			soldado.respawn_timer = 90;
			soldado.invencivel_timer = 180;
			soldado.frame = 0;		
		}
	}

	// Se o inimigo morreu
	if (boss.vidas <= 0)
	{
		*concluido = true;
		return;
	}

	switch (boss.sprite)
	{
	case CIMA:
		boss_cx = boss.x + 3.5;
		boss_cy = boss.y + 9;
		break;
	case BAIXO:
		boss_cx = (boss.x + SOLDADOS_W) - 9;
		boss_cy = boss.y + SOLDADOS_H;
		break;
	case DIREITA:
		boss_cx = boss.x + SOLDADOS_W + 2;
		boss_cy = boss.y + (SOLDADOS_H / 1.6);
		break;
	case ESQUERDA:
		boss_cx = boss.x;
		boss_cy = boss.y + (SOLDADOS_H / 1.6);
		break;
	}

	if (boss_count_frames >= 120)
	{
		boss_atirar = false;
		boss_count_frames = 0;
		boss.atirar_timer = between(120, 180);
	}	
	else if (!boss_atirar)
	{
		boss.atirar_timer--;
		if (!boss.atirar_timer) boss_atirar = true;
	}
	else
	{				
		boss_count_frames++;
		// Diminui o tempo do tiro, se estiver zerado, ele tem que disparar
		boss.tiro_timer--;
		if (boss.tiro_timer <= 0)
		{
			disparar(false, 1, boss_cx, boss_cy, soldado.x, soldado.y, 2.2);
			boss.tiro_timer = 20;
		}
	}
	

}

void boss_draw(GameContext* ctx)
{
	if (boss.vidas < 0)
		return;
	if (boss.respawn_timer)
		return;

	int spacing = 7 + 1;
	boss_vida_y = boss.y - 10;
	boss_vida_x = boss.x;
	for (int i = 0; i < boss.vidas; i++)
	{
		al_draw_tinted_bitmap(sprites_soldado.vida_boss, ctx->cores.preto, (boss_vida_x + (i * spacing)) + 1, boss_vida_y + 1, 0);
		al_draw_tinted_bitmap(sprites_soldado.vida_boss, ctx->cores.branco, boss_vida_x + (i * spacing), boss_vida_y, 0);
	}

	if (((boss.invencivel_timer / 2) % 3) == 1)
		return;

	if (boss_moveu)
	{
		boss_frame_move = (boss.frame / 2) % 2;
		al_draw_bitmap(sprites_soldado.inimigo[boss.sprite][boss_frame_move], boss.x, boss.y, 0);

	}
	else
	{
		al_draw_bitmap(sprites_soldado.inimigo[boss.sprite][0], boss.x, boss.y, 0);
		boss.frame = 0;
	}

	boss_moveu = false;

}