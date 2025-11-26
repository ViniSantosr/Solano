
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/navios_sprites.h"

SPRITES_NAVIOS sprites_navios;

void sprites_navios_init()
{
	sprites_navios._navios_sheet = al_load_bitmap("assets/images/spritesheets/navios_spritesheet2.png");
	must_init(sprites_navios._navios_sheet, "_navios_sheet");

	sprites_navios.navio = sprite_grab(sprites_navios._navios_sheet, 290, 5, NAVIO_W, NAVIO_H);
	must_init(sprites_navios.navio, "navio_sprite");

	sprites_navios.shots = sprite_grab(sprites_navios._navios_sheet, 381, 415, SHOT_W, SHOT_H);
	must_init(sprites_navios.navio, "shot_sprite");


}

void sprites_navios_deinit()
{
	al_destroy_bitmap(sprites_navios.navio);
	al_destroy_bitmap(sprites_navios.shots);

	al_destroy_bitmap(sprites_navios._navios_sheet);
}

