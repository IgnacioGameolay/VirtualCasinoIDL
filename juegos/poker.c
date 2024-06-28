#include "poker.h"


struct TipoCarta{
	int valor;
	char palo;
	int clave;
};

struct TipoBaraja{
	List* listaCartas;
	List* cartasComunitarias;
};

// Cartas comunitarias (flop, turn, river)
// 1 para As, 11 para J, 12 para Q, 13 para K, y 2-10 para las cartas numéricas
// Función para comparar dos cartas por valor (para ordenarlas)
int CompararCartas(const void *data1, const void *data2) {
	TipoCarta *carta1 = (TipoCarta *)data1;
	TipoCarta *carta2 = (TipoCarta *)data2;

	if (carta1->valor < carta2->valor) {
		return -1;
	} else if (carta1->valor > carta2->valor) {
		return 1;
	} else {
		return 0;
	}
}

// Función para comparar dos cartas por valor (para ordenarlas)
int CompararCartasMayorAMenor(const void *data1, const void *data2) {
	TipoCarta *carta1 = (TipoCarta *)data1;
	TipoCarta *carta2 = (TipoCarta *)data2;

	if (carta1->valor > carta2->valor) {
		return -1;
	} else if (carta1->valor < carta2->valor) {
		return 1;
	} else {
		return 0;
	}
}

// Funcion comparación para el mapa
static int IsLowerInt(void *key1, void *key2) {
	return *(int *)key1 <= *(int *)key2; 
}

