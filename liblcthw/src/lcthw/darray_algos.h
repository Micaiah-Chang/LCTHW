#ifndef darray_algos_h
#define darray_algos_h

#include <lcthw/darray.h>

typedef int (*DArray_compare)(const void *a, const void *b);

int partition(DArray *array, int left, int right, int pivot, DArray_compare cmp);
DArray *my_qsort(DArray *array, int left, int right, DArray_compare cmp);

int DArray_qsort(DArray *array, DArray_compare cmp);
int DArray_my_qsort(DArray *array, DArray_compare cmp);

void heapify(DArray *array, int length, DArray_compare cmp);
void sift_down(DArray *array, int start, int end, DArray_compare cmp);

int DArray_heapsort(DArray *array, DArray_compare cmp);
int DArray_my_heapsort(DArray *array, DArray_compare cmp);

int DArray_mergesort(DArray *array, DArray_compare cmp);
int DArray_my_mergesort(DArray *array, DArray_compare cmp);

DArray *my_mergesort(DArray *array, DArray_compare cmp);
DArray *my_merge(DArray *left, DArray *right, DArray_compare cmp);


inline static void DArray_swap(DArray *array, int el1, int el2)
{
	 void *temp = array->contents[el2];
	 array->contents[el2] = array->contents[el1];
	 array->contents[el1] = temp;
}

#endif
