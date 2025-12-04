
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
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

	// ----- SOLANO ------

	// 0: 144, 89
	// 1: 144, 134 
	sprites_soldado.solano[ESQUERDA][0] = sprite_grab(sprites_soldado._soldados_sheet, 144, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.solano[ESQUERDA][1] = sprite_grab(sprites_soldado._soldados_sheet, 144, 134, SOLDADOS_W, SOLDADOS_H);


	// 0: 180, 89
	// 1: 180, 134
	sprites_soldado.solano[CIMA][0] = sprite_grab(sprites_soldado._soldados_sheet, 180, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.solano[CIMA][1] = sprite_grab(sprites_soldado._soldados_sheet, 180, 134, SOLDADOS_W, SOLDADOS_H);


	// 0: 219, 89
	// 1: 219, 134
	sprites_soldado.solano[DIREITA][0] = sprite_grab(sprites_soldado._soldados_sheet, 219, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.solano[DIREITA][1] = sprite_grab(sprites_soldado._soldados_sheet, 219, 134, SOLDADOS_W, SOLDADOS_H);

	// 0: 256, 89
	// 1: 256, 134
	sprites_soldado.solano[BAIXO][0] = sprite_grab(sprites_soldado._soldados_sheet, 256, 89, SOLDADOS_W, SOLDADOS_H);
	sprites_soldado.solano[BAIXO][1] = sprite_grab(sprites_soldado._soldados_sheet, 256, 134, SOLDADOS_W, SOLDADOS_H);
		
	sprites_soldado.vida_boss = sprite_grab(sprites_soldado._soldados_sheet, 200, 70, 7, 7);


	// ----- EXTRAS ------
	sprites_soldado.jovem[0] = sprite_grab(sprites_soldado._soldados_sheet, 42, 182, JOVEM_W, JOVEM_H);
	sprites_soldado.jovem[1] = sprite_grab(sprites_soldado._soldados_sheet, 75, 182, JOVEM_W, JOVEM_H);

	sprites_soldado.soldado_loiro = sprite_grab(sprites_soldado._soldados_sheet, 7, 182, 27, 40);
	sprites_soldado.soldado_moreno = sprite_grab(sprites_soldado._soldados_sheet, 110, 182, 30, 40);

	sprites_soldado.livro = sprite_grab(sprites_soldado._soldados_sheet, 176, 198, LIVRO_W, LIVRO_H);
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

	al_destroy_bitmap(sprites_soldado.solano[CIMA][0]);
	al_destroy_bitmap(sprites_soldado.solano[CIMA][1]);

	al_destroy_bitmap(sprites_soldado.solano[BAIXO][0]);
	al_destroy_bitmap(sprites_soldado.solano[BAIXO][1]);

	al_destroy_bitmap(sprites_soldado.solano[ESQUERDA][0]);
	al_destroy_bitmap(sprites_soldado.solano[ESQUERDA][1]);

	al_destroy_bitmap(sprites_soldado.solano[DIREITA][0]);
	al_destroy_bitmap(sprites_soldado.solano[DIREITA][1]);
	
	al_destroy_bitmap(sprites_soldado._soldados_sheet);	
}