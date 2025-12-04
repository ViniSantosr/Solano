
#pragma region Biblitotecas Externas
#include <stdbool.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#pragma endregion

#pragma region Headers Game
#include "main.h"
#include "core/sprites/sprites_util.h"
#pragma endregion

#include "core/funcoes_auxiliares.h"

void must_init(bool test, const char* description)
{
	if (test) return;

	fprintf(stderr, "Não pode ser inicializado: %s\n", description);
	exit(1);
}

ALLEGRO_AUDIO_STREAM* switch_music(GameContext* ctx, ALLEGRO_AUDIO_STREAM* old_stream, const char* path)
{
	// 1) pare e destrua o stream antigo, se houver
	if (old_stream) {
		al_set_audio_stream_playing(old_stream, false);    // pausa
		al_detach_audio_stream(old_stream);                // desanexa do mixer
		al_drain_audio_stream(old_stream);                 // espera encher/esvaziar buffers
		al_destroy_audio_stream(old_stream);               // destrói
		old_stream = NULL;
	}

	// 2) carregue o novo stream
	ALLEGRO_AUDIO_STREAM* new_stream = al_load_audio_stream(path, 4, 2048);
	if (!new_stream) {
		fprintf(stderr, "Erro: não foi possível carregar '%s'\n", path);
		return NULL;
	}

	// 3) configure e anexe
	al_set_audio_stream_playmode(new_stream, ALLEGRO_PLAYMODE_LOOP);
	al_set_audio_stream_gain(new_stream, 1.0f);
	if (!al_attach_audio_stream_to_mixer(new_stream, ctx->sons.mixer)) {
		fprintf(stderr, "Aviso: falha ao anexar stream ao mixer (verifique se o áudio está inicializado)\n");
		// ainda assim retornamos o stream para escolha do chamador
	}

	// 4) comece a tocar
	al_set_audio_stream_playing(new_stream, ctx->play_music);
	return new_stream;
}

ALLEGRO_BITMAP* switch_background(GameContext* ctx, ALLEGRO_BITMAP* old_background, const char* path)
{
	// 1) pare e destrua o stream antigo, se houver
	if (old_background) {
		al_destroy_bitmap(ctx->background);
		old_background = NULL;
	}

	// 2) carregue o novo stream
	ALLEGRO_BITMAP* new_background = al_load_bitmap(path);
	if (!new_background) {
		fprintf(stderr, "Erro: não foi possível carregar '%s'\n", path);
		return NULL;
	}

	return new_background;
}

ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h)
{
	ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
	must_init(sprite, "sprite grab");
	return sprite;
}

void load_mute_bitmap(GameContext* ctx, float x, float y)
{
	if (!ctx->play_music)
	{
		al_draw_bitmap(sprites_util.mute, x, y, 0);
	}
	else
	{
		al_draw_bitmap(sprites_util.desmute, x, y, 0);
	}
}