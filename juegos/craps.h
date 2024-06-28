#ifndef CRAPS_H
#define CRAPS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"

#include "rondaBonus.h"

#define MAX_CARAS 6

typedef struct TipoDado TipoDado;

typedef struct TipoApuesta TipoApuesta;

typedef struct TipoJuego TipoJuego;

// Función para inicializar la ronda de dados y el juego
// @param *dados Puntero a la estructura TipoDado que representa los dados
// @param *juego Puntero a la estructura TipoJuego que representa el estado del juego
void InicializarRonda(TipoDado *dados, TipoJuego *juego);

// Función para crear una apuesta según el estado actual del juego
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta a realizar
// @param *juego Puntero a la estructura TipoJuego que representa el estado del juego
static void CrearApuestaCraps(TipoApuesta *apuesta, TipoJuego *juego);

// Función para lanzar los dados y devolver el índice del resultado
// @param *dados Puntero a la estructura TipoDado que representa los dados
// @return Índice del resultado obtenido al lanzar los dados
int LanzarDados(TipoDado *dados);

// Función para evaluar una apuesta a favor del número a venir
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta realizada
// @param *juego Puntero a la estructura TipoJuego que representa el estado del juego
// @param *dados Puntero a la estructura TipoDado que representa los dados
// @return Retorna 1 si la apuesta es ganadora, de lo contrario 0
int EvaluarApuestaFavor(TipoApuesta *apuesta, TipoJuego *juego, TipoDado *dados);

// Función para evaluar una apuesta en contra del número a venir
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta realizada
// @param *juego Puntero a la estructura TipoJuego que representa el estado del juego
// @param *dados Puntero a la estructura TipoDado que representa los dados
// @return Retorna 1 si la apuesta es ganadora, 0 si es perdedora, 3 si hay empate
int EvaluarApuestaContra(TipoApuesta *apuesta, TipoJuego *juego, TipoDado *dados);

// Función para evaluar una apuesta según el tipo y el estado del juego
// @param *apuesta Puntero a la estructura TipoApuesta que representa la apuesta realizada
// @param *dados Puntero a la estructura TipoDado que representa los dados
// @param *juego Puntero a la estructura TipoJuego que representa el estado del juego
static int EvaluarApuestaCraps(TipoApuesta *apuesta, TipoDado *dados, TipoJuego *juego);

// Función principal del juego de Craps
// @param *chipCount Puntero a la cantidad de fichas del jugador
// @return Retorna el estado del juego
int CrapsGame(int *chipCount);

#endif // CRAPS_H
