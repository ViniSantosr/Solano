
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#pragma endregion

#pragma region Headers Game
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/sprites_util.h"

SPRITES_UTIL sprites_util;


void sprites_util_init()
{
	sprites_util._spritesheet_util = al_load_bitmap("assets/images/spritesheets/spritesheet_util.png");
	must_init(sprites_util._spritesheet_util, "_spritesheet_util");

	sprites_util.desmute = sprite_grab(sprites_util._spritesheet_util, 0, 0, DESMUTE_W, DESMUTE_H);
	sprites_util.mute = sprite_grab(sprites_util._spritesheet_util, 0, 31, MUTE_W, MUTE_H);
}


void sprites_util_deinit()
{
	al_destroy_bitmap(sprites_util.desmute);
	al_destroy_bitmap(sprites_util.mute);
}