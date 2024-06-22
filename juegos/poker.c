#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"

typedef struct {
    int numeroRonda; // Número de la ronda (preflop, flop, turn, river)
    int apuestaActual; // Apuesta actual en la ronda
    int jugadorActual; // Índice del jugador que debe actuar
    int accionActual; // Acción actual (apostar, igualar, subir, pasar, retirarse)
} TipoRondaApuestas;


typedef struct {
        int valor;  // 1 para As, 11 para J, 12 para Q, 13 para K, y 2-10 para las cartas numéricas
        int clave;
        char palo;
} TipoCarta;

typedef struct {
        List *listaCartas;
        List *cartasComunitarias; // Cartas comunitarias (flop, turn, river)
        TipoRondaApuestas ronda; // Información de la ronda actual de apuestas
} TipoBaraja;


//Funcion para inicializar una baraja principal con las 52 cartas existentes (baraja inglesa).
void InicializarBaraja(TipoBaraja *baraja) { 
    baraja->listaCartas = list_create();
    baraja->cartasComunitarias = list_create();
    baraja->ronda.numeroRonda = 0; // Empieza en preflop
    baraja->ronda.apuestaActual = 0;
    baraja->ronda.jugadorActual = 0;
    baraja->ronda.accionActual = 0;
    
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
void MostrarCartas(List* listaCartas){
    TipoCarta* carta = list_first(listaCartas);

    while(carta != NULL){
        if (carta->valor >= 2 && carta->valor <= 10) {
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

// Mostrar cartas de una baraja STACK
void MostrarBarajada(Stack* barajada){
    TipoCarta* aux = stack_pop(barajada);

    while(aux != NULL){
        printf("Palo: %c - Valor: %d\n", aux->palo, aux->valor);
        aux = stack_pop(barajada);
    }
}

TipoCarta* SacarCarta(Stack* barajada){
    return (TipoCarta*) stack_pop(barajada);
}



void Flop(TipoBaraja *baraja, Stack* pilaCartas){
    printf("========================================\n");
    printf("Repartiendo el Flop...\n");
    for (int i = 0; i < 3; i++) {
        list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
    }
    printf("========================================\n");

    printf("Cartas Comunitarias en el Flop:\n");
    MostrarCartas(baraja->cartasComunitarias);
    
}

void Turn(TipoBaraja *baraja, Stack* pilaCartas){
    printf("========================================\n");
    printf("Repartiendo el Turn...\n");
    list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
    printf("========================================\n");

    printf("Cartas Comunitarias en el Turn:\n");
    MostrarCartas(baraja->cartasComunitarias);
}

void River(TipoBaraja *baraja, Stack* pilaCartas){
    printf("========================================\n");
    printf("Repartiendo el River...\n");
    list_pushBack(baraja->cartasComunitarias, (TipoCarta*)SacarCarta(pilaCartas));
    printf("========================================\n");
    
    printf("Cartas Comunitarias en el River:\n");
    MostrarCartas(baraja->cartasComunitarias);
    
}


void Apostar(int *apuestaActual, int *fichasJugador) {
    int cantidad;
    do {
        printf("Ingrese la cantidad a apostar: ");
        scanf("%d", &cantidad);

        if (*fichasJugador >= cantidad) {
            *apuestaActual += cantidad;
            *fichasJugador -= cantidad;
            printf("El jugador ha apostado %d fichas. Apuesta actual: %d\n", cantidad, *apuestaActual);
            break;  // Salir del bucle cuando la apuesta sea válida
        } else {
            printf("No tienes suficientes fichas para apostar. Tienes %d fichas.\n", *fichasJugador);
        }
    } while (1);  // Continuar pidiendo hasta que se haga una apuesta válida
}


void Igualar(int apuestaActual, int *fichasJugador) {
    if (*fichasJugador >= apuestaActual) {
        *fichasJugador -= apuestaActual;
        printf("El jugador ha igualado con %d fichas.\n", apuestaActual);
    } else {
        printf("No tienes suficientes fichas para igualar.\n");
    }
}


void Subir(int *apuestaActual, int *fichasJugador, int cantidad) {
    if (*fichasJugador >= (cantidad + *apuestaActual)) {
        *apuestaActual += cantidad;
        *fichasJugador -= cantidad;
        printf("El jugador ha subido la apuesta en %d fichas. Apuesta actual: %d\n", cantidad, *apuestaActual);
    } else {
        printf("No tienes suficientes fichas para subir la apuesta.\n");
    }
}


void Pasar() {
    printf("El jugador ha pasado su turno.\n");
}

void Retirarse() {
    printf("El jugador se ha retirado del juego.\n");
}



int AccionesBot(int *fichasBot, int *apuestaActual){
    
    int accion = 1 + rand() % 2; // Genera un número aleatorio entre 0 y 3
    int cantidad;
    switch (accion) {
        case 1:  // buena mano
            // Bot siempre sube con una buena mano
            cantidad = *apuestaActual + (rand() % 100 + 50);  // Subir entre 50 y 150 fichas

            if (*fichasBot >= cantidad) {
                *apuestaActual += cantidad;
                *fichasBot -= cantidad;
                printf("El bot ha subido la apuesta en %d fichas. Apuesta actual: %d\n", cantidad, *apuestaActual);
            } else {
                printf("El bot no tiene suficientes fichas para subir.\n");
            }
            break;

        case 2:
            printf("El bot ha pasado su turno.\n");
            break;
    }
    return accion;
}

void RondaApuestas(int *cantFichasJugador, int *apuestaActual, int *cantFichasBot, int *cantFichasBote){
    int apuestaAux = 0; //variable de apuesta auxiliar, para igualar o subir
    char option;
    int accionBot;
    do {
        puts("========================================");
        printf("\n   Cantidad Actual de Fichas del Bot: %d\n\n", *cantFichasBot);
        puts("========================================");
        accionBot = AccionesBot(cantFichasBot, apuestaActual);

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
                        Apostar(apuestaActual, cantFichasJugador);
                        return;
                    case '2':
                        Igualar(*apuestaActual, cantFichasJugador);
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
                        Apostar(apuestaActual, cantFichasJugador);
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
    
void TurnoJugador(int *fichasJugador, int *apuestaActual) {
    printf("Turno del jugador\n");
    int opcion;
    printf("1. Apostar\n2. Igualar\n3. Subir\n4. Pasar\n5. Retirarse\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            Apostar(apuestaActual, fichasJugador);
            break;
        case 2:
            Igualar(*apuestaActual, fichasJugador);
            break;
        case 3: {
            int cantidad;
            printf("Ingrese la cantidad a subir: ");
            scanf("%d", &cantidad);
            Subir(apuestaActual, fichasJugador, cantidad);
            break;
        }
        case 4:
            Pasar();
            break;
        case 5:
            Retirarse();
            *fichasJugador = 0;  // Se retira del juego
            break;
        default:
            printf("Opción inválida. Por favor, seleccione una opción válida.\n");
            break;
    }
}

int main(){
    int cantFichasJugador = 10000;
    int cantFichasBot = 1000;
    int cantFichasBote = 0;
    int apuesta = 0;
    
    TipoBaraja baraja;
    InicializarBaraja(&baraja);

    Stack* pilaCartas;
    pilaCartas = MezclarBaraja((&baraja)->listaCartas);
    
    List* manoJugador = list_create();
    List* manoCPU = list_create();

    // Repartir cartas iniciales
    for (int i = 0; i < 2; i++) {
        list_pushBack(manoJugador, (TipoCarta*)SacarCarta(pilaCartas));
        list_pushBack(manoCPU, (TipoCarta*)SacarCarta(pilaCartas));
    }

    puts("========================================");
    puts(" Bienvenido a Poker.");
    puts("========================================");
    puts("========================================");
    /*
    puts("Repartendo Mano del Jugador:");
    MostrarCartas(manoJugador);
    puts("========================================");
    
    Flop(&baraja, pilaCartas);
    RondaApuestas(&cantFichasJugador, &apuesta, &cantFichasBot, &cantFichasBote);    
    
    Turn(&baraja, pilaCartas);
    RondaApuestas(&cantFichasJugador, &apuesta, &cantFichasBot, &cantFichasBote);    
    
    River(&baraja, pilaCartas);
    RondaApuestas(&cantFichasJugador, &apuesta, &cantFichasBot, &cantFichasBote);    
    */


    // Empezamos el ciclo de apuestas
    while (cantFichasJugador > 0 && cantFichasBot > 0) {
        printf("========================================\n");
        printf("Inicio de una nueva ronda de apuestas\n");
        printf("========================================\n");

        // Turno del bot primero
        AccionesBot(&cantFichasBot, &apuesta);

        // Si el bot no ha pasado, el jugador tiene que actuar
        if (apuesta > 0) {
            TurnoJugador(&cantFichasJugador, &apuesta);
        }

        // Continuar con la siguiente ronda si ambos jugadores tienen fichas
        if (cantFichasJugador > 0 && cantFichasBot > 0) {
            // Simular las siguientes rondas del juego (Flop, Turn, River)
            Flop(&baraja, pilaCartas);
            Turn(&baraja, pilaCartas);
            River(&baraja, pilaCartas);

            // Resetear apuestas para la siguiente ronda
                apuesta = 0;
        }
    }

    printf("Fin del juego. Gracias por jugar.\n");
    
    list_clean(manoJugador);
    list_clean(manoCPU);
    stack_clean(pilaCartas);
    return 0;
}