#ifndef HUD_FASE2_H
#define HUD_FASE2_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "fases/fase2/fase2.h"

void hud_init();
void hud_update(Fase2Context* f2_ctx);
void hud_draw(ALLEGRO_FONT* font, Fase2Context* f2_ctx);

#endif
