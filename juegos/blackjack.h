#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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

#endif /* BLACKJACK_H */