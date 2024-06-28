#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../tdas/list.h"
#include "../tdas/stack.h"
#include "../tdas/map.h"
#include "../tdas/extra.h"
#define NUM_CASILLAS 37
#define MIN_CHIPS 50

typedef struct
{
  int monto;
  int numero; 
  const char* color; 
  const char* paridad; 
  int columna; 
  int docena; 
  int mitad; 
  int tipo; 
}TipoApuesta;

typedef struct
{
  int roulette[NUM_CASILLAS];
  int casillaActual;
}TipoRuleta;

void inicializarRuleta(TipoRuleta *ruleta);
{  
  int i;
  for(i = 0; i < NUM_CASILLAS; i++)
  {
    ruleta->roulette[i] = i;
  }
  ruleta->casillaActual = -1;
}

void crearApuesta(TipoApuesta* apuesta, int *chips)
{
  printf("¿Qué tipo de apuesta desea hacer?\n");
  printf("1. Número\n");
  printf("2. Color\n");
  printf("3. Paridad\n");
  printf("4. Columna\n");
  printf("5. Docena\n");
  printf("6. Mitad\n");

  int tipo;
  scanf("%d", &tipo);

  int monto;
  printf("¿Qué monto desea apostar?\n");
  scanf("%d", &monto);
  if(monto > *chips || monto < MIN_CHIPS)
  {
    printf("No tienes suficientes fichas para apostar o has apostado una cantidad menor que el valor mínimo. Prueba con otro juego.\n");
    return;
  }
  apuesta->monto = monto;

  switch (tipo) 
  {
    case 1: // Apuesta a número
      apuesta->tipo = 1;
      printf("Ingrese el número al que desea apostar (0-36):\n");
      scanf("%d", &apuesta->numero);
      break;
    case 2: // Apuesta a color
      apuesta->tipo = 2;
      printf("Ingrese el color al que desea apostar (Rojo, Negro, Verde):\n");
      char color[10];
      scanf("%s", color);
      if (strcmp(color, "Rojo") == 0 || strcmp(color, "Negro") == 0 || strcmp(color, "Verde") == 0)
      {
        apuesta->color = strdup(color);
      } 
      else
      {
        printf("Color inválido. Apuesta cancelada.\n");
        return;
      }
      break;
    case 3: // Apuesta a paridad
      apuesta->tipo = 3;
      printf("Ingrese la paridad a la que desea apostar (Par, Impar):\n");
      char paridad[10];
      scanf("%s", paridad);
      if (strcmp(paridad, "Par") == 0 || strcmp(paridad, "Impar") == 0)
      {
        apuesta->paridad = strdup(paridad);
      } 
      else 
      {
        printf("Paridad inválida. Apuesta cancelada.\n");
        return;
      }
      break;
    case 4: // Apuesta a columna
      apuesta->tipo = 4;
      printf("Ingrese la columna a la que desea apostar (1 - 2 - 3):\n");
      scanf("%d", &apuesta->columna);
      if (apuesta->columna < 1 || apuesta->columna > 3) 
      {
        printf("Columna inválida. Apuesta cancelada.\n");
        return;
      }
      break;
    case 5: // Apuesta a docena
      apuesta->tipo = 5;
      printf("Ingrese la docena a la que desea apostar (1 - 2 - 3):\n");
      scanf("%d", &apuesta->docena);
      if (apuesta->docena < 1 || apuesta->docena > 3) 
      {
        printf("Docena inválida. Apuesta cancelada.\n");
        return;
      }
      break;
    case 6: // Apuesta a mitad
      apuesta->tipo = 6;
      printf("Ingrese la mitad a la que desea apostar (1 - 2):\n");
      scanf("%d", &apuesta->mitad);
      if (apuesta->mitad < 1 || apuesta->mitad > 2) 
      {
        printf("Mitad inválida. Apuesta cancelada.\n");
        return;
      }
      break;
    default:
      printf("Tipo de apuesta inválido. Apuesta cancelada.\n");
      return;
  }
  printf("Apuesta creada exitosamente.\n");
}

void girarRuleta(TipoRuleta *ruleta)
{
  srand(time(NULL));
  int indiceGanador = rand() % NUM_CASILLAS;
  ruleta->casillaActual = ruleta->roulette[indiceGanador];
}

