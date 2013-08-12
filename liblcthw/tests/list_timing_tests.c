#include "minunit.h"
#include <lcthw/list_algos.h>
#include <lcthw/list.h>
#include <time.h>


List *create_words(char *val[], int num_val)
{
	 int i = 0;
	 List *words = List_create();

	 for (i = 0; i < num_val; i++) {
		  List_push(words, val[i]);
	 }

	 return words;
}

void *time_bubble_sort()
{
	 int N = 10000;
	 int i = 0;
	 List *list = NULL;
	 	 char *values[] = {"blah", "blee", "bloo", "walking", "language", "1234", "see", "13987asdf", "hey yoo", "wub wub wub"}; 	 
	 struct timespec before;
	 clock_gettime(CLOCK_REALTIME, &before);

	 for (i = 0; i < N; i++) {
		  list = create_words(values, 6);
		  List_bubble_sort(list, (List_compare)strcmp);
	 }
	 struct timespec after;
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("bubble_sort time: %ld", (after.tv_nsec - before.tv_nsec) / N);
	 return NULL;
}


void *time_merge_sort()
{
	 int N = 10000;
	 int i = 0;
	 List *list = NULL;
	 char *values[] = {"blah", "blee", "bloo", "walking", "language", "1234", "see", "13987asdf", "hey yoo", "wub wub wub"};
	 
	 struct timespec before;
	 clock_gettime(CLOCK_REALTIME, &before);
	 for (i = 0; i < N; i++) {
		  list = create_words(values, 6);
		  List_merge_sort(list, (List_compare)strcmp);
	 }
	 
	 struct timespec after;
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("merge_sort time: %ld", (after.tv_nsec - before.tv_nsec) / N);
	 
	 return NULL;
}

char *time_insert_sorted()
{
	 int N = 10000;
	 int i = 0;
	 List *list = NULL;
	 	 char *values[] = {"blah", "blee", "bloo", "walking", "language", "1234", "see", "13987asdf", "hey yoo", "wub wub wub"};
	 
	 struct timespec before;
	 clock_gettime(CLOCK_REALTIME, &before);
	 for (i = 0; i < N; i++) {
		  list = List_create();
		  List_insert_sorted(list, values, (List_compare)strcmp);
	 }
	 
	 struct timespec after;
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("Insert in sorted time: %ld", (after.tv_nsec - before.tv_nsec) / N);	 
	 return NULL;
}

void *all_tests()
{
	 mu_suite_start();

	 mu_run_test(time_bubble_sort);
	 mu_run_test(time_merge_sort);
	 mu_run_test(time_insert_sorted);
	 return NULL;
}


RUN_TESTS(all_tests);
