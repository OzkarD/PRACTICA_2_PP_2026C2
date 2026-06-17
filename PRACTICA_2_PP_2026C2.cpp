// PRACTICA_2_PP_2026C2.cpp : Este archivo contiene la función "main"
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "config.h"
#include "matrix_tools.h"
#include "matmul_algorithms.h"
#include "benchmark.h"
#include "metrics.h"


int main()
{
    MatrixConfig cfg = readConfigFromUser();

    if (!validModulo(cfg.modN)) 
    { 
        printf("Modulo invalido. Debe ser mayor que 1.\n"); 
        return 1; 
    }
    
    Matrix A = createMatrix(cfg.rowsA, cfg.colsA);
    Matrix B = createMatrix(cfg.rowsB, cfg.colsB);
    
    if (!A.data || !B.data) 
    { 
        printf("Error de memoria creando A o B.\n"); 
        destroyMatrix(&A); 
        destroyMatrix(&B); 
        return 1; 
    }
    if (!canMultiply(&A, &B)) 
    {
        printf("\nNo es posible calcular A * B. Se requiere A.cols == B.rows.\n");
        printf("A es %d x %d\n", A.rows, A.cols);
        printf("B es %d x %d\n", B.rows, B.cols);
        if (canMultiplyTransposeA(&A, &B)) 
            printf("Nota: A^T * B si seria posible.\n");
        else 
            printf("Nota: A^T * B tampoco seria posible.\n");

        destroyMatrix(&A); destroyMatrix(&B); return 1;
    }

    Matrix Cseq = createMatrix(A.rows, B.cols);
    Matrix Ctmp = createMatrix(A.rows, B.cols);
    
    if (!Cseq.data || !Ctmp.data) 
    { 
        printf("Error de memoria creando C.\n"); 
        destroyMatrix(&A); 
        destroyMatrix(&B); 
        destroyMatrix(&Cseq); 
        destroyMatrix(&Ctmp); 
        return 1; 
    }
    fillRandomMatrix(&A, cfg.minValue, cfg.maxValue, cfg.seed);
    fillRandomMatrix(&B, cfg.minValue, cfg.maxValue, cfg.seed + 1);
    printMatrixSample(&A, 4, 6, "A");
    printMatrixSample(&B, 4, 6, "B");
    printf("\nCalculando referencia secuencial...\n");
    matmulModSequential(&A, &B, &Cseq, cfg.modN);
    TimingResult seq = benchmarkMatMul(matmulModSequential, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);
    
    /* VERSIONES PARALELAS: LAS IMPLEMENTA EL PROF*/
    //TimingResult ompRows = benchmarkMatMul(matmulModOmpRows, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);
    //TimingResult ompCollapse = benchmarkMatMul(matmulModOmpCollapse, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);
    //TimingResult ompTranspose = benchmarkMatMul(matmulModOmpTransposeB, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);
    //TimingResult ompBlocked = benchmarkMatMulBlocked(matmulModOmpBlocked, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.blockSize, cfg.repetitions);

    printf("\nMultiplicacion matricial modulo %d\n", cfg.modN);
    printf("A: %d x %d\n", A.rows, A.cols);
    printf("B: %d x %d\n", B.rows, B.cols);
    printf("C: %d x %d\n", Cseq.rows, Cseq.cols);
    //printf("Threads max OpenMP: %d\n", omp_get_max_threads());
    //printBenchmarkTable(&seq, &ompRows, &ompCollapse, &ompTranspose, &ompBlocked);
    printTheoreticalMetrics(A.rows, A.cols, B.cols);
    printAssignmentReminder();
    destroyMatrix(&A); 
    destroyMatrix(&B); 
    destroyMatrix(&Cseq); 
    destroyMatrix(&Ctmp);
    return 0;
}

//Conclusiones:
/*
* Pedro Meza Flores     11087
En esta práctica el objetivo principal era seguir trabajando con arerglosp dinámicos, que es lo que hemos estado revisando en clases, de igual manera
los cambios más significativos fueron los siguientes:

Un triple ciclo for, donde los primeros dos ciclos de i y j, tenemos una inspeccion de las filas y columnas de cada una de las matrices A y B, y
finalmente el ciclo de K donde tenemos el proposito de hacer el producto punto de las dos matrices y estar haciendo el recorrido de ir a la derecha
de la matriz A y hacia abajo de la matriz B.

Finalmente, se integro el modN con la funcion declarada en matrix_tools.cpp llamada modNormalize, la cual nos ayuda a calcular el residuo de la
multiplicación de matrices.

*Nahomy Rivadeneyra     11082

*/