static int is_equal_int(void *key1, void *key2) {
	return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

static int is_equal_str(void *key1, void *key2) {
	return strcasecmp((char *)key1, (char *)key2) == 0;
}


//Funcion para inicializar una baraja principal con las 52 cartas existentes (baraja inglesa).
static void InicializarBaraja(TipoBaraja *baraja) { 
	baraja->listaCartas = list_create();
	baraja->cartasComunitarias = list_create();
	
	int i, j, k = 0;
	char palos[] = {'C', 'P', 'T', 'D'}; // C = Corazones, D = Diamantes, P = Picas, T = Tréboles

	//Para cada palo
	for (i = 0; i < 4 ; i++) {
		//Para cada valor	del 1 al 13
		for (j = 1; j <= 13; j++) {
			TipoCarta *carta = (TipoCarta *)malloc(sizeof(TipoCarta));
			if (carta == NULL){
				printf("Error al designar memoria para la carta: %d\n", j);
				EXIT_FAILURE;
			}
			carta->palo = palos[i];
			carta->valor = j;
			carta->clave = k++;
			list_pushBack(baraja->listaCartas, carta);

		}
	}
}


static Stack* MezclarBaraja(List* listaCartas) {
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
static void MostrarCartas(List* listaCartas){
	TipoCarta* carta = list_first(listaCartas);

	while(carta != NULL){
		if ((carta->valor >= 2) && (carta->valor <= 10)) {
			printf("%d - %c \n", carta->valor, carta->palo);
		} else {
			switch (carta->valor) {
					case 1:
							printf("A - %c \n", carta->palo);
							break;
					case 11:
							printf("J - %c \n", carta->palo);
							break;
					case 12:
							printf("Q - %c \n", carta->palo);
							break;
					case 13:
							printf("K - %c \n", carta->palo);
							break;
			}
		}

			carta = list_next(listaCartas);
	}
}

//Funcion para sacar la carta del tope de la baraja
static TipoCarta* SacarCarta(Stack* barajada){
	return (TipoCarta*) stack_pop(barajada);
}

// FUncion para subir una apuesta
void Apostar(int *apuestaRonda, int *fichasJugador) {
	int cantidad;
	
	if ((*apuestaRonda) > (*fichasJugador)){
		printf("No tienes suficientes fichas para subir esta apuesta. \n");
	}
	
	do {
		printf("Ingrese la cantidad a apostar: ");
		scanf("%d", &cantidad);
		
		if ((*fichasJugador >= cantidad) && 
			(cantidad >= (*apuestaRonda)) &&
			(cantidad >= 25)) {
			*apuestaRonda += cantidad;
			*fichasJugador -= cantidad;
			printf("El jugador ha apostado %d fichas. Bote actual: %d\n", cantidad, *apuestaRonda);
			break;  // Salir del bucle cuando la apuesta sea válida
		} else {
			puts("========================================");
			printf("La cantidad de fichas no es suficiente para subir. Tienes %d fichas.\n", *fichasJugador);
			puts("Recordatorio: La cantidad mínima a apostar es de 25 fichas");
			puts("========================================");
		}
	} while (cantidad < 25);  // Continuar pidiendo hasta que se haga una apuesta válida
}

// Funcion para igualar a la apuesta actual de la ronda
void Igualar(int apuestaRonda, int *fichasJugador, int *cantFichasBote) {
	if (*fichasJugador >= apuestaRonda) {
		*fichasJugador -= apuestaRonda;
		(*cantFichasBote) += apuestaRonda;
		printf("El jugador ha igualado con %d fichas. Bote actual: %d\n", apuestaRonda, *cantFichasBote);
	} else {
		printf("No tienes suficientes fichas para igualar.\n");
	}
}

//FUncion para pasar turno
void Pasar() {
	printf("El jugador ha pasado su turno.\n");
}

//FUncion para retirarse del juego
void Retirarse() {
		puts("El jugador se ha intentado retirar.");
	puts("Dada la adapatación de este simulador, el jugador no puede retirarse.");
}


// Funcion para determinar las acciones del bot
int AccionesBot(int *fichasBot, int *cantFichasBote, int *apuestaRonda, int accionJugador){
	int accion;
		
	if (accionJugador == 1){
		accion = 1;
		if ((*fichasBot) >= (*apuestaRonda)) {
			//Igualar apuesta del bot
			(*fichasBot) -= (*apuestaRonda);
			(*cantFichasBote) += (*apuestaRonda);
			
			printf("El bot ha igualado la apuesta en %d fichas. Bote actual: %d\n", (*apuestaRonda), *cantFichasBote);
			return 1;
		} else {
			printf("El bot no tiene suficientes fichas para subir. ");
		}
		return 0;
	} else {
		accion = 1 + rand() % 2; // Generar num entre 1 y 2 
	}
	
	
	int cantidad;
	switch (accion) {
		case 1:  // subir apuesta
			// Bot siempre sube con una buena mano
			cantidad = rand() % 100 + 50;  // Subir entre 50 y 150 fichas

			if ((*fichasBot) >= cantidad) {
				(*apuestaRonda) += cantidad;
				(*cantFichasBote) += cantidad;
				(*fichasBot) -= cantidad;
				printf("El bot ha subido la apuesta en %d fichas. Bote actual: %d\n", cantidad, *cantFichasBote);
			} else {
				printf("El bot no tiene suficientes fichas para subir. ");
			}
			break;

		case 2: // pasar turno
			printf("El bot ha pasado su turno. Bote actual: %d\n", *cantFichasBote);
			break;
		default:
			printf("Acción de bot no válida.\n");
			return -1;
	}
	return accion;
}

void RondaApuestas(int *cantFichasJugador, int *apuestaRonda, int *cantFichasBot, int *cantFichasBote){
	// Variables de apusetas y acciones
	(*apuestaRonda) = 0; //variable de apuesta auxiliar, para igualar o subir
	char option;
	int accionBot;
	int accionJugador = 2;
	
	//Sub-Menus de juegos
	do{
		puts("========================================");
		printf("\n   Cantidad Actual de Fichas del Bot: %d\n\n", *cantFichasBot);
		puts("========================================");
		accionBot = AccionesBot(cantFichasBot, cantFichasBote, apuestaRonda, accionJugador);

		//El bot sube la apuesta
		if (accionBot == 1){
			//
			puts("========================================");
			printf("\n   Cantidad Actual de Fichas del Jugador: %d\n\n", *cantFichasJugador);
			puts("========================================");
			puts("(1) Subir");
			puts("(2) Igualar");
			puts("(3) Retirarse");
			puts("========================================");
			printf("Ingrese su opción: \n");
			puts("========================================");
			scanf(" %c", &option);

				switch (option) {
					case '1':
						
						Apostar(apuestaRonda, cantFichasJugador);
						(*cantFichasBote) += (*apuestaRonda);
						
						return;
					case '2':
						Igualar(*apuestaRonda, cantFichasJugador, cantFichasBote);
						(*cantFichasBote) += (*apuestaRonda);
						return;
					case '3':
						Retirarse();
						return;
					default:
						printf("Opción no válida. Intente nuevamente.\n");
						presioneTeclaParaContinuar();
				}
		} else {

			do {
				puts("========================================");
				printf("\n   Cantidad Actual de Fichas del Jugador: %d\n\n", *cantFichasJugador);
				puts("========================================");
				puts("(1) Apostar/Subir");
				puts("(2) Pasar");
				puts("(3) Retirarse");
				puts("========================================");
				printf("Ingrese su opción: \n");
				puts("========================================");
				scanf(" %c", &option);

				switch (option) {
					case '1':
						Apostar(apuestaRonda, cantFichasJugador);
						(*cantFichasBote) += (*apuestaRonda);
						accionJugador = 1;
						return;
					case '2':
						Pasar();
						return;
					case '3':
						Retirarse();
						return;
					default:
						printf("Opción no válida. Intente nuevamente.\n");
						presioneTeclaParaContinuar();
				}
			} while (1);
		}        
	} while (1);
}

// Funcion para saber el Flop
void Flop(TipoBaraja *baraja, Stack* pilaCartas){
	printf("========================================\n");
	printf("Repartiendo el Flop...\n");
	//Sacar 3 cartas del tope de la baraja y agregarlas a la lista de cartas comunitarias
	for (int i = 0; i < 3; i++) {
		list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
	}
	printf("========================================\n");

	printf("Cartas Comunitarias en el Flop:\n");
	MostrarCartas(baraja->cartasComunitarias);

}

// Funcion para saber el Turn
void Turn(TipoBaraja *baraja, Stack* pilaCartas){
	
	printf("========================================\n");
	printf("Repartiendo el Turn...\n");
	//Sacar carta del tope de la baraja y agregarlo a la lista de cartas comunitarias
	list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
	printf("========================================\n");

	printf("Cartas Comunitarias en el Turn:\n");
	MostrarCartas(baraja->cartasComunitarias);
}

// Funcion para saber el River
void River(TipoBaraja *baraja, Stack* pilaCartas){
	printf("========================================\n");
	printf("Repartiendo el River...\n");
	list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
	printf("========================================\n");
	//Sacar carta del tope de la baraja y agregarlo a la lista de cartas comunitarias
	printf("Cartas Comunitarias en el River:\n");
	MostrarCartas(baraja->cartasComunitarias);

}

// Funcion para saber si es color - 5 cartas del mismo palo
int EsColor(List* manoCompleta){
	//Crear mapa de frecuencias de palos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_str);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

		//Buscamos el palo en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->palo);

		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){           
			//Crear lista de cartas con el mismo palo e insertarlo al mapa
			List* listaCartasPorPalo = list_create();
			map_insert(mapaFrecuenciaValores, &carta->palo, listaCartasPorPalo);
			list_pushFront(listaCartasPorPalo, carta);
		} else {
			//Si ya est[a] en el mapa lo agregamos a la lista de cartas del palo
			list_pushFront(pair->value, carta);
		}
	}

	//Recorrer cada lista de palos
	MapPair* current_pair = map_first(mapaFrecuenciaValores);

	while (current_pair != NULL) {
		// Contador de cartas por poalo
		int contadorCartasPorPalo = 0;
		//Recorrer cada carta del palo
		TipoCarta* carta = list_first(current_pair->value);
		
		while(carta != NULL){

			contadorCartasPorPalo += 1; //Aumentar contador de cartas del palo

			// Verificar si el contador de cartas del mismo palo es igual a 5 (es color)
			if (contadorCartasPorPalo == 5){
				// Si es color limpiar mapa y retornar resultado
				map_clean(mapaFrecuenciaValores);
				return 1;
			}
			carta = list_next(current_pair->value);//Pasar a la siguiente carta
		}
		current_pair = map_next(mapaFrecuenciaValores); //Pasar al siguiente palo
	}

	//Limpiar mapa y retornar resultado
	map_clean(mapaFrecuenciaValores);
	return 0;
}

