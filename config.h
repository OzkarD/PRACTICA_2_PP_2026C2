#pragma once

typedef struct MatrixConfig {
    int rowsA;
    int colsA;
    int rowsB;
    int colsB;
    int modN;
    int minValue;
    int maxValue;
    int repetitions;
    int blockSize;
    unsigned int seed;
} MatrixConfig;

typedef struct Matrix {
    int rows;
    int cols;
    int* data;
} Matrix;

typedef struct TimingResult {
    double chronoSeconds;
    double ompSeconds;
    int correct;
} TimingResult;

