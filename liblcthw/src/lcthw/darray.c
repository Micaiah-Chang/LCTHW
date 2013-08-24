#include <lcthw/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{

	 DArray *array = malloc(sizeof(DArray));
	 check_mem(array);
	 array->max = initial_max;
	 check(array->max > 0, "You must set an initial_max > 0");

	 array->contents = calloc(initial_max, sizeof(void *));
	 check_mem(array->contents);

	 array->end = 0;
	 array->element_size = element_size;
	 array->expand_rate = DEFAULT_EXPAND_RATE;

	 check(array->expand_rate > 0, "Expand rate must be greater than zero.");

	 return array;

error:
	 if(array) free(array);
	 return NULL;
}

void DArray_clear(DArray *array)
{
	 assert(array != NULL && "Input array should not be NULL.");

	 int i = 0;
	 if(array->element_size > 0) {
		  assert(array->max > 0 && "Array max somehow negative.");
		  for (i = 0; i < array->max; i++) {
			   if(array->contents[i] != NULL) {
					free(array->contents[i]);
			   }
		  }
	 }
	 // All elements of array must be freed by the end
}

static inline int DArray_resize(DArray *array, size_t newsize)
{
	 assert(array != NULL && "Input array should not be NULL.");
	 array->max = newsize;
	 check(array->max > 0, "The newsize must be > 0");

	 void *contents = realloc(array->contents, array->max * sizeof(void *));

	 check_mem(contents);

	 array->contents = contents;

	 return 0;
error:
	 return -1;
}

int DArray_expand(DArray *array)
{
	 assert(array != NULL && "Input array should not be NULL.");
	 size_t old_max = array->max;
	 check(DArray_resize(array, array->max + array->expand_rate) == 0,
		   "Failed to expand array to new size: %d",
		   array->max + array->expand_rate);

	 memset(array->contents + old_max, 0, array->expand_rate + 1);
	 return 0;

error:
	 return -1;
}

int DArray_mul_expand(DArray *array)
{
	 assert(array != NULL && "Input array should not be NULL.");
	 size_t old_max = array->max;
	 size_t old_expand = array->expand_rate;
	 array->expand_rate = 2;
	 check(DArray_resize(array, array->max * array->expand_rate) == 0,
		   "Failed to expand array to new size: %d",
		  array->max * array->expand_rate);

	 memset(array->contents + old_max, 0, old_max + 1);

	 array->expand_rate = old_expand;
	 return 0;
error:
	 return -1;
}

int DArray_contract(DArray *array)
{
	 int new_size = array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;

	 check(new_size > 0, "Array size cannot be zero");

	 return DArray_resize(array, new_size + 1);
error:
	 return -1;
}


void DArray_destroy(DArray *array)
{
	 if(array) {
		  if(array->contents) free(array->contents);
		  free(array);
	 }
}

void DArray_clear_destroy(DArray *array)
{
	 DArray_clear(array);
	 DArray_destroy(array);
}

int DArray_push(DArray *array, void *el)
{
	 assert(array != NULL && "Input array should not be NULL.");
	 array->contents[array->end] = el;
	 array->end++;
	 check(array->end > 0, "Array should have a size greater than zero.");

	 if(DArray_end(array) >= DArray_max(array)) {
		  return DArray_expand(array);
	 } else {
		  return 0;
	 }
error:
	 return -1;
}

void *DArray_pop(DArray *array)
{
	 assert(array != NULL && "Input array should not be NULL.");
	 check(array->end - 1 >= 0, "Attempt to pop from an empty array.");

	 void *el = DArray_remove(array, array->end - 1);
	 array->end--;

	 check(array->end >= 0, "Array should be non negative.");

	 if(DArray_end(array) > (int)array->expand_rate && DArray_end(array) % array->expand_rate) {
		  DArray_contract(array);
	 }

	 return el;
error:
	 return NULL;
}
