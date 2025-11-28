
#pragma region Biblitotecas Externas
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/funcoes_auxiliares.h"
#pragma endregion

#include "core/sprites/navios_sprites.h"
#include "fases/fase1/inimigos_fase1.h"  

SPRITES_NAVIOS sprites_navios;



//#define ALIEN_BUG_W      ALIEN_W[0]//aqui definimos as constantes de cada alien, e atribuimos o valor de acordo com o a posição do array acima!
//#define ALIEN_BUG_H      ALIEN_H[0]
//#define ALIEN_ARROW_W    ALIEN_W[1]
//#define ALIEN_ARROW_H    ALIEN_H[1]
//#define ALIEN_THICCBOI_W ALIEN_W[2]
//#define ALIEN_THICCBOI_H ALIEN_H[2]

const int ALIEN_W[] = { 31, 31, 45 };
const int ALIEN_H[] = { 55, 89, 128 };

void sprites_navios_init()
{

	sprites_navios._navios_sheet = al_load_bitmap("assets/images/spritesheets/navios_spritesheet.png");
	must_init(sprites_navios._navios_sheet, "_navios_sheet");

	sprites_navios.navio = sprite_grab(sprites_navios._navios_sheet, 290, 5, NAVIO_W, NAVIO_H);
	must_init(sprites_navios.navio, "navio_sprite");

	sprites_navios.shots = sprite_grab(sprites_navios._navios_sheet, 381, 415, SHOT_W, SHOT_H);
	must_init(sprites_navios.navio, "shot_sprite");

	sprites_navios.alien[0] = sprite_grab(sprites_navios._navios_sheet, 344, 1, ALIEN_BUG_W, ALIEN_BUG_H);
	must_init(sprites_navios.navio, "bug_sprite");

	sprites_navios.alien[1] = sprite_grab(sprites_navios._navios_sheet, 0, 279, ALIEN_ARROW_W, ALIEN_ARROW_H);
	must_init(sprites_navios.navio, "bug_sprite");

	sprites_navios.alien[2] = sprite_grab(sprites_navios._navios_sheet, 501, 537, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);
	must_init(sprites_navios.navio, "bug_sprite");
}

void sprites_navios_deinit()
{
	al_destroy_bitmap(sprites_navios.navio);
	al_destroy_bitmap(sprites_navios.shots);

	al_destroy_bitmap(sprites_navios._navios_sheet);
}

void navios_draw()// essa função desenha os aliens na tela
{
	for (int i = 0; i < ALIENS_N; i++)
	{
		if (!aliens[i].used)//se não estiver em uso pula pro proximo indice 'i'
			continue;
		if (aliens[i].blink > 2)//se estiver piscando por dano, pula o desenho do alien
			continue;



		al_draw_bitmap(sprites_navios.alien[aliens[i].type], aliens[i].x, aliens[i].y, 0);//se passar pelas duas verificações então ele desenha o alien na tela
	}
}

