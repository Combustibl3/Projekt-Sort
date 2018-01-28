#ifndef PROJEKT_SORT_SORT_H
#define PROJEKT_SORT_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

//Rückgabe der Funktionen ist die Anzahl der internen Vergleiche der Elemente (z.B. uint64_t comparisons)

uint64_t BubbleSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t MergeSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t SelectionSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t InsertionSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t QuickSort(uint32_t * first, uint32_t * last);

uint64_t ShellSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t CocktailSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t HeapSort(uint32_t * sortarray, uint32_t arraysize);

uint64_t RadixSort(uint32_t * sortarray, uint32_t arraysize);

#endif //PROJEKT_SORT_SORT_H
