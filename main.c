#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(0));

    int j_uno = 0, j_dos = 0, dado = 6, casillas = 12, dado_num = 0, turno = 0;
    int j_ale = 0, dado_uno = 0, dado_dos = 0, perdio_uno = 0, perdio_dos = 0;

    printf("---------------------------------\n");
    printf(" Bienvenido al ludo lineal!\n");
    printf(" Este juego consiste en quien llega primero a la casilla N-12.\n");
    printf(" Las reglas son:\n");
    printf(" 1.- Antes de comenzar la partida, los jugadores tienen que lanzar el y el que saque un número más alto, será el jugador que comience el juego.\n");
    printf(" 2.- Hacer que en caso de que un jugador se pase de la casilla 12 , retroceda la cantidad restante.\n");
    printf(" 3.- Si uno de los jugadores llega a la casilla 7, este jugador pierde el turno siguiente.\n");
    printf(" 4.- El jugador que llegue primero a la casilla 12, ganará el juego.\n");
    printf("---------------------------------\n\n");

    // Decide quién comienza
    printf("Ambos jugadores lanzan para decidir quién comienza...\n");

    while (1) { // Ciclo infinito hasta que haya un ganador claro
        dado_uno = rand() % 6 + 1;
        dado_dos = rand() % 6 + 1;
        printf("Jugador 1 lanzó: %d\n", dado_uno);
        printf("Jugador 2 lanzó: %d\n", dado_dos);

        if (dado_uno != dado_dos) {
            // Salir del bucle si no hay empate
            break;
        }
        printf("Empate! Ambos jugadores lanzan de nuevo.\n\n");
    }

    j_ale = (dado_uno > dado_dos) ? 0 : 1; // Jugador que empieza (0 = jugador 1, 1 = jugador 2)
    printf("\nComienza el jugador %i!\n", j_ale + 1);
    printf("\nPresiona Enter para continuar...");
    getchar();

    // Inicio del juego
    while (j_uno < 12 && j_dos < 12) {
        // Limpiar pantalla al inicio de cada turno
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if ((j_ale == 0 && perdio_uno) || (j_ale == 1 && perdio_dos)) {
            // El jugador pierde el turno si está en la casilla 7
            printf("\nEl jugador %i pierde su turno por estar en la casilla 7.\n", j_ale + 1);
            if (j_ale == 0) perdio_uno = 0; else perdio_dos = 0;
        } else {
            // Tirar el dado
            printf("\nEs el turno del jugador: %i\n", j_ale + 1);
            printf("Presiona Enter para tirar dado...");
            getchar();
            dado_num = rand() % 6 + 1;
            printf("Número aleatorio es: %i\n", dado_num);

            // Actualizar posición del jugador
            if (j_ale == 0) {
                j_uno += dado_num;
                if (j_uno == 7) perdio_uno = 1; // Si cae en la casilla 7, pierde el siguiente turno
                if (j_uno > 12) {
                    j_uno = 12 - (j_uno - 12); // Retrocede si pasa de la casilla 12
                    printf("Jugador 1 retrocedió %i casillas.\n", 12 - j_uno);
                }
                printf("Jugador 1 avanzó a la casilla: %i\n", j_uno);
            } else {
                j_dos += dado_num;
                if (j_dos == 7) perdio_dos = 1; // Si cae en la casilla 7, pierde el siguiente turno
                if (j_dos > 12) {
                    j_dos = 12 - (j_dos - 12); // Retrocede si pasa de la casilla 12
                    printf("Jugador 2 retrocedió %i casillas.\n", 12 - j_dos);
                }
                printf("Jugador 2 avanzó a la casilla: %i\n", j_dos);
            }
        }

        // Cambiar turno al otro jugador
        j_ale = 1 - j_ale;
        printf("\nEl próximo turno es del jugador: %i\n", j_ale + 1);

        // Mostrar estado del tablero
        printf("\nEstado del tablero:\n");
        printf("Jugador 1: %i\n", j_uno);
        for (int i = 1; i <= 12; i++) printf("O");
        printf("\n");
        for (int i = 1; i <= j_uno; i++) printf(i == j_uno ? "+" : "-");
        printf("\n");
        printf("Jugador 2: %i\n", j_dos);
        for (int i = 1; i <= 12; i++) printf("O");
        printf("\n");
        for (int i = 1; i <= j_dos; i++) printf(i == j_dos ? "+" : "-");
        printf("\n");

        // Comprobar si algún jugador ha ganado
        if (j_uno >= 12) {
            printf("\n\n¡GANO EL JUGADOR UNO!\n");
            break;
        }
        if (j_dos >= 12) {
            printf("\n\n¡GANO EL JUGADOR DOS!\n");
            break;
        }

        printf("\nPresiona Enter para continuar...");
        getchar();
    }

    return 0;
}
