#include "rondaBonus.h"

// FUncion para manejar la ronda bonus de 1 en 100 de probabilidad.
int RondaBonus(int* apuestaInicial){

	srand(time(NULL)); // Generar seed para aleatoridad
	int esBonus = rand() % 100; //un valor aleatorio entre 1 y 100

	if (esBonus == 1){
		// Si el la ronda es una bonus, la apuesta de la ronda aumenta en la mitad de su total.
		int rondaBonus = (*apuestaInicial)*1.5; 
		puts("========================================\n");
		puts("Felicidades, has ganado una ronda bonus!\n");
		printf("Has ganado %d fichas extra.\n", rondaBonus);
		puts("========================================\n");
		return rondaBonus; // Retornar aumento de apuesta de la ronda bonus
	} 

	return 0;
}