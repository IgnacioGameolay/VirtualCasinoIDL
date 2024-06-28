# CASINO IDL

## Descripción del programa

Este programa cumple la funcionalidad de ser un simulador de juegos de casino, proporcionando seis juegos diferentes: Póker, Blackjack, Higher Or Lower, Ruleta, Jackpot, y Craps. El objetivo es ofrecer una experiencia de casino interactiva y fácil de usar a través de una consola, buscando una solución divertida a esos momentos de ocio y aquellos sin conexión a internet, esto dado que los juegos implementados son off-line.



## Cómo compilar y ejecutar

Como uno de los objetivos del programa es ser fácil de utilizar y ser sumamente accesible, es recomendable utilizar webs como `Repl.it` para probar y ejecutar el sistema rápidamente. 
Para ello seguir los siguientes pasos:

1. Visitar [Repl.it](https://repl.it/).
2. Crear una nueva cuenta o iniciar sesión si ya tienes una.
3. Estando en el `dashboard`, seleccionar la opción "`New Repl`" y eligir "`Import from GitHub`".
4. Clonar el repositorio de GitHub: `https://github.com/IgnacioGameolay/VirtualCasinoIDL.git`
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará el entorno de ejecución automáticamente.
6. Finalmente, presionar el botón "Run" para compilar y ejecutar la aplicación de manera automática. O bien, compilar el código manualmente utilizando: `gcc tdas/*.c juegos/*.c main.c -Wno-unused-result -o main` , y posteriormente ejecutar con: `./main`


## Funcionalidades

### Funcionando correctamente:

- Todos los juegos.
- Impresión de eventos por consola.
- Sistema de guardado, carga y reinicio de fichas (progreso).
- Sistema de rondas bonus.
- Todos los sistemas en orden.
### Problemas conocidos:

- Algunos juegos podrían tener limitaciones de memoria y/o ejecución dependiendo del entorno en el que se ejecuten.
- Si bien no es un problema, pueden llegar a haber inconsistencias ente las reglas de algunos juegos implementados con las reglas tradicionales de los juegos de la vida real, esto debido a que el simulador adaptó las reglas para darle un toque personal y distinto a los juegos.

### A mejorar:

- Incorporar una interfaz gráfica para mejorar la experiencia del usuario.
- Mejorar la eficiencia de los algoritmos utilizados en los juegos para reducir el consumo de memoria y tiempo de ejecución.
- Añadir funcionalidades adicionales como multijugador y tablas de clasificación global.

## Ejemplo de uso
A continuación, veremos un ejemplo de cómo utilizar el sistema para jugar uno de los juegos disponibles. 

Cabe mencionar que el sistema de guardado es automático y manual, es decir, el progreso se guarda cada que vez que volvemos al menú principal, pero de igual manera podemos seleccionar la opción "8" para guardar manualmente. Por otro lado, la ronda bonus es una probabilidad de 1 en 100, en ella el usuario gana una cantidad adicional correspondiente a la mitad de lo que haya ganado al final de la sesión de juego.

Con lo anterior en cuenta, veremos un ejemplo de uso, y es que al iniciar el sistema tendremos el siguiente menú principal con el cual interactuar:

``` 
========================================
   Bienvenido al Casino Virtual IDL
========================================
========================================

   Cantidad Actual de Fichas: 1000

========================================
(1) Blackjack (Apuesta mínima $25)
(2) Poker (Apuesta mínima $25)
(3) Higher or Lower (Apuesta mínima $100)
(4) Ruleta (Apuesta mínima $25)
(5) Jackpot (Apuesta mínima $25)
(6) Craps (Apuesta mínima $50)
-
(7) Reiniciar Progreso
(8) Guardar Progreso
(9) Cargar Progreso
(0) Salir del Casino
========================================
Ingrese su opción: 
========================================

```
En este menú, podremos seleccionar una de las 10 opciones cuando se nos solicite `Ingrese su opción: `.

Los nombres de las opciones son bastante descriptivas (hacen lo que mencionan), pero de igual manera a continuación se mostrarán los pasos a seguir en el caso de uso de uno de los 6 juegos implementados. Dado que son muchos juegos y todos siguen la misma estructura, se utilizará un único juego de ejemplo, siendo este el Jackpot. Dicho esto, vamos con un recorrido desde que empezamos a jugar hasta que salimos del simulador:

**Primer Paso - Escoger Juego**

Al seleccionar la opción de nuestro juego, en este caso el **Jackpot**, se nos mostrará por consola el sub-menú del juego escogido, dando la opción de entrar directamente a jugar, consultar por las reglas que se han adaptado al simulador, y por ultimo volver al menú principal si se desea. A continuación un ejemplo:

```
========================================
Ingrese su opción: 
========================================
5
========================================
 Bienvenido a Jackpot.
========================================

   Cantidad Actual de Fichas: 1000

========================================
(1) Jugar
(2) Reglas
(3) Volver al menú principal
========================================
Ingrese su opción: 
========================================

```

**Segundo Paso - Escoger Opción Deseada**

Como se mencionó anteriormente se nos dan 3 opciones a elegir, a continuación veremos qué pasa al escoger cada una, nos centraremos en la opción de jugar, pero se dejará un ejemplo a continuación de qué se mostraría al escoger la 2da opción:

```
========================================
Objetivo: Obtener una combinación de símbolos idénticos en todas las casillas del rodillo.

Inicio del Juego: El jugador podrá ingresar la cantidad de fichas que desea apostar.

Rodillo: El rodillo está compuesto por 3 casillas, cada una mostrando un símbolo geométrico (cuadrado, triángulo, círculo, y pentagono).

Opciones del Jugador: Después de realizar la apuesta, el jugador podrá hacer girar el rodillo para ver la combinación de símbolos resultante.

Condiciones de Victoria: El jugador gana si todos los símbolos de la combinación son iguales. Caso contrario pierde.

Resultado: Después de evaluar la combinación de símbolos, se informará al jugador si ha ganado o perdido, junto con la cantidad de fichas ganadas o perdidas.

========================================

Presione una tecla para continuar...

```

**Tercer Paso - Empezar a jugar**

Al seleccionar la 1ra opción, pasaremos al sub-menú de juego, en el que podremos apostar y finalmente empezar a divertirnos. A continuación el sub-menú del Jackpot tanto si ganamos como si perdemos:

```
========================================
 Bienvenido a Jackpot.
========================================

   Cantidad Actual de Fichas: 1000

========================================
(1) Jugar
(2) Reglas
(3) Volver al menú principal
========================================
Ingrese su opción: 
========================================
1
========================================
¡Muy bien, vamos a jugar!
 Ingrese su apuesta: 
100
========================================
Resultados:
Casilla 1: pentagono
Casilla 2: pentagono
Casilla 3: pentagono
========================================
 Has ganado 150 fichas
 ¡Bien Jugado!
 Volviendo al menú principal....
========================================
Presione una tecla para continuar...

```

Por otra parte, un ejemplo de derrota:

```
========================================
 Bienvenido a Jackpot.
========================================

   Cantidad Actual de Fichas: 1000

========================================
(1) Jugar
(2) Reglas
(3) Volver al menú principal
========================================
Ingrese su opción: 
========================================
1
========================================
¡Muy bien, vamos a jugar!
 Ingrese su apuesta: 
200
========================================
Resultados:
Casilla 1: cuadrado
Casilla 2: triangulo
Casilla 3: pentagono
========================================
 Has perdido 200 fichas
 ¡Mejor suerte para la próxima!
 Volviendo al menu principal....
========================================
Presione una tecla para continuar...
```


**Cuarto Paso - ¿Qué hacer después de jugar?**

Luego de terminar cualquier juego y volver al menú principal, el usuario tiene la posibilidad de escoger cualquiera de los juegos, volviendo así al **1er paso**.

**Pasos Adicionales - Sistemas de Guardado y Ronda Bonus**

Adicionalmente, si el usuario tiene la fortuna de ganar una ronda bonus, verá un mensaje como siguiente mensaje:
```
========================================
¡Felicidades, has ganado una ronda bonus!
Has ganado 100 fichas extra
========================================
```

Por otro lado, si el usuario quisiera guardar, cargar y reiniciar su progreso vería lo siguiente:

Para Guardar:
```
========================================
Ingrese su opción: 
========================================
8
========================================
Progreso guardado con éxito
========================================
Presione una tecla para continuar...
```

Para Cargar:
```
========================================
Ingrese su opción: 
========================================
8
========================================
Progreso cargado con éxito
========================================
Presione una tecla para continuar...
```

En el caso de que no se logre cargar el progreso aparecerá lo siguiente y será reiniciado a la cantidad de fichas iniciales (1000):
```
========================================
Ingrese su opción: 
========================================
9
========================================
Progreso no pudo ser guardado
========================================
Presione una tecla para continuar...
```

Para Reiniciar el progreso:
```
========================================
Ingrese su opción: 
========================================
7
========================================
Progreso reiniciado con éxito. Cantidad de fichas actuales: 1000
========================================
Presione una tecla para continuar...
```


Finalmente, para terminar la ejecución del programa, seleccionamos la opción 0 en el menú principal y finalizará automáticamente.


***Cualquier consulta o duda que pueda surgir, contactarse a cualquiera de los siguientes mails:***
 -
- ignacio.reyes.t@mail.pucv.cl 
-  diego.alvarado.m@mail.pucv.cl 
- lucas.pinto.a@mail.pucv.cl

Aportes individuales:
-
- Ignacio Reyes: Este integrante demostró una disposición y dedicación ejemplar a lo largo de la realización del proyecto, liderando y aportando ideas/soluciones de manera óptima. Fue el encargado de desarrollar los sistemas de guardado, ronda bonus, incorporar los juegos al main(), y de desarrollar el juego Poker y Jackpot.

- Lucas Pinto: Trabaja de manera eficaz en las tareas asignadas, ayudando en todo lo que pudiera y desarrollando correctamente sus juegos asignados, siendo estos la Ruleta/Roulette y el Craps. Se destaca su destreza para implementar estos complejos juegos de manera simple y eficiente al simulador.


- Diego Alvarado: Este integrante colaboró activamente en sus tareas asignadas, ayudando en aportar ideas y distintos puntos de vista, lo que permitió implementar ideas creativas y soluciones óptimas. Fue el encargado de desarrollar los juegos de cartas Blackjack y Higher or Lower.
    

    
