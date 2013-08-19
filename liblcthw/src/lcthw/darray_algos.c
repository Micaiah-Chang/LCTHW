#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);


	 return 0; 
}

int DArray_my_qsort(DArray *array, DArray_compare cmp)
{
	 // -1 in order to enforce left and right are inclusive in the partition
	 // or sort function.
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
	 void *temp = NULL;

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
	 qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	 return 0;

 /* 	  function heapSort(a, count) is */
 /*     input:  an unordered array a of length count */
 
 /*     (first place a in max-heap order) */
 /*     heapify(a, count) */
 
 /*     end := count-1 //in languages with zero-based arrays the children are 2*i+1 and 2*i+2 */
 /*     while end > 0 do */
 /*         (swap the root(maximum value) of the heap with the last element of the heap) */
 /*         swap(a[end], a[0]) */
 /*         (decrease the size of the heap by one so that the previous max value will */
 /*         stay in its proper placement)  */
 /*         end := end - 1 */
 /*         (put the heap back in max-heap order) */
 /*         siftDown(a, 0, end)           */
 
}

void heapify(DArray *array, int length, DArray_compare cmp)
{

	  /* function heapify(a, count) is */
 /*     (start is assigned the index in a of the last parent node) */
 /*     start := (count - 2 ) / 2 */
     
 /*     while start ≥ 0 do */
 /*         (sift down the node at index start to the proper place such that all nodes below */
 /*          the start index are in heap order) */
 /*         siftDown(a, start, count-1) */
 /*         start := start - 1 */
 /*     (after sifting down the root all nodes/elements are in heap order) */

}

void sift_down(DArray *array, int start, int end, DArray_compare cmp)
{
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
