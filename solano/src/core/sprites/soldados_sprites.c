
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "configs/sprites/soldados_dimensions.h"
#include "core/sprites/soldados_sprites.h"

const int SOLDADO_W[] = { 34, 32, 33, 35 };

const int INIMIGO_W[] = { 34, 32, 33, 35 };

SPRITES_SOLDADOS sprites;

void sprites_soldados_init()
{
	sprites._tutorial_sheet = al_load_bitmap("assets/images/spritesheets/tutorial_spritesheet.png");
	sprites._soldados_sheet = al_load_bitmap("assets/images/spritesheets/soldados_spritesheet.png");	
	must_init(sprites._tutorial_sheet, "_tutorial_sheet");
	must_init(sprites._soldados_sheet, "_soldados_sheet");	

	sprites.soldado[CIMA] = sprite_grab(sprites._soldados_sheet, 36, 45, INIMIGO_W[CIMA], INIMIGO_H);
	sprites.soldado[BAIXO] = sprite_grab(sprites._soldados_sheet, 109, 45, INIMIGO_W[BAIXO], INIMIGO_H);
	sprites.soldado[ESQUERDA] = sprite_grab(sprites._soldados_sheet, 0, 45, INIMIGO_W[ESQUERDA], INIMIGO_H);
	sprites.soldado[DIREITA] = sprite_grab(sprites._soldados_sheet, 72, 45, INIMIGO_W[DIREITA], INIMIGO_H);	

	sprites.soldado_tiros[0] = sprite_grab(sprites._soldados_sheet, 147, 19, SOLDADO_TIRO_W, 13);
	sprites.soldado_tiros[1] = sprite_grab(sprites._soldados_sheet, 154, 19, SOLDADO_TIRO_W, 15);
	sprites.soldado_tiros[2] = sprite_grab(sprites._soldados_sheet, 160, 19, SOLDADO_TIRO_W, SOLDADO_TIRO_H);

	sprites.vida = sprite_grab(sprites._soldados_sheet, 148, 0, VIDA_W, VIDA_H);
	sprites.mira = sprite_grab(sprites._soldados_sheet, 168, 56, MIRA_W, MIRA_H);

	sprites.inimigo[CIMA] = sprite_grab(sprites._soldados_sheet, 36, 0, SOLDADO_W[CIMA], SOLDADO_H);
	sprites.inimigo[BAIXO] = sprite_grab(sprites._soldados_sheet, 109, 0, SOLDADO_W[BAIXO], SOLDADO_H);
	sprites.inimigo[ESQUERDA] = sprite_grab(sprites._soldados_sheet, 0, 0, SOLDADO_W[ESQUERDA], SOLDADO_H);
	sprites.inimigo[DIREITA] = sprite_grab(sprites._soldados_sheet, 72, 0, SOLDADO_W[DIREITA], SOLDADO_H);

	sprites.inimigo_tiros[0] = sprite_grab(sprites._soldados_sheet, 147, 36, INIMIGO_TIRO_W, 13);
	sprites.inimigo_tiros[1] = sprite_grab(sprites._soldados_sheet, 154, 36, INIMIGO_TIRO_W, 15);
	sprites.inimigo_tiros[2] = sprite_grab(sprites._soldados_sheet, 160, 36, INIMIGO_TIRO_W, SOLDADO_TIRO_H);

	sprites.inimigo_tiro = sprite_grab(sprites._tutorial_sheet, 13, 10, INIMIGO_TIRO_W, INIMIGO_TIRO_H);

	/*
	sprites.explosion[0] = sprite_grab(33, 10, 9, 9);
	sprites.explosion[1] = sprite_grab(43, 9, 11, 11);
	sprites.explosion[2] = sprite_grab(46, 21, 17, 18);
	sprites.explosion[3] = sprite_grab(46, 40, 17, 17);

	sprites.sparks[0] = sprite_grab(34, 0, 10, 8);
	sprites.sparks[1] = sprite_grab(45, 0, 7, 8);
	sprites.sparks[2] = sprite_grab(54, 0, 9, 8);

	sprites.powerup[0] = sprite_grab(0, 49, 9, 12);
	sprites.powerup[1] = sprite_grab(10, 49, 9, 12);
	sprites.powerup[2] = sprite_grab(20, 49, 9, 12);
	sprites.powerup[3] = sprite_grab(30, 49, 9, 12);
	*/
}

void sprites_soldados_deinit()
{
	al_destroy_bitmap(sprites.soldado[CIMA]);
	al_destroy_bitmap(sprites.soldado[BAIXO]);
	al_destroy_bitmap(sprites.soldado[ESQUERDA]);
	al_destroy_bitmap(sprites.soldado[DIREITA]);

	al_destroy_bitmap(sprites.soldado_tiros[0]);
	al_destroy_bitmap(sprites.soldado_tiros[1]);

	al_destroy_bitmap(sprites.vida);
	al_destroy_bitmap(sprites.mira);
	
	al_destroy_bitmap(sprites.inimigo[0]);
	al_destroy_bitmap(sprites.inimigo[1]);
	al_destroy_bitmap(sprites.inimigo[2]);

	al_destroy_bitmap(sprites.inimigo_tiro);

	/*
	al_destroy_bitmap(sprites.explosion[0]);
	al_destroy_bitmap(sprites.explosion[1]);
	al_destroy_bitmap(sprites.explosion[2]);
	al_destroy_bitmap(sprites.explosion[3]);

	al_destroy_bitmap(sprites.sparks[0]);
	al_destroy_bitmap(sprites.sparks[1]);
	al_destroy_bitmap(sprites.sparks[2]);

	al_destroy_bitmap(sprites.powerup[0]);
	al_destroy_bitmap(sprites.powerup[1]);
	al_destroy_bitmap(sprites.powerup[2]);
	al_destroy_bitmap(sprites.powerup[3]);
	*/


	al_destroy_bitmap(sprites._tutorial_sheet);
	al_destroy_bitmap(sprites._soldados_sheet);	
}