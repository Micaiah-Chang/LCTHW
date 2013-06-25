#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17.  */
void die(const char *message)
{
	 if(errno) {
		  perror(message);
	 } else {
		  printf("ERROR: %s\n", message);
	 }

	 exit(1);
}


// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int *(*sort)(int *numbers, int count, compare_cb cmp);

int *insert_sort(int *numbers, int count, compare_cb cmp)
{

     int i = 0;
     int j = 0;
     int temp = 0;
     int *target = malloc(count * sizeof(int));

	 if(count <= 1) return *numbers;
     if(!target) die("Memory error.");

     memcpy(target, numbers, count * sizeof(int));

     int hole = 0;
     
     for(i = 0; i < count; i++)
     {
	  temp = target[i];
	  hole = i;
	  while(hole > 0 && (cmp(target[hole-1], temp) > 0)) {
	       target[hole] = target[hole-1];
	       hole--;
	  }
	  target[hole] = temp;
     }

	 
	 return target;
     
}

/**
 *A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	 int temp = 0;
	 int i = 0;
	 int j = 0;
	 
	 if(count <= 1) return *numbers;

	 int *target = malloc(count * sizeof(int));

	 if(!target) die("Memory error.");

	 memcpy(target, numbers, count * sizeof(int));
	 
	 for(i = 0; i < count; i++) {
		  for(j = 0; j < count - 1; j++) {
			   if(cmp(target[j], target[j+1]) > 0) {
					temp = target[j+1];
					target[j+1] = target[j];
					target[j] = temp;
			   }
		  }
	 }

	 return target;
}

int sorted_order(int a, int b)
{
	 return a - b;
}

int reverse_order(int a, int b)
{
	 return b - a;
}

int strange_order(int a, int b)
{
	 if(a == 0 || b == 0) {
		  return 0;
	 } else {
		  return a % b;
	 }	 
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out
 */
void test_sorting(int *numbers, int count, compare_cb cmp, sort alg)
{
	 int i = 0;
	 int *sorted = alg(numbers, count, cmp);

	 if(!sorted) die("Failed to sort as requested");

	 for(i = 0; i < count; i++) {
		  printf("%d ", sorted[i]);
	 }
	 printf("\n");
	 
	 free(sorted);

	 /* unsigned char *data = (unsigned char *)cmp; */

	 /* for(i = 0; i < 25; i++) { */
	 /* 	  printf("%02x:", data[i]); */
	 /* } */

	 /* printf("\n"); */
}


int main(int argc, char *argv[])
{
	 if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

	 int count = argc - 1;
	 int i = 0;
	 char **inputs = argv + 1;

	 int *numbers = malloc(count * sizeof(int));
	 if(!numbers) die("Memory error.");

	 for(i = 0; i < count; i++) {
		  numbers[i] = atoi(inputs[i]);
	 }

	 printf("bubble_sort: ");
	 test_sorting(numbers, count, sorted_order, bubble_sort);
	 printf("insert_sort: ");
	 test_sorting(numbers, count, sorted_order, insert_sort);


	 printf("bubble_sort: ");
	 test_sorting(numbers, count, reverse_order, bubble_sort);
	 printf("insert_sort: ");
	 test_sorting(numbers, count, reverse_order, insert_sort);


	 printf("bubble_sort: ");
	 test_sorting(numbers, count, strange_order, bubble_sort);
	 printf("insert_sort: ");
	 test_sorting(numbers, count, strange_order, insert_sort);
	 // test_sorting(numbers, count , die);
	 // test_sorting(numbers, count, NULL);

	 free(numbers);

	 return 0;
}
