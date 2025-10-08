/****************************************************
*
*   Fecha: 7/10/25
*   Autor: Santiago Bautista Velasquez
*   Materia: Sistemas Operativos
*   Tema: Comunicación entre procesos (PIPE)
*
*   Descripción:
*   --------------------------------------------
*   Este programa implementa un ejemplo básico de
*   comunicación entre procesos usando la llamada
*   al sistema pipe() en C.
*
*   El proceso PADRE envía un mensaje al proceso HIJO
*   a través del PIPE. El proceso HIJO lo recibe e imprime.
*
*   - pipefd[0] → extremo de lectura
*   - pipefd[1] → extremo de escritura
*   - fork() crea un proceso hijo que hereda los descriptores
*   - close() cierra los extremos no utilizados
*
*   Compilación:
*       gcc -Wall -Wextra -O2 -o comunicacion_pipe comunicacion_pipe.c
*
*   Ejecución:
*       ./comunicacion_pipe
*
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2]; // Archivo descriptor para el "PIPE"
    pid_t pHijo_PID;

    if (pipe(pipefd) == -1) {
        perror("PIPE");
        exit(EXIT_FAILURE);
    }

    pHijo_PID = fork(); // Creación proceso HIJO
    if (pHijo_PID == -1) {
        perror("FORK");
        exit(EXIT_FAILURE);
    }

    if (pHijo_PID == 0) {
        // Código del proceso hijo
        close(pipefd[1]); // Cierra el descriptor de escritura
        char mensaje[100];
        int lecturaBYTES;

        lecturaBYTES = read(pipefd[0], mensaje, sizeof(mensaje));
        if (lecturaBYTES == -1) {
            perror("LECTURA!");
            exit(EXIT_FAILURE);
        }

        printf("Proceso HIJO: Recibe mensaje del PADRE: %.*s \n", lecturaBYTES, mensaje);
        close(pipefd[0]);
    } else {
        close(pipefd[0]);
        char mensajePADRE[] = "Hola HIJO desde el PADRE!";
        int escrituraBYTES;
        escrituraBYTES = write(pipefd[1], mensajePADRE, strlen(mensajePADRE));

        if (escrituraBYTES == -1) {
            perror("ESCRITURA");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
    }

    return 0;
}


