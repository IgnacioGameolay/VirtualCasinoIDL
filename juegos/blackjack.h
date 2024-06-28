#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/extra.h"
#include "../tdas/map.h"

// Estructuras de datos
typedef struct TipoCarta TipoCarta;

typedef struct TipoBaraja TipoBaraja;

// Prototipos de funciones
static int IsLowerInt(void *key1, void *key2);

void InicializarBarajaBL(TipoBaraja *baraja);

Stack* MezclarBarajaBL(List* listaCartas);

TipoCarta* SacarCartaBL(Stack* barajada);

void MostrarMano(List* mano);

int CalcularPuntaje(List* mano);

void MostrarReglasBlackjack();

int BlackjackGame(int *chipCount);

void jugarBL(int *chipCount);

void determinarGanador(int puntajeJugador, int puntajeDealer, int apuesta, int* chipCount);

void menuBL();

#endif /* BLACKJACK_H */