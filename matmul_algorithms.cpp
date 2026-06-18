#include <omp.h>
#include "matmul_algorithms.h"
#include "matrix_tools.h"

void matmulModSequential(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{
    zeroMatrix(C);

    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < B->cols; j++)
        {
            long long suma = 0;

            for (int k = 0; k < A->cols; k++)
            {
                suma += (long long)
                    A->data[i * A->cols + k] *
                    B->data[k * B->cols + j];
            }

            C->data[i * C->cols + j] = modNormalize(suma, modN);
        }
    }
}

void matmulModOmpRows(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{
   
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
