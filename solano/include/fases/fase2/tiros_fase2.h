#ifndef TIROS_FASE2_H
#define TIROS_FASE2_H

#include <allegro5/allegro5.h>

typedef struct TIRO {
	float x, y, dx, dy;
	int frame;
	bool soldado;
	bool usado;
} TIRO;

#define TIROS_N 128
extern TIRO tiros[TIROS_N];

void tiro_init();
bool disparar(bool soldado, bool reto, float x, float y, float mira_x, float mira_y);
void tiros_update();
bool tiros_collide(bool soldado, int x, int y, int w, int h);
void tiros_draw();

#endif

