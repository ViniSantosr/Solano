#ifndef GLOBALS_H
#define GLOBALS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

typedef struct CORES {
    ALLEGRO_COLOR verde;
    ALLEGRO_COLOR amarelo;
    ALLEGRO_COLOR branco;
    ALLEGRO_COLOR preto;
} CORES;

// Enum de telas
typedef enum {
    TELA_MENU,
    FASE1,
    FASE2,
    FASE3,
    FASE4,
    FASE5
} TELAS;

// Struct 
typedef struct GameContext {
    TELAS estado_tela;
    bool exit_program;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* font_titulo;
    ALLEGRO_FONT* font_subtitulo;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* tela;		    // Monitor do jogador
    ALLEGRO_BITMAP* canvas;		    // Quadro/Bitmap onde o jogo vai ser desenhado
    ALLEGRO_TRANSFORM transform;	// Responsável por redimensionar a tela
    ALLEGRO_BITMAP* background_menu;
    CORES cores;
} GameContext;

extern GameContext ctx;

void must_init(bool test, const char* description);
ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);

#endif // !GLOBALS_H

