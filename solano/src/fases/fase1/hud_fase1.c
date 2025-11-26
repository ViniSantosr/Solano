#include "core/tela_utils.h"
#include "core/sprites/sprites_fase2.h"  // para sprites.life
#include "fases/fase1/hud_fase1.h"      // declarações de font e score_display
#include "fases/fase2/coisas_gerais_fase2.h"     // para must_init()
#include "fases/fase1/navio_fase1.h" 
#include "main.h"
#include <fases/fase1/fase1.h>

Fase1Context f1_ctx;
long score_display;


void iniciar_hud()//inicia o hud 
{
    font = al_create_builtin_font();//cria a fonte padrão e tenta inicializa-la
    must_init(font, "test");

    score_display = 0;//seta o score como 0
}

void hud_deinit()//destroi o hud após a utilização
{
    al_destroy_font(font);
}

void atualizar_hud()//faz o update continuo do hud
{
    if (f1_ctx.frames % 2)//faz o update uma vez a cada frames % 2
        return;

    for (long i = 5; i > 0; i--)
    {
        long diff = 1 << i;//não entendi legal não, preciso perguntar depois
        if (score_display <= (f1_ctx.score - diff))
            score_display += diff;
    }
}

void desenhar_hud()//função responsavel por desenhar o hud na tela
{
    al_draw_textf(
        font,
        al_map_rgb_f(1, 1, 1),
        1, 1,
        0,
        "%06ld",
        score_display
    );

    int spacing = LIFE_W + 1;
    for (int i = 0; i < ship.lives; i++)
        al_draw_bitmap(sprites_n.life, 1 + (i * spacing), 10, 0);

    if (ship.lives < 0)
        al_draw_text(
            font,
            al_map_rgb_f(1, 1, 1),
            
            CANVAS_W / 2, CANVAS_H / 2,
            ALLEGRO_ALIGN_CENTER,
            "G A M E  O V E R"
        );
}
