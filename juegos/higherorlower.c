#include "higherorlower.h""

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
  puts("5. Puedes elegir si retirarte o apostar la siguiente carta. Si fallas, pierdes la cantidad apostada. Si te retiras, ganas lo apostado por el multiplicador");
  puts("6. El juego continúa hasta que decidas retirarte o te quedes sin fichas.");
  puts("7. ¡Buena suerte y diviértete!");
  puts("========================================");
}

void juegoHL(int *chipCount){
  int apuesta = 0;
  tipoCarta cartaActual = 0;
  tipoCarta cartaSiguiente = 0;
  tipoCarta cartaAnterior = 0;
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