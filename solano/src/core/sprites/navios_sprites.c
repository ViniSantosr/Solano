
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/navios_sprites.h"

SPRITES_NAVIOS sprites;

void sprites_navios_init()
{
	sprites._navios_sheet = al_load_bitmap("assets/images/spritesheets/navios_spritesheet.png");
	must_init(sprites._navios_sheet, "_navios_sheet");

	sprites.navio = sprite_grab(sprites._navios_sheet, 0, 0, NAVIO_W, NAVIO_H);
}

void sprites_navios_deinit()
{
	al_destroy_bitmap(sprites.navio);

	al_destroy_bitmap(sprites._navios_sheet);
}

