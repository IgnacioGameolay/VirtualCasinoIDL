#ifndef HIGHERORLOWER_H
#define HIGHERORLOWER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"



typedef struct TipoCarta TipoCarta;

typedef struct TipoBaraja TipoBaraja;

TipoCarta* SacarCarta(Stack* barajada);
Stack* MezclarBaraja(List* listaCartas);
TipoCarta* SacarCarta(Stack* barajada);

int HigherOrLower(int *chipCount);
void juegoHL(int *chipCount);
void reglasHL();
void MenuHL();



#endif