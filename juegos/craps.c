#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"
#define MAX_CARAS 6

typedef struct
{
    int dado1[MAX_CARAS];
    int dado2[MAX_CARAS];
}TipoDado

typedef struct
{
    int monto; 
    int tipo; 
}TipoApuesta;

typedef struct
{
    int punto; 
    int estado; 
}TipoJuego

void inicializarRonda(TipoDado *dados, TipoJuego *juego)
{
  for (int i = 1; i <= MAX_CARAS; i++)
  {
    dados->dado1[i] = i;
  }
  juego->punto = -1;
  juego->estado = 1;
}

void crearApuesta(TipoApuesta *apuesta, TipoJuego *juego)
{
  printf("¿Qué tipo de apuesta desea hacer?\n");

  int monto, tipo;
  
  switch (juego->estado)
  {
    case 1:
      printf("1. Línea de pase\n");
      printf("2. Barra de no pase\n");
      printf("Ingrese su opción: ");
      scanf("%d", tipo);
      if(tipo < 1 || tipo > 2)
      {
        printf("Opción inválida. Intente de nuevo.\n");
        crearApuesta(apuesta, juego);
      }
      apuesta->tipo = tipo;
      break;
    case 2:
      printf("1. A favor del número a venir\n");
      printf("2. Contra el número a venir\n");
      printf("Ingrese su opción: ");
      scanf("%d", tipo);
      if(tipo < 1 || tipo > 2)
      {
        printf("Opción inválida. Intente de nuevo.\n");
        crearApuesta(apuesta, juego);
      }
      apuesta->tipo = tipo;
      break;
    default:
      printf("Estado inválido. Intente de nuevo.\n");
      return;
  }
  printf("Ingrese el monto de su apuesta: ");
  scanf("%d", monto);
  if(monto < 1)
  {
    printf("Monto inválido. Intente de nuevo.\n");
    crearApuesta(apuesta, juego);
  }
  apuesta->monto = monto;
}

void lanzarDados(TipoDado *dados)
{
  srand(time(NULL));
  for (int i = 1; i <= MAX_CARAS; i++)
  {
    dados->dado1[i] = rand() % MAX_CARAS + 1;
  }
}