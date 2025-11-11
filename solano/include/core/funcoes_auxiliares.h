#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "main.h"


void must_init(bool test, const char* description);
void switch_music(GameContext* ctx, ALLEGRO_AUDIO_STREAM* stream, const char* path);
ALLEGRO_BITMAP* switch_background(GameContext* ctx, ALLEGRO_BITMAP* old_background, const char* path);
ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);
void load_mute_bitmap(GameContext* ctx, float x, float y);

#endif