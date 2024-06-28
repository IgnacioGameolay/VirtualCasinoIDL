#ifndef RONDABONUS_H
#define RONDABONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../tdas/extra.h"

// Función para manejar la ronda bonus
// @param *apuestaInicial Puntero a la cantidad de la apuesta inicial
// @return Retorna la cantidad ganada en la ronda bonus si aplica, de lo contrario retorna 0
int RondaBonus(int* apuestaInicial);

#endif /* RONDABONUS_H */