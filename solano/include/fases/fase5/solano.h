#ifndef SOLANO_H
#define SOLANO_H

#define SOLANO_SPEED		1.5

typedef struct SOLANO
{
	float x, y;
	int max_x, max_y;	
	long frame;
	int sprite;
	int tiro_timer;
	int atirar_timer;	
	int vidas;
	int dano;
	int respawn_timer;
	int move_timer;		
	int parado;
	int invencivel_timer;
} SOLANO;

extern SOLANO solano;

void solano_init();
void solano_update(bool* concluido);
void solano_draw(GameContext* ctx);

#endif
