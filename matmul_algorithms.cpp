#include <omp.h>
#include "matmul_algorithms.h"
#include "matrix_tools.h"

void matmulModSequential(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{
    /* TODO Limpiar la matriz multiplicaci�n antes de llenarla */
    zeroMatrix(C);
    /* TODO : Implementar el algoritmo */
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            int sum = 0;
            for (int k = 0; k < A->cols; k++) {
                sum += A->data[i * A->cols + k] * B->data[k * B->cols + j];
            }
            C->data[i * C->cols + j] = sum % modN;
        }
    }   
}

void matmulModOmpRows(const Matrix* A, const Matrix* B, Matrix* C, int modN){

}

void matmulModOmpCollapse(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{
    
}

void matmulModOmpTransposeB(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{

}

void matmulModOmpBlocked(const Matrix* A, const Matrix* B, Matrix* C, int modN, int blockSize)
{

}
