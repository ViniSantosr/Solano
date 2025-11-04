#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct {
    ALLEGRO_COLOR verde;
    ALLEGRO_COLOR amarelo;
    ALLEGRO_COLOR branco;
    ALLEGRO_COLOR preto;
    ALLEGRO_COLOR vermelho;
} CORES;

typedef struct {
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* font_size2;
    ALLEGRO_FONT* font_fases;
    ALLEGRO_FONT* font_titulo;
    ALLEGRO_FONT* font_subtitulo;
} FONTS;

typedef struct {
    ALLEGRO_MIXER* mixer;
    ALLEGRO_SAMPLE* gun_shot;
    ALLEGRO_AUDIO_STREAM* music;
} SONS;

// Enum de telas
typedef enum {
    TELA_MENU,
    FASE1,
    FASE2,
    FASE3,
    FASE4,
    FASE5,
    INTRO_FASE
} TELAS;

// Struct 
typedef struct {    
    bool exit_program;
    ALLEGRO_EVENT_QUEUE* queue;    
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* tela;		    // Monitor do jogador
    ALLEGRO_BITMAP* canvas;		    // Quadro/Bitmap onde o jogo vai ser desenhado
    ALLEGRO_TRANSFORM transform;	// Responsável por redimensionar a tela
    ALLEGRO_BITMAP* background;

    TELAS estado_tela;
    int fase_intro;
    CORES cores;
    FONTS fonts;
    SONS sons;
} GameContext;

extern GameContext ctx;

#endif // !GLOBALS_H

