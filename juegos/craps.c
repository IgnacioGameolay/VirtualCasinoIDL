#include "craps.h"
#define MAX_CARAS 6
#define MIN_CHIPS 50

// Estructura para silumar los dados y su caras
struct TipoDado
{
    ArrayList *dado1;
    int cara1;
    ArrayList *dado2;
    int cara2;
};

// Estructura para silumar la apuesta con su tipo y monto
struct TipoApuesta
{
    int monto; 
    int tipo; 
};

// Estructura para silumar el juego
struct TipoJuego
{
    int punto; 
    int estado; 
};

// Función para inicializar la ronda de dados y el juego
void InicializarRonda(TipoDado *dados, TipoJuego *juego)
{
  initializeArrayList(dados->dado1, MAX_CARAS);
  initializeArrayList(dados->dado2, MAX_CARAS);

  for(int i = 0; i < MAX_CARAS; i++)
  {
    insert(dados->dado1, (i + 1));
    insert(dados->dado2, (i + 1));
  }

  juego->punto = -1;
  juego->estado = 1;
}

// Función para crear una apuesta según el estado actual del juego
static void CrearApuestaCraps(TipoApuesta *apuesta, TipoJuego *juego, int *chipCount)
{
  printf("¿Qué tipo de apuesta desea hacer?\n");

  int monto; 
  int tipo;

  switch (juego->estado)
  {
    case 1:
      puts("========================================");
      printf("1. Línea de pase\n");
      printf("2. Barra de no pase\n");
      printf("3. Realizar Tiro y proceder con apuestas de Punto\n");
      puts("========================================");
      puts("Ingrese su opción: ");
      puts("========================================");
      scanf("%d", &tipo);
      if(tipo < 1 || tipo > 3)
      {
        printf("Opción inválida. Intente de nuevo.\n");
        return;
      }
      if(tipo == 3)
      {
        apuesta->tipo = 0;
        return;
      }
      apuesta->tipo = tipo;
      break;
    case 2:
      puts("========================================");
      printf("1. A favor del número a venir\n");
      printf("2. Contra el número a venir\n");
      puts("========================================");
      printf("Ingrese su opción: \n");
      puts("========================================");
      scanf("%d", &tipo);
      if(tipo < 1 || tipo > 2)
      {
        printf("Opción inválida. Intente de nuevo.\n");
        return;
      }
      apuesta->tipo = tipo + 2;
      break;
    default:
      printf("Estado inválido. Intente de nuevo.\n");
      return;
  }
  puts("========================================");
  printf("Ingrese el monto de su apuesta: ");
  scanf("%d", &monto);
  if(monto > *chipCount || monto < MIN_CHIPS)
  {
    printf("Monto inválido o no tienes suficientes fichas para apostar a este juego ($50 mínimo).\n");
    monto = 0;
    apuesta->tipo = -1;
    return;
  }
  apuesta->monto = monto;
  puts("========================================");
}

// Función para lanzar los dados y devolver el índice del resultado
void LanzarDados(TipoDado *dados)
{
  srand(time(NULL) ^ clock());
  int indice1 = rand() % 6;
  //printf("indice 1L %d\n", indice1);
  int indice2 = rand() % 6;
  //printf("indice 2L %d\n", indice2);
  int cara1 = getElement(dados->dado1, indice1);
  int cara2 = getElement(dados->dado2, indice2);
  dados->cara1 = cara1;
  dados->cara2 = cara2;
}


