/****************************************************
*
*  Fecha: 7/10/25
*  Autor: Santiago Bautista Velásquez
*  Materia: Sistemas Operativos
*  Tema: Función fork(), creación de procesos
*
*  Descripción general:
*  --------------------
*  Este programa ilustra el comportamiento de fork():
*   - fork() crea un nuevo proceso (proceso hijo) duplicando el proceso actual.
*   - En el proceso padre, fork() devuelve un entero > 0 (el PID del hijo).
*   - En el proceso hijo, fork() devuelve 0.
*   - En caso de error, fork() devuelve un valor negativo.
*
*  Expectativa de salida:
*  ----------------------
*  Se imprimirán mensajes diferenciando el rol (PADRE/HIJO) y,
*  al final, un bloque común impreso por ambos procesos para evidenciar
*  que ambos continúan ejecutando el mismo código tras el fork().
*
*******************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Llamada al sistema: crea un proceso hijo duplicando el actual.
    // Valor de retorno:
    //  > 0 : estamos en el PADRE (valor = PID del hijo)
    //    0 : estamos en el HIJO
    //  < 0 : error al crear el proceso
    int processID = fork();

    // Proceso Padre
    if (processID > 0) {
        printf("[PADRE] fork() devolvió un valor positivo.\n"
               "[PADRE] Este es el 'proceso padre' con PID: %d\n", getpid());
    }

    // Proceso Hijo
    else if (processID == 0) {
        printf("[HIJO]  fork() devolvió 0.\n"
               "[HIJO]  Este es un 'proceso hijo' recién creado con PID: %d\n", getpid());
        // Nota: Para mostrar el PID del padre real, se usa getppid().
        // Aquí se imprime getpid() porque pediste usar únicamente lo que ya está en el código.
        printf("[HIJO]  El 'proceso padre' de este 'proceso hijo' tiene el (supuesto) ID: %d\n", getpid());
    }

    // Opción en caso de fallo al crear el proceso hijo
    else {
        printf("[ERROR] fork() devolvió un valor negativo; la llamada al sistema falló.\n");
    }

    // Salida común a ambos procesos:
    // Se imprime exactamente el mismo bloque si fork() fue exitoso,
    // este texto aparecerá dos veces (una por el padre y otra por el hijo).
    printf("\n--- EJECUCIÓN CONTINUA EN AMBOS PROCESOS ---\n");
    printf("Si fork() tuvo éxito, tanto el 'proceso padre' como el 'proceso hijo' se ejecutan simultáneamente.\n");
    printf("Por eso, este bloque de texto aparece dos veces.\n");

    return 0;
}

