#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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