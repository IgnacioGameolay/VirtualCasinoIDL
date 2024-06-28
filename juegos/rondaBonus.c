#include "rondaBonus.h"


int RondaBonus(int* apuestaInicial){

	srand(time(NULL));
	int esBonus = rand() % 2; //un valor aleatorio entre 1 y 2

	if (esBonus == 1){
		int rondaBonus = (*apuestaInicial)*1.5;
		puts("========================================\n");
		puts("Felicidades, has ganado una ronda bonus!\n");
		printf("Has ganado %d fichas extra.\n", rondaBonus);
		puts("========================================\n");
		return rondaBonus;
	} 

	return 0;
}