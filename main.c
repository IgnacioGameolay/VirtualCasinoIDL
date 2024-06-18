#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <string.h>




/**
 *
 * Función main
 *
*/ 
int main() 
{ 
	
	puts("========================================");
	puts("     Cantidad Actual de Fichas:\n");
	printf("%d\n", chipCount);
	puts("========================================");
	
	int chipCount = 10000;
	char option; //Option del menu
	do {
		puts("========================================");
		puts("     Bienvenido al Casino Virtual IDL");
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
		printf("Ingrese su opción: ");
		puts("========================================");
		scanf(" %c", &option);


		//Opciones del menu
		
		switch (option) {
		case '1':
			blackjack(chipCount);
			break;
		case '2':
			poker(chipCount);
			break;
		case '3':
			higherOrLower(chipCount);
			break;
		case '4':
			ruleta(chipCount);
			break;
		case '5':
			jackpot(chipCount);
			break;
		case '6':
			craps(chipCount);
			break;
		case '8':
			saveProgress(chipCount);
			break;
		case '9':
			loadProgress(chipCount);
			break;
		}
		presioneTeclaParaContinuar();
		limpiarPantalla();

	} while (option != '0');

	return 0;
}
