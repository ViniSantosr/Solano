//#pragma region Biblitotecas Externas
////Bibliotecas de C
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
////Bibliotecas do Allegro
//#include <allegro5/allegro5.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_color.h>
//#pragma endregion
//
//#pragma region Headers Game
////Headers que não fazem parte exclusivamente da fase 1
//#include "core/draw_tela.h"
//#include "configs/config_tela.h"
//#include "core/teclado.h"
//#include "main.h"
//#include "core/efeitos/efeito_gerais.h"
//#include "fases/fase2/fase2.h"
//
////Headers exclusivamente da fase 1
//#include "fases/fase1/tiros_fase1.h"
//#include "fases/fase1/navio_fase1.h"
//#include "fases/fase1/inimigos_fase1.h"
//#include "fases/fase1/hud_fase1.h"
//#include "fases/fase1/coisas_gerais_fase1.h"
//#include "fases/fase2/coisas_gerais_fase2.h"
//#include "fases/fase1/fase1.h"
//#pragma endregion
//
////Declaração das funções de Game Context que serão utilizadas na Fase 1
//Fase1Context f1_ctx;
////GameContext ctx;
//
//void fase1_init(ALLEGRO_DISPLAY* tela);					//Função de inicialização da fase 1
//void fase1_gameplay_update(ALLEGRO_DISPLAY* tela);		//Função de atualizar os objetos na tela da fase 1
//void fase1_gameplay_draw(GameContext* ctx);				//Função de desenhar os objetos na tela da fase 1
//void tela_inicial_f1(GameContext* ctx);
//void tela_pause_f1(ALLEGRO_FONT* font);
//void tela_game_over_f1(ALLEGRO_FONT* font);
//void tela_concluido_f1(ALLEGRO_FONT* font);
//
//bool jogo_em_inicio_f1();			//Enquanto o jogo está nos frames iniciais
//
//void fase1(GameContext* ctx)
//{
//    fase1_init(ctx->tela);
//    // Variáveis de controle da fase
//    f1_ctx.game_over = false;
//    f1_ctx.pause = false;
//    f1_ctx.concluido = false;
//    f1_ctx.exit_tela = false;
//    f1_ctx.frames_iniciais = 240; // Número de frames iniciais para mostrar o objetivo da fase
//    bool desenhar = false;
//
//
//
//
//
//
//    //must_init(al_init(), "allegro");
//    //must_init(al_install_keyboard(), "keyboard");
//
//    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
//    must_init(timer, "timer");
//
//    //ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
//    //must_init(queue, "queue");
//
//    ////tela_init();
//
//    //audio_init();
//
//    //must_init(al_init_image_addon(), "image");
//    //iniciar_sprites();
//
//    //iniciar_hud();
//
//    //must_init(al_init_primitives_addon(), "primitives");
//
//    //must_init(al_install_audio(), "audio");
//    //must_init(al_init_acodec_addon(), "audio codecs");
//    //must_init(al_reserve_samples(16), "reserve samples");
//
//    //al_register_event_source(queue, al_get_keyboard_event_source());
//    //al_register_event_source(queue, al_get_display_event_source(ctx->tela));
//    //al_register_event_source(queue, al_get_timer_event_source(timer));
//
//    //teclado_init();
//    //fx_init();
//    shots_init();
//    //ship_init();
//    //aliens_init();
//
//    f1_ctx.frames = 0;
//    f1_ctx.score = 0;
//
//    bool done = false;
//    bool redraw = true;
//    ALLEGRO_EVENT event;
//
//    al_start_timer(timer);
//
//    while (!ctx->exit_program && !f1_ctx.exit_tela)
//    {
//        al_wait_for_event(ctx->queue, &event);
//
//        switch (event.type) {
//        case ALLEGRO_EVENT_TIMER: printf("EVENT: TIMER\n"); break;
//        case ALLEGRO_EVENT_DISPLAY_CLOSE: printf("EVENT: DISPLAY_CLOSE\n"); break;
//        case ALLEGRO_EVENT_KEY_DOWN: printf("EVENT: KEY_DOWN\n"); break;
//        case ALLEGRO_EVENT_MOUSE_AXES: printf("EVENT: MOUSE_AXES\n"); break;
//        default: printf("EVENT: %d\n", event.type); break;
//        }
//        fflush(stdout);
//
//
//        switch (event.type)
//        {
//        case ALLEGRO_EVENT_TIMER:
//
//            if (ship.lives < 0) {
//                f1_ctx.game_over = true;
//            }
//
//            // Se o jogo não estiver em pausa ou acabado			
//            if (!f1_ctx.concluido && !f1_ctx.game_over && !f1_ctx.pause) {
//                fase1_gameplay_update(ctx->tela);
//            }
//
//            desenhar = true;
//
//            fx_update();
//            shots_update();
//
//            ship_update();
//            navios_update();
//            atualizar_hud();
//
//            if (tecla[ALLEGRO_KEY_ESCAPE])
//                done = true;
//
//            redraw = true;
//            f1_ctx.frames++;
//            break;
//
//        case ALLEGRO_EVENT_DISPLAY_CLOSE:
//            ctx->exit_program = true;
//            break;
//
//
//        case ALLEGRO_EVENT_KEY_DOWN:
//            if (!jogo_em_inicio_f1()) // Só vai rodar o jogo depois dos frames iniciais (jogo_em_inicio() = false)
//            {
//                if (tecla[ALLEGRO_KEY_SPACE])
//                {
//                    if (f1_ctx.concluido) // A fase foi concluída 
//                    {
//                        f1_ctx.exit_tela = true;
//                        ctx->estado_tela = FASE2;
//                    }
//
//                    if (f1_ctx.game_over) // Se o jogador perdeu
//                    {
//                        // Reinicia a fase
//                    }
//
//                    if (f1_ctx.pause) // Se o jogo estiver em pausa
//                    {
//                        f1_ctx.pause = false; // Retoma o jogo
//                    }
//                }
//
//
//                if (tecla[ALLEGRO_KEY_ESCAPE])
//                {
//                    if (f1_ctx.pause) // Se o jogo já estiver em pausa
//                    {
//                        f1_ctx.exit_tela = true;
//                        ctx->estado_tela = TELA_MENU;
//                    }
//                    else // Se o jogo não estiver em pausa
//                    {
//                        f1_ctx.pause = true; // Coloca o jogo em pausa
//                    }
//
//                    if (f1_ctx.concluido || f1_ctx.game_over)
//                    {
//                        f1_ctx.exit_tela = true;
//                        ctx->estado_tela = TELA_MENU;
//                    }
//                }
//            }
//            break;
//        }
//
//
//
//
//        // Draw (desenhar na tela)
//        if (desenhar && al_is_event_queue_empty(ctx->queue))
//
//        {
//            tela_pre_draw(ctx->canvas);
//            al_clear_to_color(al_map_rgb(0, 0, 0));
//
//            al_draw_scaled_bitmap(f1_ctx.background,
//                0, 0, al_get_bitmap_width(f1_ctx.background), al_get_bitmap_height(f1_ctx.background),
//                0, 0, CANVAS_W, CANVAS_H,
//                0);
//
//            if (jogo_em_inicio_f1()) // Enquanto o jogo está nos frames iniciais
//            {
//                tela_inicial_f1(ctx);
//            }
//            else
//            {
//                fase1_gameplay_draw(ctx);
//
//                if (f1_ctx.pause) // Se o jogo estiver em pausa
//                {
//                    tela_pause_f1(ctx->font);
//                }
//
//                if (f1_ctx.concluido) // Se a fase foi concluída
//                {
//                    tela_concluido_f1(ctx->font);
//                }
//
//                if (f1_ctx.game_over) // Se o jogador perdeu
//                {
//                    tela_game_over_f1(ctx->font);
//                }
//            }
//
//            tela_pos_draw(ctx->canvas, ctx->tela);
//            desenhar = false;
//        }
//    }
//    //destruir_sprites();
//    //hud_deinit();
//    //audio_deinit();
//    ////tela_destroy();
//    //al_destroy_timer(timer);
//    //al_destroy_event_queue(queue);
//}
//
//
//
//void fase1_init(ALLEGRO_DISPLAY* tela)
//{
//    sprites_navios_init();
//    iniciar_sprites();
//    iniciar_hud();
//
//    shots_init();
//    teclado_init();
//    ship_init();
//    aliens_init();
//    f1_ctx.frames = 0;
//    f1_ctx.score = 0;
//    f1_ctx.background = al_load_bitmap("assets/images/fase1_background.png");
//    must_init(f1_ctx.background, "fase 1 background");
//}
//
//void fase1_gameplay_update(ALLEGRO_DISPLAY* tela)
//{
//    //teclado_update(&event);
//    shots_update();
//    ship_update();
//    atualizar_hud();
//    navios_update();
//}
//
//void fase1_gameplay_draw(GameContext* ctx)
//{
//    shots_draw();
//    ship_draw();
//    navios_draw();
//    desenhar_hud();
//}
//
//void tela_inicial_f1(GameContext* ctx)
//{
//    TextosConfigs textos[3] =
//    {
//        {"FASE 1", CANVAS_W / 2, CANVAS_H / 4, ctx->cores.amarelo},
//        {"Guerra dos navios (1865)", CANVAS_W / 2, CANVAS_H / 2.5, ctx->cores.amarelo},
//        {"META:  Derrubar alguns navios (?)", CANVAS_W / 2, CANVAS_H / 2, ctx->cores.amarelo}
//    };
//
//    for (int i = 0; i < 3; i++)
//    {
//        int sombra_x = textos[i].x + 2;
//        int sombra_y = textos[i].y + 1;
//
//        al_draw_text(ctx->font_subtitulo, ctx->cores.preto, sombra_x, sombra_y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
//        al_draw_text(ctx->font_subtitulo, textos[i].cor, textos[i].x, textos[i].y, ALLEGRO_ALIGN_CENTER, textos[i].texto);
//    }
//}
//
//void tela_pause_f1(ALLEGRO_FONT* font)
//{
//    // Desenha um retângulo preto semi-transparente sobre a tela
//    al_draw_filled_rectangle(
//        0, 0, CANVAS_W, CANVAS_H,
//        al_map_rgba(0, 0, 0, 150) // RGBA → A = transparência (0 = invisível, 255 = opaco)
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 0, 0),
//        CANVAS_W / 2, CANVAS_H / 3,
//        ALLEGRO_ALIGN_CENTER,
//        "JOGO PAUSADO"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 1, 1),
//        CANVAS_W / 3.5, CANVAS_H / 2,
//        ALLEGRO_ALIGN_CENTER,
//        "Space ->"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1.0, 0.5, 0),
//        CANVAS_W / 2, CANVAS_H / 2,
//        ALLEGRO_ALIGN_CENTER,
//        "Retomar"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 1, 1),
//        CANVAS_W / 3.5, CANVAS_H / 1.8,
//        ALLEGRO_ALIGN_CENTER,
//        "Esc   ->"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1.0, 0.5, 0),
//        CANVAS_W / 1.5, CANVAS_H / 1.8,
//        ALLEGRO_ALIGN_CENTER,
//        "Volta a tela de menu"
//    );
//}
//
//void tela_game_over_f1(ALLEGRO_FONT* font)
//{
//    al_draw_filled_rectangle(
//        0, 0, CANVAS_W, CANVAS_H,
//        al_map_rgb(0, 0, 0)
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 0.2, 0.2),
//        CANVAS_W / 2, CANVAS_H / 3,
//        ALLEGRO_ALIGN_CENTER,
//        "G A M E  O V E R"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 0.2, 0.2),
//        CANVAS_W / 2, CANVAS_H / 2,
//        ALLEGRO_ALIGN_CENTER,
//        "Space -> Reiniciar"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(1, 0.2, 0.2),
//        CANVAS_W / 2, CANVAS_H / 1.8,
//        ALLEGRO_ALIGN_CENTER,
//        "Esc -> Volta a tela de menu"
//    );
//}
//
//void tela_concluido_f1(ALLEGRO_FONT* font)
//{
//    al_draw_filled_rectangle(
//        0, 0, CANVAS_W, CANVAS_H,
//        al_map_rgb(0, 0, 0)
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(0, 1, 0),
//        CANVAS_W / 2, CANVAS_H / 3,
//        ALLEGRO_ALIGN_CENTER,
//        "FASE 2 CONCLUIDA!!!!"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(0, 1, 0),
//        CANVAS_W / 2, CANVAS_H / 2,
//        ALLEGRO_ALIGN_CENTER,
//        "Space -> Ir para a fase 3"
//    );
//
//    al_draw_text(
//        font,
//        al_map_rgb_f(0, 1, 0),
//        CANVAS_W / 2, CANVAS_H / 1.8,
//        ALLEGRO_ALIGN_CENTER,
//        "Esc -> Volta a tela de menu"
//    );
//}
//
//bool jogo_em_inicio_f1()
//{
//    return f1_ctx.frames < f1_ctx.frames_iniciais;
//}
//
