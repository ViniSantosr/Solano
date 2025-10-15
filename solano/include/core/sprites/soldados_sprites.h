#ifndef SPRITES_SOLDADOS_H
#define SPRITES_SOLDADOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct SPRITES_SOLDADOS {
	ALLEGRO_BITMAP* _tutorial_sheet;
	ALLEGRO_BITMAP* _soldados_sheet;	

	ALLEGRO_BITMAP* soldado;
	ALLEGRO_BITMAP* soldado_tiros[2];
	ALLEGRO_BITMAP* vida;


	ALLEGRO_BITMAP* inimigo[3];
	ALLEGRO_BITMAP* inimigo_tiro;
	/*
		ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
		ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

		ALLEGRO_BITMAP* powerup[4];
	*/
} SPRITES_SOLDADOS;

// Declaração externa da variável global
extern SPRITES_SOLDADOS sprites;

void sprites_soldados_init();

void sprites_soldados_deinit();

#endif

