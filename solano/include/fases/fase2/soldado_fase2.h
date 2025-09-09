#ifndef SOLDADO_FASE2_H
#define SOLDADO_FASE2_H

#define SOLDADO_SPEED		3
#define SOLDADO_MAX_X (CANVAS_W - SOLDADO_W)
#define SOLDADO_MAX_Y (CANVAS_H - SOLDADO_H)

typedef struct SOLDADO
{
	int x, y;
	int tiro_timer;
	int vidas;
	int respawn_timer;
	int invencivel_timer;
} SOLDADO;
extern SOLDADO soldado;

void soldado_init();
void soldado_update();
void soldado_draw();

#endif
