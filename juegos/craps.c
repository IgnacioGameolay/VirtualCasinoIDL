#include "craps.h"
#define MAX_CARAS 6

// Estructura para silumar los dados y su caras
struct TipoDado
{
    int dado1[MAX_CARAS];
    int cara1;
    int dado2[MAX_CARAS];
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
  for (int i = 0; i < MAX_CARAS; i++)
  {
    dados->dado1[i] = i + 1;
    dados->dado2[i] = i + 1;
  }
  juego->punto = -1;
  juego->estado = 1;
}

// Función para crear una apuesta según el estado actual del juego
static void CrearApuestaCraps(TipoApuesta *apuesta, TipoJuego *juego)
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
        CrearApuestaCraps(apuesta, juego);
      }
      if(tipo == 3)
      {
        apuesta->tipo = 0;
        return;
      }
      apuesta->tipo = tipo;
      puts("========================================");
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
        CrearApuestaCraps(apuesta, juego);
      }
      apuesta->tipo = tipo + 2;
      puts("========================================");
      break;
    default:
      printf("Estado inválido. Intente de nuevo.\n");
      return;
  }
  puts("========================================");
  printf("Ingrese el monto de su apuesta: ");
  scanf("%d", &monto);
  if(monto < 1)
  {
    printf("Monto inválido. Intente de nuevo.\n");
    CrearApuestaCraps(apuesta, juego);
  }
  apuesta->monto = monto;
  puts("========================================");
}

// Función para lanzar los dados y devolver el índice del resultado
void LanzarDados(TipoDado *dados)
{
  srand(time(NULL));
  int indice1 = rand() % 6;
  //printf("indice 1L %d\n", indice1);
  int indice2 = rand() % 6;
  //printf("indice 2L %d\n", indice2);
  dados->cara1 = dados->dado1[indice1];
  dados->cara2 = dados->dado2[indice2];
}


// Función para evaluar una apuesta según el tipo y el estado del juego
int EvaluarApuestaCraps(TipoApuesta *apuesta, TipoDado *dados, TipoJuego *juego, int suma, int sumaPunto)
{
  int sumaPuntoVenir;
  switch (apuesta->tipo)
  {
    case 1: // Línea de Pase
      if (juego->estado == 1)
      { // Tiro de salida
        if (suma == 7 || suma == 11) 
        {
          printf("Ganaste la apuesta de Línea de Pase!\n");
          return 1;
        } 
        else if (suma == 2 || suma == 3 || suma == 12)
        {
          printf("Perdiste la apuesta de Línea de Pase.\n");
          return 0;
        } 
      } 
      else
      { // Tiro de punto
        if (sumaPunto == juego->punto)
        {
          printf("Ganaste la apuesta de Línea de Pase!\n");
          return 1;
        } 
        else if (sumaPunto == 7)
        {
          printf("Perdiste la apuesta de Línea de Pase.\n");
          return 0;
        }
      }
      break;
    case 2: // Barra de No Pase
      if (juego->estado == 1)
      { // Tiro de salida
        if (suma == 2 || suma == 3)
        {
          printf("Ganaste la apuesta de Barra de No Pase!\n");
          return 1;
        } 
        else if (suma == 7 || suma == 11)
        {
          printf("Perdiste la apuesta de Barra de No Pase.\n");
          return 0;
        } 
        else if (suma == 12)
        {
          printf("Empate en la apuesta de Barra de No Pase.\n");
          return 2;
        } 
      } 
      else 
      { // Tiro de punto
        if (sumaPunto == 7)
        {
          printf("Ganaste la apuesta de Barra de No Pase!\n");
          return 1;
        } 
        else if (sumaPunto == juego->punto) 
        {
          printf("Perdiste la apuesta de Barra de No Pase.\n");
          return 0;
        }
      }
      break;
      case 3: // A favor del número a venir
        if (sumaPunto ==  7 || sumaPunto == 11)
        {
          printf("Ganaste la apuesta a favor del número a venir!\n");
          return 1;
        }
        else if(sumaPunto == 2 || sumaPunto == 3 || sumaPunto == 12)
        {
          printf("Perdiste la apuesta a favor del número a venir.\n");
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
              printf("Ganaste la apuesta a favor del número a venir!\n");
              return 1;
            }
            else if(sumaPuntoVenir == 7)
            {
              printf("Perdiste la apuesta a favor del número a venir.\n");
              return 0;
            }
          }
        }
        break;
      case 4: // En contra del número a venir
        if (sumaPunto ==  2 || sumaPunto == 3)
          {
            printf("Ganaste la apuesta a favor del número a venir!\n");
            return 1;
          }
          else if(sumaPunto == 7 || sumaPunto == 11)
          {
            printf("Perdiste la apuesta a favor del número a venir.\n");
            return 0;
          }
          else if(sumaPunto == 12)
          {
            printf("Empate en la apuesta a favor del número a venir.\n");
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
                printf("Ganaste la apuesta a favor del número a venir!\n");
              }
              else if(sumaPuntoVenir == juego->punto)
              {
                printf("Perdiste la apuesta a favor del número a venir.\n");
              }
            }
          }
        break;
      default:
        printf("Tipo de apuesta inválido.\n");
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
        CrearApuestaCraps(&apuesta, &juego);
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
            printf("El tiro de salida no ha definido punto, pero ha definido números determinantes del tiro de salida. Sin embargo, no has hecho apuesta alguna. Que mal!\n");
            printf("Se determina entonces que la ronda acaba aquí. Puedes volver a jugar otra ronda y realizar una apuesta!\n");
            break;
          }
          else
          {
            CrearApuestaCraps(&apuesta, &juego);
          }
        }

        if(juego.estado == 2)
        {
          do
          {
            LanzarDados(&dados);
            sumaPunto = dados.cara1 + dados.cara2;
            printf("Lanzamiento: %d + %d = %d\n", dados.cara1, dados.cara2, sumaPunto); 
          } while (sumaPunto != 2 && sumaPunto != 3 && sumaPunto != 7 & sumaPunto != 11 && sumaPunto != 12 && sumaPunto != juego.punto);
        }
        resultado = EvaluarApuestaCraps(&apuesta, &dados, &juego, suma, sumaPunto);
        if (resultado == 1)
        {
          apuesta.monto += RondaBonus(&(apuesta.monto));
          *chipCount += apuesta.monto;
        }
        else if(resultado == 0)
        {
          *chipCount -= apuesta.monto;
        }
        break;
        case '2':
            puts("Las reglas son...");
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