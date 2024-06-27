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

// Definiciones de estructuras
typedef struct {
    int valor;
    char palo;
    int clave;
} TipoCarta;

typedef struct {
    List* listaCartas;
    List* cartasComunitarias;
} TipoBaraja;

// Funciones Auxiliares
int CompararCartas(const void *data1, const void *data2);
int CompararCartasMayorAMenor(const void *data1, const void *data2);
int IsLowerInt(void *key1, void *key2);
int is_equal_int(void *key1, void *key2);
int is_equal_str(void *key1, void *key2);


// Funciones para las barajas
void InicializarBaraja(TipoBaraja *baraja);
Stack* MezclarBaraja(List* listaCartas);
void MostrarCartas(List* listaCartas);
void MostrarBarajada(Stack* barajada);

// Funciones para las rondas
TipoCarta* SacarCarta(Stack* barajada);
void Apostar(int *apuestaRonda, int *fichasJugador);
void Igualar(int apuestaRonda, int *fichasJugador, int *cantFichasBote);
void Subir(int *apuestaRonda, int *fichasJugador, int cantidad);
void Pasar();
void Retirarse();
int AccionesBot(int *fichasBot, int *cantFichasBote, int *apuestaRonda, int accionJugador);
void RondaApuestas(int *cantFichasJugador, int *apuestaRonda, int *cantFichasBot, int *cantFichasBote);
void VerificarPremio(List* manoJugadorCompleta, List* manoCPUCompleta, int* cantFichasJugador, int* cantFichasBote);

//FUnciones de fases
void Flop(TipoBaraja* baraja, Stack* pilaCartas);
void Turn(TipoBaraja* baraja, Stack* pilaCartas);
void River(TipoBaraja* baraja, Stack* pilaCartas);


// Funciones relacionadas con las manos de poker
int EsEscaleraReal(List* manoCompleta);
int EsEscalera(List* manoCompleta);
int EsEscaleraDeColor(List* manoCompleta);
int EsPoker(List* manoCompleta);
int EsFullHouse(List* manoCompleta);
int EsColor(List* manoCompleta);
int EsTrio(List* manoCompleta);
int EsDoblePareja(List* manoCompleta);
int EsPareja(List* manoCompleta);
TipoCarta* ObtenerCartaMasAlta(List* mano);

//
void MostrarCartas(List* mano);
void ObtenerManoCompleta(List* manoCompleta, List* manoParcial, TipoBaraja* baraja);
int PokerGame(int *cantFichasJugador);

#endif // POKER_H
