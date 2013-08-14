#include "minunit.h"
#include <lcthw/darray.h>
#include <time.h>


static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "DArray_create failed.");
    mu_assert(array->contents != NULL, "contents are wrong in darray.");
    mu_assert(array->end == 0, "end isn't at the right spot.");
    mu_assert(array->element_size == sizeof(int), "element size is wrong.");
    mu_assert(array->max == 100, "wrong max length size on initial.");

    return NULL;
}

char *test_destroy()
{
    DArray_destroy(array);

    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "failed to make a new element");

    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "failed to make a new element");

    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);

    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1,"Wrong first value.");
    mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");

    return NULL;
}

char *test_remove()
{
    int *val_check = DArray_remove(array, 0);
    mu_assert(val_check != NULL, "Should not get NULL.");
    mu_assert(*val_check == *val1, "Should get the first value.");
    mu_assert(DArray_get(array, 0) ==  NULL, "Should be gone.");
    DArray_free(val_check);

    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "Should not get NULL.");
    mu_assert(*val_check == *val2, "Should get the first value.");
    mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
    DArray_free(val_check);

    return NULL;
     
}

char *test_expand_contract()
{
    int old_max = array->max;
    DArray_expand(array);
    mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand.");

    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand rate at least");
     
    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand rate at least.");

    return NULL;
}


char *test_push_pop()
{
    int i = 0;
    for(i = 0; i < 1000; i++) {
        int *val = DArray_new(array);
        *val = i * 333;
        DArray_push(array, val);
    }

    mu_assert(array->max == 1201, "Wrong max size.");

    for(i = 999; i >= 0; i--) {
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't get a NULL.");
        mu_assert(*val == i * 333, "Wrong value.");
        DArray_free(val);
    }

    return NULL;
}

char *test_iterate()
{
    int i = 0;
    for(i = 0; i < 10; i++) {
        int *val = DArray_new(array);
        *val = i + 1;
        DArray_set(array, i, val);
    }

    mu_assert(array->max == 302, "Wrong max size.");

    for(i = 0; i < array->end; i++) {
        int *val = DArray_get(array, i);
        mu_assert(*val == i + 1, "Wrong value while iterating");
    }
    
    return NULL;
}

char *test_expand_time()
{
    struct timespec before;
    struct timespec after;
	const long int N = 5000;
	const int size = 6000;
	int i = 0;
    array = DArray_create(sizeof(int), 100);
    clock_gettime(CLOCK_REALTIME, &before);
	for(i = 0; i < N; i++) {
		while (array->max < size) {
			DArray_expand(array);
		}
		if(i == 1) 	printf("It is currently at size: %d\n", array->max);
		DArray_contract(array);
	}
    clock_gettime(CLOCK_REALTIME, &after);

	printf("Addition expand took: %ld.%09ld on average.\n",(after.tv_sec - before.tv_sec) / N , (after.tv_nsec - before.tv_nsec) / N);
	printf("It is currently at size: %d\n", array->max);
	
	clock_gettime(CLOCK_REALTIME, &before);
	for(i = 0; i < N; i++) {
		while(array->max < size) {
			DArray_mul_expand(array);
		}
		if(i == 1) 	printf("It is currently at size: %d\n", array->max);
		DArray_contract(array);
	}
	clock_gettime(CLOCK_REALTIME, &after);

	printf("Multiply expand took: %ld.%09ld on average.\n", (after.tv_sec - before.tv_sec) / N, (after.tv_nsec - before.tv_nsec) / N);
	
    return NULL;
}

char *all_tests(){
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_iterate);
    mu_run_test(test_destroy);

    mu_run_test(test_expand_time);
     
    return NULL;
}

RUN_TESTS(all_tests);
