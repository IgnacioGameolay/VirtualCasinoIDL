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
void MostrarCartas(TipoBaraja *baraja){
  TipoCarta* carta = list_first(baraja->listaCartas);

  while(carta != NULL){
    if (carta->valor >= 2 && carta->valor <= 10) {
      printf("%d%c ", carta->valor, carta->palo);
    } else {
      switch (carta->valor) {
          case 1:
              printf("A%c ", carta->palo);
              break;
          case 11:
              printf("J%c ", carta->palo);
              break;
          case 12:
              printf("Q%c ", carta->palo);
              break;
          case 13:
              printf("K%c ", carta->palo);
              break;
      }
    }

      carta = list_next(baraja->listaCartas);
  }
}

// Funcion para sacar una carta de la baraja

TipoCarta* SacarCarta(Stack* barajada){
  TipoCarta* carta = stack_pop(barajada);
  return carta;
}

// Funcion para mostrar mano

void MostrarMano(List* mano){
  TipoCarta* carta = list_first(mano);
  while(carta != NULL){
    printf( "%d%c ", carta->valor, carta->palo);
    carta = list_next(mano);
  }
}

int calcularPuntaje(List* mano){
  int puntaje = 0;
  TipoCarta* carta = list_first(mano);
  while(carta != NULL){
    puntaje += carta->valor;
    carta = list_next(mano);
  }

  return puntaje;
}


void mostrarReglas(){

  printf("===== Reglas del Blackjack =====\n");
  printf("Objetivo del Juego:\n");
  printf("  - El objetivo del Blackjack es sumar 21 puntos o acercarse lo más posible a esta cifra sin     pasarse.\n");
  printf("  - Cada jugador juega contra el crupier, no contra otros jugadores.\n\n");

  printf("Valor de las Cartas:\n");
  printf("  - Las cartas numeradas del 1 al 10 tienen su valor nominal.\n");
  printf("  - Las cartas con figuras (11, 12, 13) valen 10 puntos cada una.\n");

  printf("Desarrollo del Juego:\n");
  printf(" 1. El jugador recibe dos cartas al inicio del juego, al igual que el crupier.\n");
  printf(" 2. Una de las cartas del crupier se reparte boca arriba y la otra boca abajo.\n");
  printf(" 3. El jugador pueden pedir más cartas para acercarse a 21 puntos o plantarse si creen que tienen una mano fuerte.\n");
  printf(" 4. Si la mano de un jugador supera los 21 puntos, pierde automáticamente.\n");
  printf(" 5. Después de que el jugador ha terminado su turno, el crupier revela su carta oculta y debe pedir cartas hasta sumar al menos 17 puntos.\n\n");

  printf("Condiciones de Victoria:\n");
  printf("  - Si el crupier se pasa de 21 puntos, el jugador si no se ha pasado de 21 gana.\n");
  printf("  - Si el jugador tiene más puntos que el crupier sin pasarse de 21, gana.\n");
  printf("  - Si el jugador tiene menos puntos que el crupier, pierde.\n");
  printf("  - Si el jugador y el crupier tienen la misma cantidad de puntos, es un empate y se devuelve   la apuesta al jugador.\n\n");

  printf("Apuestas y Pagos:\n");
  printf("  - El Blackjack (21 puntos con las dos primeras cartas) paga x3.\n");
  printf("  - Las apuestas ganadoras normales pagan x2.\n");

  printf("================================\n");

}


void Blackjack(int chipCount){
  char respuesta;
  int apuesta;
  
  printf("===== Bienvenido al Blackjack =====\n");
  printf("Conoces las reglas del juego? (s/n): ");
  scanf(" %c", &respuesta);
  
  if (respuesta == 'n'){
    mostrarReglas();
  }
  
  while(apuesta < 25){
    printf("Ingrese la apuesta (mínimo $25): ");
    scanf("%d", &apuesta);
    if (apuesta < 25){
      printf("La apuesta mínima es de $25.\n");
    }
  }

  printf("================================\n");
  printf("Iniciando el juego...\n");
  printf("================================\n");
  // Inicializar la baraja

  TipoBaraja barajaPrincipal;
  InicializarBaraja(&barajaPrincipal);
  
  // Repartir cartas 1ra ronda
  Stack* pilaCartas = MezclarBaraja((&barajaPrincipal)->listaCartas);

  int puntajeJugador = 0;
  int puntajeDealer= 0;

  List * cartasJugador = list_create();
  List * cartasDealer = list_create();

  // Repartir cartas 1ra ronda

  for (int i = 0; i < 2; i++){
    list_pushBack(cartasJugador, (TipoCarta*)SacarCarta(pilaCartas));
    list_pushBack(cartasDealer, (TipoCarta*)SacarCarta(pilaCartas));
  }

  printf("Mano del jugador: \n");
  MostrarMano(cartasJugador);
  printf("Mano de la CPU \n");
  MostrarMano(cartasDealer);

  // Pedir cartas al jugador
  char respuestaJugador;

  puntajeJugador = calcularPuntaje(cartasJugador);
  puntajeDealer = calcularPuntaje(cartasDealer);

  printf("Puntaje del jugador: %d\n", puntajeJugador);
  printf("Puntaje del crupier: %d\n", puntajeDealer);

  printf("¿Desea pedir otra carta? (s/n): ");

  scanf(" %c", &respuestaJugador);
  while (respuestaJugador == 's' && puntajeJugador < 21){
    list_pushBack(cartasJugador, (TipoCarta*)SacarCarta(pilaCartas));
    puntajeJugador = calcularPuntaje(cartasJugador);
    printf("Puntaje del jugador: %d\n", puntajeJugador);
    printf("¿Desea pedir otra carta? (s/n): ");
    scanf(" %c", &respuestaJugador);
  }

  // Pedir cartas al crupier
  while (puntajeDealer < 17){
    list_pushBack(cartasDealer, (TipoCarta*)SacarCarta(pilaCartas));
    puntajeDealer = calcularPuntaje(cartasDealer);
  }
  
  
  
}