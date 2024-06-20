#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"


typedef struct {
        int valor;  // 1 para As, 11 para J, 12 para Q, 13 para K, y 2-10 para las cartas numéricas
        int clave;
        char palo;
} TipoCarta;

typedef struct {
        List *listaCartas;
        int cartaActual;  // Índice de la próxima carta a repartir
} TipoBaraja;


//Funcion para inicializar una baraja principal con las 52 cartas existentes (baraja inglesa).
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
    TipoCarta* aux = stack_pop(barajada);
    return aux;
}

int main(){
    printf("d");
    TipoBaraja baraja;

    InicializarBaraja(&baraja);

    Stack* pilaCartas;
    pilaCartas = MezclarBaraja((&baraja)->listaCartas);
    printf("d");
    List* manoJugador = list_create();
    List* manoCPU = list_create();

    // Repartir cartas 1ra ronda
    for (int i = 0; i < 5; i++) {
        list_pushBack(manoJugador, (TipoCarta*)SacarCarta(pilaCartas));
        list_pushBack(manoCPU, (TipoCarta*)SacarCarta(pilaCartas));
    }

    printf("Mano del jugador: \n");
    MostrarCartas(manoJugador);
    printf("Mano de la CPU \n");
    MostrarCartas(manoCPU);
    return 0;
}


/*void Poker(int chipCount) {
    TipoBaraja baraja;
    InicializarBaraja(&baraja);
    Stack* pilaCartas = MezclarBaraja(baraja.listaCartas);

    List* manoJugador = list_create();
    List* manoCPU = list_create();

    // Repartir cartas
    for (int i = 0; i < 5; i++) {
        list_pushBack(manoJugador, stack_pop(pilaCartas));
        list_pushBack(manoCPU, stack_pop(pilaCartas));
    }

    // Mostrar mano del jugador
    printf("Tu mano:\n");
    MostrarMano(manoJugador);

    // Mostrar mano de la CPU
    printf("\nMano de la CPU:\n");
    MostrarMano(manoCPU);

    // Evaluar manos y determinar ganador
    printf("\nGanador: ");
    // Implementa la lógica de evaluación de manos aquí

    // Liberar memoria
    list_destroy(manoJugador);
    list_destroy(manoCPU);
    stack_destroy(pilaCartas);
}*/