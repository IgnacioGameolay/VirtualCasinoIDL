#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"

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
int IsLowerInt(void *key1, void *key2) {
    return *(int *)key1 <= *(int *)key2; 
}

int is_equal_int(void *key1, void *key2) {
    return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

int is_equal_str(void *key1, void *key2) {
    return strcasecmp((char *)key1, (char *)key2) == 0;
}


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
    
    int accion = 1 + rand() % 2; // Generar num entre 1 y 2 
    int cantidad;
    switch (accion) {
        case 1:  // subir apuesta
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

        case 2: // pasar turno
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


List* CrearManoCompletaPerso(){
    List* mano = list_create();

    // Crear una escalera real del mismo palo, por ejemplo, Corazones ('C')
    int valoresEscaleraReal[] = {1, 10, 11, 12, 13};  // 10, J, Q, K, A
    char paloEscaleraReal = 'C';  // Corazones

    // Agregar las 5 cartas de la escalera real a la mano
    for (int i = 0; i < 5; i++) {
        TipoCarta *carta = (TipoCarta *)malloc(sizeof(TipoCarta));
        carta->valor = valoresEscaleraReal[i];
        carta->palo = paloEscaleraReal;
        carta->clave = 1 + rand() % 4;
        list_pushBack(mano, carta);
    }

    // Agregar 2 cartas adicionales al azar
    for (int i = 0; i < 2; i++) {
        TipoCarta *carta = (TipoCarta *)malloc(sizeof(TipoCarta));
        carta->valor = 2 + rand() % 9;  // Valores entre 2 y 10
        carta->palo = 'C' + rand() % 4;  // Un palo al azar
        carta->clave = 1 + rand() % 4;
        list_pushBack(mano, carta);
    }

    list_sort(mano, CompararCartas);
    return mano;
}

int EsColor(List* manoCompleta){
    TipoCarta* cartaActual = NULL;
    
    TipoCarta* cartaPrimera = list_first(manoCompleta);
    char palo = cartaPrimera->palo;
    
    for (int i = 0; i < 5; i++){
        cartaActual = list_next(manoCompleta);   
        if (cartaActual->palo != palo) return 0;
    }
    return 1;
}

int EsEscalera(List* manoCompleta){
    // Ordenar la mano por valor de carta de forma ascendente
    //list_sort(manoCompleta, CompararCartas);

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

int EsEscaleraDeColor(List* manoCompleta){
    if ((EsColor(manoCompleta)) && (EsEscalera(manoCompleta))) return 1;
    return 0;
}

int EsPareja(List* manoCompleta){
    Map* mapaFrecuenciaValores = NULL;
    mapaFrecuenciaValores = map_create(is_equal_int);

    TipoCarta* carta = NULL;
    for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {
        
        MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

        if (pair == NULL){
            int* frecuenciaValor = (int*)malloc(sizeof(int));
            *frecuenciaValor = 1;
            map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
        } else {
            (*((int *)pair->value))++;
        }
    }
    
    //printf("Cantidad de apariciones de cada valor en la mano:\n");
    int cantParejas = 0;
    MapPair *current_pair = map_first(mapaFrecuenciaValores);
    while (current_pair != NULL) {
        int frecuencia = *((int *)current_pair->value);
        if (frecuencia == 2) cantParejas++;
        current_pair = map_next(mapaFrecuenciaValores);
    }
    
    map_clean(mapaFrecuenciaValores);
    free(mapaFrecuenciaValores);
    
    if (cantParejas == 1) return 1;
    else if (cantParejas == 2) return 2;
    return 0;
}


int EsTrio(List* manoCompleta){
    Map* mapaFrecuenciaValores = NULL;
    mapaFrecuenciaValores = map_create(is_equal_int);

    TipoCarta* carta = NULL;
    for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

        MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

        if (pair == NULL){
            int* frecuenciaValor = (int*)malloc(sizeof(int));
            *frecuenciaValor = 1;
            map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
        } else {
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

int EsFullHouse(List* manoCompleta){
    Map* mapaFrecuenciaValores = NULL;
    mapaFrecuenciaValores = map_create(is_equal_int);

    TipoCarta* carta = NULL;
    for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

        MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

        if (pair == NULL){
            int* frecuenciaValor = (int*)malloc(sizeof(int));
            *frecuenciaValor = 1;
            map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
        } else {
            (*((int *)pair->value))++;
        }
    }

    //printf("Cantidad de apariciones de cada valor en la mano:\n");
    int cantParejas = 0;
    int cantTrios = 0;
    MapPair *current_pair = map_first(mapaFrecuenciaValores);
    while (current_pair != NULL) {
        int frecuencia = *((int *)current_pair->value);
        
        if ((cantParejas == 1) && (cantTrios == 1)){
            map_clean(mapaFrecuenciaValores);
            free(mapaFrecuenciaValores);
            return 1;
        }
        if (frecuencia == 2) cantParejas++;
        if (frecuencia == 3) cantTrios++;
        current_pair = map_next(mapaFrecuenciaValores);
    }

    printf("Cantidad de apariciones de cada valor en la mano:\n");
    current_pair = map_first(mapaFrecuenciaValores);
    while (current_pair != NULL) {
        int frecuencia = *((int *)current_pair->value);
        int card = *((int *)current_pair->key);
        printf("la carta %d se repite %d veces\n", card, frecuencia);
        current_pair = map_next(mapaFrecuenciaValores);
    }
    printf("LA cant de trios y duplas es: %d y %d\n", cantTrios, cantParejas);
    map_clean(mapaFrecuenciaValores);
    free(mapaFrecuenciaValores);

    return 0;
}

int EsPoker(List* manoCompleta){
    Map* mapaFrecuenciaValores = NULL;
    mapaFrecuenciaValores = map_create(is_equal_int);

    TipoCarta* carta = NULL;
    for (carta = list_first(manoCompleta); carta != NULL; carta = list_next(manoCompleta)) {

        MapPair* pair = map_search(mapaFrecuenciaValores, &carta->valor);

        if (pair == NULL){
            int* frecuenciaValor = (int*)malloc(sizeof(int));
            *frecuenciaValor = 1;
            map_insert(mapaFrecuenciaValores, &carta->valor, frecuenciaValor);
        } else {
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

int EsEscaleraReal(List* manoCompleta){
    Map* mapaFrecuenciaValores = NULL;
    mapaFrecuenciaValores = map_create(is_equal_int);

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
    
    while (current_pair != NULL) {
        //printf(" Cartas del palo: %s\n", (char*)current_pair->key);
        // Verificar si hay una escalera real en este palo

        int hayAs = 0, hayRey = 0, hayReina = 0, hayJota = 0, hayDiez = 0;

        TipoCarta* carta = list_first(current_pair->value);

        while(carta != NULL){

            //Logica para determinar si es escalera real
            if (carta->valor == 1) hayAs = 1;  // As
            else if (carta->valor == 13) hayRey = 1;  // Rey
            else if (carta->valor == 12) hayReina = 1;  // Reina
            else if (carta->valor == 11) hayJota = 1;  // Jota
            else if (carta->valor == 10) hayDiez = 1;  // Diez
            
            carta = list_next(current_pair->value);
        }

        //Comprobar si estan las Cartas Reales
        if (hayAs && hayRey && hayReina && hayJota && hayDiez) {
            map_clean(mapaFrecuenciaValores);
            free(mapaFrecuenciaValores);
            return 1;
        }

        current_pair = map_next(mapaFrecuenciaValores);
    }
    
    return 0;
}


TipoCarta* ObtenerCartaMasAlta(List* mano) {
    TipoCarta* cartaMasAlta = list_first(mano);
    TipoCarta* cartaActual = cartaMasAlta;

    while (cartaActual != NULL) {
        if (cartaActual->valor == 1) return cartaMasAlta; //retornar el As como carta mas alta
        if (cartaActual->valor > cartaMasAlta->valor) {
            cartaMasAlta = cartaActual;
        }
        cartaActual = list_next(mano);
    }

    return cartaMasAlta;
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
    List* manoJugadorCompleta = list_create();
    
    List* manoCPU = list_create();
    List* manoCPUCompleta = list_create();

    List* manoPerso = NULL;
    manoPerso = CrearManoCompletaPerso();
    
    // Repartir cartas iniciales
    for (int i = 0; i < 2; i++) {
        list_pushBack(manoJugador, (TipoCarta*)SacarCarta(pilaCartas));
        list_pushBack(manoCPU, (TipoCarta*)SacarCarta(pilaCartas));
    }
    printf("========================================\n");
    puts("Repartendo Mano del Jugador:");
    MostrarCartas(manoJugador);
    Flop(&baraja, pilaCartas);
    Turn(&baraja, pilaCartas);
    River(&baraja, pilaCartas);
    printf("========================================\n");
    puts("Mostrando Mano Completa del Jugador (Ordenada):");
    ObtenerManoCompleta(manoJugadorCompleta, manoJugador, &baraja);
    MostrarCartas(manoJugadorCompleta);
    printf("========================================\n");

    /*if (EsFullHouse(manoJugadorCompleta)){
        printf("El jugador tiene FULL HOUSE!!\n");
        return 4;
    }*/

    if (EsEscaleraReal(manoJugadorCompleta)){
        printf("El jugador tiene Escalera Real!!\n");
        //return 1;
    }
    else if (EsEscaleraDeColor(manoJugadorCompleta)){
        printf("El jugador tiene una escalera de color!!\n");
        //return 2;
    }
    else if (EsPoker(manoJugadorCompleta)){
        printf("El jugador tiene POKER!!\n");
        //return 3;
    }
    else if (EsFullHouse(manoJugadorCompleta)){
        printf("El jugador tiene FULL HOUSE!!\n");
        //return 4;
    } 
    else if (EsColor(manoJugadorCompleta)){
        printf("El jugador tiene COLOR!!\n");
        //return 5;
    }
    else if (EsEscalera(manoJugadorCompleta)){
        printf( "El jugador tiene ESCALERA!!\n");
        //return 6;
    }
    else if (EsTrio(manoJugadorCompleta)){
        printf("El jugador tiene UN TRIOO!!\n");
        //return 7;
    } else {
        int esPareja = EsPareja(manoJugadorCompleta);
        if (esPareja){
            if (esPareja != 1){
                printf("El jugador tiene PAREJA  DOBLE!!\n");
                //return 8;
            } else {
                printf("El jugador tiene PAREJA SIMPLE!!\n");
                //return 9;
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
            //return 10;
        }
    }


    


    
    /*
    puts("========================================");
    puts(" Bienvenido a Poker.");
    puts("========================================");
    puts("========================================");

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
    /*while (cantFichasJugador > 0 && cantFichasBot > 0) {
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
    }*/

    printf("Fin del juego. Gracias por jugar.\n");
    
    list_clean(manoJugador);
    list_clean(manoCPU);
    stack_clean(pilaCartas);
    return 0;
}