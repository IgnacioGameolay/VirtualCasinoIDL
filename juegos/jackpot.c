#include "jackpot.h"



//Función para crear una casilla del rodillo de jackpot
TipoCasilla* CrearCasilla() {
    
    TipoCasilla* casilla = (TipoCasilla*)malloc(sizeof(TipoCasilla));
    if (casilla == NULL){
        printf("Error al designar memoria para la casilla\n");
        EXIT_FAILURE;
    } 
    
    int figuraAleatoria = rand() % 4;
    switch (figuraAleatoria) {
        case 0:
            strcpy(casilla->figura, "cuadrado");
            break;
        case 1:
            strcpy(casilla->figura, "triangulo");
            break;
        case 2:
            strcpy(casilla->figura, "circulo");
            break;
        case 3:
            strcpy(casilla->figura, "pentagono");
            break;
    }
    return casilla;
}



//Función para crear el rodillo y agregarle las casillas del jackpot
TipoRodillo* CrearRodillo() {
    TipoRodillo* rodillo = (TipoRodillo*)malloc(sizeof(TipoRodillo));
    if (rodillo == NULL){
        printf("Error al designar memoria para el rodillo\n");
        EXIT_FAILURE;
    }
    rodillo->listaCasillas = list_create();

    
    for (int i = 0; i < 3; i++) {
        TipoCasilla* casilla = CrearCasilla();
        list_pushFront(rodillo->listaCasillas, casilla);
        //printf("Se agrego la Casilla %d: %s\n", i + 1, casilla->figura);
    }
    return rodillo;
}


// Función para verificar las condiciones de victoria del usuario

int VerificarPremioJackpot(TipoRodillo* rodillo) {
    TipoCasilla* casilla1 = (TipoCasilla*)list_first(rodillo->listaCasillas);
    TipoCasilla* casilla2 = (TipoCasilla*)list_next(rodillo->listaCasillas);
    TipoCasilla* casilla3 = (TipoCasilla*)list_next(rodillo->listaCasillas);
    
    if (strcmp(casilla1->figura, casilla2->figura) == 0 &&
        strcmp(casilla2->figura, casilla3->figura) == 0) {
        return 1; // Premio!
    }
    return 0; // Sin premio
}


//Función principal del juego.
 
int JackpotGame(int *cantFichasJugador) {
    srand(time(NULL));
    TipoRodillo* rodillo = CrearRodillo();
    
    char option; //Option del menu
    int apuesta = 0;
    do {
        puts("========================================");
        puts(" Bienvenido a $Jackpot.");
        puts("========================================");
        printf("\n   Cantidad Actual de Fichas: %d\n\n", *cantFichasJugador);
        puts("========================================");
        puts("(1) Jugar");
        puts("(2) Reglas");
        puts("(3) Volver al menú principal");
        puts("========================================");
        printf("Ingrese su opción: \n");
        puts("========================================");
        scanf(" %c", &option);

        //Opciones del menu
        switch (option) {
        case '1':
            puts("========================================");
            puts("¡Muy bien, vamos a jugar!");
            puts(" Ingrese su apuesta: ");
            scanf("%d", &apuesta);
            if (apuesta <= 0 || apuesta > *cantFichasJugador){
                while (apuesta <= 0 || apuesta > *cantFichasJugador){
                    puts(" Ingrese una apuesta válida: ");
                    scanf("%d", &apuesta);
                }
            }
            
            puts("========================================");
            
            printf("Resultados:\n");
            TipoCasilla* casilla = (TipoCasilla*)list_first(rodillo->listaCasillas);
            for (int i = 0; i < 3; i++) {
                printf("Casilla %d: %s\n", i + 1, casilla->figura);
                casilla = (TipoCasilla*)list_next(rodillo->listaCasillas);
            }
            if (VerificarPremioJackpot(rodillo)){
                puts("========================================");
                printf(" Has ganado %d fichas\n", (int)(apuesta*1.5));
                puts(" ¡Bien Jugado!");
                puts(" Volviendo al menu principal....");
                puts("========================================");
                apuesta += RondaBonus(&apuesta);
                (*cantFichasJugador) += apuesta*1.5;
            } else {
                (*cantFichasJugador) -= apuesta;
                puts("========================================");
                printf(" Has perdido %d fichas\n", apuesta);
                puts(" ¡Mejor suerte para la proxima!");
                puts(" Volviendo al menu principal....");
                puts("========================================");
            }
            free(rodillo);
            return 0;
            
        case '2':
            limpiarPantalla();
            puts("========================================");
            puts("Objetivo: Obtener una combinación de símbolos idénticos en todas las casillas del rodillo.\n");

            puts("Inicio del Juego: El jugador podrá ingresar la cantidad de fichas que desea apostar.\n");

            puts("Rodillo: El rodillo está compuesto por 3 casillas, cada una mostrando un símbolo geométrico (cuadrado, triángulo, círculo, y pentágono).\n");

            puts("Opciones del Jugador: Después de realizar la apuesta, el jugador podrá hacer girar el rodillo para ver la combinación de símbolos resultante.\n");

            puts("Condiciones de Victoria: El jugador gana si todos los símbolos de la combinación son iguales. Caso contrario pierde.\n");

            puts("Resultado: Después de evaluar la combinación de símbolos, se informará al jugador si ha ganado o perdido, junto con la cantidad de fichas ganadas o perdidas.\n");
            puts("========================================\n");
            break;
        case '3':
            return 0;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (option != '0');
    return 0;
}