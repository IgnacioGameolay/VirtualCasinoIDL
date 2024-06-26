#ifndef CARTAS_H
#define CARTAS_H
#include "blackjack.h"

typedef struct {
    int valor;  // 1 para As, 11 para J, 12 para Q, 13 para K, y 2-10 para las cartas numéricas
    int clave;
    char palo;
} TipoCarta;

typedef struct {
    List *listaCartas;
    int cartaActual;  // Índice de la próxima carta a repartir
} TipoBaraja;


void InicializarBaraja(TipoBaraja* baraja);
Stack* MezclarBaraja(List* listaCartas);


#endif