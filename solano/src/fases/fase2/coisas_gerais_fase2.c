
#pragma region Biblitotecas Externas
#define _USE_MATH_DEFINES
#include <allegro5/allegro5.h>
#include <math.h>
#pragma endregion

#pragma region Headers Game

#include "core/sprites/soldados_sprites.h"

#pragma endregion

#include "fases/fase2/coisas_gerais_fase2.h"

float round_float(float valor, int casas)
{
	return round(valor * pow(10, casas)) / pow(10, casas);
}

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

void calcular_direcao_vel(float x, float y, float alvo_x, float alvo_y, float* dx, float* dy, float vel)
{

	float dirx = round_float(x - alvo_x, 2); // Calcula a distância da origem até o alvo no eixo X
	float diry = round_float(y - alvo_y, 3); // Calcula a distância da origem até o alvo no eixo Y	

	float dist = sqrt(dirx * dirx + diry * diry); // Calcula a distância real da origem até o alvo na diagonal

	*dx = (dirx / dist) * vel; // Calcula quanto a origem deve se mover no eixo X
	*dy = (diry / dist) * vel; // Calcula quanto a origem deve se mover no eixo Y

	if (dist != 0)
	{
		*dx = round_float(((dirx / dist) * vel), 1);
		*dy = round_float(((diry / dist) * vel), 1);
	}
	else
	{
		*dx = 0;
		*dy = 0;
	}

}

void calcular_sprite(float x, float y, float alvo_x, float alvo_y, int* sprite)
{
	// Vetores que indicam a distância do soldado em relação ao mouse
	float vx = round_float(alvo_x - x, 1);
	float vy = round_float(alvo_y - y, 1);

	double angulo = atan2(vy, vx);
	angulo = angulo * (180 / M_PI); // Normaliza o ângulo

	if (angulo < 0) angulo += 360;

	if (angulo >= 45 && angulo < 135) {
		*sprite = BAIXO;
	}
	else if (angulo >= 135 && angulo < 225) {
		*sprite = ESQUERDA;
	}
	else if (angulo >= 225 && angulo < 315) {
		*sprite = CIMA;
	}
	else {
		*sprite = DIREITA;
	}
}