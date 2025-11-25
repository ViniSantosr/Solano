#ifndef EFEITOS_GERAIS_H
#define EFEITOS_GERAIS_H

#include <stdbool.h>        // Para o tipo bool
#include "fases/fase2/coisas_gerais_fase2.h"   // Para funções utilitárias como must_init
#include "core/sprites/sprites_fase2.h"       // Para acesso aos sprites de explosão/faísca ao desenhar os efeitos
#include <allegro5/allegro_audio.h>

//não sei se é a opção mais viavel ou a mais racional, mas, na minha cabeça faz sentido guardar os efeitos FX e os soms todos no mesmo lugar, então é isso que estou fazendo aqui

extern ALLEGRO_SAMPLE* sample_shot;//variavel tipo ponteiro que guardará o .flac do tiro
extern ALLEGRO_SAMPLE* sample_explode[2];//aqui temos um array que guarda o som das explo~sões, são dois sons diferentes

void audio_init();
void audio_deinit();


typedef struct FX//struct dos efeitos que serão usados no jogo
{
    int x, y;//posição X e Y de onde estarão na tela
    int frame;//frame atual
    bool spark;// se for true, é um efeito de faísca, se for false, é uma explosão
    bool used;//indica se está em uso ou não
} FX;

#define FX_N 128//define a constante com 128 posições 
FX fx[FX_N];//cria o array fx com 128 posições

void fx_init();
void fx_add(bool spark, int x, int y);
void fx_update();
void fx_draw();

#endif