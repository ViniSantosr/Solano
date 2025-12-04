
#pragma region Bibliotecas Externas
#include <allegro5/allegro_primitives.h>
#pragma endregion

#pragma region Headers Game

#include "fases/fase2/coisas_gerais_fase2.h"

#include "core/tela_utils.h"

#include "core/sprites/soldados_sprites.h"
#include "core/teclado.h"

#include "fases/fase2/mouse_fase2.h"
#include "fases/fase2/tiros_fase2.h"

#pragma endregion

#include "fases/fase2/soldado_fase2.h"

SOLDADO soldado;
bool movimentou;
short frame_move_inimigo;

float soldado_cx;
float soldado_cy;

void soldado_init()
{
	soldado.sprite = CIMA;
	soldado.x = round_float((CANVAS_W / 2) - (SOLDADOS_W / 2), 1);
	soldado.y = round_float((CANVAS_H / 2) - (SOLDADOS_H / 2), 1);
	soldado.max_x = (CANVAS_W - SOLDADOS_W);
	soldado.max_y = (CANVAS_H - SOLDADOS_H);
	soldado.tiro_timer = 0;
	soldado.frame = 0;
	soldado.vidas = 3;
	soldado.respawn_timer = 0;
	soldado.invencivel_timer = 120;

	movimentou = false;
	soldado_cx = 0.0f;
	soldado_cy = 0.0f;
}

void soldado_update()
{
	if (soldado.vidas <= 0)
		return;

	if (soldado.respawn_timer > 0)
	{
		soldado.respawn_timer--;
		return;
	}

	// Vai calcular qual é o sprite
	calcular_sprite(soldado.x, soldado.y, mira_x, mira_y, &soldado.sprite);	

	if (tecla[ALLEGRO_KEY_A])
	{
		soldado.x -= SOLDADO_SPEED;
		movimentou = true;
		soldado.frame++;
	}

	if (tecla[ALLEGRO_KEY_D])
	{
		soldado.x += SOLDADO_SPEED;
		movimentou = true;
		soldado.frame++;
	}

	if (tecla[ALLEGRO_KEY_W])
	{
		soldado.y -= SOLDADO_SPEED;
		movimentou = true;
		soldado.frame++;
	}

	if (tecla[ALLEGRO_KEY_S])
	{
		soldado.y += SOLDADO_SPEED;
		movimentou = true;
		soldado.frame++;
	}


	if (soldado.x < 0)
		soldado.x = 0;
	if (soldado.y < 0)
		soldado.y = 0;

	// Limite do soldado na tela
	soldado.max_x = (CANVAS_W - SOLDADOS_W);

	if (soldado.x > soldado.max_x)
		soldado.x = soldado.max_x;
	if (soldado.y > soldado.max_y)
		soldado.y = soldado.max_y;

	if (soldado.invencivel_timer)
	{
		soldado.invencivel_timer--;
	}
	else
	{
		if (tiros_collide(true, soldado.x, soldado.y, SOLDADOS_W, SOLDADOS_H))
		{						
			soldado.vidas--;
			soldado.respawn_timer = 90;
			soldado.invencivel_timer = 180;
			soldado.frame = 0;
		}
	}

	if (soldado.tiro_timer)
		soldado.tiro_timer--;
	else if (al_mouse_button_down(&mouse_state, 1))
	{
		soldado_cx = 0.0f;
		soldado_cy = 0.0f;

		switch (soldado.sprite)
		{
		case CIMA:
			soldado_cx = soldado.x + 3.5;
			soldado_cy = soldado.y + 9;
			break;
		case BAIXO:
			soldado_cx = (soldado.x + SOLDADOS_W) - 9;
			soldado_cy = soldado.y + SOLDADOS_H;
			break;
		case DIREITA:
			soldado_cx = soldado.x + SOLDADOS_W + 2;
			soldado_cy = soldado.y + (SOLDADOS_H / 1.6);
			break;
		case ESQUERDA:
			soldado_cx = soldado.x;
			soldado_cy = soldado.y + (SOLDADOS_H / 1.6);
			break;
		}

		if (disparar(true, false, soldado_cx, soldado_cy, mira_x, mira_y, 4.5))
		{
			soldado.tiro_timer = 15;
		}

	}
}

void soldado_draw()
{
	if (soldado.vidas < 0)
		return;
	if (soldado.respawn_timer)
		return;
	if (((soldado.invencivel_timer / 2) % 3) == 1)
		return;	

	if (movimentou)
	{		
		frame_move_inimigo = (soldado.frame / 2) % 2;
		al_draw_bitmap(sprites_soldado.soldado[soldado.sprite][frame_move_inimigo], soldado.x, soldado.y, 0);

	}
	else
	{
		al_draw_bitmap(sprites_soldado.soldado[soldado.sprite][0], soldado.x, soldado.y, 0);
		soldado.frame = 0;
	}

	movimentou = false;

}