// Funcion para verificar si la mano completa es escalera
int EsEscalera(List* manoCompleta){
	TipoCarta* cartaAnterior = NULL;
	int contador = 0;

	// Recorrer la mano para verificar si hay una escalera
	for (TipoCarta* cartaActual = list_first(manoCompleta); cartaActual != NULL; cartaActual = list_next(manoCompleta)) {
		if (cartaAnterior != NULL) {
			// Verificar si la carta actual tiene un valor consecutivo al anterior
			if (cartaActual->valor == cartaAnterior->valor + 1) {
				contador++;
			} else if (cartaActual->valor != cartaAnterior->valor) {
				// Si hay una brecha en los valores, reiniciar el contador
				contador = 0;
			}
		}

		cartaAnterior = cartaActual;

		// Si se encontraron cinco cartas consecutivas, es una escalera
		if (contador == 4) {
			return 1;
		}
	}

	return 0;
}

// Funcion para verificar si la mano completa es escalera de color
int EsEscaleraDeColor(List* manoCompleta){
	//Crear mapa de frecuencias de palos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_str);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {
		
		//Buscamos el palo en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->palo);

		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){           
			//Crear lista de cartas con el mismo palo 
			List* listaCartasPorPalo = list_create();
			map_insert(mapaFrecuenciaValores, &carta->palo, listaCartasPorPalo);
			list_pushFront(listaCartasPorPalo, carta);
		} else {
			//Si ya est[a] en el mapa lo agregamos a la lista de cartas del palo
			list_pushFront(pair->value, carta);
		}
	}

	//Recorrer cada lista de palos
	MapPair* current_pair = map_first(mapaFrecuenciaValores);

	while (current_pair != NULL) {
		// Verificar si hay una escalera real en este palo

		int contadorCartasPorPalo = 0;

		TipoCarta* carta = list_first(current_pair->value);
		//Recorrer cada carta del palo
		while(carta != NULL){

			contadorCartasPorPalo += 1; // AUmentamos el contador de cartas de un palo

			// Si el contador de cartas es =5 significa que es color
			// Por lo que ahora toca verificar si ese color genera una escalera
			if (contadorCartasPorPalo == 5){
				if (EsEscalera(current_pair->value)){
					map_clean(mapaFrecuenciaValores);
					return 1;
				}
				
			}
			carta = list_next(current_pair->value);//Pasar a la siguiente carta
		}
		current_pair = map_next(mapaFrecuenciaValores); //Pasar al siguiente palo
	}

	//Liberar memoria y retornar resultado
	map_clean(mapaFrecuenciaValores);
	return 0;
}

