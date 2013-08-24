#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
	 return strcmp(*a, *b);
}

DArray *create_words()
{
	 DArray *result = DArray_create(0, 5);
	 char *words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"};
	 int i = 0;

	 for(i = 0; i < 5; i++) {
		  DArray_push(result, words[i]);
	 }

	 return result;
}

int is_sorted(DArray *array)
{
	 int i = 0;

	 for(i = 0; i < DArray_count(array) - 1; i++) {
		  if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
			   return 0;
		  }
	 }

	 return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
	 DArray *words = create_words();
	 mu_assert(!is_sorted(words), "Words should start not stored.");

	 debug("--- Testing %s sorting algorithm", name);
	 int rc = func(words, (DArray_compare)testcmp);
	 mu_assert(rc == 0, "sort failed");
	 mu_assert(is_sorted(words), "didn't sort it");

	 DArray_destroy(words);
	 return NULL;
}


char *test_qsort()
{
	 return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
	 return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
	 return run_sort_test(DArray_mergesort, "mergesort");
}

char *test_my_qsort()
{
	 return run_sort_test(DArray_my_qsort, "my_qsort");
}

char *test_my_heapsort()
{
	 return run_sort_test(DArray_my_heapsort, "my_heapsort");
}

char *test_my_mergesort()
{
	 return run_sort_test(DArray_my_mergesort, "my_mergesort");
}

char *test_sort_add()
{
	 DArray *words = create_words();
	 mu_assert(!is_sorted(words), "Words should start not stored.");

	 debug("--- Testing sort_add");
	 int rc = DArray_sort_add(words, "moo moo farm", (DArray_compare)testcmp);
	 mu_assert(rc == 0, "Failed to sort_add");
	 mu_assert(is_sorted(words), "Array should be sorted after");
	 return NULL;
}

char *test_find()
{
	 DArray *words = create_words();
	 debug("--- Testing DArray_find");
	 int rc = DArray_sort_add(words, "moo moo farm", (DArray_compare)testcmp);
	 mu_assert(rc == 0, "Failed to sort_add");
	 mu_assert(is_sorted(words), "Array should be sorted after");

	 void *el = DArray_find(words, "moo moo farm", (DArray_compare)testcmp);
	 mu_assert(el != NULL, "Failed to find element");

	 el = DArray_find(words, "blah blee bloo blee boo blah", (DArray_compare)testcmp);
	 mu_assert(el == NULL, "Should not find elements that don't exist.");

	 return NULL;
}

char *all_tests() {
	 mu_suite_start();


	 mu_run_test(test_qsort);
	 mu_run_test(test_heapsort);
	 mu_run_test(test_mergesort);

	 mu_run_test(test_my_qsort);
	 mu_run_test(test_my_heapsort);
	 mu_run_test(test_my_mergesort);

	 mu_run_test(test_sort_add);
	 mu_run_test(test_find);

	 return NULL;
}

RUN_TESTS(all_tests);
