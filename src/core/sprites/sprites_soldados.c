#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "core/sprites/sprites_soldados.h"

#include "configs/sprites/config_sprites_soldados.h"
#include "core/must_init.h"

const int INIMIGO_W[] = { 14, 13, 45 };
const int INIMIGO_H[] = { 9, 10, 27 };

SPRITES sprites;

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
	must_init(sprite, "sprite grab");
	return sprite;
}

void sprites_init()
{
	sprites._sheet = al_load_bitmap("assets/images/spritesheet.png");
	must_init(sprites._sheet, "spritesheet");

	sprites.soldado = sprite_grab(0, 0, SOLDADO_W, SOLDADO_H);

	sprites.soldado_tiros[0] = sprite_grab(13, 0, SOLDADO_TIRO_W, SOLDADO_TIRO_H);
	sprites.soldado_tiros[1] = sprite_grab(16, 0, SOLDADO_TIRO_W, SOLDADO_TIRO_H);

	sprites.vida = sprite_grab(0, 14, VIDA_W, VIDA_H);

	sprites.inimigo[0] = sprite_grab(19, 0, INIMIGO_MENOR_W, INIMIGO_MENOR_H);
	sprites.inimigo[1] = sprite_grab(19, 10, INIMIGO_ESPADA_W, INIMIGO_ESPADA_H);
	sprites.inimigo[2] = sprite_grab(0, 21, INIMIGO_SNIPER_W, INIMIGO_SNIPER_H);

	sprites.inimigo_tiro = sprite_grab(13, 10, INIMIGO_TIRO_W, INIMIGO_TIRO_H);

	/*
	sprites.explosion[0] = sprite_grab(33, 10, 9, 9);
	sprites.explosion[1] = sprite_grab(43, 9, 11, 11);
	sprites.explosion[2] = sprite_grab(46, 21, 17, 18);
	sprites.explosion[3] = sprite_grab(46, 40, 17, 17);

	sprites.sparks[0] = sprite_grab(34, 0, 10, 8);
	sprites.sparks[1] = sprite_grab(45, 0, 7, 8);
	sprites.sparks[2] = sprite_grab(54, 0, 9, 8);

	sprites.powerup[0] = sprite_grab(0, 49, 9, 12);
	sprites.powerup[1] = sprite_grab(10, 49, 9, 12);
	sprites.powerup[2] = sprite_grab(20, 49, 9, 12);
	sprites.powerup[3] = sprite_grab(30, 49, 9, 12);
*/
}

void sprites_deinit()
{
	al_destroy_bitmap(sprites.soldado);

	al_destroy_bitmap(sprites.soldado_tiros[0]);
	al_destroy_bitmap(sprites.soldado_tiros[1]);

	al_destroy_bitmap(sprites.vida);
	
	al_destroy_bitmap(sprites.inimigo[0]);
	al_destroy_bitmap(sprites.inimigo[1]);
	al_destroy_bitmap(sprites.inimigo[2]);

	al_destroy_bitmap(sprites.inimigo_tiro);

	/*
	al_destroy_bitmap(sprites.explosion[0]);
	al_destroy_bitmap(sprites.explosion[1]);
	al_destroy_bitmap(sprites.explosion[2]);
	al_destroy_bitmap(sprites.explosion[3]);

	al_destroy_bitmap(sprites.sparks[0]);
	al_destroy_bitmap(sprites.sparks[1]);
	al_destroy_bitmap(sprites.sparks[2]);

	al_destroy_bitmap(sprites.powerup[0]);
	al_destroy_bitmap(sprites.powerup[1]);
	al_destroy_bitmap(sprites.powerup[2]);
	al_destroy_bitmap(sprites.powerup[3]);
	*/


	al_destroy_bitmap(sprites._sheet);
}