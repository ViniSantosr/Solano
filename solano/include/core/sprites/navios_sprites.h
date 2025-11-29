#ifndef NAVIOS_SPRITES_H
#define NAVIOS_SPRITES_H

#pragma region Dimensions

#define NAVIO_W	32
#define NAVIO_H	89

#define	SHOT_W 5
#define SHOT_H 5


extern const int ALIEN_W[];// neste caso, como temos 3 categorias diferentes de Aliens, definimos um array que guarda a altura e largura de cada um dentro do spritesheet
extern const int ALIEN_H[];

#define ALIEN_BUG_W      ALIEN_W[0]//aqui definimos as constantes de cada alien, e atribuimos o valor de acordo com o a posição do array acima!
#define ALIEN_BUG_H      ALIEN_H[0]
#define ALIEN_ARROW_W    ALIEN_W[1]
#define ALIEN_ARROW_H    ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#pragma endregion

typedef struct SPRITES_NAVIOS {
	ALLEGRO_BITMAP* _navios_sheet;

	ALLEGRO_BITMAP* navio;
	ALLEGRO_BITMAP* shots;

	ALLEGRO_BITMAP* alien[3];
	ALLEGRO_BITMAP* alien_shot;

	ALLEGRO_BITMAP* explosao[4];
	ALLEGRO_BITMAP* fumaca[4];

	ALLEGRO_BITMAP* alien_bug_frames[8];
	ALLEGRO_BITMAP* alien_arrow_frames[8];
	ALLEGRO_BITMAP* alien_thiccboi_frames[8];

	
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