// Funcion para verificar si la mano completa es pareja simple o doble
int EsPareja(List* manoCompleta){
	//Crear mapa de frecuencias de valores numericos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_int);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {
		//Buscamos el valor en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){
			int* frecuenciaValor = (int*)malloc(sizeof(int));
			*frecuenciaValor = 1;
			map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
		} else {
			// aumentar frecuencia de aparicion del numero de la carta
			(*((int *)pair->value))++;
		}
	}

	//Contador de cantidad de parejas
	int cantParejas = 0;
	
	//Recorremos el mapa
	MapPair *current_pair = map_first(mapaFrecuenciaValores);
	
	while (current_pair != NULL) {
		int frecuencia = *((int *)current_pair->value);
		if (frecuencia == 2) cantParejas++; //Aumentamos el contador de pares
		current_pair = map_next(mapaFrecuenciaValores);
	}

	//Liberar memoria y retornar resultado
	map_clean(mapaFrecuenciaValores);
	
	if (cantParejas == 1) return 1;
	else if (cantParejas >= 2) return 2;
	return 0;
}

// Funcion para verificar si la mano completa es trio
int EsTrio(List* manoCompleta){
	//Crear mapa de frecuencias de valores numericos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_int);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {
		//Buscamos el valor en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);
		
		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){
			int* frecuenciaValor = (int*)malloc(sizeof(int));
			*frecuenciaValor = 1; // aumentar frecuencia de aparicion del numero de la carta
			map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
		} else {
			//Aumentar frecuencia si ya est[a] en el mapa
			(*((int *)pair->value))++;
		}
	}

	//printf("Cantidad de apariciones de cada valor en la mano:\n");
	MapPair *current_pair = map_first(mapaFrecuenciaValores);
	while (current_pair != NULL) {
		int frecuencia = *((int *)current_pair->value);
		if (frecuencia == 3){
			map_clean(mapaFrecuenciaValores);
			free(mapaFrecuenciaValores);
			return 1;
		}
		current_pair = map_next(mapaFrecuenciaValores);
	}
	return 0;
}

