#ifndef ROULETTE_GAME_H
#define ROULETTE_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/arraylist.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"
#include "rondaBonus.h"
#define NUM_CASILLAS 37
#define MIN_CHIPS 25

// Estructura para representar de mejor manera la apuesta
// A que se está apostando(numero, color, paridad, columna, docena, mitad, tipo) y el monto.
typedef struct TipoApuesta TipoApuesta; 

// Estructura para representar la ruleta, tanto la casilla como el arreglo de la ruleta.
typedef struct TipoRuleta TipoRuleta;

// Función para inicializar la ruleta
// @param *ruleta Puntero a la estructura TipoRuleta que representa la ruleta
void InicializarRuleta(TipoRuleta *ruleta);

// Función para crear una apuesta
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta
// @param *chips Puntero a la cantidad de fichas del jugador
static void CrearApuestaRoulette(TipoApuesta* apuesta, int *chips);

// Función para girar la ruleta
// @param *ruleta Puntero a la estructura TipoRuleta que representa la ruleta
void GirarRuleta(TipoRuleta *ruleta);

// Función para determinar si un número es rojo
// @param numero Número a verificar
// @return Retorna 1 si el número es rojo, de lo contrario 0
int EsRojo(int numero);

// Función para determinar si un número es negro
// @param numero Número a verificar
// @return Retorna 1 si el número es negro, de lo contrario 0
int EsNegro(int numero);

// Función para obtener la columna de un número
// @param numero Número a verificar
// @return Retorna el número de columna del 1 al 3, retorna 0 si el número es 0
int ObtenerColumna(int numero);

// Función para evaluar una apuesta
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta
// @param *ruleta Puntero a la estructura TipoRuleta que representa la ruleta
// @return Retorna 1 si la apuesta es ganadora, de lo contrario 0
static int EvaluarApuestaRoulette(TipoApuesta *apuesta, TipoRuleta *ruleta);

// Función principal del juego de ruleta
// @param *chipCount Puntero a la cantidad de fichas del jugador
// @return Retorna el estado del juego
int RouletteGame(int *chipCount);


#endif // ROULETTE_GAME_H
