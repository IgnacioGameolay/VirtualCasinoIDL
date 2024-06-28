#ifndef JACKPOT_H
#define JACKPOT_H

// Incluye los archivos de cabecera necesarios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../tdas/list.h"
#include "../tdas/extra.h"
#include "rondaBonus.h"

// Estructura para una casilla del rodillo
typedef struct {
    char figura[10];
} TipoCasilla;

// Estructura para una rodillo de casillas
typedef struct {
    List* listaCasillas;
} TipoRodillo;


// Función para crear una casilla del rodillo de jackpot
// @return Retorna un puntero a la casilla creada por la funcion
TipoCasilla* CrearCasilla();


//Función para crear el rodillo y agregarle las casillas del jackpot
//@return Retorna un puntero a al rodillo generado por la funcion
TipoRodillo* CrearRodillo();


//Función para verificar las condiciones de victoria del usuario
//@param *rodillo Puntero al rodillo del jackpot
//@return Retorna 1 si el usuario gana, 0 si pierde
int VerificarPremioJackpot(TipoRodillo* rodillo);


//Función principal del juego.
int JackpotGame(int* chipCount);

#endif
