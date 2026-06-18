// PRACTICA_2_PP_2026C2.cpp
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
    // -------------------------------------------------------
    // 1. Leer configuracion del usuario
    // -------------------------------------------------------
    MatrixConfig cfg = readConfigFromUser();

    if (!validModulo(cfg.modN))
    {
        printf("Modulo invalido. Debe ser mayor que 1.\n");
        return 1;
    }

    // -------------------------------------------------------
    // 2. Crear matrices A y B
    // -------------------------------------------------------
    Matrix A = createMatrix(cfg.rowsA, cfg.colsA);
    Matrix B = createMatrix(cfg.rowsB, cfg.colsB);

    if (!A.data || !B.data)
    {
        printf("Error de memoria creando A o B.\n");
        destroyMatrix(&A);
        destroyMatrix(&B);
        return 1;
    }

    // Verificar que la multiplicacion A*B sea posible
    if (!canMultiply(&A, &B))
    {
        printf("\nNo es posible calcular A * B. Se requiere A.cols == B.rows.\n");
        printf("A es %d x %d\n", A.rows, A.cols);
        printf("B es %d x %d\n", B.rows, B.cols);
        if (canMultiplyTransposeA(&A, &B))
            printf("Nota: A^T * B si seria posible.\n");
        else
            printf("Nota: A^T * B tampoco seria posible.\n");
        destroyMatrix(&A);
        destroyMatrix(&B);
        return 1;
    }

    // -------------------------------------------------------
    // 3. Crear matrices resultado
    //    Cseq = referencia secuencial
    //    Ctmp = buffer reutilizable para cada benchmark
    // -------------------------------------------------------
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

    // -------------------------------------------------------
    // 4. Llenar A y B con valores aleatorios y mostrar muestra
    // -------------------------------------------------------
    fillRandomMatrix(&A, cfg.minValue, cfg.maxValue, cfg.seed);
    fillRandomMatrix(&B, cfg.minValue, cfg.maxValue, cfg.seed + 1);
    printMatrixSample(&A, 4, 6, "A");
    printMatrixSample(&B, 4, 6, "B");

    // -------------------------------------------------------
    // 5. Calcular resultado de referencia (secuencial)
    // -------------------------------------------------------
    printf("\nCalculando referencia secuencial...\n");
    matmulModSequential(&A, &B, &Cseq, cfg.modN);

    // -------------------------------------------------------
    // 6. Benchmarks
    // -------------------------------------------------------
    printf("\nEjecutando benchmarks (%d repeticiones cada uno)...\n", cfg.repetitions);

    TimingResult seq =
        benchmarkMatMul(matmulModSequential, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);

    TimingResult ompRows =
        benchmarkMatMul(matmulModOmpRows, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);

    TimingResult ompCollapse =
        benchmarkMatMul(matmulModOmpCollapse, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);

    TimingResult ompTranspose =
        benchmarkMatMul(matmulModOmpTransposeB, &A, &B, &Ctmp, &Cseq, cfg.modN, cfg.repetitions);

    TimingResult ompBlocked =
        benchmarkMatMulBlocked(matmulModOmpBlocked, &A, &B, &Ctmp, &Cseq,
            cfg.modN, cfg.blockSize, cfg.repetitions);

    // -------------------------------------------------------
    // 7. Imprimir resultados
    // -------------------------------------------------------
    printf("\nMultiplicacion matricial modulo %d\n", cfg.modN);
    printf("A: %d x %d\n", A.rows, A.cols);
    printf("B: %d x %d\n", B.rows, B.cols);
    printf("C: %d x %d\n", Cseq.rows, Cseq.cols);
    printf("Threads max OpenMP: %d\n", omp_get_max_threads());

    printBenchmarkTable(&seq, &ompRows, &ompCollapse, &ompTranspose, &ompBlocked);
    printTheoreticalMetrics(A.rows, A.cols, B.cols);
    printAssignmentReminder();

    // -------------------------------------------------------
    // 8. Liberar memoria
    // -------------------------------------------------------
    destroyMatrix(&A);
    destroyMatrix(&B);
    destroyMatrix(&Cseq);
    destroyMatrix(&Ctmp);

    return 0;
}
