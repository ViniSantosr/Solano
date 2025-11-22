#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

typedef struct {
    ALLEGRO_COLOR verde;
    ALLEGRO_COLOR verde_opaco;
    ALLEGRO_COLOR amarelo;
    ALLEGRO_COLOR branco;
    ALLEGRO_COLOR preto;
    ALLEGRO_COLOR cinza_opaco;
    ALLEGRO_COLOR cinza_medium;
    ALLEGRO_COLOR vermelho;
    ALLEGRO_COLOR azul;
    ALLEGRO_COLOR azul_claro;
    ALLEGRO_COLOR azul_escuro;
} CORES;

typedef struct {
    ALLEGRO_FONT* font_small;
    ALLEGRO_FONT* font_medium;
    ALLEGRO_FONT* font_big;
    ALLEGRO_FONT* font_titulo;
    ALLEGRO_FONT* font_subtitulo;
} FONTS;

typedef struct {
    ALLEGRO_MIXER* mixer;
    ALLEGRO_SAMPLE_INSTANCE* gun_shot;
    ALLEGRO_SAMPLE_INSTANCE* voice;
    ALLEGRO_SAMPLE_INSTANCE* text_bip;
    ALLEGRO_SAMPLE_INSTANCE* typing;
    ALLEGRO_SAMPLE_INSTANCE* click;
    ALLEGRO_AUDIO_STREAM* music;
    float volume_general;
    float volume_music;
    float volume_effects;
} SONS;


// Enum de telas
typedef enum {
    TELA_MENU,
    FASE1,
    FASE2,
    FASE3,
    FASE4,   
    INTRO_FASE,
    CUTSCENE
} TELAS_PRINCIPAIS;

// Struct 
typedef struct GameContext {
    bool exit_program;
    bool play_music;
    bool pause;
    bool options;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* tela;		    // Monitor do jogador
    ALLEGRO_BITMAP* canvas;		    // Quadro/Bitmap onde o jogo vai ser desenhado
    ALLEGRO_TRANSFORM transform;	// Responsável por redimensionar a tela
    ALLEGRO_BITMAP* background;

    TELAS_PRINCIPAIS estado_tela;
    int proxima_fase;
    int cena_atual;
    CORES cores;
    FONTS fonts;
    SONS sons;
} GameContext;

extern GameContext ctx;

#endif 

