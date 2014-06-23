#include <lcthw/darray_algos.h>
#include <bsd/stdlib.h>
#include <stdlib.h>


int DArray_qsort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
}

int DArray_my_qsort(DArray *array, DArray_compare cmp)
{
	 // It's array->end - 1 in order to enforce left and right
	 // inclusiveness in the qsort.
	 my_qsort(array, 0, array->end - 1, cmp);
	 return 0;
}

int partition(DArray *array, int left, int right, int pivot, DArray_compare cmp)
{
	 assert(pivot >= left && pivot =< right &&
			"pivot outside of acceptable range.");
	 assert(array != NULL && "array cannot be NULL");

	 void *pivot_value = array->contents[pivot];
	 int index = left;

	 DArray_swap(array, pivot, right);

	 int i = 0;

	 for(i = 0; i < right; i++) {
		  if(cmp(&array->contents[i], &pivot_value) < 0) {
			   DArray_swap(array, index, i);
			   index++;
		  }
	 }
	 DArray_swap(array, index, right);

	 return index;
}

DArray *my_qsort(DArray *array, int left, int right, DArray_compare cmp)
{
	 // NOTE: This algorithm assumes left and right are INCLUSIVE.
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
	 heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
	 // return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_my_heapsort(DArray *array, DArray_compare cmp)
{
	 heapify(array, array->end, cmp);
	 int end = array->end - 1;

	 while(end > 0) {
	 	  DArray_swap(array, end, 0);
	 	  end--;
	 	  sift_down(array, 0, end, cmp);
	 }

	 return 0;

}

void heapify(DArray *array, int length, DArray_compare cmp)
{
	 int start = (length - 2) / 2;

	 while(start >= 0) {
		  sift_down(array, start, length - 1, cmp);
		  start--;
	 }
}

void sift_down(DArray *array, int start, int end, DArray_compare cmp)
{
	 int root = start;
	 int child = 0;
	 int swap = 0;

	 while(2 * root + 1 <= end) {
		  child = 2 * root + 1;
		  swap = root;
		  if(cmp(&array->contents[swap], &array->contents[child]) < 0) {
			   swap = child;
		  }
		  if(child + 1 <= end &&
			 cmp(&array->contents[swap], &array->contents[child+1]) < 0) {
			   swap = child + 1;
		  }
		  if(swap != root) {
			   DArray_swap(array, root, swap);
			   root = swap;
					} else {
			   return;
		  }
	 }
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	 mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
//	 return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_my_mergesort(DArray *array, DArray_compare cmp)
{
	 DArray *temp = DArray_create(array->element_size,
								  array->max);
	 int i = 0;
	 temp = my_mergesort(array, cmp);
	 for(i = 0; i < array->end; i++) {
		  DArray_set(array, i ,DArray_get(temp, i));
	 }
	 return 0;
}

DArray *my_mergesort(DArray *array, DArray_compare cmp)
{
	 if(array->end <= 1) return array;

	 DArray *left = DArray_create(array->element_size,
								  array->max);
	 DArray *right = DArray_create(array->element_size,
								   array->max);

	int mid = array->end / 2;

	int i = 0;
	for(i = 0; i < mid; i++) {
		 DArray_push(left, DArray_get(array, i));
	}
	for(i = mid; i < array->end; i++) {
		 DArray_push(right, DArray_get(array, i));
	}
	left = my_mergesort(left, cmp);
	right = my_mergesort(right, cmp);
	return my_merge(left, right, cmp);
}

DArray *my_merge(DArray *left, DArray *right, DArray_compare cmp)
{
	 DArray *result = DArray_create(left->element_size,
									left->max);
	 int left_len = 0;
	 int right_len = 0;

	 while(left->end > left_len || right->end > right_len) {
		  if(left->end > left_len && right->end > right_len) {
			   if(cmp(&left->contents[left_len],
					  &right->contents[right_len]) <= 0) {
					DArray_push(result, DArray_get(left, left_len));
					left_len++;
			   } else {
					DArray_push(result, DArray_get(right, right_len));
					right_len++;
			   }
		  } else if(left->end > left_len) {
			   DArray_push(result, DArray_get(left, left_len));
			   left_len++;
		  } else if(right->end > right_len) {
			   DArray_push(result, DArray_get(right, right_len));
			   right_len++;
		  } else {
			   sentinel("Shouldn't be here");
		  }
	 }
	 DArray_destroy(left);
	 DArray_destroy(right);
	 return result;
error:
	 if(left) DArray_destroy(left);
	 if(right) DArray_destroy(right);
	 return NULL;
}

int DArray_sort_add(DArray *array, void *el, DArray_compare cmp)
{
	 check(array != NULL, "Input cannot be NULL");

	 DArray_push(array, el);
	 DArray_qsort(array, cmp);
	 return 0;
error:
	 return -1;
}
