#ifndef SPRITE_FASE2_H
#define SPRITE_FASE2_H

#include <allegro5/allegro.h>
#include "fases/fase2/coisas_gerais_fase2.h"
#define SHIP_W 12// Longa explicação: no allegro para que possamos usar os sprites, temos que receber um spritesheet e recortalo manualmente a partir de seu X e Y e Largura e Altura
#define SHIP_H 13// por isso, definimos constantes de altura e largura de cada objeto do spritesheet, esse será um padrão para todos que tiverem um _H e _W

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

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

#define FRAMES_EXPLOSAO 4
#define FRAMES_RAIO    3

typedef struct SPRITES_N//nesse struct nós definimos todos os ponteiros sprites que mais para frente deverão receber o seu sprite recortado do spritesheet!!
{
    ALLEGRO_BITMAP* _sheet;

    ALLEGRO_BITMAP* ship;
    ALLEGRO_BITMAP* ship_shot[2];
    ALLEGRO_BITMAP* life;

    ALLEGRO_BITMAP* alien[3];
    ALLEGRO_BITMAP* alien_shot;

    ALLEGRO_BITMAP* explosion[FRAMES_EXPLOSAO];
    ALLEGRO_BITMAP* sparks[FRAMES_RAIO];

    ALLEGRO_BITMAP* powerup[4];
} SPRITES_N;

extern SPRITES_N sprites_n;

ALLEGRO_BITMAP* cortar_sprites(int x, int y, int w, int h);
void iniciar_sprites();
void destruir_sprites();



#endif 