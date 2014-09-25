#include "minunit.h"
#include <lcthw/ringbuffer.h>

int SIZE_OF_BUFFER = 7;
char test1[5] = "test1";
char test2[5] = "test2";

static RingBuffer *buffer = NULL;

char *test_create()
{
	 buffer = RingBuffer_create(SIZE_OF_BUFFER);
	 mu_assert(buffer != NULL, "Failed to create RingBuffer.");

	 int avail_data = RingBuffer_available_data(buffer);
	 mu_assert(avail_data == 0, "RingBuffer must be devoid of data after creation.");
	 int avail_space = RingBuffer_available_space(buffer);
	 mu_assert(avail_space == SIZE_OF_BUFFER, "RingBuffer must be completely free after creation");

	 return NULL;
}

char *test_read_write()
{
	 return NULL;
}

char *test_destroy()
{
	 return NULL;
}

char *all_tests() {
	 mu_suite_start();

	 mu_run_test(test_create);
	 mu_run_test(test_read_write);
	 mu_run_test(test_destroy);

	 return NULL;
}

RUN_TESTS(all_tests);
