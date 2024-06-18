#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include <string.h>


typedef struct{
  char nombre[30];
  int edad;
} waka;

/**
 *
 * Función main
 *
*/ 
int main() 
{ 
	
	int chipCount = 10000;
	puts("========================================");
	puts("     Cantidad Actual de Fichas:\n");
	printf("%d\n", chipCount);
	puts("========================================");
	
	
	char option; //Option del menu
	do {
		puts("========================================");
		puts("     Escoge una opci[on");
		puts("========================================");
		
		puts("1) Búsqueda en Profundidad");
		puts("4) Salir");
	
		printf("Ingrese su opción: ");
		scanf(" %c", &option);
	
		switch (option) {
		case '1':
			break;
		case '2':
			break;
			
		case '3':
			break;
		}
		presioneTeclaParaContinuar();
		limpiarPantalla();

	} while (option != '4');

	return 0;
}
