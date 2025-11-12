#ifndef SPRITES_UTIL_H
#define SPRITES_UTIL_H

#pragma region Dimensions

#define DESMUTE_W	25
#define DESMUTE_H	29

#define MUTE_W	25
#define MUTE_H	29

#pragma endregion

typedef struct {
	ALLEGRO_BITMAP* _spritesheet_util;

	ALLEGRO_BITMAP* mute;
	ALLEGRO_BITMAP* desmute;
} SPRITES_UTIL;

// Declaração externa da variável global
extern SPRITES_UTIL sprites_util;

void sprites_util_init();

void sprites_util_deinit();

#endif

