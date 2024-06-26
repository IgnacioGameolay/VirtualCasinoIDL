#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "blackjack.h"

// Funcion comparación para el mapa
int IsLowerInt(void *key1, void *key2) {
  return *(int *)key1 <= *(int *)key2; 
}


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

int CalcularPuntaje(List* mano){
  int puntaje = 0;
  TipoCarta* carta = list_first(mano);
  while(carta != NULL){
    puntaje += carta->valor;
    carta = list_next(mano);
  }

  return puntaje;
}


void MostrarReglasBlackjack(){

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

void menuBL(){
  printf("========================================\n");
  printf(" Bienvenido a Blackjack.\n");
  printf("========================================\n");
  printf(" 1. Jugar Blackjack\n");
  printf(" 2. Reglas del Juego\n");
  printf(" 3. Menu Principal\n");
}

void determinarGanador(int puntajeJugador, int puntajeDealer, int apuesta, int* chipCount){
  if (puntajeJugador > 21){
    printf("Te has pasado de 21, pierdes la apuesta.\n");
    *chipCount -= apuesta;
  }
  else if (puntajeDealer > 21 && puntajeJugador <= 21){
    printf("El crupier se ha pasado de 21, ganaste la apuesta.\n");
    *chipCount += apuesta * 2;
  }

  else if (puntajeJugador > puntajeDealer && puntajeJugador < 22){
    printf("Ganaste la apuesta.\n");
    *chipCount += apuesta * 2;
  }

  else if (puntajeJugador < puntajeDealer && puntajeDealer < 22){
    printf("Perdiste la apuesta.\n");
    *chipCount -= apuesta;
  }
  else if (puntajeJugador == puntajeDealer && puntajeJugador < 22 && puntajeDealer < 22){
    printf("Es un empate, se devuelve la apuesta.\n");
    *chipCount += apuesta;
  }
  puts("xdddd");
}

void jugarBL(int *chipCount){
  int apuesta;
  char respuesta;
  printf("================================\n");
  printf("Creditos disponibles : %d\n", *chipCount);
  printf("================================\n");
  
  while(1){
    printf("Ingrese la apuesta (mínimo $25): ");
    scanf("%d", &apuesta);
    if (apuesta < 25){
      printf("La apuesta mínima es de $25.\n");
    }
    else if(apuesta >= 25) break;
    else if (apuesta > *chipCount){
      printf("No tienes suficientes fichas para realizar esta apuesta.\n");
      printf("Deseas volver al menu principal? (s/n): ");
      scanf(" %c", &respuesta);
      if (respuesta == 's'){
        return; 
      }
    }
  }

  presioneTeclaParaContinuar();
  limpiarPantalla();

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

  printf("Mano del jugador: ");
  MostrarMano(cartasJugador);
  printf("\nMano del Crupier: ");
  MostrarMano(cartasDealer);

  // Pedir cartas al jugador
  char respuestaJugador;

  puntajeJugador = CalcularPuntaje(cartasJugador);
  puntajeDealer = CalcularPuntaje(cartasDealer);
  printf("\n================================\n");
  printf("Puntaje del jugador: %d\n", puntajeJugador);
  printf("Puntaje del crupier: %d\n", puntajeDealer);

  printf("¿Desea pedir otra carta? (s/n):");

  scanf(" %c", &respuestaJugador);

  presioneTeclaParaContinuar();
  limpiarPantalla();

  while (respuestaJugador == 's' && puntajeJugador < 21){
    list_pushBack(cartasJugador, (TipoCarta*)SacarCarta(pilaCartas));
    puntajeJugador = CalcularPuntaje(cartasJugador);
    printf("Mano del jugador: ");
    MostrarMano(cartasJugador);
    printf("\nMano del Crupier : ");
    MostrarMano(cartasDealer);
    printf("\nPuntaje del jugador: %d\n", puntajeJugador);
    printf("Puntaje del crupier: %d\n", puntajeDealer);
    printf("¿Desea pedir otra carta? (s/n): \n");
    printf("================================\n");
    scanf(" %c", &respuestaJugador);

  }

  // Pedir cartas al crupier
  while (puntajeDealer < 17){
    list_pushBack(cartasDealer, (TipoCarta*)SacarCarta(pilaCartas));
    puntajeDealer = CalcularPuntaje(cartasDealer);
  }
  printf("================================\n");
  printf("Puntaje del jugador: %d\n", puntajeJugador);
  printf("Puntaje del dealer: %d\n", puntajeDealer);
  printf("================================\n");
  
  // Determinar el ganador
  
  determinarGanador(puntajeJugador, puntajeDealer, apuesta, chipCount);

  printf("Creditos: %d\n", *chipCount);

  printf("================================\n");

  printf("¿Desea volver a jugar? (s/n): ");
  scanf(" %c", &respuesta);
  if (respuesta == 's'){
    jugarBL(*chipCount);
  }
  else{
    printf("Gracias por jugar.\n");
  }
  
}

int Blackjack(int *chipCount){
  char respuesta;

  while(1){

    menuBL();
    printf("Ingrese una opcion: ");
    scanf(" %c", &respuesta);
    switch(respuesta){
      case '1':
        jugarBL(chipCount);
        return 0;
      case '2':
        MostrarReglasBlackjack();
        break;
      case '3':
        return 0;
        break;
    }

    
  }
  return 0;
}

/*
int main(){
  int chipCount = 1000;
  Blackjack(&chipCount);
  return 0;
}*/

