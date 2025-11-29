#include <allegro5/allegro.h>   // Funções básicas do Allegro
#include <stdbool.h>             // Para o tipo bool
#include "fases/fase2/coisas_gerais_fase2.h"       // Para frames, score, teclado, collide, etc.
//#include "core/sprites/sprites_fase2.h"             // Para sprites.ship
#include "fases/fase1/tiros_fase1.h"               // Para shots_add e shots_collide
#include "core/Efeitos/efeito_gerais.h"             // Para fx_add
#include "core/tela_utils.h"             // Para BUFFER_W, BUFFER_H
#include "fases/fase1/navio_fase1.h"          // Se você tiver constantes como SHIP_W, SHIP_H, SHIP_SPEED, SHIP_MAX_X/Y
#include "core/teclado.h"
#include "core/sprites/navios_sprites.h"

SPRITES_N sprites_n;// declara o struct de sprites para ser utilizado

void ship_init()//inicialização da nave, aqui definimos a posição inicial, o numero de vidas, e o tempo de invencibilidade
{
    ship.x = (CANVAS_W / 2) - (SHIP_W / 2);
    ship.y = (CANVAS_H / 1.25) - (SHIP_H / 2);
    ship.shot_timer = 0;
    ship.lives = 3;
    ship.respawn_timer = 0;
    ship.invincible_timer = 120;
}

void ship_update()// essa função será a responsavel por atualizar a posição da nave, vida e tiros constantemente
{

    if (ship.respawn_timer)//se estiver no tempo de respawn, diminui o tempo de respawn
    {
        ship.respawn_timer--;
        return;
    }

    if (tecla[ALLEGRO_KEY_LEFT])//movimentação para os lados
        ship.x -= SHIP_SPEED;
    if (tecla[ALLEGRO_KEY_RIGHT])
        ship.x += SHIP_SPEED;
    //if (key[ALLEGRO_KEY_UP])
        //ship.y -= SHIP_SPEED;
    //if (key[ALLEGRO_KEY_DOWN])
        //ship.y += SHIP_SPEED;

    if (ship.x > SHIP_MAX_X)//impede que a nave saia da tela
        ship.x = SHIP_MAX_X;

    if (ship.x < SHIP_MIN_X)//impede que a nave saia da tela
        ship.x = SHIP_MIN_X;

    if (ship.invincible_timer)//checa se a nave está invencivel, se estiver diminui o tempo de invencibilidade
        ship.invincible_timer--;
    else//se não estiver invencivel então verifica a colisão os os tiros
    {
        if (shots_collide(true, ship.x, ship.y, SHIP_W, SHIP_H))//se a colisão for verdadeira ele gera uma explosão, diminui uma vida e ativa o timer de respawn e invencibilidade
        {
            int x = ship.x + (SHIP_W / 2);
            int y = ship.y + (SHIP_H / 2);

            ship.lives--;
            ship.respawn_timer = 90;
            ship.invincible_timer = 180;
        }
    }

    if (ship.shot_timer)//se um tiro foi disparado ele diminui o timer de espera até o proximo tiro
        ship.shot_timer--;
    else if (tecla[ALLEGRO_KEY_X])//se você apertou o botão de tiro, ele seta o timer do tiro
    {
        int x = ship.x + (SHIP_W / 2);
        if (shots_add(true, false, x, ship.y))
            ship.shot_timer = 5;
    }
}

void ship_draw()//função responsavel por desenhar a nave na tela
{
    if (ship.lives < 0)//se estiver morto acaba a função
        return;
    if (ship.respawn_timer)//se estiver no tempo de respawn acaba a função
        return;
    if (((ship.invincible_timer / 2) % 3) == 1)// acabei me esquecendo o que faz
        return;


    al_draw_bitmap(sprites_navios.navio, ship.x, ship.y, 0);//se nenhum dos casos acima for verdadeiro então ele desenha a nave

}