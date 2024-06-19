#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
//#include "juegos/blackjack.h"
//#include "juegos/craps.h"
//#include "juegos/higherorlower.h"
//#include "juegos/poker.h"
//#include "juegos/roulette.h"
#include <string.h>



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


void InicializarBaraja(TipoBaraja *baraja) { //Funcion para inicializar la baraja.
	baraja->listaCartas = list_create();
		
	int i, j, k = 0;
	char palos[] = {'C', 'D', 'P', 'T'}; // C = Corazones, D = Diamantes, P = Picas, T = Tréboles
	
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
/*
void barajarBaraja(TipoBaraja *baraja) {
		srand(time(NULL));
		for (int i = 0; i < 52; i++) {
				int j = rand() % 52;
				TipoCarta temp = baraja->listaCartas[i];
				baraja->listaCartas[i] = baraja->listaCartas[j];
				baraja->listaCartas[j] = temp;
		}
		baraja->cartaActual = 0;  // Reinicia el índice de la próxima carta a repartir
}*/

void MostrarCartas(TipoBaraja *baraja){
	TipoCarta* aux = list_first(baraja->listaCartas);

	while(aux != NULL){
		printf("Palo: %c - Valor: %d\n", aux->palo, aux->valor);
		aux = list_next(baraja->listaCartas);
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
		
		switch (option) {
		case '1':
			MostrarCartas(&barajaPrincipal);
			break;
		case '2':
			MostrarCartas(&barajaPrincipal);
			//Poker(chipCount);
			break;
		case '3':
			//HigherOrLower(chipCount);
			break;
		case '4':
			//Ruleta(chipCount);
			break;
		case '5':
			//Jackpot(chipCount);
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
