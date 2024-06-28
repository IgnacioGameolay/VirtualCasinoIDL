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
#include "rondaBonus.h"


typedef struct TipoCarta TipoCarta;

typedef struct TipoBaraja TipoBaraja;

//Función para comparar 2 enteros
// @param el primer valor a comparar
// @param el segundo valor a comparar
// @return 1 si el primer valor es mayor que el segundo
static int IsLowerInt(void *key1, void *key2);

//Función para inicializar baraja
// @param *baraja Puntero a la baraja
static void InicializarBaraja(TipoBaraja *baraja);

//Función para merzclar la baraja
//@param *listaCartas lista de las cartas
//@return Stack como un "Mazo de cartas"
static Stack* MezclarBaraja(List* listaCartas);

//Función para sacar cartas del top de un stack
//@param *barajada Puntero a la baraja mezclada
// @return retorna un TipoCarta con la carta que esta en el top
static TipoCarta* SacarCarta(Stack* barajada);

//Función de juego principal Higher or Lower
// @param *chipCount Puntero a la cantidad de fichas del jugador
void juegoHL(int *chipCount);

//Funcion de reglas de Higher or lower
void reglasHL();

//Funcion de printeo de menu de Higher or Lower
void MenuHL();

//Funcion de menu de Higher or lower
// @param *chipCount Puntero a la cantidad de fichas del jugador
// @return Retorna 0 al finalizar el juego
int HigherOrLower(int *chipCount);

#endif