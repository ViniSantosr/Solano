#ifndef HUD_FASE1_H
#define HUD_FASE1_H

#include <allegro5/allegro_font.h>

ALLEGRO_FONT* font;
extern long score_display;

void iniciar_hud();
void hud_deinit();
void atualizar_hud();
void desenhar_hud(GameContext* ctx);


#endif // !