// Función para evaluar una apuesta según el tipo y el estado del juego
int EvaluarApuestaCraps(TipoApuesta *apuesta, TipoDado *dados, TipoJuego *juego, int suma)
{
  int sumaPunto, sumaPuntoVenir;
  switch (apuesta->tipo)
  {
    case 1: // Línea de Pase
      if (juego->estado == 1)
      { // Tiro de salida
        if (suma == 7 || suma == 11) 
        {
          puts("========================================");
          printf("Ganaste la apuesta de Línea de Pase. Suertudo, fue a la primera!\n");
          puts("========================================");
          return 1;
        } 
        else if (suma == 2 || suma == 3 || suma == 12)
        {
          puts("========================================");
          printf("Perdiste la apuesta de Línea de Pase... \n");
          puts("========================================");
          return 0;
        } 
      } 
      else
      { // Tiro de punto
        while(1)
        {
          LanzarDados(dados);
          sumaPunto = dados->cara1 + dados->cara2;
          printf("Lanzamientos: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPunto);
          if (sumaPunto == 7)
          {
            puts("========================================");
            printf("Perdiste la apuesta de Línea de Pase, establecido un punto. Quizá no debas jugar la lotería esta semana...\n");
            puts("========================================");
            return 0;
          }
          else if(sumaPunto == suma)
          {
            puts("========================================");
            printf("Ganaste la apuesta de Línea de Pase, establecido un punto! Wow, suertudo!\n");
            puts("========================================");
            return 1;
          }
        }
      }
      break;
    case 2: // Barra de No Pase
      if (juego->estado == 1)
      { // Tiro de salida
        if (suma == 2 || suma == 3)
        {
          puts("========================================");
          printf("Ganaste la apuesta de Barra de No Pase... a la primera!\n");
          puts("========================================");
          return 1;
        } 
        else if (suma == 7 || suma == 11)
        {
          puts("========================================");
          printf("Perdiste la apuesta de Barra de No Pase... Qué mala suerte...\n");
          puts("========================================");
          return 0;
        } 
        else if (suma == 12)
        {
          puts("========================================");
          printf("Empate en la apuesta de Barra de No Pase.... ¿Qué? ¿Existen los empates en esto? No se te han restado fichas.\n");
          puts("========================================");
          return 2;
        } 
      } 
      else 
      { // Tiro de punto
        while(1)
        {
          LanzarDados(dados);
          sumaPunto = dados->cara1 + dados->cara2;
          printf("Lanzamientos: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPunto);
          if (sumaPunto == 7)
          {
            puts("========================================");
            printf("Ganaste la apuesta de Barra de No Pase, establecido un punto! Quizá debas apostarle a este mismo número en el kino!\n");
            puts("========================================");
            return 1;
          }
          else if(sumaPunto == suma)
          {
            puts("========================================");
            printf("Perdiste la apuesta de Barra de No Pase, establecido un punto... Te maldigo, punto!\n");
            puts("========================================");
            return 0;
          }
        }
      }
      break;
      case 3: // A favor del número a venir
        LanzarDados(dados);
        sumaPunto = dados->cara1 + dados->cara2;
        printf("Lanzamientos: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPunto);
        if (sumaPunto ==  7 || sumaPunto == 11)
        {
          puts("========================================");
          printf("Ganaste la apuesta a favor del número a venir! ¿Será este tu número suertudo de la semana?\n");
          puts("========================================");
          return 1;
        }
        else if(sumaPunto == 2 || sumaPunto == 3 || sumaPunto == 12)
        {
          puts("========================================");
          printf("Perdiste la apuesta a favor del número a venir... la suerte no estuvo a tu lado...\n");
          puts("========================================");
          return 0;
        }
        else
        {
          juego->punto = sumaPunto;
          printf("Se ha establecido el punto a venir: %d\n", juego->punto);
          while(1)
          {
            LanzarDados(dados);
            sumaPuntoVenir = dados->cara1 + dados->cara2;
            printf("Lanzamiento: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPuntoVenir);
            if(sumaPuntoVenir == juego->punto)
            {
              puts("========================================");
              printf("Ganaste la apuesta a favor del número a venir, establecido un punto a venir! Wow!\n");
              puts("========================================");
              return 1;
            }
            else if(sumaPuntoVenir == 7)
            {
              puts("========================================");
              printf("Perdiste la apuesta a favor del número a venir, establecido un punto a venir... No es tu día de suerte...\n");
              puts("========================================");
              return 0;
            }
          }
        }
        break;
      case 4: // En contra del número a venir
        LanzarDados(dados);
        sumaPunto = dados->cara1 + dados->cara2;
        printf("Lanzamientos: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPunto);
        if (sumaPunto ==  2 || sumaPunto == 3)
          {
            puts("========================================");
            printf("Ganaste la apuesta en contra del número a venir, al primer tiro!\n");
            puts("========================================");
            return 1;
          }
          else if(sumaPunto == 7 || sumaPunto == 11)
          {
            puts("========================================");
            printf("Perdiste la apuesta en contra del número a venir.... Demonios!\n");
            puts("========================================");
            return 0;
          }
          else if(sumaPunto == 12)
          {
            puts("========================================");
            printf("Empate en la apuesta en contra del número a venir... ¡¿Hay empates aquí también?!\n");
            puts("========================================");  
            return 2;
          }
          else
          {
            juego->punto = sumaPunto;
            printf("Se ha establecido el punto a venir: %d\n", juego->punto);
            while(1)
            {
              LanzarDados(dados);
              sumaPuntoVenir = dados->cara1 + dados->cara2;
              printf("Lanzamiento: %d + %d = %d\n", dados->cara1, dados->cara2, sumaPuntoVenir);
              if(sumaPuntoVenir == 7)
              {
                puts("========================================");
                printf("Ganaste la apuesta en contra del número a venir, establecido un punto a venir! Lucky seven!\n");
                puts("========================================");
                return 1;
              }
              else if(sumaPuntoVenir == juego->punto)
              {
                puts("========================================");
                printf("Perdiste la apuesta en contra del número a venir, establecido un punto a venir! Al cabo que ni quería dar fichas...\n");
                puts("========================================");
                return 0;
              }
            }
          }
        break;
      default:
        printf("Tipo de apuesta inválido. ¡¿A qué le has apostado?!\n");
        break;
  }
}

// Función principal del juego de Craps
int CrapsGame(int *chipCount)
{
  char option; //Option del menu
  TipoApuesta apuesta; //Apuesta a realizar
  int resultado; //Resultado de la juego
  TipoDado dados;
  TipoJuego juego;
  dados.dado1 = (ArrayList *)malloc(sizeof(ArrayList *));
  dados.dado2 = (ArrayList *)malloc(sizeof(ArrayList *));
  do
  {
    puts("========================================");
    puts(" Bienvenido al juego de Craps");
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
        InicializarRonda(&dados, &juego);
        CrearApuestaCraps(&apuesta, &juego, chipCount);
        if(apuesta.tipo == -1)
        {
          break;
        }
        LanzarDados(&dados);
        int suma, sumaPunto;
        suma = dados.cara1 + dados.cara2;
        printf("Tiro de Salida: %d + %d = %d\n", dados.cara1, dados.cara2, suma);
        if(suma > 3 && suma < 7 || suma > 7 && suma < 11)
        {
          juego.estado = 2;
          juego.punto = suma;
          printf("Se ha establecido punto en %d\n", juego.punto);
        }
        if(apuesta.tipo == 0)
        {
          if(suma == 2 || suma == 3 || suma == 7 || suma == 11 || suma == 12)
          {
            printf("El tiro de salida no ha definido punto, pero ha definido un número determinante del tiro de salida. Sin embargo, no has hecho apuesta alguna. Que mal!\n");
            printf("Se determina entonces que la ronda acaba aquí. Puedes volver a jugar otra ronda y realizar una apuesta!\n");
            break;
          }
          else
          {
            CrearApuestaCraps(&apuesta, &juego, chipCount);
            if(apuesta.tipo == -1)
            {
              break;
            }
          }
        }

        resultado = EvaluarApuestaCraps(&apuesta, &dados, &juego, suma);
        if (resultado == 1)
        {
          printf("Ganaste %d fichas!\n", apuesta.monto);
          apuesta.monto += RondaBonus(&(apuesta.monto));
          *chipCount += apuesta.monto;
        }
        else if(resultado == 0)
        {
          *chipCount -= apuesta.monto;
          printf("Lo siento... Perdiste %d fichas!\n", apuesta.monto);
        }
        break;
        case '2':
            puts("El clásico juego de Craps adaptado a este programa! Se han simplificado algunas reglas, así que te las explicaré a continuación:");
            puts("Primero, este juego consta de 2 etapas: Un tiro de salida, y si se establece un punto, pasas a la etapa del tiro de punto! Un tiro consistirá en el lanzar 2 dados comunes, de 6 caras.");
          puts("==================================================================================");
            puts("Que qué rayos es un tiro de salida y un tiro de punto? Pues aquí te lo explico!");
            puts("Un tiro de salida es el primer tiro que realizas en una ronda de Craps. Se considerarán como números determinantes para este tiro los números 2, 3, 7, 11 y 12. Cualquier otro número se considerará punto y pasará a la 2da etapa del juego.");
            puts("Este tiro tiene 2 tipos de apuestas asociados a él, que solo pueden ser hechas antes del tiro: Línea de Pase y Barra de No Pase.");
            puts("==================================================================================");
            puts("Una Apuesta de línea de pase consiste en que le apuestas a que en tu tiro de salida el número que se obtiene con la suma de los 2 dados sea igual a 7 u 11.");
            puts("Si el número llegase a ser un 2, 3 o 12, se considerará perdida la apuesta.");
            puts("Si tu tiro de salida fuera cualquier otro número, ese número se considerará tu punto, y deberás lanzar los dados hasta que obtengas el punto para ganar.");
            puts("Si obtienes un 7 antes de obtener tu punto, automáticamente perderás tu apuesta.");
          puts("Una Apuesta de Barra de No Pase consiste en que le apuestas a que en tu tiro de salida el número que se obtiene con la suma de los 2 dados sea igual a 2 u 3.");
          puts("Si el número llegase a ser un 7 o un 11, se considerará perdida la apuesta.");
          puts("Si el número es un 12, wow! Has empatado tu apuesta! No perderás ni ganarás dinero en este caso");
          puts("Si tu tiro de salida fuera cualquier otro número, ese número se considerará tu punto, y deberás lanzar los dados hasta que obtengas un 7 para ganar.");
          puts("Si obtienes tu punto de nuevo antes que el 7, automáticamente perderás tu apuesta.");
          puts("==================================================================================");
          puts("Un tiro de punto es el tiro que realizas después de haber establecido un punto. Para este tiro, se tienen 2 tipos de apuestas, que solo pueden ser hechas después de haber hecho un tiro de salida. Estas son: La apuesta a favor del número a venir y la apuesta en contra del número a venir.");
          puts("La apuesta a favor del número a venir consiste en que le apuestas a que el siguiente número que obtendrás será o un 7 o un 11. Si obtienes un 2, 3 o 12, se considerará perdida la apuesta.");
          puts("Si obtienes cualquier otro número, este se convertirá en tu punto a venir y deberás seguir rolleando. Si vuelves a rollear tu punto a venir, ganas. Si rolleas un 7, pierdes!");
          puts("La apuesta en contra del número a venir consiste en que le apuestas a que el siguiente número que obtendrás será un 2 o 3. Si obtienes un 12, has empatado! Cualquier otro número se volverá tu punto a venir, en cuyo caso deberás seguir lanzando los dados hasta volver a obtener tu punto, o un 7");
          puts("Si obtienes un 7, felicidades! Has ganado tu apuesta! Pero si vuelves a rollear tu punto a venir, perderás tu apuesta.");

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