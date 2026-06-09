#pragma once
#include "config.h"

void matmulModSequential(const Matrix* A, const Matrix* B, Matrix* C, int modN);
void matmulModOmpRows(const Matrix* A, const Matrix* B, Matrix* C, int modN);
void matmulModOmpCollapse(const Matrix* A, const Matrix* B, Matrix* C, int modN);
void matmulModOmpTransposeB(const Matrix* A, const Matrix* B, Matrix* C, int modN);
void matmulModOmpBlocked(const Matrix* A, const Matrix* B, Matrix* C, int modN, int blockSize);
