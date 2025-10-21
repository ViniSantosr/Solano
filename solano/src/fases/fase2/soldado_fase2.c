
#pragma region Bibliotecas Externas
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#pragma endregion

#pragma region Headers Game

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
	soldado.x = (CANVAS_W / 2) - (SOLDADO_W[CIMA] / 2);
	soldado.y = (CANVAS_H / 2) - (SOLDADO_H / 2);
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

	// Vetores que indicam a distância do soldado em relação ao mouse
	float vx = mira_x - soldado.x;
	float vy = mira_y - soldado.y;

	double angulo = atan2(vy, vx);
	angulo = angulo * (180 / M_PI);

	if (angulo < 0) angulo += 360;

	if (angulo >= 45 && angulo < 135) {
		soldado.sprite = BAIXO;
	}
	else if (angulo >= 135 && angulo < 225) {
		soldado.sprite = ESQUERDA;
	}
	else if (angulo >= 225 && angulo < 315) {
		soldado.sprite = CIMA;
	}
	else {
		soldado.sprite = DIREITA;
	}	
	
	soldado.max_x = (CANVAS_W - SOLDADO_W[soldado.sprite]);
	soldado.w = soldado.x + SOLDADO_W[soldado.sprite];

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
		printf("W0 - Collide(Tiro): %d\n", SOLDADO_W[soldado.sprite]);
		if (tiros_collide(true, soldado.x, soldado.y, SOLDADO_W[soldado.sprite], SOLDADO_H))
		{
			float cx = soldado.x + (SOLDADO_W[soldado.sprite] / 2);
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
		float cx = soldado.x + (SOLDADO_W[soldado.sprite] / 2);
		if (disparar(true, false, cx, soldado.y, mira_x, mira_y, 4.5))
			soldado.tiro_timer = 10;
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

	
	al_draw_filled_rectangle(soldado.x, soldado.y, soldado.x + 5, soldado.y + 5, al_map_rgb(255, 0, 0));

	al_draw_bitmap(sprites.soldado[soldado.sprite], soldado.x, soldado.y, 0);
}