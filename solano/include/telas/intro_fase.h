#ifndef INTRO_FASE_H
#define INTRO_FASE_H


typedef struct {
	const char* texto;
	float x;
	float y;
	ALLEGRO_COLOR cor;
} TextosConfigsIntro;

typedef enum {
	_FASE1 = 1,
	_FASE2, 
	_FASE3, 
	_FASE4, 	
	_FASE5, 	
	_FASES_N
} FASES_INTRO;

void intro_fase(GameContext* ctx, int fase_selected);

#endif
