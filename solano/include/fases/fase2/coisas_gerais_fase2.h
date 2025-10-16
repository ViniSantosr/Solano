#ifndef COISAS_GERAIS_FASE2_H
#define COISAS_GERAIS_FASE2_H

#include <allegro5/allegro5.h>

int between(int lo, int hi);
float between_f(float lo, float hi);
bool collide(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2);
void calcular_direcao_vel(bool jogador, float origem_x, float origem_y, float alvo_x, float alvo_y, float* dx, float* dy, float vel);
#endif
