# Práctica 2 — Multiplicación matricial module N

## Problema

Generar 2 matrices NxM y multplicarlas. Al resultado aplicar la operación modulo N`.

Dado tres valores objetivo, por ejemplo `10`, `20` y `30`, el programa debe contar

## Métodos obligatorios para alumnos
1. Multiplicación.


## Posterior en clase
El profesor mostrará: las diferentes opciones de paralelización, la implementación de cada una, y el análisis de resultados.


## Requisitos
- Usar estilo C.
- Usar apuntadores intensivamente.
- Se permite usar `struct` para configuración y resultados.
- Usar C++ únicamente para `std::chrono`.
- Comparar tiempo con `omp_get_wtime()`.
- Implementar todo lo que diga "TODO""

## Parámetros configurables
- tamaño del columnas y renglones de las matrices
- Verificar si es posible la multiplicación con los tamaños dados
- Modulo N
- repeticiones

## Entregables
- código completo
- tabla de tiempos
- TDG
- cálculo de T1, Tinf, paralelismo y Pmin
