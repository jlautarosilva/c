/*
* Nombre      : matriz_mpi
* Autor       : Juan Lautaro Silva Ortíz, Jorge Andrés Elgueta Morales 
* fecha       : 30-05-2013
* Descripción : Aplicación que multiplica dos matrices utilizando MPI.
*
* Require     : gcc compiler and OpenSSL library
* Compile     : gcc -fopenmp multiplicacion_matricial.c -o matriz_mpi -Wall
*               ld -lgomp matriz_mpi
*/

#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    //Declaración de matrices y sus indices
    int largo = atoi(argv[4]);
    int i, j, k;
    double **A = (double**)malloc(sizeof(double*) * largo);
    double **B = (double**)malloc(sizeof(double*) * largo);
    double **C = (double**)malloc(sizeof(double*) * largo);
    FILE *m1, *m2, *resultado;
    //Variables auxiliares
    int suma;
    //Definicion de las variables del reloj
    clock_t startTime, endTime;
    struct tms startTms, endTms;
    unsigned int micros;
    long int ticksPerSec;

    if(argc != 5) {
       printf("Instrucciones de uso: matriz_mpi <Fichero Matriz 1> <Fichero Matriz 2> <Fichero Matriz resultado> <Largo_Matriz>\n");
       return 1;
    }
    
    //Reservar memoria para la matriz
    for(i=0;i<largo;i++){
	    A[i] = (double*)malloc(sizeof(double) * largo);
    }
    for(i=0;i<largo;i++){
	    B[i] = (double*)malloc(sizeof(double) * largo);
    }
    for(i=0;i<largo;i++){
	    C[i] = (double*)malloc(sizeof(double) * largo);
    }
    if(!A || !B || !C){
    printf("No se pudo reservar memoria para la matriz");
    }
    
    // Abrir los ficheros de entrada en lectura y binario
    m1 = fopen(argv[1], "rb"); 
    if(!m1) {
       printf("El fichero %s no existe o no puede ser abierto.\n", argv[1]);
       return 1;
    }
    m2 = fopen(argv[2], "rb"); 
    if(!m2) {
       printf("El fichero %s no existe o no puede ser abierto.\n", argv[2]);
       return 1;
    }

    // Crear o sobreescribir el fichero de salida en escritura y binario
    resultado = fopen(argv[3], "wb"); 
    if(!resultado) {
       printf("El fichero %s no puede ser creado.\n", argv[3]);
       fclose(m1);
       fclose(m2);
       return 1;
    }

    //Inicializar matrices en 0
    for(i = 0; i< largo; i++){
        for(j = 0; j < largo; j++){
    	    A[i][j] = 0;
    	    B[i][j] = 0;
    	    C[i][j] = 0;
        }
    }

    //Llenado de las matrices con el archivo
    for (i = 0; i < largo; i++) {
	for (j = 0; j < largo ; j++) {
			fscanf(m1,"%lf",&A[i][j]);
			fscanf(m2,"%lf",&B[i][j]);
	}
    }

    //Iniciar reloj
    startTime = times(&startTms);

    // Multiplicación de las matrices
    for (i = 0; i < largo; i++) {
	for (j = 0; j < largo; j++) {
		suma = 0.0;
		for (k = 0; k < largo; k++) {
			suma += A[i][k]*B[k][j];
		}
	C[i][j] += suma;
	}
    }

    //Finalizar reloj
    endTime = times(&endTms);
    
    //Calcular y mostrar los tiempos de ejecución
    micros = endTime - startTime;
    ticksPerSec = sysconf(_SC_CLK_TCK);
    printf("Tiempo transcurrido (us): %lu\n", micros*1000000/ticksPerSec);
    printf("Tiempo de CPU modo usuario (us): %lu\n",(endTms.tms_utime - startTms.tms_utime)*1000000/ticksPerSec);
    printf("Tiempo de CPU modo sistema (us): %lu\n",(endTms.tms_stime - startTms.tms_stime)*1000000/ticksPerSec);
    
    //Esribir los resultados en el archivo de resultado
    for (i = 0; i < largo; i++) {
    	for (j = 0; j < largo; j++) {
    		fprintf(resultado,"%lf ",C[i][j]);
            }
            fprintf(resultado,"\n");
    }
    
    free(A);
    free(B);
    free(C);
    return 0;
}
