#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_tools.h"

Matrix createMatrix(int rows, int cols)
{
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = NULL;
    if (rows <= 0 || cols <= 0)
        return m;

    /* TODO : Crear la matriz*/

    m.data = (int*)malloc(rows * cols * sizeof(int));
    return m;
}

void destroyMatrix(Matrix* m)
{
    if (!m) return;
    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

int canMultiply(const Matrix* A, const Matrix* B)
{
    return A && B && A->cols == B->rows;
}

int canMultiplyTransposeA(const Matrix* A, const Matrix* B)
{
    return A && B && A->rows == B->rows;
}

int validModulo(int modN)
{
    return modN > 1;
}

void fillRandomMatrix(Matrix* m, int minValue, int maxValue, unsigned int seed)
{
    if (!m || !m->data)
        return;
    // TODO: llenar la matriz /
        srand(seed);

    for (int i = 0; i < m->rows * m->cols; i++)
    {
        m->data[i] = minValue + rand() % (maxValue - minValue + 1);
    }
}

void zeroMatrix(Matrix* m)
{
    if (!m || !m->data)
        return;
    /* TODO: limpiar la matriz*/
    for (int i = 0; i < m->rows * m->cols; i++)
    {
        m->data[i] = 0;
    }
}

void printMatrixSample(const Matrix* m, int maxRows, int maxCols, const char* name)
{
    if (!m || !m->data)
        return;
    int rLim = m->rows < maxRows ? m->rows : maxRows;
    int cLim = m->cols < maxCols ? m->cols : maxCols;
    printf("\nMuestra de %s (%d x %d):\n", name, m->rows, m->cols);

    /* TODO: Imprimir solo un fragmento de la matriz*/
    for (int i = 0; i < rLim; i++)
    {
        for (int j = 0; j < cLim; j++)
        {
            printf("%4d ", m->data[i * m->cols + j]);
        }

        printf("\n");
    }
}

void transposeMatrix(const Matrix* src, Matrix* dst)
{
    if (!src || !dst || !src->data || !dst->data) return;
    if (dst->rows != src->cols || dst->cols != src->rows) return;
    for (int i = 0; i < src->rows; i++)
        for (int j = 0; j < src->cols; j++)
            dst->data[j * dst->cols + i] = src->data[i * src->cols + j];
}

int matricesEqual(const Matrix* A, const Matrix* B)
{
    if (!A || !B || !A->data || !B->data)
        return 0;
    if (A->rows != B->rows || A->cols != B->cols)
        return 0;
    for (int i = 0; i < A->rows * A->cols; i++)
        if (A->data[i] != B->data[i])
            return 0;
    return 1;
}

MatrixConfig readConfigFromUser(void)
{
    MatrixConfig cfg;
    cfg.rowsA = 512;
    cfg.colsA = 512;
    cfg.rowsB = 512;
    cfg.colsB = 512;
    cfg.modN = 101;
    cfg.minValue = 0;
    cfg.maxValue = 100;
    cfg.repetitions = 3;
    cfg.blockSize = 32;
    cfg.seed = (unsigned int)time(NULL);
    printf("Filas de A: ");
    scanf_s("%d", &cfg.rowsA);
    printf("Columnas de A: ");
    scanf_s("%d", &cfg.colsA);
    printf("Filas de B: ");
    scanf_s("%d", &cfg.rowsB);
    printf("Columnas de B: ");
    scanf_s("%d", &cfg.colsB);
    printf("Modulo N: "); scanf_s("%d", &cfg.modN);
    printf("Valor minimo aleatorio: ");
    scanf_s("%d", &cfg.minValue);
    printf("Valor maximo aleatorio: ");
    scanf_s("%d", &cfg.maxValue);
    printf("Repeticiones benchmark: ");
    scanf_s("%d", &cfg.repetitions);
    printf("Block size para version blocked: ");
    scanf_s("%d", &cfg.blockSize);
    cfg.seed = (unsigned int)time(NULL);
    return cfg;
}

int modNormalize(long long x, int modN)
{
    int r = (int)(x % modN);
    if (r < 0)
        r += modN;
    return r;
}