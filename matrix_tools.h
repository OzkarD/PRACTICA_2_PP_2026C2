#include "config.h"

Matrix createMatrix(int rows, int cols);
void destroyMatrix(Matrix* m);

int canMultiply(const Matrix* A, const Matrix* B);
int canMultiplyTransposeA(const Matrix* A, const Matrix* B);
int validModulo(int modN);

void fillRandomMatrix(Matrix* m, int minValue, int maxValue, unsigned int seed);
void zeroMatrix(Matrix* m);
void printMatrixSample(const Matrix* m, int maxRows, int maxCols, const char* name);
void transposeMatrix(const Matrix* src, Matrix* dst);
int matricesEqual(const Matrix* A, const Matrix* B);

MatrixConfig readConfigFromUser(void);
int modNormalize(long long x, int modN);
