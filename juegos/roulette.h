#ifndef ROULETTE_H
#define ROULETTE_H

#define NUM_CASILLAS 37

typedef struct{
  int apuesta; //Cantidad apostada por el jugador
  int numero; //Número de la casilla a la que apuesta el jugador
  int color; //Color de la casilla a la que apuesta el jugador
  const char* tipo; //Tipo de apuesta hecha por el jugador
}TipoApuesta;

int evaluarApuesta(int apuesta, int numero);
void girarRuleta();
void ruleta(int chipCount);


#endif /* ROULETTE_H */