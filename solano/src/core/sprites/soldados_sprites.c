
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/soldados_sprites.h"

const int INIMIGO_W[] = { 35, 32, 33, 35 };

SPRITES_SOLDADOS sprites_soldado;

void sprites_soldados_init()
{	
	sprites_soldado._soldados_sheet = al_load_bitmap("assets/images/spritesheets/soldados_spritesheet.png");		
	must_init(sprites_soldado._soldados_sheet, "_soldados_sheet");	

	// 0: 0, 0
	// 1: 0, 44
	sprites_soldado.soldado[ESQUERDA][0] = sprite_grab(sprites_soldado._soldados_sheet, 0, 0, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.soldado[ESQUERDA][1] = sprite_grab(sprites_soldado._soldados_sheet, 0, 44, SOLDADOS_W, SOLDADOS_H);


	// 0: 36, 0
	// 1: 36, 44
	sprites_soldado.soldado[CIMA][0] = sprite_grab(sprites_soldado._soldados_sheet, 36, 0, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.soldado[CIMA][1] = sprite_grab(sprites_soldado._soldados_sheet, 36, 44, SOLDADOS_W, SOLDADOS_H);


	// 0: 72, 0
	// 1: 72, 44
	sprites_soldado.soldado[DIREITA][0] = sprite_grab(sprites_soldado._soldados_sheet, 72, 0, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.soldado[DIREITA][1] = sprite_grab(sprites_soldado._soldados_sheet, 72, 44, SOLDADOS_W, SOLDADOS_H);

	// 0: 108, 0
	// 1: 108, 44
	sprites_soldado.soldado[BAIXO][0] = sprite_grab(sprites_soldado._soldados_sheet, 108, 0, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.soldado[BAIXO][1] = sprite_grab(sprites_soldado._soldados_sheet, 108, 44, SOLDADOS_W, SOLDADOS_H);

	

	sprites_soldado.vida = sprite_grab(sprites_soldado._soldados_sheet, 148, 0, VIDA_W, VIDA_H);
	sprites_soldado.mira = sprite_grab(sprites_soldado._soldados_sheet, 162, 50, MIRA_W, MIRA_H);


	// ---- INIMIGOS ------

	// 0: 0, 89
	// 1: 0, 134
	sprites_soldado.inimigo[ESQUERDA][0] = sprite_grab(sprites_soldado._soldados_sheet, 0, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.inimigo[ESQUERDA][1] = sprite_grab(sprites_soldado._soldados_sheet, 0, 134, SOLDADOS_W, SOLDADOS_H);


	// 0: 36, 89
	// 1: 36, 134
	sprites_soldado.inimigo[CIMA][0] = sprite_grab(sprites_soldado._soldados_sheet, 36, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.inimigo[CIMA][1] = sprite_grab(sprites_soldado._soldados_sheet, 36, 134, SOLDADOS_W, SOLDADOS_H);


	// 0: 72, 89
	// 1: 72, 134
	sprites_soldado.inimigo[DIREITA][0] = sprite_grab(sprites_soldado._soldados_sheet, 72, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.inimigo[DIREITA][1] = sprite_grab(sprites_soldado._soldados_sheet, 72, 134, SOLDADOS_W, SOLDADOS_H);

	// 0: 108, 89
	// 1: 108, 134
	sprites_soldado.inimigo[BAIXO][0] = sprite_grab(sprites_soldado._soldados_sheet, 108, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.inimigo[BAIXO][1] = sprite_grab(sprites_soldado._soldados_sheet, 108, 134, SOLDADOS_W, SOLDADOS_H);


	// ----- TIROS ------

	sprites_soldado.soldado_tiros[0] = sprite_grab(sprites_soldado._soldados_sheet, 147, 19, SOLDADO_TIRO_W, 13);
	sprites_soldado.soldado_tiros[1] = sprite_grab(sprites_soldado._soldados_sheet, 154, 19, SOLDADO_TIRO_W, 15);
	sprites_soldado.soldado_tiros[2] = sprite_grab(sprites_soldado._soldados_sheet, 160, 19, SOLDADO_TIRO_W, SOLDADO_TIRO_H);


	sprites_soldado.inimigo_tiros[0] = sprite_grab(sprites_soldado._soldados_sheet, 147, 36, INIMIGO_TIRO_W, 13);
	sprites_soldado.inimigo_tiros[1] = sprite_grab(sprites_soldado._soldados_sheet, 154, 36, INIMIGO_TIRO_W, 15);
	sprites_soldado.inimigo_tiros[2] = sprite_grab(sprites_soldado._soldados_sheet, 160, 36, INIMIGO_TIRO_W, SOLDADO_TIRO_H);	

	/*
	sprites_soldado.explosion[0] = sprite_grab(33, 10, 9, 9);
	sprites_soldado.explosion[1] = sprite_grab(43, 9, 11, 11);
	sprites_soldado.explosion[2] = sprite_grab(46, 21, 17, 18);
	sprites_soldado.explosion[3] = sprite_grab(46, 40, 17, 17);

	sprites_soldado.sparks[0] = sprite_grab(34, 0, 10, 8);
	sprites_soldado.sparks[1] = sprite_grab(45, 0, 7, 8);
	sprites_soldado.sparks[2] = sprite_grab(54, 0, 9, 8);

	sprites_soldado.powerup[0] = sprite_grab(0, 49, 9, 12);
	sprites_soldado.powerup[1] = sprite_grab(10, 49, 9, 12);
	sprites_soldado.powerup[2] = sprite_grab(20, 49, 9, 12);
	sprites_soldado.powerup[3] = sprite_grab(30, 49, 9, 12);
	*/
}

void sprites_soldados_deinit()
{
	al_destroy_bitmap(sprites_soldado.soldado[CIMA][0]);
	al_destroy_bitmap(sprites_soldado.soldado[CIMA][1]);

	al_destroy_bitmap(sprites_soldado.soldado[BAIXO][0]);
	al_destroy_bitmap(sprites_soldado.soldado[BAIXO][1]);

	al_destroy_bitmap(sprites_soldado.soldado[ESQUERDA][0]);
	al_destroy_bitmap(sprites_soldado.soldado[ESQUERDA][1]);

	al_destroy_bitmap(sprites_soldado.soldado[DIREITA][0]);
	al_destroy_bitmap(sprites_soldado.soldado[DIREITA][1]);

	al_destroy_bitmap(sprites_soldado.soldado_tiros[0]);
	al_destroy_bitmap(sprites_soldado.soldado_tiros[1]);

	al_destroy_bitmap(sprites_soldado.vida);
	al_destroy_bitmap(sprites_soldado.mira);


	al_destroy_bitmap(sprites_soldado.inimigo[CIMA][0]);
	al_destroy_bitmap(sprites_soldado.inimigo[CIMA][1]);

	al_destroy_bitmap(sprites_soldado.inimigo[BAIXO][0]);
	al_destroy_bitmap(sprites_soldado.inimigo[BAIXO][1]);

	al_destroy_bitmap(sprites_soldado.inimigo[ESQUERDA][0]);
	al_destroy_bitmap(sprites_soldado.inimigo[ESQUERDA][1]);

	al_destroy_bitmap(sprites_soldado.inimigo[DIREITA][0]);
	al_destroy_bitmap(sprites_soldado.inimigo[DIREITA][1]);	

	/*
	al_destroy_bitmap(sprites_soldado.explosion[0]);
	al_destroy_bitmap(sprites_soldado.explosion[1]);
	al_destroy_bitmap(sprites_soldado.explosion[2]);
	al_destroy_bitmap(sprites_soldado.explosion[3]);

	al_destroy_bitmap(sprites_soldado.sparks[0]);
	al_destroy_bitmap(sprites_soldado.sparks[1]);
	al_destroy_bitmap(sprites_soldado.sparks[2]);

	al_destroy_bitmap(sprites_soldado.powerup[0]);
	al_destroy_bitmap(sprites_soldado.powerup[1]);
	al_destroy_bitmap(sprites_soldado.powerup[2]);
	al_destroy_bitmap(sprites_soldado.powerup[3]);
	*/


	/*al_destroy_bitmap(sprites_soldado._tutorial_sheet);*/
	al_destroy_bitmap(sprites_soldado._soldados_sheet);	
}