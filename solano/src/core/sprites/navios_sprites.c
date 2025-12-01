
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/navios_sprites.h"

SPRITES_NAVIOS sprites_navios;

const int NAVIOS_INIMIGO_W[] = { 31, 31 };
const int NAVIOS_INIMIGO_H[] = { 55, 89 };

void sprites_navios_init()
{

	sprites_navios._navios_sheet = al_load_bitmap("assets/images/spritesheets/navios_spritesheet.png");
	must_init(sprites_navios._navios_sheet, "_navios_sheet");	

	sprites_navios.tiro = sprite_grab(sprites_navios._navios_sheet, 314, 436, TIRO_W, TIRO_H);
	must_init(sprites_navios.tiro, "shot_sprite");	

	sprites_navios.navio = sprite_grab(sprites_navios._navios_sheet, 290, 5, NAVIO_W, NAVIO_H);
	must_init(sprites_navios.navio, "navio_sprite");

	sprites_navios.tiro_inimigo = sprite_grab(sprites_navios._navios_sheet, 381, 415, INIMIGO_TIRO_W_H, INIMIGO_TIRO_W_H);	
	must_init(sprites_navios.tiro_inimigo, "tiro_inimigo_sprite");
}

void sprites_navios_deinit()
{	
	al_destroy_bitmap(sprites_navios.tiro);	
	al_destroy_bitmap(sprites_navios.tiro_inimigo);
	al_destroy_bitmap(sprites_navios.navio);

	al_destroy_bitmap(sprites_navios._navios_sheet);
}

