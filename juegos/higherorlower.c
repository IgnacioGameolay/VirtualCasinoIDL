#include "higherorlower.h"

typedef struct {
    char palo;
    int valor;
    int clave;
} TipoCarta;

typedef struct {
    List* listaCartas;
    int cartaActual;
} TipoBaraja;



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


void HigherOrLower(int *chipCount){

  int opcion;
    
  while(opcion != 3){
    MenuHL();
    scanf("%i", &opcion);
    switch(opcion){
      case 1:
        juegoHL(chipCount);
        break;
      case 2:
        reglasHL();
        break;
      case 3:
        break;
    }
  }
  
}