int esRojo(int numero)
{
  int rojos[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
  int n = sizeof(rojos) / sizeof(rojos[0]);
  for (int i = 0; i < n; i++) {
      if (rojos[i] == numero) {
          return 1;
      }
  }
  return 0;
}

int esNegro(int numero)
{
  int negros[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
  int n = sizeof(negros) / sizeof(negros[0]);
  for (int i = 0; i < n; i++) {
      if (negros[i] == numero) {
          return 1;
      }
  }
  return 0;
}

int obtenerColumna(int numero)
{
  if(numero == 0) return 0;
  if (numero % 3 == 1) {
    return 1; // Primera columna
  } else if (numero % 3 == 2) {
    return 2; // Segunda columna
  } else if (numero % 3 == 0) {
    return 3; // Tercera columna
  }
}

int evaluarApuesta(TipoApuesta *apuesta, TipoRuleta *ruleta)
{
  int resultado = ruleta->casillaActual;
  switch (apuesta->tipo)
    {
      case 1:
        if (apuesta->numero == resultado)
        {
          printf("¡Felicidades! Has ganado!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido.\n");
          return 0;
        }
        break;
      case 2:
        if (esRojo(resultado) && strcmp(apuesta->color, "Rojo") == 0 || esNegro(resultado) && strcmp(apuesta->color, "Negro") || resultado == 0 || resultado == 0 && strcmp(apuesta->color, "Verde") == 0))
        {
          printf("¡Felicidades! Has ganado!\n");
        }
        else
        {
          printf("Lo siento, has perdido.\n");
        }
        break;
      case 3:
        if (strcmp(apuesta->paridad, "Par") == 0 && resultado % 2 == 0 || strcmp(apuesta->paridad, "Impar") == 0 && resultado % 2 != 0))
        {
          printf("¡Felicidades! Has ganado!\n");
        }
        else
        {
          printf("Lo siento, has perdido.\n");
        }
        break;
      case 4:
        if (apuesta->columna == obtenerColumna(resultado))
        {
          printf("¡Felicidades! Has ganado!\n");
        }
        else
        {
          printf("Lo siento, has perdido.\n");
        }
        break;
      case 5:
        if (apuesta->docena == 1 && resultado >= 1 && resultado <= 12 || apuesta->docena == 2 && resultado >= 13 && resultado <= 24 || apuesta->docena == 3 && resultado >= 25 && resultado <= 36)
        {
          printf("¡Felicidades! Has ganado!\n");
        }
        else
        {
          printf("Lo siento, has perdido.\n");
        }
        break;
      case 6:
        if (apuesta->mitad == 1 && resultado >= 1 && resultado <= 18 || apuesta->mitad == 2 && resultado >= 19 && resultado <= 36))
        {
          printf("¡Felicidades! Has ganado!\n");
        }
        else
        {
          printf("Lo siento, has perdido.\n");
        }
        break;
      default:
        printf("Tipo de apuesta inválido.\n");
        break;
    }
}

int Ruleta(int *chipCount)
{
  char option; //Option del menu
  int apuesta = 0;
  do
  {
    puts("========================================");
    puts(" Bienvenido a la Ruleta.");
    puts("========================================");
    printf("\n   Cantidad Actual de Fichas: %d\n\n", *chipCount);
    puts("========================================");
    puts("(1) Jugar");
    puts("(2) Reglas");
    puts("(3) Volver al menú principal");
    puts("========================================");
    printf("Ingrese su opción: \n");
    puts("========================================");
    scanf(" %c", &option);

    //Opciones del menu
    switch (option)
    {
      case '1':
        puts("========================================");
        puts("¡Muy bien, vamos a jugar!");
        puts(" Ingrese su apuesta: ");
        scanf("%d", &apuesta);
        puts("========================================");

            printf("Resultados:\n");
            TipoCasilla* casilla = (TipoCasilla*)list_first(rodillo->listaCasillas);
            for (int i = 0; i < 3; i++) {
                printf("Casilla %d: %s\n", i + 1, casilla->figura);
                casilla = (TipoCasilla*)list_next(rodillo->listaCasillas);
            }
            if (VerificarPremio(rodillo)){
                puts("========================================");
                printf(" Has ganado %d fichas\n", (int)(apuesta*1.5));
                puts(" ¡Bien Jugado!");
                puts(" Volviendo al menu principal....");
                puts("========================================");
                (*chipCount) += apuesta*1.5;
            } else {
                (*chipCount) -= apuesta;
                puts("========================================");
                printf(" Has perdido %d fichas\n", apuesta);
                puts(" ¡Mejor suerte para la proxima!");
                puts(" Volviendo al menu principal....");
                puts("========================================");
            }
            return 0;

        case '2':
            puts("Las reglas son...");
            break;
        case '3':
            //HigherOrLower(chipCount);
            return 0;
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (option != '0');
    return 0;
}