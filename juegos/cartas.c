#include "juegos/cartas.h"

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