/****************************************************
*
*   Fecha: 7/10/25
*   Autor: Santiago Bautista Velasquez
*   Materia: Sistemas Operativos
*   Tema: Función Fork, Creación de procesos
*
*******************************************************/
//-----------------------------------------------------------
// Observación general:
//
// Este programa demuestra el uso de la función fork() para
// crear procesos en un sistema operativo basado en UNIX.
//
// La función fork():
//   - Crea un proceso hijo que es una copia del proceso padre.
//   - Devuelve:
//       > 0  → Al proceso padre (valor: PID del hijo)
//       = 0  → Al proceso hijo
//       < 0  → Si ocurre un error en la creación
//
// Nota importante:
//   Al ejecutarse varias veces, puede parecer que los mensajes
//   del padre y del hijo se “intercalan” o mezclan. Esto no es
//   un bug real, sino un comportamiento normal debido a la
//   concurrencia: ambos procesos se ejecutan simultáneamente
//   y comparten la misma salida estándar (stdout).
//-----------------------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Llamada al sistema fork(), crea un nuevo proceso.
    // El valor retornado se almacena en la variable processID.
    int processID = fork();


    // Si fork() devuelve un número positivo, estamos en el proceso padre.
    if(processID > 0) {

        printf("\n 'proceso padre'");

    }


    // Si fork() devuelve 0, significa que estamos en el proceso hijo recién creado.
    else if(processID == 0) {

        printf("\n 'proceso hijo' recien creado \n");

    }


    // Si fork() devuelve un valor negativo, la creación del proceso falló.
    else {

        printf("\n llamada al sistema fork() falló\n");

    }

  
    // Ambas ejecuciones (padre e hijo) llegan a este punto.
    // Este bloque de código se ejecuta en paralelo en ambos procesos.

    printf("\n\n Imprimiendo ... \n");

    // Bucle for: imprime los números del 0 al 4.
    // Cada proceso (padre e hijo) ejecutará este bucle por separado.
    for (int i = 0; i < 5; i++)
        printf(" %d ", i);

    // Mensaje de finalización que indica el fin de la ejecución del proceso.
    printf("\n Fin \n");


    // Fin del programa principal. Retorna 0 para indicar ejecución correcta.
    return 0;
}

