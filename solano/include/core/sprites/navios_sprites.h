#ifndef NAVIOS_SOLDADOS_H
#define NAVIOS_SOLDADOS_H

#pragma region Dimensions

#define NAVIO_W	46
#define NAVIO_H	128

#pragma endregion

typedef struct SPRITES_NAVIOS {	
	ALLEGRO_BITMAP* _navios_sheet;

	ALLEGRO_BITMAP* navio;
	
} SPRITES_NAVIOS;

// Declaração externa da variável global
extern SPRITES_NAVIOS sprites_navios;

void sprites_navios_init();

void sprites_navios_deinit();

#endif
