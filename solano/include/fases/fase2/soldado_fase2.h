#ifndef SOLDADO_FASE2_H
#define SOLDADO_FASE2_H

#define SOLDADO_SPEED		1.5

typedef struct SOLDADO
{
	float x, y;
	int max_x, max_y;	
	long frame;
	int sprite;
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
