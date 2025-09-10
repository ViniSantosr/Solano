#include "fases/fase2/inimigos_fase2.h"

#include "configs/sprites/config_sprites_soldados.h"
#include "core/sprites/sprites_soldados.h"
#include "configs/config_tela.h"
#include "fases/fase2/coisas_gerais_fase2.h"

INIMIGO inimigos[INIMIGOS_N];

void inimigo_init()
{
	for (int i = 0; i < INIMIGOS_N; i++)
	{
		inimigos[i].usado = false;
	}
}

void inimigo_add()
{
}

void inimigo_update()
{
	int nova_onda = (frames % 120) ? 0 : between(2, 4); // A cada 120 frames, será gerado uma nova onda, dá para melhorar isso?
	int new_x = between(-60, CANVAS_W + 120); // Posição aleatória dos inimigos no eixo x


	for (int i = 0; i < INIMIGOS_N; i++)
	{
		if (!inimigos[i].usado)
		{
			if (nova_onda > 0)
			{
				new_x += between(40, 80);
				if (new_x > CANVAS_W + 60)
					new_x -= CANVAS_W + 60;

				inimigos[i].x = new_x;

				inimigos[i].y = between(-40, -60);
				inimigos[i].tipo = between(0, INIMIGO_TIPO_N);
				inimigos[i].tiro_timer = 0;

			}
		}
	}
}

void inimigo_draw()
{

}




