#ifndef GLOBALS_H
#define GLOBALS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// Enum de telas
typedef enum TELAS {
    TELA_MENU,
    FASE1,
    FASE2
} TELAS;

// Struct 
typedef struct {
    TELAS estado_tela;
    bool exit_program;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_FONT* font;
    ALLEGRO_TIMER* timer;
} GameContext;

extern GameContext ctx;

#endif // !GLOBALS_H

