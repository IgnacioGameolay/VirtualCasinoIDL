#include "jackpot.h"


/**
 *
 * Función para crear una casilla del rodillo de jackpot
 *
 * @return Retorna un puntero a la casilla creada por la funcion
 */
// 
TipoCasilla* CrearCasilla() {
    
    TipoCasilla* casilla = (TipoCasilla*)malloc(sizeof(TipoCasilla));
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


/**
 *
 * Función para crear el rodillo y agregarle las casillas del jackpot
 *
 * @return Retorna un puntero a al rodillo generado por la funcion
 */
// 
TipoRodillo* CrearRodillo() {
    TipoRodillo* rodillo = (TipoRodillo*)malloc(sizeof(TipoRodillo));
    rodillo->listaCasillas = list_create();

    
    for (int i = 0; i < 3; i++) {
        TipoCasilla* casilla = CrearCasilla();
        list_pushFront(rodillo->listaCasillas, casilla);
        //printf("Se agrego la Casilla %d: %s\n", i + 1, casilla->figura);
    }
    return rodillo;
}

/**
 *
 * Función para verificar las condiciones de victoria del usuario
 *
 * @param *rodillo Puntero al rodillo del jackpot
 * @return Retorna 1 si el usuario gana, 0 si pierde
 */
// 
int VerificarPremio(TipoRodillo* rodillo) {
    TipoCasilla* casilla1 = (TipoCasilla*)list_first(rodillo->listaCasillas);
    TipoCasilla* casilla2 = (TipoCasilla*)list_next(rodillo->listaCasillas);
    TipoCasilla* casilla3 = (TipoCasilla*)list_next(rodillo->listaCasillas);
    
    if (strcmp(casilla1->figura, casilla2->figura) == 0 &&
        strcmp(casilla2->figura, casilla3->figura) == 0) {
        return 1; // Premio!
    }
    return 0; // Sin premio
}


/**
 *
 * Función principal del juego.
 *
 */
// 
int JackpotGame(int *cantFichasJugador) {

    TipoRodillo* rodillo = CrearRodillo();

    char option; //Option del menu
    int apuesta = 0;
    do {
        puts("========================================");
        puts(" Bienvenido a Jackpot.");
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
            if (apuesta <= 0 || apuesta >= *cantFichasJugador){
                while (apuesta <= 0 || apuesta >= *cantFichasJugador){
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
            if (VerificarPremio(rodillo)){
                puts("========================================");
                printf(" Has ganado %d fichas\n", (int)(apuesta*1.5));
                puts(" ¡Bien Jugado!");
                puts(" Volviendo al menu principal....");
                puts("========================================");
                (*cantFichasJugador) += apuesta*1.5;
            } else {
                (*cantFichasJugador) -= apuesta;
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
            //HigherOrLower(cantFichasJugador);
            return 0;
            break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

    } while (option != '0');
    return 0;
}