
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "core/sprites/sprites_soldados.h"
#include "configs/sprites/config_sprites_soldados.h"
#include "core/must_init.h"

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

	// sprites.life = sprite_grab(0, 14, LIFE_W, LIFE_H);

	/*
		sprites.alien[0] = sprite_grab(19, 0, ALIEN_BUG_W, ALIEN_BUG_H);
		sprites.alien[1] = sprite_grab(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H);
		sprites.alien[2] = sprite_grab(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);

		sprites.alien_shot = sprite_grab(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H);

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

	// al_destroy_bitmap(sprites.life);


	/*
	al_destroy_bitmap(sprites.alien[0]);
	al_destroy_bitmap(sprites.alien[1]);
	al_destroy_bitmap(sprites.alien[2]);

	al_destroy_bitmap(sprites.alien_shot);

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