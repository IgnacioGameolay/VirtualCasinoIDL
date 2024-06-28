#include "higherorlower.h"

struct TipoCarta{
		char palo;
		int valor;
		int clave;
};

struct TipoBaraja {
		List* listaCartas;
		int cartaActual;
};

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

TipoCarta* SacarCarta(Stack* barajada){
	TipoCarta* carta = stack_pop(barajada);
	return carta;
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


void MenuHL(){

	puts("========================================");
	puts(" Bienvenido a Higher or Lower.");
	puts("========================================");
	puts("1) Jugar");
	puts("2) Reglas");
	puts("3) Volver al menú principal");
	puts("========================================");
}

void reglasHL(){
	puts("========================================");
	puts("         Higher or Lower - Reglas");
	puts("========================================");
	puts("1. En este juego, se te mostrará una carta.");
	puts("2. Debes adivinar si la siguiente carta será de mayor o menor valor que la actual.");
	puts("3. Las cartas tienen los siguientes valores:");
	puts("   - As (A) = 1");
	puts("   - Números del 2 al 10 tienen su valor numérico.");
	puts("   - Jota (J) = 11");
	puts("   - Reina (Q) = 12");
	puts("   - Rey (K) = 13");
	puts("4. Si adivinas correctamente, tu apuesta se multiplicara un x1.1.");
	puts("5. Puedes elegir si retirarte o apostar la siguiente carta. Si fallas, pierdes la cantidad apostada. Si te retiras, ganas lo apostado por el multiplicador. En caso de empate se repite la apuesta.");
	puts("6. El juego continúa hasta que decidas retirarte o te quedes sin fichas.");
	puts("7. ¡Buena suerte y diviértete!");
	puts("========================================");
}

void juegoHL(int *chipCount){
	int apuesta = 0;
	int apuestaInicial = 0;
	int multiplicadorActual = 1.1;
	TipoCarta cartaActual;
	TipoCarta cartaSiguiente;
	TipoCarta cartaAnterior;

	TipoBaraja *baraja = InicializarBaraja();
	TipoBaraja *barajaMezclada = MezclarBaraja(baraja);

	printf("========================================\n");
	printf("Inicio de una nueva ronda de apuestas\n");
	printf("========================================\n");

	printf("Ingrese su apuesta: ");
	scanf("%d", &apuesta);
	apuestaInicial = apuesta;
	cartaActual = SacarCarta(barajaMezclada);
	cartaSiguiente = SacarCarta(barajaMezclada);
	
	while(1){

		printf("========================================\n");
		printf("Carta actual: %d de %s\n", cartaActual.valor, cartaActual.palo);
		printf("========================================\n");
		printf("1) Mayor\n");
		printf("2) Menor\n");
		printf("3) Retirarse\n");
		printf("========================================\n");

		printf("Ingrese su opción: ");
		int opcion;
		scanf("%d", &opcion);
		cartaAnterior = cartaActual;
		cartaActual = SacarCarta(barajaMezclada);
		if(opcion == 1){
			if(cartaSiguiente.valor > cartaActual.valor){
				printf("========================================\n");
				printf("¡Felicidades! Tu apuesta aumenta en un x1.1.\n");
				printf("========================================\n");
				apuesta = apuesta * multiplicadorActual;
				multiplicadorActual += 0.1;
			}
			else if(cartaSiguiente.valor < cartaActual.valor){
				printf("========================================\n");
				printf("Lo siento, has fallado. Pierdes %d fichas.\n", apuesta);
				printf("========================================\n");
				*chipCount -= apuestaInicial;
				break;
			}
			else if(cartaSiguiente.valor == cartaActual.valor){
				printf("========================================\n");
				printf("La carta siguiente es igual a la actual. se repite la apuesta\n");
				printf("========================================\n");
			}
		}
		if(opcion == 2){
			if(cartaSiguiente.valor < cartaActual.valor){
				printf("========================================\n");
				printf("¡Felicidades! Tu apuesta aumenta en un x1.1.\n");
				printf("========================================\n");
				apuesta = apuesta * multiplicadorActual;
				multiplicadorActual += 0.1;
			}
			else if (cartaSiguiente.valor > cartaActual.valor){
				printf("========================================\n");
				printf("Lo siento, has fallado. Pierdes %d fichas.\n", apuesta);
				printf("========================================\n");
				*chipCount -= apuestaInicial;
				break;
			}
			else if (cartaSiguiente.valor == cartaActual.valor){
				printf("========================================\n");
				printf("La carta siguiente es igual a la actual. se repite la apuesta\n");
				printf("========================================\n");
			}
		}
		if(opcion == 3){
			printf("========================================\n");
			printf("Te retiras. Ganas %d fichas.\n", apuesta);
			printf("========================================\n");
			*chipCount += apuesta;
			break;
		}
		
	}
}


int HigherOrLower(int *chipCount){

	char opcion;

	do {
		MenuHL();
		scanf(" %c", &opcion);
		switch(opcion){
			case '1':
				juegoHL(chipCount);
				return 0;
			case '2':
				reglasHL();
				break;
			case '3':
				return 0;
		}
	} while(opcion != '3');

	return 0;
	
}

