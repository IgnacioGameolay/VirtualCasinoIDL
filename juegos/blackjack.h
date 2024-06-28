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
#include "rondaBonus.h"

// Estructura para las cartas
typedef struct TipoCarta TipoCarta;

// Estructura para las barajas
typedef struct TipoBaraja TipoBaraja;

//Función para comparar 2 enteros
// @param el primer valor a comparar
// @param el segundo valor a comparar
// @return 1 si el primer valor es mayor que el segundo
static int IsLowerInt(void *key1, void *key2);


//Función para inicializar baraja
// @param *baraja Puntero a la baraja
void InicializarBarajaBL(TipoBaraja *baraja);


//Función para merzclar la baraja
//@param *listaCartas lista de las cartas
//@return Stack como un "Mazo de cartas"
Stack* MezclarBarajaBL(List* listaCartas);


 
//Función para sacar cartas del top de un stack
//@param *barajada Puntero a la baraja mezclada
// @return retorna un TipoCarta con la carta que esta en el top
TipoCarta* SacarCartaBL(Stack* barajada);

//Función para mostrar mano
// @param *mano Una lista con las cartas de la mano
// @return Retorna 1 si el usuario gana, 0 si pierde
void MostrarMano(List* mano);

//Función para calcular puntaje de una mano
// @param *mano Una lista con las cartas de la mano
// @return Retorna un entero con la suma de los valores de la mano
int CalcularPuntaje(List* mano);

//Funcion que muestra reglas del blackjack
void MostrarReglasBlackjack();

//Función de juego de blackjack
// @param *chipCount puntero con las fichas del jugador
// @return Retorna 1 al finalizar el codigo
int BlackjackGame(int *chipCount);

//Función para mostrar menu de blackjack
// @param *chipCount puntero con las fichas del jugador
void jugarBL(int *chipCount);

//Funcion para determinar ganador del blackjack
// @param (puntajeJugador, puntajeDealer) puntaje de cada jugador (apuesta) apuesta recibida (*chipCount) fichas del jugador)
void determinarGanador(int puntajeJugador, int puntajeDealer, int apuesta, int* chipCount);

//Funcion de printeo del menu
void menuBL();

#endif /* BLACKJACK_H */