#ifndef NAVIOS_SPRITES_H
#define NAVIOS_SPRITES_H

#pragma region Dimensions

#define NAVIO_W	32
#define NAVIO_H	89

#define	TIRO_W 5
#define TIRO_H 6

#define	INIMIGO_TIRO_W_H 5


extern const int NAVIOS_INIMIGO_W[];// neste caso, como temos 3 categorias diferentes de Aliens, definimos um array que guarda a altura e largura de cada um dentro do spritesheet
extern const int NAVIOS_INIMIGO_H[];

#define BARCO_INIMIGO_W      NAVIOS_INIMIGO_W[0]//aqui definimos as constantes de cada alien, e atribuimos o valor de acordo com o a posição do array acima!
#define BARCO_INIMIGO_H      NAVIOS_INIMIGO_H[0]

#define NAVIO_INIMIGO_W NAVIOS_INIMIGO_W[1]
#define NAVIO_INIMIGO_H NAVIOS_INIMIGO_H[1]

#pragma endregion

typedef struct SPRITES_NAVIOS {
	ALLEGRO_BITMAP* _navios_sheet;
	
	ALLEGRO_BITMAP* tiro;	
	ALLEGRO_BITMAP* tiro_inimigo;
	ALLEGRO_BITMAP* navio;
		
} SPRITES_NAVIOS;

typedef struct ship_animation {
	int frame;           // frame atual
	int frame_count;     // quantos frames existem
	int frame_delay;     // quantos ticks esperar antes de trocar o frame
	int frame_timer;     // contador interno
	int frame_w;         // largura de um frame
	int frame_h;   
	int start_x;      // posição inicial X no spritesheet
	int start_y;      // posição inicial Y no spritesheet
}ship_animation;

// Declaração externa da variável global
extern SPRITES_NAVIOS sprites_navios;

extern ship_animation alien_bug_anim;
extern ship_animation alien_arrow_anim;
extern ship_animation alien_thicc_anim;


void sprites_navios_init();

void sprites_navios_deinit();

#endif
