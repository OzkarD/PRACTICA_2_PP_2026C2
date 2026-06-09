#include <stdio.h>
#include "metrics.h"

void printTheoreticalMetrics(int rowsA, int colsA, int colsB)
{
    long long elementsC = (long long)rowsA * (long long)colsB;
    long long work = elementsC * (long long)colsA;
    printf("\nAnalisis teorico sugerido:\n");
    printf("C tiene %lld elementos.\n", elementsC);
    printf("Cada C[i][j] requiere %d productos/sumas.\n", colsA);
    printf("T1 ~ rowsA * colsA * colsB = %lld operaciones base.\n", work);
    printf("Tinf ideal si cada C[i][j] fuera tarea independiente ~ colsA = %d.\n", colsA);
    printf("Paralelismo ideal aproximado ~ rowsA*colsB = %lld.\n", elementsC);
}

void printAssignmentReminder(void)
{
    printf("\nRecordatorio para el reporte:\n");
    printf("- Dibujar TDG: cada nodo puede ser un calculo C[i][j].\n");
    printf("- Comparar parallel for, collapse(2), B transpuesta y blocked.\n");
    
}
