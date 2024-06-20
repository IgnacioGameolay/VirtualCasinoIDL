#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include "tdas/map.h"
//#include "juegos/blackjack.h"
//#include "juegos/craps.h"
//#include "juegos/higherorlower.h"
//#include "juegos/poker.h"
//#include "juegos/roulette.h"

#include "juegos/jackpot.h"



/*Convenciones: 
1. Variables en espanhol
2. camelCase para variables
3. PascalCase para funciones

*/

typedef struct {
		int valor;  // 1 para As, 11 para J, 12 para Q, 13 para K, y 2-10 para las cartas numéricas
		int clave;
		char palo;
} TipoCarta;

typedef struct {
		List *listaCartas;
		int cartaActual;  // Índice de la próxima carta a repartir
} TipoBaraja;


//Funcion para inicializar una baraja principal con las 52 cartas existentes (baraja inglesa).
void InicializarBaraja(TipoBaraja *baraja) { 
	baraja->listaCartas = list_create();
		
	int i, j, k = 0;
	char palos[] = {'C', 'P', 'T', 'D'}; // C = Corazones, D = Diamantes, P = Picas, T = Tréboles
	
	//Para cada palo
	for (i = 0; i < 4 ; i++) {
		//Para cada valor	del 1 al 13
		for (j = 1; j <= 13; j++) {
			TipoCarta *carta = (TipoCarta *)malloc(sizeof(TipoCarta));
			carta->palo = palos[i];
			carta->valor = j;
			carta->clave = k++;
			list_pushBack(baraja->listaCartas, carta);
				
		}
	}
	baraja->cartaActual = 0;  // Inicializa el índice de la próxima carta a repartir
}

// Funcion comparación para el mapa
int IsLowerInt(void *key1, void *key2) {
	return *(int *)key1 <= *(int *)key2; 
}

Stack* MezclarBaraja(List* listaCartas) {
	// Crear mapa y stack
		Map* mapaCartas = sorted_map_create(IsLowerInt);
		Stack* barajada = stack_create(NULL);
	
		srand(time(NULL));


	// Recorremos la lista de 52 cartas, asignamos clave aleatoria a cada carta 
	// y guardamos en mapa por clave
	TipoCarta* cartaAux = NULL;
	cartaAux = list_first(listaCartas);
	
	while(cartaAux != NULL){
			cartaAux->clave = rand() % 52; // asignamos una clave aleatoria entre 1 y 52
			map_insert(mapaCartas, &cartaAux->clave, cartaAux); // insertamos por clave
			cartaAux = list_next(listaCartas); // pasamos a la siguiente carta.
	}

	// Recorrer el mapa y añadir las cartas a la pila
	MapPair *pair = map_first(mapaCartas); // obtenemos el 1er pair del mapa
	while (pair != NULL) {
			TipoCarta *carta = pair->value; // obtenemos la carta del pair obtenido
			stack_push(barajada, carta); // agregamops la carta a la pila
			pair = map_next(mapaCartas); // pasamos al siguiente pair del mapa
	}

	// Limpiar la memoria ocupada por el mapa
	map_clean(mapaCartas);
	free(mapaCartas);

	// Retornar la pila con las cartas barajadas
	return barajada;
}

// Mostrar cartas de una baraja TipoBaraja
void MostrarCartas(TipoBaraja *baraja){
	TipoCarta* carta = list_first(baraja->listaCartas);

	while(carta != NULL){
		if (carta->valor >= 2 && carta->valor <= 10) {
			printf("%d%c ", carta->valor, carta->palo);
		} else {
			switch (carta->valor) {
					case 1:
							printf("A%c ", carta->palo);
							break;
					case 11:
							printf("J%c ", carta->palo);
							break;
					case 12:
							printf("Q%c ", carta->palo);
							break;
					case 13:
							printf("K%c ", carta->palo);
							break;
			}
		}
		
			carta = list_next(baraja->listaCartas);
	}
}

// Mostrar cartas de una baraja STACK
void MostrarBarajada(Stack* barajada){
	TipoCarta* aux = stack_pop(barajada);

	while(aux != NULL){
		printf("Palo: %c - Valor: %d\n", aux->palo, aux->valor);
		aux = stack_pop(barajada);
	}
}


/**
 *
 * Función main
 *
*/ 
int main() 
{ 

	TipoBaraja barajaPrincipal;
	InicializarBaraja(&barajaPrincipal);
	
	int chipCount = 10000;
	
	char option; //Option del menu
	do {
		puts("========================================");
		puts("   Bienvenido al Casino Virtual IDL");
		puts("========================================");
		puts("========================================");
		printf("\n   Cantidad Actual de Fichas: %d\n\n", chipCount);
		puts("========================================");
		
		puts("(1) Blackjack (Apuesta mínima $25)");
		puts("(2) Poker (Apuesta mínima $25)");
		puts("(3) Higher or Lower  (Apuesta mínima $100)");
		puts("(4) Ruleta (Apuesta mínima $25)");
		puts("(5) Jackpot (Apuesta mínima $25)");
		puts("(6) Craps (Apuesta mínima $50)");

		puts("(8) Guardar Progreso");
		puts("(9) Cargar Progreso");
		puts("(0) Salir del Casino");
		
		puts("========================================");
		printf("Ingrese su opción: \n");
		puts("========================================");
		scanf(" %c", &option);


		//Opciones del menu
		Stack* pilaCartas;
		switch (option) {
		case '1':
			MostrarCartas(&barajaPrincipal);
			break;
		case '2':
			//MostrarCartas(&barajaPrincipal);
			pilaCartas = MezclarBaraja((&barajaPrincipal)->listaCartas);
			//printf("Cartas barajadas:\n");
			MostrarBarajada(pilaCartas);
			//Poker(chipCount);
			break;
		case '3':
			//HigherOrLower(chipCount);
			break;
		case '4':
			//Ruleta(chipCount);
			break;
		case '5':
			JackpotGame(&chipCount);
			break;
		case '6':
			//Craps(chipCount);
			break;
		case '8':
			//SaveProgress(chipCount);
			break;
		case '9':
			//LoadProgress(chipCount);
			break;
		}
		presioneTeclaParaContinuar();
		limpiarPantalla();

	} while (option != '0');

	return 0;
}
