#ifndef FASE2_H
#define FASE2_H

typedef struct Fase2Context
{
	long frames;
	int frames_iniciais;
	long score;

	// Condições da fase
	bool game_over;
	bool pause;
	bool concluido;
	bool exit_tela;	

	ALLEGRO_BITMAP* background;
} Fase2Context;

extern Fase2Context f2_ctx;

void fase2(GameContext* ctx);

#endif
