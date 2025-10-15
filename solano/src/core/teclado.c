
#pragma region Biblitotecas Externas
	#include <allegro5/allegro5.h>
#pragma endregion

#include "core/teclado.h"

unsigned char tecla[ALLEGRO_KEY_MAX]; // Um array que armazena todos os tipos de tecla

void teclado_init() // Inicializa o array zerando todos as teclas com '0'
{
	memset(tecla, 0, sizeof(tecla));
}

void teclado_update(ALLEGRO_EVENT* event) // Vai atualizar os estados(valores) das teclas a cada frame
{
	switch (event->type)
	{
	case ALLEGRO_EVENT_TIMER:
		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
			tecla[i] &= ~TECLA_REGISTRADA;
		break;

	case ALLEGRO_EVENT_KEY_DOWN:
		tecla[event->keyboard.keycode] = TECLA_REGISTRADA | TECLA_PRESSIONADA;
		break;

	case ALLEGRO_EVENT_KEY_UP:
		tecla[event->keyboard.keycode] &= ~TECLA_PRESSIONADA;
		break;
	}
}

