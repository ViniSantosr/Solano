#include <allegro5/allegro.h>          // Funções gerais do Allegro
#include <allegro5/allegro_audio.h>    // Funções de áudio do Allegro
#include <allegro5/allegro_acodec.h>   // Para carregar arquivos de áudio (.flac, .wav, etc)
#include <stdio.h>                      // printf
#include <stdlib.h>                     // exit
#include <stdbool.h>                    // tipo bool
#include "fases/fase2/coisas_gerais_fase2.h"              // must_init e funções utilitárias gerais
#include "core/sprites/sprites_fase2.h"   
#include "fases/fase1/fase1.h" 
#include "core/Efeitos/efeito_gerais.h"
#include "main.h"
#include "fases/fase1/inimigos_fase1.h"

ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

FONTS fonts;

void audio_init()//essa função inicializa o sistema de audio os carregando na memoria
{
    al_install_audio();//inicializa o sistema de audio do Allegro
    al_init_acodec_addon();//essa função basicamente inicializa os formatos de audio que o allegro utiliza
    al_reserve_samples(128);//reserva 128 slots de audio para serem guardados e futuramente utilizados

    sample_shot = al_load_sample("assets/sounds/shot.flac");//como o padrão para tudo que inicializamos no allegro, aqui teremos o ponteiro recebendo o arquivo de som
    must_init(sample_shot, "shot sample");//aqui tentamos inicializar o som, conforme tudo no allegro, como isso é extremamente simples e recorrente vou me poupar de explicar isso nas próximas vezes.

    sample_explode[0] = al_load_sample("assets/sounds/explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("assets/sounds/explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()//o mesmo vale para essa função que aparece repetidamente, sempre servirá para apagar as funções que não serão mais necessarias após o fechamento do programa
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}



void fx_init()// inicializa o array de efeitos colocando todas as suas posições used em false indicando que não foram usadas
{
    for (int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

void fx_add(bool spark, int x, int y)// essa função é a necessaria por colocar o efeito na tela
{
    //if (!spark)//se for uma explosão ele tocará o som de explosão
    //    al_play_sample(sample_explode[between(0, 2)], 0.75, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    for (int i = 0; i < FX_N; i++)
    {
        if (fx[i].used)//se a posição já tiver sido usada ele pula para o próximo indice 'i'
            continue;

        fx[i].x = x;//se não, ele define o X e o Y do efeito
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].spark = spark;
        fx[i].used = true;
        return;
    }
}

void fx_update()//essa função atualiza o estado atual do frame efeito a cada execução do programa
{
    for (int i = 0; i < FX_N; i++)
    {
        if (!fx[i].used)//se a posição não tiver sido usada ele pula para o próximo indice 'i'
            continue;

        fx[i].frame++;//se não, ele atualiza o frame para continuar sua animação

        if ((!fx[i].spark && (fx[i].frame == (FRAMES_EXPLOSAO * 2)))
            || (fx[i].spark && (fx[i].frame == (FRAMES_RAIO * 2)))
            )
            fx[i].used = false;
    }
}

//void fx_draw()//essa função é responsavel por desenhas o efeito na tela
//{
//    for (int i = 0; i < FX_N; i++)
//    {
//        if (!fx[i].used)//se o efeito ainda não tiver sido usado ele pula para o próximo indice 'i'
//            continue;
//
//        int frame_display = fx[i].frame / 2;
//        ALLEGRO_BITMAP* bmp =
//            fx[i].spark//se spark for true o sprite usado será o de faísca, se não, o de explosão
//            ? sprites_n.sparks[frame_display]
//            : sprites_n.explosion[frame_display]
//            ;
//
//        int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);//centraliza o efeito na posição X e abaixo na posição Y
//        int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
//        al_draw_bitmap(bmp, x, y, 0);//desenha o bitmap na tela
//        /*if(aliens->life[i] <= 0)
//            al_draw_text(ctx.font_subtitulo, ctx.cores.preto, fx[i].x, fx[i].y, ALLEGRO_ALIGN_CENTER, "TEXT EXEMPLE TEST");*/
//
//    }
//
//    for (int i = 0; i < ALIENS_N; i++)
//    {
//        if (aliens[i].life <= 0 && aliens[i].y > 1) {
//             if (f1_ctx.frames % 3) {
//                 if (aliens[i].type == 0) {
//                        al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "200");
//                 }
//                 if (aliens[i].type == 1) {
//                     al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "150");
//                 }
//                 if (aliens[i].type == 2) {
//                     al_draw_text(fonts.font_subtitulo, ctx.cores.preto, aliens[i].x, aliens[i].y, ALLEGRO_ALIGN_CENTER, "800");
//                 }
//             }
//         }   
//    }
//}