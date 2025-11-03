#ifndef SPRITES_SOLDADOS_H
#define SPRITES_SOLDADOS_H

typedef struct SPRITES_SOLDADOS {
	ALLEGRO_BITMAP* _tutorial_sheet;
	ALLEGRO_BITMAP* _soldados_sheet;	

	ALLEGRO_BITMAP* soldado[4];
	ALLEGRO_BITMAP* soldado_tiros[3];	
	
	ALLEGRO_BITMAP* vida;

	ALLEGRO_BITMAP* inimigo[4];
	ALLEGRO_BITMAP* inimigo_tiros[3];
	ALLEGRO_BITMAP* inimigo_tiro;
	/*
		ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
		ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

		ALLEGRO_BITMAP* powerup[4];
	*/
} SPRITES_SOLDADOS;

typedef enum {
	CIMA,
	BAIXO,
	ESQUERDA,
	DIREITA
} DIR_SOLDADO;

// Declaração externa da variável global
extern SPRITES_SOLDADOS sprites;

void sprites_soldados_init();

void sprites_soldados_deinit();

#endif

