#ifndef TECLADO_H
#define TECLADO_H

#define TECLA_REGISTRADA		1
#define TECLA_PRESSIONADA		2

extern unsigned char tecla[ALLEGRO_KEY_MAX];

void teclado_init();

void teclado_update(ALLEGRO_EVENT* event);

#endif

