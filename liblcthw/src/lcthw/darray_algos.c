#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);


	 return 0; 
}

int DArray_my_qsort(DArray *array, DArray_compare cmp)
{
	  /*  function quicksort(array, left, right) */
 
      /* // If the list has 2 or more items */
      /* if left < right */
 
      /*     // See "Choice of pivot" section below for possible choices */
      /*     choose any pivotIndex such that left ≤ pivotIndex ≤ right */
 
      /*     // Get lists of bigger and smaller items and final position of pivot */
      /*     pivotNewIndex := partition(array, left, right, pivotIndex) */
 
      /*     // Recursively sort elements smaller than the pivot */
      /*     quicksort(array, left, pivotNewIndex - 1) */
 
      /*     // Recursively sort elements at least as big as the pivot */
      /*     quicksort(array, pivotNewIndex + 1, right) */
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
//	 return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
//	 return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}
