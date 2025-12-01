#ifndef TELA_MENU_H
#define TELA_MENU_H

#include "main.h"

typedef struct {
	const char* texto;
	float x;
	float y;
} BotoesConfig;

typedef enum {
	NOVO_JOGO,
	CONTINUAR,
	OPCOES,
	SAIR,
	BOTOES_N
} BOTOES;

typedef struct {	
	const char* titulo;
	const char* subtitulo;			
} MenuContext;

void tela_menu(GameContext* ctx);

#endif // !TELA_MENU_H

