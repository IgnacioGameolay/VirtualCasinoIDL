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
typedef struct {
    char palo;
    int valor;
    int clave;
} TipoCarta;

typedef struct {
    List* listaCartas;
    int cartaActual;
} TipoBaraja;

// Prototipos de funciones
int IsLowerInt(void *key1, void *key2);

void InicializarBaraja(TipoBaraja *baraja);

Stack* MezclarBaraja(List* listaCartas);

TipoCarta* SacarCarta(Stack* barajada);

void MostrarMano(List* mano);

int CalcularPuntaje(List* mano);

void MostrarReglasBlackjack();

int Blackjack(int *chipCount);

void jugarBL(int *chipCount);

void determinarGanador(int puntajeJugador, int puntajeDealer, int apuesta, int* chipCount);

void menuBL();

#endif /* BLACKJACK_H */