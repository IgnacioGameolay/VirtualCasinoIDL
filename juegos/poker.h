#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"
#include "rondaBonus.h"

// Definiciones de estructuras
typedef struct TipoCarta TipoCarta;

typedef struct TipoBaraja TipoBaraja;

// Funciones Auxiliares de comparacion y orden
int CompararCartas(const void *data1, const void *data2);
int CompararCartasMayorAMenor(const void *data1, const void *data2);
static int IsLowerInt(void *key1, void *key2);
static int is_equal_int(void *key1, void *key2);
static int is_equal_str(void *key1, void *key2);


//Función para inicializar baraja
// @param *baraja Puntero a la baraja
static void InicializarBaraja(TipoBaraja *baraja);

//Función para merzclar la baraja
//@param *listaCartas lista de las cartas
//@return Stack como un "Mazo de cartas"
static Stack* MezclarBaraja(List* listaCartas);

//Función para mostrar una lista de cartas
// @param *listaCartas Una lista de cartas cualquiera
static void MostrarCartas(List* listaCartas);

//Función para sacar cartas del top de un stack
//@param *barajada Puntero a la baraja mezclada
// @return retorna un TipoCarta con la carta que esta en el top
static TipoCarta* SacarCarta(Stack* barajada);

// Función para realizar una apuesta
// @param *apuestaRonda Puntero a la cantidad de apuesta en la ronda actual
// @param *fichasJugador Puntero a la cantidad de fichas del jugador
void Apostar(int *apuestaRonda, int *fichasJugador);

// Función para igualar la apuesta de la ronda
// @param apuestaRonda Cantidad de la apuesta en la ronda actual
// @param *fichasJugador Puntero a la cantidad de fichas del jugador
// @param *cantFichasBote Puntero a la cantidad de fichas en el bote
void Igualar(int apuestaRonda, int *fichasJugador, int *cantFichasBote);

// Función para pasar en la ronda de apuestas
void Pasar();
// Función para retirarse
void Retirarse();


// Función para que el bot realice una acción en la ronda
// @param *fichasBot Puntero a la cantidad de fichas del bot
// @param *cantFichasBote Puntero a la cantidad de fichas en el bote
// @param *apuestaRonda Puntero a la cantidad de apuesta en la ronda actual
// @param accionJugador Acción realizada por el jugador
// @return Retorna la acción realizada por el bot
int AccionesBot(int *fichasBot, int *cantFichasBote, int *apuestaRonda, int accionJugador);

// Función para manejar la ronda de apuestas
// @param *cantFichasJugador Puntero a la cantidad de fichas del jugador
// @param *apuestaRonda Puntero a la cantidad de apuesta en la ronda actual
// @param *cantFichasBot Puntero a la cantidad de fichas del bot
// @param *cantFichasBote Puntero a la cantidad de fichas en el bote
void RondaApuestas(int *cantFichasJugador, int *apuestaRonda, int *cantFichasBot, int *cantFichasBote);


// Función para verificar el premio al final del juego
// @param *manoJugadorCompleta Lista de cartas de la mano completa del jugador
// @param *manoCPUCompleta Lista de cartas de la mano completa del bot
// @param *cantFichasJugador Puntero a la cantidad de fichas del jugador
// @param *cantFichasBote Puntero a la cantidad de fichas en el bote
void VerificarPremio(List* manoJugadorCompleta, List* manoCPUCompleta, int* cantFichasJugador, int* cantFichasBote);


// Función para manejar la fase de Flop en el juego
// @param *baraja Puntero a la baraja
// @param *pilaCartas Puntero al stack de cartas
void Flop(TipoBaraja* baraja, Stack* pilaCartas);

// Función para manejar la fase de Turn en el juego
// @param *baraja Puntero a la baraja
// @param *pilaCartas Puntero al stack de cartas
void Turn(TipoBaraja* baraja, Stack* pilaCartas);

// Función para manejar la fase de River en el juego
// @param *baraja Puntero a la baraja
// @param *pilaCartas Puntero al stack de cartas
void River(TipoBaraja* baraja, Stack* pilaCartas);


// Función para verificar si la mano es una escalera real
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es una escalera real, de lo contrario 0
int EsEscaleraReal(List* manoCompleta);

// Función para verificar si la mano es una escalera
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es una escalera, de lo contrario 0
int EsEscalera(List* manoCompleta);

// Función para verificar si la mano es una escalera de color
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es una escalera de color, de lo contrario 0
int EsEscaleraDeColor(List* manoCompleta);

// Función para verificar si la mano es un póker (cuatro cartas iguales)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es un póker, de lo contrario 0
int EsPoker(List* manoCompleta);

// Función para verificar si la mano es un full house (tres de un tipo y dos de otro)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es un full house, de lo contrario 0
int EsFullHouse(List* manoCompleta);

// Función para verificar si la mano es un color (cinco cartas del mismo palo)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es un color, de lo contrario 0
int EsColor(List* manoCompleta);

// Función para verificar si la mano es un trío (tres cartas iguales)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es un trío, de lo contrario 0
int EsTrio(List* manoCompleta);

// Función para verificar si la mano es una doble pareja (dos pares diferentes)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es una doble pareja, de lo contrario 0
int EsDoblePareja(List* manoCompleta);

// Función para verificar si la mano es una pareja (dos cartas iguales)
// @param *manoCompleta Lista de cartas de la mano completa
// @return Retorna 1 si es una pareja, de lo contrario 0
int EsPareja(List* manoCompleta);

// Función para obtener la carta más alta de una mano
// @param *mano Lista de cartas de la mano
// @return Retorna un puntero a la carta más alta
TipoCarta* ObtenerCartaMasAlta(List* mano);

// Función para mostrar una lista de cartas
// @param *mano Lista de cartas a mostrar
void MostrarCartas(List* mano);

// Función para obtener la mano completa del jugador
// @param *manoCompleta Lista de cartas de la mano completa
// @param *manoParcial Lista de cartas de la mano parcial
// @param *baraja Puntero a la baraja
void ObtenerManoCompleta(List* manoCompleta, List* manoParcial, TipoBaraja* baraja);

// Función para gestionar el sub-menu del poker
// @param *cantFichasJugador Puntero a la cantidad de fichas del jugador
// @return Retorna la opcion del usuario
int MenuPoker(int *cantFichasJugador);

// Función principal del juego de póker
// @param *cantFichasJugador Puntero a la cantidad de fichas del jugador
// @return Retorna el estado del juego
int PokerGame(int *cantFichasJugador);

#endif // POKER_H
