#ifndef JACKPOT_H
#define JACKPOT_H

// Incluye los archivos de cabecera necesarios
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../tdas/list.h"
#include "../tdas/extra.h"

// Estructura para una casilla del rodillo
typedef struct {
    char figura[10];
} TipoCasilla;


typedef struct {
    List* listaCasillas;
} TipoRodillo;

// Funciones del juego Jackpot
TipoCasilla* CrearCasilla();
TipoRodillo* CrearRodillo();
int VerificarPremioJackpot(TipoRodillo* rodillo);
int JackpotGame(int* chipCount);

#endif
