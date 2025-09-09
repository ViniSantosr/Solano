#include <stdbool.h>
#include <stdio.h>

void must_init(bool test, const char* description)
{
	if (test) return;

	fprintf(stderr, "Não pode ser inicializado: %s\n", description);
	exit(1);
}