// Funcion para verificar si la mano completa es full house - 1 trio y 1 pareja
int EsFullHouse(List* manoCompleta){
	//Crear mapa de frecuencias de valores numericos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_int);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

		//Buscamos el valor en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){
			int* frecuenciaValor = (int*)malloc(sizeof(int));
			*frecuenciaValor = 1; // aumentar frecuencia de aparicion del numero de la carta
			map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
			
		} else {
			//Aumentar frecuencia si ya est[a] en el mapa
			(*((int *)pair->value))++;
		}
	}

	//Contadores de cantidad de apariciones de cada valor en la mano
	int cantParejas = 0;
	int cantTrios = 0;

	// Recorremos cada valor en la mano y verificamos frecuencia de aparicion para ese valor
	MapPair *current_pair = map_first(mapaFrecuenciaValores);
	while (current_pair != NULL) {
		int frecuencia = *((int *)current_pair->value);
		
		if ((cantParejas == 1) && (cantTrios == 1)){
			map_clean(mapaFrecuenciaValores);
			free(mapaFrecuenciaValores);
			return 1;
		}
		// Verificamos parejas o trios
		if (frecuencia == 2) cantParejas++;
		if (frecuencia == 3) cantTrios++;
		
		current_pair = map_next(mapaFrecuenciaValores); // Pasar al siguiente palo
	}

	//Liberar memoria
	map_clean(mapaFrecuenciaValores);

	return 0;
}

// Funcion para verificar si la mano completa es poker - 4 cartas del mismo valor
int EsPoker(List* manoCompleta){
	//Crear mapa de frecuencias de valores numericos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_int);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {
		//Buscamos el valor en el mapa
		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

		//Si no est[a] en el mapa lo agregamos
		if (pair == NULL){
			int* frecuenciaValor = (int*)malloc(sizeof(int));
			*frecuenciaValor = 1; // aumentar frecuencia de aparicion del numero de la carta
			map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
		} else {
			//Aumentar frecuencia si ya est[a] en el mapa
			(*((int *)pair->value))++;
		}
	}

	//printf("Cantidad de apariciones de cada valor en la mano:\n");
	MapPair *current_pair = map_first(mapaFrecuenciaValores);
	while (current_pair != NULL) {
		int frecuencia = *((int *)current_pair->value);
		if (frecuencia == 4){
			map_clean(mapaFrecuenciaValores);
			free(mapaFrecuenciaValores);
			return 1;
		}
		current_pair = map_next(mapaFrecuenciaValores);
	}
	return 0;
}

// Funcion para verificar si la mano completa es escalera real
int EsEscaleraReal(List* manoCompleta){
	//Crear mapa de frecuencias de valores numericos de las cartas
	Map* mapaFrecuenciaValores = NULL;
	mapaFrecuenciaValores = map_create(is_equal_int);

	// Agregar las cartas de la mano completa al mapa creado
	TipoCarta* carta = NULL;
	for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

		MapPair* pair = map_search(mapaFrecuenciaValores, &carta->palo);

		if (pair == NULL){           
			//Crear lista de cartas con el mismo palo 
			List* listaCartasPorPalo = list_create();
			map_insert(mapaFrecuenciaValores, &carta->palo, listaCartasPorPalo);
			list_pushFront(listaCartasPorPalo, carta);
		} else {
			list_pushFront(pair->value, carta);
		}
	}

	//Recorrer cada lista de palos
	MapPair* current_pair = map_first(mapaFrecuenciaValores);
	
	int hayAs = 0, hayRey = 0, hayReina = 0, hayJota = 0, hayDiez = 0;
	
	while (current_pair != NULL) {
		//printf(" Cartas del palo: %s\n", (char*)current_pair->key);
		// Verificar si hay una escalera real en este palo      

		TipoCarta* carta = list_first(current_pair->value);

		while(carta != NULL){

			//Logica para determinar si es escalera real
			if (carta->valor == 1) hayAs = 1;  // As
			else if (carta->valor == 13) hayRey = 1;  // Rey
			else if (carta->valor == 12) hayReina = 1;  // Reina
			else if (carta->valor == 11) hayJota = 1;  // Jota
			else if (carta->valor == 10) hayDiez = 1;  // Diez
			
			carta = list_next(current_pair->value); //Pasar a la siguiente carta
		}

		//Comprobar si estan las Cartas Reales
		if (hayAs && hayRey && hayReina && hayJota && hayDiez) {
			//Liberar memoria y retornar resultado
			map_clean(mapaFrecuenciaValores);
			free(mapaFrecuenciaValores);
			return 1;
		}

		current_pair = map_next(mapaFrecuenciaValores); //Pasar al siguiente palo
	}
	
	return 0;
}


// Funcion para obtener la carta mas alta de una mano
TipoCarta* ObtenerCartaMasAlta(List* mano) {
	//Obtener la carta mas alta y la carta actual
	TipoCarta* cartaMasAlta = list_first(mano);
	TipoCarta* cartaActual = cartaMasAlta;

	// Recorrer la lista de cartas para encontrar la carta mas alta
	while (cartaActual != NULL) {
		if (cartaActual->valor == 1) return cartaMasAlta; //retornar el As como carta mas alta
		
		if (cartaActual->valor > cartaMasAlta->valor) {
			cartaMasAlta = cartaActual;
		}
		
		cartaActual = list_next(mano); //Actualizamos la carta actual a la carta siguiente de la mano
	}

	return cartaMasAlta;
}


