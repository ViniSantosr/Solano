#ifndef TIROS_FASE1_H
#define TIROS_FASE1_H

#include <stdbool.h>

typedef struct SHOT//struct onde definiremos todas os atributos do tiro!!
{
	int x, y, dx, dy;//posição X e Y do tiro, e a velocidade em X e Y
	int frame;
	bool ship;//se for true o tiro vem da Nave, se for false o tiro vem do alien
	bool used;//indica se o tiro está em uso ou não
} SHOT;

#define SHOTS_N 128//nos define 128 tiros
extern SHOT shots[SHOTS_N];//criamos um array para guardar os 128 tiros

void shots_init();
bool shots_add(bool ship, bool straight, int x, int y);
void shots_update();
bool shots_collide(bool enemy, int x, int y, int w, int h);
void shots_draw();

#endif