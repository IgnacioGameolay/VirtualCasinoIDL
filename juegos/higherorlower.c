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

static int IsLowerInt(void *key1, void *key2) {
	return *(int *)key1 <= *(int *)key2; 
}

static void InicializarBaraja(TipoBaraja *baraja) {  //Inicializar la baraja
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

static TipoCarta* SacarCarta(Stack* barajada){  //Sacar carta del stack
	TipoCarta* carta = stack_pop(barajada);
	return carta;
}

static Stack* MezclarBaraja(List* listaCartas) { //Mezcla de baraja
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


void MenuHL(){  //Menu de juego

	puts("========================================");
	puts(" Bienvenido a Higher or Lower.");
	puts("========================================");
	puts("1) Jugar");
	puts("2) Reglas");
	puts("3) Volver al menú principal");
	puts("========================================");
}

void reglasHL(){ //Reglas de juego
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

void juegoHL(int *chipCount){  //Juego Higher or lower
	
	
	int apuesta = 0;
	int apuestaInicial = 0;
	float multiplicadorActual = 1.1;
	TipoCarta* cartaActual = (TipoCarta *) malloc(sizeof(TipoCarta));
	TipoCarta* cartaSiguiente = (TipoCarta *) malloc(sizeof(TipoCarta));
	TipoCarta* cartaAnterior = (TipoCarta *) malloc(sizeof(TipoCarta));
	TipoBaraja baraja;
	InicializarBaraja(&baraja);
	Stack* barajaMezclada = MezclarBaraja((&baraja)->listaCartas);

	puts("========================================");   //Inicializacion de juego
	puts("Inicio de una nueva ronda de apuestas");
	puts("========================================");

	puts("Ingrese su apuesta: ");
	scanf("%d", &apuesta);
	apuestaInicial = apuesta;
	cartaActual = SacarCarta(barajaMezclada);
	cartaSiguiente = SacarCarta(barajaMezclada);
	
	while(1){   //Ciclo de juego
		presioneTeclaParaContinuar();
		limpiarPantalla();
		
		puts("========================================");   //Mostrar carta actual
		printf("Carta actual: %d de %c\n", cartaActual->valor, cartaActual->palo);
		printf("Multiplicador actual x%.1f\n", multiplicadorActual); //Multiplicador actual
		puts("========================================");
		puts("1) Mayor");
		puts("2) Menor");
		puts("3) Retirarse");
		puts("========================================");

		puts("Ingrese su opción: ");
		int opcion;
		scanf("%d", &opcion);
		if(opcion == 1){
			if(cartaSiguiente->valor > cartaActual->valor){ //Si el valor de la siguiente carta es mayor
				puts("========================================");
				puts("¡Felicidades! Tu apuesta aumenta en un x1.1.");
				printf("Nueva carta actual %d de %c\n", cartaSiguiente->valor, cartaSiguiente->palo);
				puts("========================================");
				apuesta = apuesta * multiplicadorActual;
				multiplicadorActual += 0.1;
				cartaAnterior = cartaActual;
				cartaActual = cartaSiguiente;
				cartaSiguiente = SacarCarta(barajaMezclada);
			}
			else if(cartaSiguiente->valor < cartaActual->valor){ //Si el valor de la siguiente carta es menor
				puts("========================================");
				printf("Lo siento, has fallado. Pierdes %d fichas.\n", apuesta);
				printf("Ultima carta: %d de %c\n", cartaSiguiente->valor, cartaSiguiente->palo);
				puts("========================================");
				*chipCount -= apuestaInicial;
				free(cartaActual);
				free(cartaSiguiente);
				free(cartaAnterior);
				break;
			}
			else if(cartaSiguiente->valor == cartaActual->valor){ //Si las cartas son iguales
				puts("========================================");
				puts("La carta siguiente es igual a la actual. Se repite la apuesta");
				puts("========================================");
				cartaAnterior = cartaActual;
				cartaActual = cartaSiguiente;
				cartaSiguiente = SacarCarta(barajaMezclada);
			}
		}
		if(opcion == 2){
			if(cartaSiguiente->valor < cartaActual->valor){ //Si el valor de la siguiente carta es menor
				puts("========================================");
				puts("¡Felicidades! Tu apuesta aumenta en un x1.1.");
				printf("Nueva carta actual %d de %c\n", cartaSiguiente->valor, cartaSiguiente->palo);
				puts("========================================");
				apuesta = apuesta * multiplicadorActual;
				multiplicadorActual += 0.1;
				cartaAnterior = cartaActual;
				cartaActual = cartaSiguiente;
				cartaSiguiente = SacarCarta(barajaMezclada);
			}
			else if (cartaSiguiente->valor > cartaActual->valor){ //Si el valor de la siguiente carta es mayor
				puts("========================================");
				printf("Lo siento, has fallado. Pierdes %d fichas.\n", apuesta);
				printf("Ultima carta: %d de %c\n", cartaSiguiente->valor, cartaSiguiente->palo);
				puts("========================================");
				*chipCount -= apuestaInicial;
				free(cartaActual);
				free(cartaSiguiente);
				free(cartaAnterior);
				break;
			}
			else if (cartaSiguiente->valor == cartaActual->valor){ //Si las cartas son iguales
				puts("========================================");
				puts("La carta siguiente es igual a la actual. Se repite la apuesta");
				puts("========================================");
				cartaAnterior = cartaActual;
				cartaActual = cartaSiguiente;
				cartaSiguiente = SacarCarta(barajaMezclada);
			}
		}
		if(opcion == 3){ 
			puts("========================================");  //Retirada del juego
			printf("Te retiras. Ganas %d fichas.\n", apuesta);
			puts("========================================");

			apuesta += RondaBonus(&apuesta);
			*chipCount += apuesta;
			free(cartaActual);
			free(cartaSiguiente);
			free(cartaAnterior);
			break;
		}
		
	}
	return;
}


int HigherOrLower(int *chipCount){ //Menu del juego Higher or Lower

	int opcion;

	do {
		limpiarPantalla();
		MenuHL();
		scanf("%d", &opcion);
		switch(opcion){
			case 1:
				presioneTeclaParaContinuar();
				limpiarPantalla();
				juegoHL(chipCount);
				return 0;
			case 2:
				limpiarPantalla();
				reglasHL();
				presioneTeclaParaContinuar();
				limpiarPantalla();
				break;
			case 3:
				return 0;
			default:
				puts("Ingrese una opción válida");
			
		}
	} while(opcion != 3);

	return 0;
}

