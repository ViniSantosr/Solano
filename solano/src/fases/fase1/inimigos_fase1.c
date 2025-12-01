#include <allegro5/allegro.h>        // Base da Allegro (tipos, funções principais)

#include "core/tela_utils.h"                   // Usa BUFFER_W e BUFFER_H
#include "fases/fase2/coisas_gerais_fase2.h"            // Usa frames, score, must_init(), between()
#include "fases/fase1/tiros_fase1.h"         
#include "core/sprites/navios_sprites.h"   
#include "fases/fase1/fase1.h"

#include "main.h"

#include "fases/fase1/inimigos_fase1.h" 

INIMIGO inimigos[INIMIGOS_N];

void inimigos_anim_init(animar_inimigos* anim,
    int start_x, int start_y,
    int w, int h,
    int frame_count,
    int frame_spacing);

void inimigos_anim_update(animar_inimigos* anim);


void inimigos_init()//inicializa os aliens colocando todas posições em não usados
{
    for (int i = 0; i < INIMIGOS_N; i++)
        inimigos[i].used = false;
}

void inimigos_update(GameContext* ctx, Fase1Context* f1_ctx, long* frames, long* score) //função responsavel por atualizar o estado dos aliens
{
    int new_quota = //se entendi direito ele decide quantos aliens novos vão spawnar
        (*frames % 300)
        ? 0
        : between(2, 4)// de 2 a 4 aliens novos se spawnam a cada 120 frames
        ;
    int new_x = between(10, CANVAS_W - 50);//não sei

    for (int i = 0; i < INIMIGOS_N; i++)
    {
        if (!inimigos[i].used)
        {
            if (new_quota > 0)//se o alien ainda não estiver em uso e houver espaço para novos aliens
            {
                int base = between(160, 625);

                inimigos[i].x = base + between(-80, 80); // variação suave

                // garantir limites
                if (inimigos[i].x < 160) inimigos[i].x = 160;
                if (inimigos[i].x > 1360) inimigos[i].x = 1360;

                inimigos[i].y = between(-100, -70);
                inimigos[i].tipo = between(0, INIMIGOS_TIPO_N);
                inimigos[i].shot_timer = between(1, 99);
                inimigos[i].blink = 0;
                inimigos[i].movimento = between(-20, 20);
                inimigos[i].volta = true;
                inimigos[i].used = true;
                //preenche o struct do novo alien definindo nocas posições, aleatorizando seu tipo, seus timers de tiro e informando que agora foi utilizado

                switch (inimigos[i].tipo)//preenche a vida do alien dependendo do tipo de alien escolhido
                {
                case BARCO_INIMIGO:
                    inimigos[i].life = 3;
                    inimigos_anim_init(&inimigos[i].anim,
                        BARCO_START_X, BARCO_START_Y,
                        BARCO_W, BARCO_H,
                        BARCO_FRAME_COUNT, BARCO_SPACING);
                    break;                
                case NAVIO_INIMIGO:
                    inimigos[i].life = 5;
                    inimigos_anim_init(&inimigos[i].anim,
                        NAVIO_START_X, NAVIO_START_Y,
                        NAVIO_W, NAVIO_H,
                        NAVIO_FRAME_COUNT, NAVIO_SPACING);
                    break;
                }

                new_quota--;//ao fim, diminui o nivel de quotas do alien, fazendo com que eles não spawnem "infinitamente"
            }
            continue;
        }

        switch (inimigos[i].tipo)//essa parte da função é responsavel por mover os inimigos de acordo com o seu tipo, dando a eles uma velocidade diferente entre si
        {        
        case BARCO_INIMIGO:
           if (*frames % 4 == 0)
                inimigos[i].y++;

            if (inimigos[i].volta) {
                inimigos[i].x++;
                inimigos[i].movimento++;
                if (inimigos[i].movimento > 15 || inimigos[i].x == 160)
                    inimigos[i].volta = false;
            }
            else {
                inimigos[i].x--;
                inimigos[i].movimento--;
                if (inimigos[i].movimento < -15)
                    inimigos[i].volta = true;
            }

            break;

        case NAVIO_INIMIGO:
            if (*frames % 6 == 0)
                inimigos[i].y++;

            break;
        }

        inimigos_anim_update(&inimigos[i].anim);

        if (inimigos[i].y >= CANVAS_H)//se o alien passar do fim da tela, então ele poderá ser reutilizado para futuras quotas
        {
            inimigos[i].used = false;
            continue;
        }

        if (inimigos[i].blink)  //se estiverem piscando por dano, o tempo de piscapisca diminui
            inimigos[i].blink--;

        if (shots_collide(false, inimigos[i].x, inimigos[i].y, NAVIOS_INIMIGO_W[inimigos[i].tipo], NAVIOS_INIMIGO_H[inimigos[i].tipo]))//serve para que possamos checar a colisão de tiro com os inimigos e diminuindo a sua vida e o fazendo piscar
        {
            inimigos[i].life--;
            inimigos[i].blink = 4;
        }

        int cx = inimigos[i].x + (NAVIOS_INIMIGO_W[inimigos[i].tipo] / 2);
        int cy = inimigos[i].y + (NAVIOS_INIMIGO_H[inimigos[i].tipo] / 2);

        if (inimigos[i].life <= 0)//essa parte da função é responsavel por verificar a morte dos inimigos, caso estejam mortos recebem o cx e cy para adicionar a explosão e aumenta nosso score
        {           
            switch (inimigos[i].tipo)
            {            
            case BARCO_INIMIGO:
                f1_ctx->score += 150;                
                break;

            case NAVIO_INIMIGO:
                f1_ctx->score += 350;                               
                break;
            }

            inimigos[i].used = false;
            continue;
        }

        inimigos[i].shot_timer--; // constantemente irá diminuir o timer do alien para que ele possa atirar novamente
        if (inimigos[i].shot_timer == 0)//adiciona o tiro e dependendo do tipo de alien aumenta o seu tempo de timer para o próximo tiro
        {
            switch (inimigos[i].tipo)
            {
            case BARCO_INIMIGO:
                shots_add(false, false, cx, cy);
                inimigos[i].shot_timer = 240;
                break;            
            case NAVIO_INIMIGO:
                shots_add(false, true, cx - 5, cy);
                shots_add(false, true, cx + 5, cy);
                shots_add(false, true, cx - 5, cy + 8);
                shots_add(false, true, cx + 5, cy + 8);
                inimigos[i].shot_timer = 200;
                break;
            }
        }
    }
}

