#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tdas/extra.h"

#include "juegos/jackpot.h"
#include "juegos/blackjack.h"
//#include "juegos/cartas.h"
//#include "juegos/craps.h"
#include "juegos/higherorlower.h"
#include "juegos/poker.h"
//#include "juegos/roulette.h"


// Función para guardar el valor en un archivo
void guardarValor(const char *nombreArchivo, int valor) {
		FILE *archivo = fopen(nombreArchivo, "w");

		if (archivo == NULL) {
				printf("No se pudo abrir el archivo para escribir.\n");
				return;
		}

		fprintf(archivo, "%d\n", valor);
		fclose(archivo);
}

// Función para cargar el valor desde un archivo
int cargarValor(const char *nombreArchivo, int *valor) {
		FILE *archivo = fopen(nombreArchivo, "r");

		if (archivo == NULL) {
				printf("No se pudo abrir el archivo para leer.\n");
				return 1; // Indica que hubo un error
		}

		fscanf(archivo, "%d", valor);
		fclose(archivo);

		return 0; // Indica que la carga fue exitosa
}



/**
 *
 * Función main
 *
*/ 
int main() 
{ 
	const char *nombreArchivo = "fichasGuardadas.txt";
	int cantFichasJugador;
	// Intentar cargar el puntaje desde el archivo
	if (cargarValor(nombreArchivo, &cantFichasJugador) != 0) {
			// Si no se pudo cargar el archivo, inicializar el puntaje a 0
			puts("====== No se pudo recuperar el progreso ======");
				cantFichasJugador = 1000;
	} 
	if (cantFichasJugador <= 0){
			cantFichasJugador = 1000;
		puts("====== Se ha reiniciado el contador de fichas ======");
	}
	
	
	
	char option; //Option del menu
	do {
		if (cantFichasJugador <= 0){
			puts("========================================");
			puts("   Bienvenido al Casino Virtual IDL");
			puts("========================================");
			puts("========================================");
			printf("\n   Cantidad Actual de Fichas: $%d\n\n", cantFichasJugador);
			puts("========================================");
			puts("========================================");
			puts("No tienes fichas suficientes para seguir jugando.");
			puts("========================================");
			puts("= Game Over - Saliendo del simulador.. =");
			puts("========================================");
			return 0;
		}
		guardarValor(nombreArchivo, cantFichasJugador);
		puts("========================================");
		puts("   Bienvenido al Casino Virtual IDL");
		puts("========================================");
		puts("========================================");
		printf("\n   Cantidad Actual de Fichas: $%d\n\n", cantFichasJugador);
		puts("========================================");
		
		puts("(1) Blackjack (Apuesta mínima $25)");
		puts("(2) Poker (Apuesta mínima $25)");
		puts("(3) Higher or Lower (Apuesta mínima $100)");
		puts("(4) Ruleta (Apuesta mínima $25)");
		puts("(5) Jackpot (Apuesta mínima $25)");
		puts("(6) Craps (Apuesta mínima $50)");
		puts("-");
		puts("(7) Reiniciar Progreso");
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
			// Blackjack
			BlackjackGame(&cantFichasJugador);
			break;
		case '2':
			if (cantFichasJugador < 25) {
				puts("No tienes suficientes fichas para jugar");
				break;
			}
			PokerGame(&cantFichasJugador);
			
			break;
		case '3':
			if (cantFichasJugador < 101) {
				puts("No tienes suficientes fichas para jugar");
				break;
			}
			
			HigherOrLower(&cantFichasJugador);
			break;
		case '4':
			if (cantFichasJugador < 0) {
				puts("No tienes suficientes fichas para jugar");
				break;
			}
			
			//Ruleta(cantFichasJugador);
			break;
		case '5':
			if (cantFichasJugador < 0) {
				puts("No tienes suficientes fichas para jugar");
				break;
			} 
			
			JackpotGame(&cantFichasJugador);
			break;
		case '6':
			if (cantFichasJugador < 0) {
				puts("No tienes suficientes fichas para jugar");
				break;
			}
			
			//Craps(cantFichasJugador);
			break;

		case '7':
			cantFichasJugador = 1000;
			guardarValor(nombreArchivo, cantFichasJugador);
			printf("Progreso reiniciado con exito. Cantidad de fichas actuales: %d\n", cantFichasJugador);
		break;
			
		case '8':
			//SaveProgress(cantFichasJugador);
			guardarValor(nombreArchivo, cantFichasJugador);
			break;
		case '9':
			if (cargarValor(nombreArchivo, &cantFichasJugador) != 0) {
					printf("Puntaje no pudo ser cargado");
			} else {
					printf("Puntaje cargado con exito");
			}
			break;
		}
		presioneTeclaParaContinuar();
		limpiarPantalla();

	} while (option != '0' && cantFichasJugador >= 0);

	void guardarAlSalir(void) {
			guardarValor(nombreArchivo, cantFichasJugador);
	}
	
	atexit(guardarAlSalir);
	return 0;
}
