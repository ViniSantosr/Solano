#ifndef COISAS_GERAIS_FASE2_H
#define COISAS_GERAIS_FASE2_H

#include <allegro5/allegro5.h>

extern long frames;
extern long score;

int between(int lo, int hi);
float between_f(float lo, float hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

#endif