void inimigos_draw()// essa função desenha os aliens na tela
{
    for (int i = 0; i < INIMIGOS_N; i++)
    {
        if (!inimigos[i].used)
            continue;

        // ignorar se estiver piscando por dano
        if (inimigos[i].blink > 2)
            continue;

        animar_inimigos* A = &inimigos[i].anim;

        // calcula o frame atual dentro do spritesheet
        int src_x = A->start_x + A->frame * (A->frame_w + A->frame_spacing);
        int src_y = A->start_y;

        al_draw_bitmap_region(
            sprites_navios._navios_sheet,   // spritesheet dos navios/aliens
            src_x,                          // X da regi�o (frame)
            src_y,                          // Y da regi�o
            A->frame_w,                     // largura do frame
            A->frame_h,                     // altura do frame
            inimigos[i].x,                    // posi��o X na tela
            inimigos[i].y,                    // posi��o Y na tela
            0
        );
    }
}


void inimigos_anim_update(animar_inimigos* anim)
{
    anim->frame_timer++;
    if (anim->frame_timer >= anim->frame_time) {
        anim->frame_timer = 0;
        anim->frame++;
        if (anim->frame >= anim->frame_count)
            anim->frame = 0;
    }
}

void inimigos_anim_init(animar_inimigos* anim,
    int start_x, int start_y,
    int w, int h,
    int frame_count,
    int frame_spacing)
{
    anim->frame = 0;
    anim->frame_count = frame_count;
    anim->frame_w = w;
    anim->frame_h = h;
    anim->frame_spacing = frame_spacing;
    anim->start_x = start_x;
    anim->start_y = start_y;
    anim->frame_time = 6; // troca a cada 6 frames
    anim->frame_timer = 0;
}


