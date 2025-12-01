
#pragma region Biblitotecas Externas
#include <allegro5/allegro.h> 
#pragma endregion

#pragma region Headers Game
#include "core/tela_utils.h"             // Para BUFFER_W, BUFFER_H        
#include "core/teclado.h"
#include "core/sprites/navios_sprites.h"
#include "fases/fase1/tiros_fase1.h"
#pragma endregion


#include "fases/fase1/navio_fase1.h"  // Se você tiver constantes como SHIP_W, SHIP_H, SHIP_SPEED, SHIP_MAX_X/Y

ship_animation ship_anim;
NAVIO navio;

// Origem do sprite no spritesheet
int ship_anim_start_x;    // <-- X inicial do ship no sheet
int ship_anim_start_y;    // <-- Y inicial do ship no sheet

void navio_init() //inicialização da nave, aqui definimos a posição inicial, o numero de vidas, e o tempo de invencibilidade
{
    navio.x = (CANVAS_W / 2) - (NAVIO_W / 2);
    navio.y = (CANVAS_H / 1.25) - (NAVIO_W / 2);
    navio.shot_timer = 0;
    navio.lives = 3;
    navio.respawn_timer = 0;
    navio.invincible_timer = 120;

    ship_anim.frame = 0;

    // Quantos frames do ship existem na horizontal:
    ship_anim.frame_count = 4;  

    // Quantos ticks para trocar frame:
    ship_anim.frame_delay = 15;
    ship_anim.frame_timer = 0;

    // Largura e altura de CADA FRAME (em pixels)
    ship_anim.frame_w = 37;   //  tamanho real do ship
    ship_anim.frame_h = 88;   //

    //// Origem do sprite no spritesheet
    ship_anim_start_x = 176;    //  X inicial do ship no sheet
    ship_anim_start_y = 5;    //  Y inicial do ship no sheet

}

void navio_update()  // essa função será a responsavel por atualizar a posição da nave, vida e tiros constantemente
{

    if (navio.respawn_timer)//se estiver no tempo de respawn, diminui o tempo de respawn
    {
        navio.respawn_timer--;
        return;
    }

    if (tecla[ALLEGRO_KEY_LEFT])//movimentação para os lados
        navio.x -= SHIP_SPEED;
    if (tecla[ALLEGRO_KEY_RIGHT])
        navio.x += SHIP_SPEED;

    if (navio.x > SHIP_MAX_X)//impede que a nave saia da tela
        navio.x = SHIP_MAX_X;

    if (navio.x < SHIP_MIN_X)//impede que a nave saia da tela
        navio.x = SHIP_MIN_X;

    if (navio.invincible_timer)//checa se a nave está invencivel, se estiver diminui o tempo de invencibilidade
        navio.invincible_timer--;
    else//se não estiver invencivel então verifica a colisão os os tiros
    {
        if (shots_collide(true, navio.x, navio.y, NAVIO_W, NAVIO_H))//se a colisão for verdadeira ele gera uma explosão, diminui uma vida e ativa o timer de respawn e invencibilidade
        {
            int x = navio.x + (NAVIO_W / 2);
            int y = navio.y + (NAVIO_H / 2);

            navio.lives--;
            navio.respawn_timer = 90;
            navio.invincible_timer = 180;
        }
    }

    if (navio.shot_timer)//se um tiro foi disparado ele diminui o timer de espera até o proximo tiro
        navio.shot_timer--;
    else if (tecla[ALLEGRO_KEY_X])//se você apertou o botão de tiro, ele seta o timer do tiro
    {
        int x = navio.x + (NAVIO_W / 2);
        if (shots_add(true, false, x, navio.y))
            navio.shot_timer = 5;
    }

    ship_anim.frame_timer++;

    if (ship_anim.frame_timer >= ship_anim.frame_delay) {
        ship_anim.frame_timer = 0;

        ship_anim.frame++;
        if (ship_anim.frame >= ship_anim.frame_count)
            ship_anim.frame = 0;
    }

}

void navio_draw()//função responsavel por desenhar a nave na tela
{
    if (navio.lives < 0)//se estiver morto acaba a função
        return;
    if (navio.respawn_timer)//se estiver no tempo de respawn acaba a função
        return;
    if (((navio.invincible_timer / 2) % 3) == 1)// acabei me esquecendo o que faz
        return;

    int sx = ship_anim_start_x + (ship_anim.frame * ship_anim.frame_w);
    int sy = ship_anim_start_y;

    al_draw_bitmap_region(
        sprites_navios._navios_sheet,
        sx, sy,
        ship_anim.frame_w,
        ship_anim.frame_h,
        navio.x, navio.y,
        0
    );
}