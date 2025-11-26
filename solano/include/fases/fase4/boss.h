#ifndef BOSS_H
#define BOSS_H

#define BOSS_SPEED		1.5

typedef struct BOSS
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
} BOSS;

extern BOSS boss;

void boss_init();
void boss_update(bool* concluido);
void boss_draw(GameContext* ctx);

#endif
