#include <omp.h>
#include "matmul_algorithms.h"
#include "matrix_tools.h"

void matmulModSequential(const Matrix* A, const Matrix* B, Matrix* C, int modN)
{
    /* TODO Limpiar la matriz multiplicación antes de llenarla */
    /* TODO : Implementar el algoritmo */

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
