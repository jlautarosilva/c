#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#define LONG 4
int main(int argc, char **argv) {
    //Declaración de matrices y sus indices
    int i, j, k;
    double A[LONG][LONG];
    FILE *m1, *m2, *resultado;
    //Variables auxiliares
    int suma;
    //Definicion de las variables del reloj
    clock_t startTime, endTime;
    struct tms startTms, endTms;
    unsigned int micros;
    long int ticksPerSec;

    if(argc != 2) {
       printf("Instrucciones de uso: matriz_mpi <Fichero Matriz 1>\n");
       return 1;
    }

    // Abrir los ficheros de entrada en lectura y binario
    m1 = fopen(argv[1], "rb"); 
    if(!m1) {
       printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
       return 1;
    }
    //Inicializar matrices en 0
    for(i = 0; i< LONG; i++){
        for(j = 0; j < LONG; j++){
	    A[i][j] = 0;
        }
    }

//Llenado de la matriz con el archivo
    for (i = 0; i < LONG; i++) {
	for (j = 0; j < LONG ; j++) {
			fscanf(m1,"%lf",&A[i][j]);
	}
    }

    for (i = 0; i < LONG; i++) {
	for (j = 0; j < LONG ; j++) {
			printf("%f ",A[i][j]);
	}
	printf("\n");
    }

return 0;
}

