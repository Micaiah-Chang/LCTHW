#ifndef darray_algos_h
#define darray_algos_h

#include <lcthw/darray.h>

typedef int (*DArray_compare)(const void *a, const void *b);

int partition(DArray *array, int left, int right, int pivot, DArray_compare cmp);
DArray *my_qsort(DArray *array, int left, int right, DArray_compare cmp);

int DArray_qsort(DArray *array, DArray_compare cmp);
int DArray_my_qsort(DArray *array, DArray_compare cmp);


int DArray_heapsort(DArray *array, DArray_compare cmp);

int DArray_mergesort(DArray *array, DArray_compare cmp);

#endif
