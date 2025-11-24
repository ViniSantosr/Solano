#ifndef SPRITES_SOLDADOS_H
#define SPRITES_SOLDADOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#pragma region Dimensions

#define SOLDADOS_H	43

#define SOLDADOS_W	35

#define INIMIGO_H 43

extern const int INIMIGO_W[];

#define SOLDADO_TIRO_W	5
#define SOLDADO_TIRO_H	9

#define VIDA_W 13
#define VIDA_H 12

#define MIRA_W 24
#define MIRA_H 24

#define INIMIGO_TIRO_W	5
#define INIMIGO_TIRO_H	9

#pragma endregion

typedef struct SPRITES_SOLDADOS {
	/*ALLEGRO_BITMAP* _tutorial_sheet;*/
	ALLEGRO_BITMAP* _soldados_sheet;	

	ALLEGRO_BITMAP* soldado[4][2]; // [direção][frame]
	ALLEGRO_BITMAP* soldado_tiros[3];	
	
	ALLEGRO_BITMAP* vida;
	ALLEGRO_BITMAP* mira;

	ALLEGRO_BITMAP* inimigo[4][2]; // [direção][frame]
	ALLEGRO_BITMAP* inimigo_tiros[3];

	ALLEGRO_BITMAP* solano[4][2]; // [direção][frame]
	ALLEGRO_BITMAP* vida_boss;
	
	/*
		ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
		ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

		ALLEGRO_BITMAP* powerup[4];
	*/
} SPRITES_SOLDADOS;

typedef enum {
	ESQUERDA,
	CIMA,
	DIREITA,
	BAIXO
} DIR_SOLDADO;

// Declaração externa da variável global
extern SPRITES_SOLDADOS sprites_soldado;

void sprites_soldados_init();

void sprites_soldados_deinit();

#endif

