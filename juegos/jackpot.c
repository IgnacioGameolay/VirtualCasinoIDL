#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../tdas/list.h"

typedef struct {
    char figura[10];
} TipoCasilla;

typedef struct {
    List* listaCasillas;
} TipoRodillo;

TipoCasilla* CrearCasilla() {
    srand(time(NULL));
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

TipoRodillo* CrearRodillo() {
    TipoRodillo* rodillo = (TipoRodillo*)malloc(sizeof(TipoRodillo));
    rodillo->listaCasillas = list_create();
    
    for (int i = 0; i < 3; i++) {
        TipoCasilla* casilla = CrearCasilla();
        list_pushFront(rodillo->listaCasillas, casilla);
        printf("Se agrego la Casilla %d: %s\n", i + 1, casilla->figura);
    }
    return rodillo;
}

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

int main() {
    
    TipoRodillo* rodillo = CrearRodillo();
    
    TipoCasilla* casilla = (TipoCasilla*)list_first(rodillo->listaCasillas);
    for (int i = 0; i < 3; i++) {
        printf("Casilla %d: %s\n", i + 1, casilla->figura);
        casilla = (TipoCasilla*)list_next(rodillo->listaCasillas);
    }

    if (VerificarPremio(rodillo)) {
        printf("¡Felicidades, has ganado el premio!\n");
    } else {
        printf("Lo siento, sigue intentando...\n");
    }

    list_clean(rodillo->listaCasillas);
    free(rodillo);

    return 0;
}
