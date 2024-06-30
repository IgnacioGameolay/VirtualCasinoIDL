#include "roulette.h"
#define NUM_CASILLAS 37
#define MIN_CHIPS 25

// Estructura para representar de mejor manera la apuesta
// A que se está apostando(numero, color, paridad, columna, docena, mitad, tipo) y el monto.
struct TipoApuesta
{
  int monto;
  int numero; 
  const char* color; 
  const char* paridad; 
  int columna; 
  int docena; 
  int mitad; 
  int tipo; 
};

// Estructura para representar la ruleta, tanto la casilla como el arreglo de la ruleta.
struct TipoRuleta
{
  ArrayList *roulette;
  int casillaActual;
};

// Función para inicializar la ruleta
void InicializarRuleta(TipoRuleta *ruleta)
{  
  initializeArrayList(ruleta->roulette, NUM_CASILLAS);
  for(int i = 0; i < NUM_CASILLAS; i++)
  {
    insert(ruleta->roulette, i);
  }
  ruleta->casillaActual = -1;
}

// Función para crear una apuesta TipoApuesta
static void CrearApuestaRoulette(TipoApuesta* apuesta, int *chips)
{
  puts("========================================");
  printf("¿Qué tipo de apuesta desea hacer?\n");
  printf("1. Número\n");
  printf("2. Color\n");
  printf("3. Paridad\n");
  printf("4. Columna\n");
  printf("5. Docena\n");
  printf("6. Mitad\n");
  puts("========================================");
  int tipo;
  scanf("%d", &tipo);
  puts("========================================");
  int monto;
  printf("¿Qué monto desea apostar?\n");
  scanf("%d", &monto);
  if(monto > *chips || monto < MIN_CHIPS)
  {
    puts("No tienes suficientes fichas para apostar o has apostado una cantidad menor que el valor mínimo ($25).");
    puts("Prueba con otro juego. Gracias por jugar.");
    monto = 0;
    return;
  }
  apuesta->monto = monto;
  puts("========================================");

  switch (tipo) 
  {
    case 1: // Apuesta a número
      printf("Ingrese el número al que desea apostar (0-36):\n");
      scanf("%d", &apuesta->numero);
      if(apuesta->numero < 0 || apuesta->numero > 36)
      {
        printf("Número inválido. Apuesta cancelada\n");
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 1;
      puts("========================================");
      break;
    case 2: // Apuesta a color
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
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 2;
      puts("========================================");
      break;
    case 3: // Apuesta a paridad
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
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 3;
      puts("========================================");
      break;
    case 4: // Apuesta a columna
      printf("Ingrese la columna a la que desea apostar (1 - 2 - 3):\n");
      scanf("%d", &apuesta->columna);
      if (apuesta->columna < 1 || apuesta->columna > 3) 
      {
        printf("Columna inválida. Apuesta cancelada.\n");
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 4;
      puts("========================================");
      break;
    case 5: // Apuesta a docena
      printf("Ingrese la docena a la que desea apostar (1 - 2 - 3):\n");
      scanf("%d", &apuesta->docena);
      if (apuesta->docena < 1 || apuesta->docena > 3) 
      {
        printf("Docena inválida. Apuesta cancelada.\n");
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 5;
      puts("========================================");
      break;
    case 6: // Apuesta a mitad
      printf("Ingrese la mitad a la que desea apostar (1 - 2):\n");
      scanf("%d", &apuesta->mitad);
      if (apuesta->mitad < 1 || apuesta->mitad > 2) 
      {
        printf("Mitad inválida. Apuesta cancelada.\n");
        apuesta->monto = 0;
        apuesta->tipo = 0;
        puts("========================================");
        return;
      }
      apuesta->tipo = 6;
      puts("========================================");
      break;
    default:
      printf("Tipo de apuesta inválido. Apuesta cancelada.\n");
      puts("========================================");
      return;
  }
  printf("Apuesta creada exitosamente.\n");
  puts("========================================");
}

// Función para simular el giro de una ruleta real
void GirarRuleta(TipoRuleta *ruleta)
{
  srand(time(NULL));
  int indiceGanador = rand() % NUM_CASILLAS;
  int elementoGanador = getElement(ruleta->roulette, indiceGanador);
  ruleta->casillaActual = elementoGanador;
  printf("La ruleta ha girado y ha caído en la casilla %d!\n", ruleta->casillaActual);
  puts("================================");
}

//Funcion para determinar si el numero es rojo
int EsRojo(int numero)
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

//Funcion para determinar si el numero es negro
int EsNegro(int numero)
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

// Función para obtener la columna de un número (1ra, 2da, 3ra)
int ObtenerColumna(int numero)
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

// Función para evaluar el resultado de juego
static int EvaluarApuestaRoulette(TipoApuesta *apuesta, TipoRuleta *ruleta)
{
  int resultado = ruleta->casillaActual;
  switch (apuesta->tipo)
    {
      case 1:
        if (apuesta->numero == resultado)
        {
          printf("¡Felicidades! Has ganado tu apuesta por número!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido...\n");
          return 0;
        }
        break;
      case 2:
        if (EsRojo(resultado) && strcmp(apuesta->color, "Rojo") == 0 || 
          EsNegro(resultado) && strcmp(apuesta->color, "Negro") || 
          resultado == 0 || 
          resultado == 0 && strcmp(apuesta->color, "Verde") == 0)
        {
          printf("¡Felicidades! Has ganado tu apuesta a un color!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido... Mejor suerte a la próxima!\n");
          return 0;
        }
        break;
      case 3:
        if (strcmp(apuesta->paridad, "Par") == 0 && resultado % 2 == 0 || 
          strcmp(apuesta->paridad, "Impar") == 0 && resultado % 2 != 0)
        {
          printf("¡Felicidades! Has ganado tu apuesta a la paridad del número!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido... Quizá tengas más suerte en otro giro!\n");
          return 0;
        }
        break;
      case 4:
        if (apuesta->columna == ObtenerColumna(resultado))
        {
          printf("¡Felicidades! Has ganado tu apuesta a la columna a la que pertenezca el número!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido... Malditas columnas y su distribución rara...\n");
          return 0;
        }
        break;
      case 5:
        if (apuesta->docena == 1 && resultado >= 1 && resultado <= 12 || apuesta->docena == 2 && resultado >= 13 && resultado <= 24 || apuesta->docena == 3 && resultado >= 25 && resultado <= 36)
        {
          printf("¡Felicidades! Has ganado tu apuesta a la docena a la que pertenezca el número!\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido... Con lo caras que están las docenas hoy en día...\n");
          return 0;
        }
        break;
      case 6:
        if (apuesta->mitad == 1 && resultado >= 1 && resultado <= 18 || apuesta->mitad == 2 && resultado >= 19 && resultado <= 36)
        {
          printf("¡Felicidades! Has ganado tu apuesta a la mitad a la que pertenezca el número\n");
          return 1;
        }
        else
        {
          printf("Lo siento, has perdido... Quizá Gojo te pueda ayudar a la próxima que apuestes por alguna mitad!\n");
          return 0;
        }
        break;
      default:
        printf("Tipo de apuesta inválido. A qué le has apostado?\n");
        break;
    }
}

//FUncion principald de juego
int RouletteGame(int *chipCount)
{
  char option; //Option del menu
  TipoApuesta apuesta; //Apuesta a realizar
  apuesta.tipo == 0;
  int resultado; //Resultado de la juego
  TipoRuleta ruleta;
  ruleta.roulette = (ArrayList *)malloc(sizeof(ArrayList*));
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
        InicializarRuleta(&ruleta);
        printf("                      26  0  32\n");
        printf("                    3           15\n");
        printf("                  35               19\n");
        printf("                12                   4\n");
        printf("              28                      21\n");
        printf("             7                          2\n");
        printf("           29                            25\n");
        printf("         18                                17\n");
        printf("         22            ROULETTE            34\n");
        printf("          9                                6\n");
        printf("           31                             27\n");
        printf("            14                           13\n");
        printf("              20                       36\n");
        printf("                1                    11\n");
        printf("                 33                30\n");
        printf("                   16            8\n");
        printf("                      24 5 10 23\n");
        puts("========================================");
        printf("Lista de Números para colores: \n");
        printf("Rojos: 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36\n");
        printf("Negros: 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35\n");
        printf("Verde: 0\n");
        CrearApuestaRoulette(&apuesta, chipCount);
        if(apuesta.tipo == 0)
        {
          break;
        }
        GirarRuleta(&ruleta);
        resultado = EvaluarApuestaRoulette(&apuesta, &ruleta);
        if (resultado == 1){

          apuesta.monto += RondaBonus(&(apuesta.monto));
          *chipCount += apuesta.monto;
        }
        else
        {
          *chipCount -= apuesta.monto;
        }
        break;
        case '2':
            puts("================================");
            puts("El juego de la ruleta consiste en algo tan simple como apostar por uno de 6 tipos de apuestas, girar la ruleta y ver si ganas o pierdes!");
            puts("Los tipos de apuestas son: \n");
            puts("1. Apuesta por número: Puedes apostar por cualquier número de la ruleta, desde el 0 al 36!");
            puts("2. Apuesta por color: Puedes apostar por los números rojos, verdes, o la extremadamente remota posibilidad de que te salga un 0, único verde en la ruleta!");
            puts("3. Apuesta por paridad: Puedes apostar a que el número que salga será par o impar!");
            puts("4. Apuesta por columna: Puedes apostar a que el número que salga pertenezca a la primera, segunda o tercera columna de la ruleta. Las columnas se distribuyen de la siguiente forma:");
            puts("1. Columna 1: 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34");
            puts("2. Columna 2: 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35");
            puts("3. Columna 3: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36");
            puts("5. Apuesta por docena: Puedes apostar a que el número que salga pertenezca a la primera (1 a 12), segunda (13 a 24) o tercera (25 a 36) docena de la ruleta!");
            puts("6. Apuesta por mitad: Puedes apostar a que el número que salga pertenezca a la primera (1 a 18) o segunda (19 a 36) mitad de la ruleta!");
            puts("================================");
            break;
        case '3':
            return 0;
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (option != '0');
    return 0;
}