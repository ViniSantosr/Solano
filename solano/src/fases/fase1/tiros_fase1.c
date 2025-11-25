#include <stdbool.h>        // Para o tipo bool
#include "fases/fase2/coisas_gerais_fase2.h"   // Para funções utilitárias como between() e collide()
#include "core/sprites/sprites_fase2.h"        // Para os sprites de tiros
#include "core/Efeitos/efeito_gerais.h"       // Para fx_add()
#include "fases/fase1/tiros_fase1.h"        
//#include "efeitos.c"
#include "core/tela_utils.h"
#include <allegro5/allegro_audio.h>

void shots_init()// inicializa os tiros e coloca todas suas posições como ainda não utilizados
{
    for (int i = 0; i < SHOTS_N; i++)
        shots[i].used = false;
}

bool shots_add(bool ship, bool straight, int x, int y)//essa função adiciona o tiro na tela
{
    //al_play_sample(
    //    sample_shot,
    //    0.3,
    //    0,
    //    ship ? 1.0 : between_f(1.5, 1.6),
    //    ALLEGRO_PLAYMODE_ONCE,
    //    NULL
    //);//a primeira coisa que a função faz é tocar o som do tiro, mudando ligeiramente se for do Alien ou da Nave

    for (int i = 0; i < SHOTS_N; i++)
    {
        if (shots[i].used)//se a posição já tiver sido usada ele pula para o próximo indice 'i'
            continue;

        shots[i].ship = ship;

        if (ship)//se o tiro vier da nave ele seguira em linha reta para cima
        {
            shots[i].x = x - (SHIP_SHOT_W / 2);
            shots[i].y = y;
        }
        else // alien
        {
            shots[i].x = x - (ALIEN_SHOT_W / 2);
            shots[i].y = y - (ALIEN_SHOT_H / 2);

            if (straight)//se vier do alien e for reto, ele descerá em linha reta pode ser em outras direções conforme o else abaixo
            {
                shots[i].dx = 0;
                shots[i].dy = 2;
            }
            else
            {

                shots[i].dx = between(-2, 2);
                shots[i].dy = between(-2, 2);
            }

            // if the shot has no speed, don't bother
            if (!shots[i].dx && !shots[i].dy)
                return true;

            shots[i].frame = 0;
        }

        shots[i].frame = 0;
        shots[i].used = true;

        return true;
    }
    return false;
}

void shots_update()//essa função serve para efetivamente atualizar a posição dos tiros na tela
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!shots[i].used)
            continue;

        if (shots[i].ship)//se o tiro for da nave sobre 5 pixels por execução em linha reta
        {
            shots[i].y -= 5;

            if (shots[i].y < -SHIP_SHOT_H)//se o tiro sair da tela ele já termina a execução e libera a posição
            {
                shots[i].used = false;
                continue;
            }
        }
        else // alien
        {
            shots[i].x += shots[i].dx;
            shots[i].y += shots[i].dy;

            if ((shots[i].x < -ALIEN_SHOT_W)//verifica se o tiro saiu da tela
                || (shots[i].x > CANVAS_W)
                || (shots[i].y < -ALIEN_SHOT_H)
                || (shots[i].y > CANVAS_H)
                ) {
                shots[i].used = false;
                continue;
            }
        }

        shots[i].frame++;
    }
}

bool shots_collide(bool ship, int x, int y, int w, int h)//a verificação desta função é responsavel por detectar se o tiro colidiu em algo
{
    for (int i = 0; i < SHOTS_N; i++)//percorre todos os tiros
    {
        if (!shots[i].used)//se o tiro não estiver em uso ele pula para o próximo
            continue;

        if (shots[i].ship == ship)
            continue;

        int sw, sh;//define uma variavel que será a altura e largura do tiro dependendo se for do alien ou da nave
        if (ship)
        {
            sw = ALIEN_SHOT_W;
            sh = ALIEN_SHOT_H;
        }
        else
        {
            sw = SHIP_SHOT_W;
            sh = SHIP_SHOT_H;
        }

        if (collide(x, y, x + w, y + h, shots[i].x, shots[i].y, shots[i].x + sw, shots[i].y + sh))//faz a verificação de colisão do tiro com o objeto
        {
            fx_add(true, shots[i].x + (sw / 2), shots[i].y + (sh / 2));
            shots[i].used = false;
            return true;
        }
    }

    return false;
}

void shots_draw()// função responsavel por desenhar os diversos tiros na tela
{
    for (int i = 0; i < SHOTS_N; i++)
    {
        if (!shots[i].used)
            continue;

        int frame_display = (shots[i].frame / 2) % 2;

        if (shots[i].ship)
            al_draw_bitmap(sprites_n.ship_shot[frame_display], shots[i].x, shots[i].y, 0);// se o tiro vier da nava ele desenha o sprite do tiro da nave
        else // alien
        {
            ALLEGRO_COLOR tint =//não entendi direto, irei perguntar depois
                frame_display
                ? al_map_rgb_f(1, 1, 1)
                : al_map_rgb_f(0.5, 0.5, 0.5)
                ;
            al_draw_tinted_bitmap(sprites_n.alien_shot, tint, shots[i].x, shots[i].y, 0);
        }
    }
}