//Funcion para verificar que jugador se lleva el premio
void VerificarPremio(List* manoJugadorCompleta, List* manoBotCompleta, int* cantFichasJugador, int* cantFichasBote){

	//Variables para determinar la fuerza de la mano de los jugadors
	int fuerzaManoJugador = 0; 
	int fuerzaManoBot = 0;


	// Determinar la fuerza de la mano completa del jugador
	puts("========================================");
	if (EsEscaleraReal(manoJugadorCompleta)){
		printf("El jugador tiene Escalera Real!!\n");
		fuerzaManoJugador = 10;
	}
	else if (EsEscaleraDeColor(manoJugadorCompleta)){
		printf("El jugador tiene una escalera de color!!\n");
		fuerzaManoJugador = 9;
	}
	else if (EsPoker(manoJugadorCompleta)){
		printf("El jugador tiene POKER!!\n");
		fuerzaManoJugador = 8;
	}
	else if (EsFullHouse(manoJugadorCompleta)){
		printf("El jugador tiene FULL HOUSE!!\n");
		fuerzaManoJugador = 7;
	} 
	else if (EsColor(manoJugadorCompleta)){
		printf("El jugador tiene COLOR!!\n");
		fuerzaManoJugador = 6;
	}
	else if (EsEscalera(manoJugadorCompleta)){
		printf( "El jugador tiene ESCALERA!!\n");
		fuerzaManoJugador = 5;
	}
	else if (EsTrio(manoJugadorCompleta)){
		printf("El jugador tiene UN TRIOO!!\n");
		fuerzaManoJugador = 4;
	} else {
		int esPareja = EsPareja(manoJugadorCompleta);
		if (esPareja){
			if (esPareja != 1){
				printf("El jugador tiene PAREJA  DOBLE!!\n");
				fuerzaManoJugador = 3;
			} else {
				printf("El jugador tiene PAREJA SIMPLE!!\n");
				fuerzaManoJugador = 2;
			}
		}   
		 else {
			printf("El jugador tiene solo Carta Alta!\n");

			TipoCarta* cartaMasAlta = ObtenerCartaMasAlta(manoJugadorCompleta);

			if ((cartaMasAlta->valor >= 2) && (cartaMasAlta->valor <= 10)) {
				printf("La carta es: %d\n - %c", cartaMasAlta->valor, cartaMasAlta->palo);
			} else {
				switch (cartaMasAlta->valor) {
						case 1:
							printf("La carta es: A - %c\n", cartaMasAlta->palo);
							break;
						case 11:
							printf("La carta es: J - %c\n", cartaMasAlta->palo);
							break;
						case 12:
							printf("La carta es: Q - %c\n", cartaMasAlta->palo);
							break;
						case 13:
							printf("La carta es: K - %c\n", cartaMasAlta->palo);
							break;
				}
			}
			 fuerzaManoJugador = 1;
		}
	}


	// Determinar la fuerza de la mano completa del bot
	puts("========================================");
	if (EsEscaleraReal(manoBotCompleta)){
		printf("El bot tiene Escalera Real!!\n");
		fuerzaManoBot = 10;
	}
	else if (EsEscaleraDeColor(manoBotCompleta)){
		printf("El bot tiene una escalera de color!!\n");
		fuerzaManoBot = 9;
	}
	else if (EsPoker(manoBotCompleta)){
		printf("El bot tiene POKER!!\n");
		fuerzaManoBot = 8;
	}
	else if (EsFullHouse(manoBotCompleta)){
		printf("El bot tiene FULL HOUSE!!\n");
		fuerzaManoBot = 7;
	} 
	else if (EsColor(manoBotCompleta)){
		printf("El bot tiene COLOR!!\n");
		fuerzaManoBot = 6;
	}
	else if (EsEscalera(manoBotCompleta)){
		printf( "El bot tiene ESCALERA!!\n");
		fuerzaManoBot = 5;
	}
	else if (EsTrio(manoBotCompleta)){
		printf("El bot tiene UN TRIOO!!\n");
		fuerzaManoBot = 4;
	} else {
		int esPareja = EsPareja(manoBotCompleta);
		if (esPareja){
			if (esPareja != 1){
				printf("El bot tiene PAREJA  DOBLE!!\n");
				fuerzaManoBot = 3;
			} else {
				printf("El bot tiene PAREJA SIMPLE!!\n");
				fuerzaManoBot = 2;
			}
		}   
		 else {
			printf("El bot tiene solo Carta Alta!\n");

			TipoCarta* cartaMasAlta = ObtenerCartaMasAlta(manoBotCompleta);

			if ((cartaMasAlta->valor >= 2) && (cartaMasAlta->valor <= 10)) {
				printf("La carta es: %d\n - %c", cartaMasAlta->valor, cartaMasAlta->palo);
			} else {
				switch (cartaMasAlta->valor) {
						case 1:
							printf("La carta es: A - %c\n", cartaMasAlta->palo);
							break;
						case 11:
							printf("La carta es: J - %c\n", cartaMasAlta->palo);
							break;
						case 12:
							printf("La carta es: Q - %c\n", cartaMasAlta->palo);
							break;
						case 13:
							printf("La carta es: K - %c\n", cartaMasAlta->palo);
							break;
				}
			}
			fuerzaManoBot = 1;
		}
	}
	
	puts("========================================");
	puts("========================================");
	if (fuerzaManoJugador > fuerzaManoBot){
		(*cantFichasBote) += RondaBonus(cantFichasBote);
		(*cantFichasJugador) += (*cantFichasBote);
		printf(" El jugador ha ganado %d fichas !!\n", (*cantFichasBote));
		
	} else if (fuerzaManoJugador < fuerzaManoBot){
		puts(" El bot gana !!");
		
	} else {
		printf(" ES EMPATE, EL BOTE SE REPARTE\n");
		(*cantFichasJugador) += (*cantFichasBote)/2;
		printf(" El Jugador recibe %d fichas !!\n", (*cantFichasBote)/2);
	}
	
	puts("========================================");
}


