#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);


	 return 0; 
}

int DArray_my_qsort(DArray *array, DArray_compare cmp)
{
	 my_qsort(array, 0, array->end - 1, cmp);
	 return 0;
}

int partition(DArray *array, int left, int right, int pivot, DArray_compare cmp)
{
	 assert(pivot >= left && pivot =< right &&
			"pivot outside of acceptable range.");
	 assert(array != NULL && "array cannot be NULL");
	 
	 void *pivot_value = array->contents[pivot];
	 array->contents[pivot] = array->contents[right];
	 array->contents[right] = pivot_value;
	 int index = left;
	 void *temp = NULL;
	 int i = 0;

	 
	 for(i = 0; i < right; i++) {
		  if(strcmp(array->contents[i], pivot_value) < 0) {
			   temp = array->contents[i];
			   array->contents[i] = array->contents[index];
			   array->contents[index] = temp;
			   index++;
		  }
	 }
	 temp = array->contents[index];
	 array->contents[index] = array->contents[right];
	 array->contents[right] = temp;

	 return index;
}

DArray *my_qsort(DArray *array, int left, int right, DArray_compare cmp)
{
	 assert(array != NULL && "Array cannot be NULL");
	 assert(left <= right && "Left value cannot be greater than right!");
	 assert(left >= 0 && right >= && "Left and right values cannot be negative!");
	 
	 if(left < right) {
		  int pivot = right;

		  pivot = partition(array, left, right, pivot, cmp);

		  my_qsort(array, left, pivot - 1, cmp);
		  my_qsort(array, pivot + 1, right, cmp);
	 }

	 
	 return array;
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
