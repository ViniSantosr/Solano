#ifndef CUTSCENES_H
#define CUTSCENES_H

typedef enum {
    PRINCIPAL,
    LEITOR,
    NARRADOR,
    CAPITAO
} PERSONAGEM;

typedef struct {
    const char* texto;
    PERSONAGEM personagem;    
} DIALOGO;

typedef struct {
    DIALOGO* dialogos;
    int total_linhas;
    int max_linha;
} CENA_DIALOGO;


typedef enum {
    CENA_INICIAL = 0,
    CENA_LIVRO,

    PRE_FASE1,
    POS_FASE1,

    PRE_FASE2,
    POS_FASE2,

    PRE_FASE3,
    POS_FASE3,

    PRE_FASE4,
    POS_FASE4,    
} CENAS;

void cutscene(GameContext* ctx, int fase_atual);

#endif
