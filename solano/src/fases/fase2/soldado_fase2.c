
#pragma region Bibliotecas Externas
#include <math.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#pragma endregion

#pragma region Headers Game

#include "fases/fase2/coisas_gerais_fase2.h"

#include "configs/config_tela.h"
#include "configs/sprites/soldados_dimensions.h"

#include "core/sprites/soldados_sprites.h"
#include "core/teclado.h"
	
#include "fases/fase2/mouse_fase2.h"
#include "fases/fase2/tiros_fase2.h"

#pragma endregion

#include "fases/fase2/soldado_fase2.h"


SOLDADO soldado;

void soldado_init()
{
	soldado.sprite = CIMA;		
	soldado.x = round_float((CANVAS_W / 2) - (SOLDADO_W[CIMA] / 2), 1);
	soldado.y = round_float((CANVAS_H / 2) - (SOLDADO_H / 2), 1);
	soldado.max_y = (CANVAS_W - SOLDADO_H);
	soldado.tiro_timer = 0;
	soldado.vidas = 3;
	soldado.respawn_timer = 0;
	soldado.invencivel_timer = 120;
}

void soldado_update()
{
	if (soldado.vidas < 0)
		return;

	if (soldado.respawn_timer > 0)
	{
		soldado.respawn_timer--;
		return;
	}

	// Vai calcular qual é o sprite
	calcular_sprite(soldado.x, soldado.y, mira_x, mira_y, &soldado.sprite);
		
	soldado.w = soldado.x + SOLDADO_W[3];

	if (tecla[ALLEGRO_KEY_A])
		soldado.x -= SOLDADO_SPEED;
	if (tecla[ALLEGRO_KEY_D])
		soldado.x += SOLDADO_SPEED;
	if (tecla[ALLEGRO_KEY_W])
		soldado.y -= SOLDADO_SPEED;
	if (tecla[ALLEGRO_KEY_S])
		soldado.y += SOLDADO_SPEED;

	if (soldado.x < 0)
		soldado.x = 0;
	if (soldado.y < 0)
		soldado.y = 0;

	// Limite do soldado na tela
	soldado.max_x = (CANVAS_W - SOLDADO_W[3]);

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
		if (tiros_collide(true, soldado.x, soldado.y, SOLDADO_W[3], SOLDADO_H))
		{
			float cx = soldado.x + (SOLDADO_W[3] / 2);
			float cy = soldado.y + (SOLDADO_H / 2);
			/*fx_add(false, x, y);
			fx_add(false, x + 4, y + 2);
			fx_add(false, x - 2, y - 4);
			fx_add(false, x + 1, y - 5);*/

			soldado.vidas--;
			soldado.respawn_timer = 90;
			soldado.invencivel_timer = 180;
		}
	}

	if (soldado.tiro_timer)
		soldado.tiro_timer--;
	else if (al_mouse_button_down(&mouse_state, 1))
	{
		float cx = 0.0f;
		float cy = 0.0f;

		switch (soldado.sprite)
		{
		case CIMA:
			cx = soldado.x + 3.5;
			cy = soldado.y + 9;
			break;
		case BAIXO:
			cx = (soldado.x + SOLDADO_W[3]) - 9;
			cy = soldado.y + SOLDADO_H;
			break;
		case DIREITA:
			cx = soldado.x + SOLDADO_W[3] + 2;
			cy = soldado.y + (SOLDADO_H / 1.6);
			break;
		case ESQUERDA:
			cx = soldado.x;
			cy = soldado.y + (SOLDADO_H / 1.6);
			break;
		}

		if (disparar(true, false, cx, cy, mira_x, mira_y, 4.5))
			soldado.tiro_timer = 15;
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

	al_draw_bitmap(sprites.soldado[soldado.sprite], soldado.x, soldado.y, 0);
}