/// Funcion para obtener las 7 cartas, 2 del jugador y 5 de la mesa 
void ObtenerManoCompleta(List* manoCompleta, List* cartasJugador, TipoBaraja *baraja) {
	TipoCarta* carta = NULL;
	for (carta = list_first(cartasJugador); carta != NULL; carta = list_next(cartasJugador)) {
		list_pushBack(manoCompleta, carta);
	}
	for (carta = list_first(baraja->cartasComunitarias); carta != NULL; 
		carta = list_next(baraja->cartasComunitarias)) {
		list_pushBack(manoCompleta, carta);
	}
	list_sort(manoCompleta, CompararCartas);
}

// Funcion para imprimir el sub-menu del poker
int MenuPoker(int *cantFichasJugador){
	char option; //Option del menu
	 int apuesta = 0;
	 do {
			puts("========================================");
			puts(" Bienvenido a Poker.");
			puts("========================================");
			printf("\n   Cantidad Actual de Fichas: %d\n\n", *cantFichasJugador);
			puts("========================================");
			puts("(1) Jugar");
			puts("(2) Reglas");
			puts("(3) Volver al menú principal");
			puts("========================================");
			printf("Ingrese su opción: \n");
			puts("========================================");
			scanf(" %c", &option);

			//Opciones del menu
			switch (option) {
			case '1':
				limpiarPantalla();
				return 1;

			case '2':
				limpiarPantalla();
				puts("========================================");
				puts("Objetivo: El simulador adapta una versión del clásico Texas Hold'em, al 		final gana todas las fichas del bote el jugador que tenga la mano más fuerte. No hay ciegas, y el bot será siempre	el primero en realizar la acción. Para agregar dificultad, el bot no está obligado a igualar cuando el usuario haga una apuesta.\n");
				puts("========================================");
				puts("Composición del Juego: \n");
				puts("- Cartas-Mazo: Se utiliza una baraja inglesa estándar de 52 cartas.");
				puts("- Jugadores: En esta adaptación, el usuario jugará contra el Dealer (bot o cpu)");
				puts("- Ronda de apuestas: Primero la acción del bot, luego la del jugador.\n");

				puts("========================================");
				puts("Desarrollo del Juego:\n");
				puts("Se reparten 2 cartas a cada jugador y empieza la ronda de apuestas.");
				puts("Luego se colocan hasta 5 cartas comunitarias 'sobre la mesa', 3 en el 'Flop', 1 en el 'Turn', la última en el 'River'.");
				puts("Habrá una ronda de apuestas luego de cada una de estas fases del juego.\n");

				puts("========================================");
				puts("Formación de la Mano:  Los jugadores forman su mejor mano de cinco cartas usando cualquier combinación de sus dos cartas ocultas y las cinco cartas comunitarias.\n");

				puts("========================================");
				puts("Combinaciones Ganadoras (De más fuerte a menos fuerte):\n");
				puts("1. Escalera Real: A, K, Q, J, 10 del mismo palo.");
				puts("2. Escalera de Color: Cinco cartas consecutivas del mismo palo.");
				puts("3. Poker: Cuatro cartas del mismo valor.");
				puts("4. Full House: Tres cartas de un valor y dos de otro.");
				puts("5. Color: Cinco cartas del mismo palo, no consecutivas.");
				puts("6. Escalera: Cinco cartas consecutivas de diferentes palos.");
				puts("7. Trío : Tres cartas del mismo valor.");
				puts("8. Doble Pareja: Dos pares de cartas del mismo valor.");
				puts("9. Pareja: Dos cartas del mismo valor.");
				puts("10. Carta Alta: Si nadie tiene ninguna de las combinaciones anteriores, gana la carta más alta.");
				puts("========================================");
				
				break;
			case '3':
				return 0;
			}
			presioneTeclaParaContinuar();
			limpiarPantalla();

	 } while (option != '0');
	 return 0;
}
//Funcion de juego principal
int PokerGame(int *cantFichasJugador){
	//Determinar apuesta y cantidad de fichas iniciales
	int cantFichasBot = 1000;
	int cantFichasBote = 0;
	int apuestaRonda = 0;
	int desicionJugador;
	//Crear baraja de juego
	TipoBaraja baraja;
	InicializarBaraja(&baraja);

	//Crear la baraja mezclada
	Stack* pilaCartas;
	pilaCartas = MezclarBaraja((&baraja)->listaCartas);

	//Crear la mano del jugador
	List* manoJugador = list_create();
	List* manoJugadorCompleta = list_create();
	//Crear las mano del bot
	List* manoCPU = list_create();
	List* manoCPUCompleta = list_create();

	desicionJugador = MenuPoker(cantFichasJugador);
	
	if (desicionJugador == 1){
		//Empezar a jugar
		puts("========================================");
		puts(" Bienvenido a Poker.");
		puts("========================================");
		// Repartir las 2 cartas iniciales
		for (int i = 0; i < 2; i++) {
			list_pushBack(manoJugador, (TipoCarta*)SacarCarta(pilaCartas));
			list_pushBack(manoCPU, (TipoCarta*)SacarCarta(pilaCartas));
		}
		printf("========================================\n");
		puts("Repartiendo Mano del Jugador:");
		MostrarCartas(manoJugador);

		// Fase de Flop
		Flop(&baraja, pilaCartas);
		RondaApuestas(cantFichasJugador, &apuestaRonda, &cantFichasBot, &cantFichasBote);
		printf(" ////Bote actual: %d///////////////\n", cantFichasBote);


		//Fase del TUrn
		limpiarPantalla();
		Turn(&baraja, pilaCartas);
		RondaApuestas(cantFichasJugador, &apuestaRonda, &cantFichasBot, &cantFichasBote);
		printf(" ////Bote actual: %d////\n", cantFichasBote);

		//Fase del River - ultima carta
		limpiarPantalla();
		River(&baraja, pilaCartas);
		RondaApuestas(cantFichasJugador, &apuestaRonda, &cantFichasBot, &cantFichasBote);


		// Obtener y mostrar las manos completas de 7 cartas
		printf("========================================\n");
		puts("Mostrando Mano Completa del Jugador (Ordenada):");
		ObtenerManoCompleta(manoJugadorCompleta, manoJugador, &baraja);
		MostrarCartas(manoJugadorCompleta);
		printf("========================================\n");
		printf("========================================\n");
		puts("Mostrando Mano Completa del BOT (Ordenada):");
		ObtenerManoCompleta(manoCPUCompleta, manoCPU, &baraja);
		MostrarCartas(manoCPUCompleta);
		printf("========================================\n");

		//Verificamos ganador
		VerificarPremio(manoJugadorCompleta, manoCPUCompleta, cantFichasJugador, &cantFichasBote);

		printf("Fin del juego. Gracias por jugar.\n");
		puts("========================================");
	} else {
		
	}

	//Liberamos la memoria utilizada.
	list_clean(manoJugador);
	list_clean(manoCPU);
	stack_clean(pilaCartas);
	return 0;
}