#include <allegro5/allegro.h>        // Base da Allegro (tipos, funções principais)
#include <allegro5/allegro_primitives.h> // Para desenhar bitmaps
#include "core/tela.h"
#include "configs/config_tela.h"                    // Usa BUFFER_W e BUFFER_H
#include "fases/fase2/coisas_gerais_fase2.h"            // Usa frames, score, must_init(), between()
#include "core/Efeitos/efeito_gerais.h"                   // Usa fx_add()
#include "fases/fase1/tiros_fase1.h"                   // Usa shots_add(), shots_collide()
#include "fases/fase1/inimigos_fase1.h"                  // Define o struct ALIEN e o array aliens[]
#include "core/sprites/sprites_fase2.h"             // Usa sprites.alien[...] para desenhar

const int ALIEN_W[] = { 14, 13, 45 };
const int ALIEN_H[] = { 9, 10, 27 };


void aliens_init()//inicializa os aliens colocando todas posições em não usados
{
    for (int i = 0; i < ALIENS_N; i++)
        aliens[i].used = false;
}

void aliens_update()//função responsavel por atualizar o estado dos aliens
{
    int new_quota = //se entendi direito ele decide quantos aliens novos vão spawnar
        (frames % 120)
        ? 0
        : between(2, 4)// de 2 a 4 aliens novos se spawnam a cada 120 frames
        ;
    int new_x = between(10, CANVAS_W - 50);//não sei

    for (int i = 0; i < ALIENS_N; i++)
    {
        if (!aliens[i].used)
        {
            if (new_quota > 0)//se o alien ainda não estiver em uso e houver espaço para novos aliens
            {
                new_x += between(40, 80);//define nova posição dos aliens
                if (new_x > (CANVAS_W - 60))
                    new_x -= (CANVAS_W - 60);



                aliens[i].x = new_x;

                aliens[i].y = between(-40, -30);
                aliens[i].type = between(0, ALIEN_TYPE_N);
                aliens[i].shot_timer = between(1, 99);
                aliens[i].blink = 0;
                aliens[i].movimento = between(-20, 20);
                aliens[i].volta = true;
                aliens[i].used = true;
                //preenche o struct do novo alien definindo nocas posições, aleatorizando seu tipo, seus timers de tiro e informando que agora foi utilizado

                switch (aliens[i].type)//preenche a vida do alien dependendo do tipo de alien escolhido
                {
                case ALIEN_TYPE_BUG:
                    aliens[i].life = 4;
                    break;
                case ALIEN_TYPE_ARROW:
                    aliens[i].life = 2;
                    break;
                case ALIEN_TYPE_THICCBOI:
                    aliens[i].life = 12;
                    break;
                }

                new_quota--;//ao fim, diminui o nivel de quotas do alien, fazendo com que eles não spawnem "infinitamente"
            }
            continue;
        }

        switch (aliens[i].type)//essa parte da função é responsavel por mover os aliens de acordo com o seu tipo, dando a eles uma velocidade diferente entre si
        {
        case ALIEN_TYPE_BUG:
            if (frames % 2)
                aliens[i].y++;
            if (aliens[i].volta) {
                aliens[i].x++;
                aliens[i].movimento++;
                if (aliens[i].movimento > 25)
                    aliens[i].volta = false;
            }
            else {
                aliens[i].x--;
                aliens[i].movimento--;
                if (aliens[i].movimento < -25)
                    aliens[i].volta = true;
            }
            break;

        case ALIEN_TYPE_ARROW:
            aliens[i].y++;

            if (aliens[i].volta) {
                aliens[i].x++;
                aliens[i].movimento++;
                if (aliens[i].movimento > 15)
                    aliens[i].volta = false;
            }
            else {
                aliens[i].x--;
                aliens[i].movimento--;
                if (aliens[i].movimento < -15)
                    aliens[i].volta = true;
            }

            break;

        case ALIEN_TYPE_THICCBOI:
            if (!(frames % 4))
                aliens[i].y++;

            break;
        }

        if (aliens[i].y >= CANVAS_H)//se o alien passar do fim da tela, então ele poderá ser reutilizado para futuras quotas
        {
            aliens[i].used = false;
            continue;
        }

        if (aliens[i].blink)//se estiverem piscando por dano, o tempo de piscapisca diminui
            aliens[i].blink--;

        if (shots_collide(false, aliens[i].x, aliens[i].y, ALIEN_W[aliens[i].type], ALIEN_H[aliens[i].type]))//serve para que possamos checar a colisão de tiro com os aliens e diminuindo a sua vida e o fazendo piscar
        {
            aliens[i].life--;
            aliens[i].blink = 4;
        }

        int cx = aliens[i].x + (ALIEN_W[aliens[i].type] / 2);
        int cy = aliens[i].y + (ALIEN_H[aliens[i].type] / 2);

        if (aliens[i].life <= 0)//essa parte da função é responsavel por verificar a morte dos aliens, caso estejam mortos recebem o cx e cy para adicionar a explosão e aumenta nosso score
        {
            fx_add(false, cx, cy);

            switch (aliens[i].type)
            {
            case ALIEN_TYPE_BUG:
                score += 200;
                break;

            case ALIEN_TYPE_ARROW:
                score += 150;
                break;

            case ALIEN_TYPE_THICCBOI:
                score += 800;
                fx_add(false, cx - 10, cy - 4);
                fx_add(false, cx + 4, cy + 10);
                fx_add(false, cx + 8, cy + 8);
                break;
            }

            aliens[i].used = false;
            continue;
        }

        aliens[i].shot_timer--; // constantemente irá diminuir o timer do alien para que ele possa atirar novamente
        if (aliens[i].shot_timer == 0)//adiciona o tiro e dependendo do tipo de alien aumenta o seu tempo de timer para o próximo tiro
        {
            switch (aliens[i].type)
            {
            case ALIEN_TYPE_BUG:
                shots_add(false, false, cx, cy);
                aliens[i].shot_timer = 150;
                break;
            case ALIEN_TYPE_ARROW:
                shots_add(false, true, cx, aliens[i].y);
                aliens[i].shot_timer = 80;
                break;
            case ALIEN_TYPE_THICCBOI:
                shots_add(false, true, cx - 5, cy);
                shots_add(false, true, cx + 5, cy);
                shots_add(false, true, cx - 5, cy + 8);
                shots_add(false, true, cx + 5, cy + 8);
                aliens[i].shot_timer = 200;
                break;
            }
        }
    }
}//fim dessa função, possivelmente a maior de todo o codigo!

void aliens_draw()// essa função desenha os aliens na tela
{
    for (int i = 0; i < ALIENS_N; i++)
    {
        if (!aliens[i].used)//se não estiver em uso pula pro proximo indice 'i'
            continue;
        if (aliens[i].blink > 2)//se estiver piscando por dano, pula o desenho do alien
            continue;

        al_draw_bitmap(sprites_n.alien[aliens[i].type], aliens[i].x, aliens[i].y, 0);//se passar pelas duas verificações então ele desenha o alien na tela
    }
}
