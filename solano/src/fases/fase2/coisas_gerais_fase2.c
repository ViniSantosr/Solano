#include <allegro5/allegro5.h>
#include <math.h>

#include "fases/fase2/coisas_gerais_fase2.h"

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

bool collide(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2)
{
	if (ax1 > bx2) return false;
	if (ax2 < bx1) return false;
	if (ay1 > by2) return false;
	if (ay2 < by1) return false;

	return true;
}

void calcular_direcao(bool jogador, float origem_x, float origem_y, float alvo_x, float alvo_y, float* dx, float* dy, float vel)
{
	if (jogador)
	{
		float dirx = origem_x - alvo_x;
		float diry = origem_y - alvo_y;
		float dist = sqrt(dirx * dirx + diry * diry);

		if (dist != 0) {
			*dx = (dirx / dist) * vel;
			*dy = (diry / dist) * vel;
		}
		else {
			*dx = 0;
			*dy = 0;
		}
	}
	else
	{
		float dirx = alvo_x - origem_x; // Calcula a distância dos inimigos até o soldado no eixo X
		float diry = alvo_y - origem_y; // Calcula a distância dos inimigos até o soldado no eixo Y
		float dist = sqrt(dirx * dirx + diry * diry); // Calcula a distância dos inimigos até o soldado no eixo diagonal, que seria a distância real

		*dx = (dirx / dist) * vel; // Calcula quanto o inimigo deve se mover no eixo X
		*dy = (diry / dist) * vel; // Calcula quanto o inimigo deve se mover no eixo Y
	}

}