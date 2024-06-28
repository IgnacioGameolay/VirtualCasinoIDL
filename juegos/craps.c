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
  for (int i = 0; i < MAX_CARAS; i++)
  {
    dados->dado1[i] = i + 1;
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
      printf("3. Realizar Tiro y proceder con apuestas de Punto\n");
      printf("Ingrese su opción: ");
      scanf("%d", tipo);
      if(tipo < 1 || tipo > 3)
      {
        printf("Opción inválida. Intente de nuevo.\n");
        crearApuesta(apuesta, juego);
      }
      if(tipo == 3)
      {
        return;
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
  int indice1 = dados->dado1 = rand() % MAX_CARAS;
  int indice2 = dados->dado2 = rand() % MAX_CARAS;
}

void evaluarApuesta(TipoApuesta *apuesta, TipoDado *dados, TipoJuego *juego)
{
  int suma = dados->dado1[indice1] + dados->dado2[indice2];
  if(suma != 2 && suma != 3 && suma != 7 && suma != 11 && suma != 12)
  {
    juego->estado = 2;
    juego->punto = suma;
  }
  switch (apuesta->tipo)
  {
    case 1: // Línea de Pase
      if (juego->estado == 1)
      { // Tiro de salida
        if (resultado == 7 || resultado == 11) 
        {
          printf("Ganaste la apuesta de Línea de Pase!\n");
        } 
        else if (resultado == 2 || resultado == 3 || resultado == 12)
        {
          printf("Perdiste la apuesta de Línea de Pase.\n");
        } 
        else 
        {
          juego->punto = resultado;
          juego->estado = 2;
          printf("Se ha establecido el punto en %d.\n", juego->punto);
        }
      } 
      else
      { // Tiro de punto
        if (resultado == juego->punto)
        {
          printf("Ganaste la apuesta de Línea de Pase!\n");
          juego->estado = 1;
        } 
        else if (resultado == 7)
        {
          printf("Perdiste la apuesta de Línea de Pase.\n");
          juego->estado = 1;
        }
      }
      break;
    case 2: // Barra de No Pase
          if (juego->estado == 1) { // Tiro de salida
              if (resultado == 2 || resultado == 3) {
                  printf("Ganaste la apuesta de Barra de No Pase!\n");
              } else if (resultado == 7 || resultado == 11) {
                  printf("Perdiste la apuesta de Barra de No Pase.\n");
              } else if (resultado == 12) {
                  printf("Empate en la apuesta de Barra de No Pase.\n");
              } else {
                  juego->punto = resultado;
                  juego->estado = 2;
                  printf("Se ha establecido el punto en %d.\n", juego->punto);
              }
          } else { // Tiro de punto
              if (resultado == 7) {
                  printf("Ganaste la apuesta de Barra de No Pase!\n");
                  juego->estado = 1;
              } else if (resultado == juego->punto) {
                  printf("Perdiste la apuesta de Barra de No Pase.\n");
                  juego->estado = 1;
              }
          }
          break;
      case 3: // A favor del número a venir
          if (juego->estado == 1) { // Tiro de salida
              printf("Las apuestas a favor del número a venir no están permitidas en el tiro de salida.\n");
          } else { // Tiro de punto
              if (resultado == 7 || resultado == 11) {
                  printf("Ganaste la apuesta a favor del número a venir!\n");
              } else if (resultado == 2 || resultado == 3 || resultado == 12) {
                  printf("Perdiste la apuesta a favor del número a venir.\n");
              } else {
                  juego->punto = resultado;
                  printf("Se ha establecido el punto en %d.\n", juego->punto);
              }
          }
          break;
      case 4: // En contra del número a venir
          if (juego->estado == 1) { // Tiro de salida
              printf("Las apuestas en contra del número a venir no están permitidas en el tiro de salida.\n");
          } else { // Tiro de punto
              if (resultado == 2 || resultado == 3) {
                  printf("Ganaste la apuesta en contra del número a venir!\n");
              } else if (resultado == 7 || resultado == 11) {
                  printf("Perdiste la apuesta en contra del número a venir.\n");
              } else if (resultado == 12) {
                  printf("Empate en la apuesta en contra del número a venir.\n");
              } else {
                  juego->punto = resultado;
                  printf("Se ha establecido el punto en %d.\n", juego->punto);
              }
          }
          break;
      default:
          printf("Tipo de apuesta inválido.\n");
          break;
  }
}