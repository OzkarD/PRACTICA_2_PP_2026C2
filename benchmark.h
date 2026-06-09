#include "config.h"

typedef void (*MatMulFn)(const Matrix* A, const Matrix* B, Matrix* C, int modN);
typedef void (*MatMulBlockedFn)(const Matrix* A, const Matrix* B, Matrix* C, int modN, int blockSize);

TimingResult benchmarkMatMul(MatMulFn fn, const Matrix* A, const Matrix* B, Matrix* C, const Matrix* reference, int modN, int repetitions);
TimingResult benchmarkMatMulBlocked(MatMulBlockedFn fn, const Matrix* A, const Matrix* B, Matrix* C, const Matrix* reference, int modN, int blockSize, int repetitions);
void printBenchmarkTable(const TimingResult* seq, const TimingResult* ompRows, const TimingResult* ompCollapse, const TimingResult* ompTranspose, const TimingResult* ompBlocked);
