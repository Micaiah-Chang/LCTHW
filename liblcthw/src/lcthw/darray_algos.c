#include <lcthw/darray_algos.h>
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
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
//	 return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
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
 /* function siftDown(a, start, end) is */
 /*     input:  end represents the limit of how far down the heap */
 /*                   to sift. */
 /*     root := start */

 /*     while root * 2 + 1 ≤ end do          (While the root has at least one child) */
 /*         child := root * 2 + 1        (root*2 + 1 points to the left child) */
 /*         swap := root        (keeps track of child to swap with) */
 /*         (check if root is smaller than left child) */
 /*         if a[swap] < a[child] */
 /*             swap := child */
 /*         (check if right child exists, and if it's bigger than what we're currently swapping with) */
 /*         if child+1 ≤ end and a[swap] < a[child+1] */
 /*             swap := child + 1 */
 /*         (check if we need to swap at all) */
 /*         if swap != root */
 /*             swap(a[root], a[swap]) */
 /*             root := swap          (repeat to continue sifting down the child now) */
 /*         else */
 /*             return */
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;
//	 return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_my_mergesort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;

/* /\* array A[] has the items to sort; array B[] is a work array *\/ */
/* 	 BottomUpSort(int n, array A[n], array B[n]) */
/* 	 { */
/* 		  int width; */
 
/* 		  /\* Each 1-element run in A is already "sorted". *\/ */
 
/* 		  /\* Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted. *\/ */
/* 		  for (width = 1; width < n; width = 2 * width) */
/* 		  { */
/* 			   int i; */
 
/* 			   /\* Array A is full of runs of length width. *\/ */
/* 			   for (i = 0; i < n; i = i + 2 * width) */
/* 			   { */
/* 					/\* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[] *\/ */
/* 					/\* or copy A[i:n-1] to B[] ( if(i+width >= n) ) *\/ */
/* 					BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B); */
/* 			   } */
 
/* 			   /\* Now work array B is full of runs of length 2*width. *\/ */
/* 			   /\* Copy array B to array A for next iteration. *\/ */
/* 			   /\* A more efficient implementation would swap the roles of A and B *\/ */
/* 			   CopyArray(A, B, n); */
/* 			   /\* Now array A is full of runs of length 2*width. *\/ */
/* 		  } */
/* 	 } */
 
/* 	 BottomUpMerge(array A[], int iLeft, int iRight, int iEnd, array B[]) */
/* 	 { */
/* 		  int i0 = iLeft; */
/* 		  int i1 = iRight; */
/* 		  int j; */
 
/* 		  /\* While there are elements in the left or right lists *\/ */
/* 		  for (j = iLeft; j < iEnd; j++) */
/* 		  { */
/* 			   /\* If left list head exists and is <= existing right list head *\/ */
/* 			   if (i0 < iRight && (i1 >= iEnd || A[i0] <= A[i1])) */
/* 			   { */
/* 					B[j] = A[i0]; */
/* 					i0 = i0 + 1; */
/* 			   } */
/* 			   else */
/* 			   { */
/* 					B[j] = A[i1]; */
/* 					i1 = i1 + 1; */
/* 			   } */
/* 		  } */
/* 	 } */

}
