#include <allegro5/allegro.h>          // Funções gerais do Allegro
#include <allegro5/allegro_image.h>    // Carregar bitmaps, al_load_bitmap, al_create_sub_bitmap
#include <stdio.h>                      // printf
#include <stdlib.h>                     // exit
#include "fases/fase2/coisas_gerais_fase2.h"            // must_init e funções/utilitários gerais
#include "core/sprites/sprites_fase2.h"
#include "main.h"

ALLEGRO_BITMAP* cortar_sprites(int x, int y, int w, int h)// aqui temos o sprite grab, essa função recebe o X e Y, W e H das constantes e recorta o do spritesheet
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites_n._sheet, x, y, w, h);//função responsavel por recortar o sprite e atribuir a um mini bitmap
    must_init(sprite, "sprite grab");//inicializa o sprite recortado a fim de verificar se está tudo em ordem!
    return sprite;//estando tudo ok, ele retorna o sprite recortado!
}

void iniciar_sprites()//aqui temos a função que inicializa todos os sprites
{
    sprites_n._sheet = al_load_bitmap("assets/images/spritesheet.png");
    must_init(sprites_n._sheet, "spritesheet");

    sprites_n.ship = cortar_sprites(0, 0, SHIP_W, SHIP_H);

    sprites_n.ship_shot[0] = cortar_sprites(13, 0, SHIP_SHOT_W, SHIP_SHOT_H);//apesar de já ter sido explicado anteriormente, aqui temos a função sprite_grab sendo usada para recortar o sprite
    sprites_n.ship_shot[1] = cortar_sprites(16, 0, SHIP_SHOT_W, SHIP_SHOT_H);//e atribuindo ao struct na posição referente ao sprite recortado, bem simples de entender mas importante se recordar sempre!!

    sprites_n.life = cortar_sprites(0, 14, LIFE_W, LIFE_H);

    sprites_n.alien[0] = cortar_sprites(19, 0, ALIEN_BUG_W, ALIEN_BUG_H);
    sprites_n.alien[1] = cortar_sprites(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H);
    sprites_n.alien[2] = cortar_sprites(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);

    sprites_n.alien_shot = cortar_sprites(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H);

    sprites_n.explosion[0] = cortar_sprites(33, 10, 9, 9);
    sprites_n.explosion[1] = cortar_sprites(43, 9, 11, 11);
    sprites_n.explosion[2] = cortar_sprites(46, 21, 17, 18);
    sprites_n.explosion[3] = cortar_sprites(46, 40, 17, 17);

    sprites_n.sparks[0] = cortar_sprites(34, 0, 10, 8);
    sprites_n.sparks[1] = cortar_sprites(45, 0, 7, 8);
    sprites_n.sparks[2] = cortar_sprites(54, 0, 9, 8);

    sprites_n.powerup[0] = cortar_sprites(0, 49, 9, 12);
    sprites_n.powerup[1] = cortar_sprites(10, 49, 9, 12);
    sprites_n.powerup[2] = cortar_sprites(20, 49, 9, 12);
    sprites_n.powerup[3] = cortar_sprites(30, 49, 9, 12);
}

void destruir_sprites()//destrói os sprites após o fim do jogo
{
    al_destroy_bitmap(sprites_n.ship);

    al_destroy_bitmap(sprites_n.ship_shot[0]);
    al_destroy_bitmap(sprites_n.ship_shot[1]);

    al_destroy_bitmap(sprites_n.life);

    al_destroy_bitmap(sprites_n.alien[0]);
    al_destroy_bitmap(sprites_n.alien[1]);
    al_destroy_bitmap(sprites_n.alien[2]);

    al_destroy_bitmap(sprites_n.alien_shot);

    al_destroy_bitmap(sprites_n.explosion[0]);
    al_destroy_bitmap(sprites_n.explosion[1]);
    al_destroy_bitmap(sprites_n.explosion[2]);
    al_destroy_bitmap(sprites_n.explosion[3]);

    al_destroy_bitmap(sprites_n.sparks[0]);
    al_destroy_bitmap(sprites_n.sparks[1]);
    al_destroy_bitmap(sprites_n.sparks[2]);

    al_destroy_bitmap(sprites_n.powerup[0]);
    al_destroy_bitmap(sprites_n.powerup[1]);
    al_destroy_bitmap(sprites_n.powerup[2]);
    al_destroy_bitmap(sprites_n.powerup[3]);

    al_destroy_bitmap(sprites_n._sheet);
}
