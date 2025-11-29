
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
#include "fases/fase1/fase1.h"
#include "core/Efeitos/efeito_gerais.h"

SPRITES_NAVIOS sprites_navios;

FONTS fonts;

//#define ALIEN_BUG_W      ALIEN_W[0]//aqui definimos as constantes de cada alien, e atribuimos o valor de acordo com o a posição do array acima!
//#define ALIEN_BUG_H      ALIEN_H[0]
//#define ALIEN_ARROW_W    ALIEN_W[1]
//#define ALIEN_ARROW_H    ALIEN_H[1]
//#define ALIEN_THICCBOI_W ALIEN_W[2]
//#define ALIEN_THICCBOI_H ALIEN_H[2]

const int ALIEN_W[] = { 31, 31, 45 };
const int ALIEN_H[] = { 55, 89, 128 };

extern SPRITES_NAVIOS sprites_navios;  
//static int ship_anim_start_x = 0; // X inicial do primeiro frame do ship no _navios_sheet
//static int ship_anim_start_y = 0; // Y inicial
//
//static ship_animation ship_anim;



void sprites_navios_init()
{

	sprites_navios._navios_sheet = al_load_bitmap("assets/images/spritesheets/navios_spritesheet.png");
	must_init(sprites_navios._navios_sheet, "_navios_sheet");

	sprites_navios.navio = sprite_grab(sprites_navios._navios_sheet, 290, 5, NAVIO_W, NAVIO_H);
	must_init(sprites_navios.navio, "navio_sprite");

	sprites_navios.shots = sprite_grab(sprites_navios._navios_sheet, 699, 594, SHOT_W, SHOT_H);
	must_init(sprites_navios.navio, "shot_sprite");

	sprites_navios.alien[0] = sprite_grab(sprites_navios._navios_sheet, 344, 1, ALIEN_BUG_W, ALIEN_BUG_H);
	must_init(sprites_navios.navio, "bug_sprite");

	sprites_navios.alien[1] = sprite_grab(sprites_navios._navios_sheet, 0, 279, ALIEN_ARROW_W, ALIEN_ARROW_H);
	must_init(sprites_navios.navio, "arrow_sprite");

	sprites_navios.alien[2] = sprite_grab(sprites_navios._navios_sheet, 501, 537, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);
	must_init(sprites_navios.navio, "thiccboi_sprite");

	sprites_navios.alien_shot = sprite_grab(sprites_navios._navios_sheet, 380, 415, SHOT_W, SHOT_H);

	sprites_navios.explosao[0] = sprite_grab(sprites_navios._navios_sheet, 628, 602, 13, 11);
	sprites_navios.explosao[1] = sprite_grab(sprites_navios._navios_sheet, 652, 616, 15, 13);
	sprites_navios.explosao[2] = sprite_grab(sprites_navios._navios_sheet, 648, 602, 15, 13);
	sprites_navios.explosao[3] = sprite_grab(sprites_navios._navios_sheet, 625, 614, 17, 16);

	//sprites_navios.fumaca[0] = sprite_grab(sprites_navios._navios_sheet, 0, 49, 9, 12);
	//sprites_navios.fumaca[1] = sprite_grab(sprites_navios._navios_sheet, 10, 49, 9, 12);
	//sprites_navios.fumaca[2] = sprite_grab(sprites_navios._navios_sheet, 20, 49, 9, 12);
	//sprites_navios.fumaca[3] = sprite_grab(sprites_navios._navios_sheet, 30, 49, 9, 12);
}

void sprites_navios_deinit()
{
	al_destroy_bitmap(sprites_navios.navio);
	al_destroy_bitmap(sprites_navios.shots);

	al_destroy_bitmap(sprites_navios._navios_sheet);
}

void navios_draw() {// essa função desenha os aliens na tela
	for (int i = 0; i < ALIENS_N; i++)
	{
		if (!aliens[i].used)
			continue;

		// ignorar se estiver piscando por dano
		if (aliens[i].blink > 2)
			continue;

		animar_alien* A = &aliens[i].anim;

		// calcula o frame atual dentro do spritesheet
		int src_x = A->start_x + A->frame * (A->frame_w + A->frame_spacing);
		int src_y = A->start_y;

		al_draw_bitmap_region(
			sprites_navios._navios_sheet,   // spritesheet dos navios/aliens
			src_x,                          // X da região (frame)
			src_y,                          // Y da região
			A->frame_w,                     // largura do frame
			A->frame_h,                     // altura do frame
			aliens[i].x,                    // posição X na tela
			aliens[i].y,                    // posição Y na tela
			0
		);
	}
}


	void fx_draw()//essa função é responsavel por desenhas o efeito na tela
	{
		for (int i = 0; i < FX_N; i++)
		{
			if (!fx[i].used)//se o efeito ainda não tiver sido usado ele pula para o próximo indice 'i'
				continue;

			int frame_display = fx[i].frame / 2;
			ALLEGRO_BITMAP* bmp =
				fx[i].spark//se spark for true o sprite usado será o de faísca, se não, o de explosão
				? sprites_navios.explosao[frame_display]
				: sprites_navios.explosao[frame_display]
				;

			int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);//centraliza o efeito na posição X e abaixo na posição Y
			int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
			al_draw_bitmap(bmp, x, y, 0);//desenha o bitmap na tela
			/*if(aliens->life[i] <= 0)
				al_draw_text(ctx.font_subtitulo, ctx.cores.preto, fx[i].x, fx[i].y, ALLEGRO_ALIGN_CENTER, "TEXT EXEMPLE TEST");*/

		}

		//for (int i = 0; i < ALIENS_N; i++)
		//{
		//	if (aliens[i].life <= 0 && aliens[i].y > 1) {
		//		if (*frames % 3) {
		//			if (aliens[i].type == 0) {
		//				al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "200");
		//			}
		//			if (aliens[i].type == 1) {
		//				al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "150");
		//			}
		//			if (aliens[i].type == 2) {
		//				al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "800");
		//			}
		//		}
		//	}
		//}
	}
