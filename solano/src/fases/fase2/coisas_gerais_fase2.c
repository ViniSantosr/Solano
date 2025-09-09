
#include "fases/fase2/coisas_gerais_fase2.h"

#include <allegro5/allegro5.h>

long frames;
long score;

// Apenas uma função para gerar um número inteiro aleatório
int between(int lo, int hi)
{
	return lo + (rand() % (hi - lo));
}

// Apenas uma função para gerar um número de ponto flutuante aleatório
float between_f(float lo, float hi)
{
	return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{

	// (collide(x, y, x + w, y + h, shots[i].x, shots[i].y, shots[i].x + sw, shots[i].y + sh))
	if (ax1 > bx2) return false;
	if (ax2 < bx1) return false;
	if (ay1 > by2) return false;
	if (ay2 < by1) return false;

	return true;
}