#include <lcthw/list.h>

typedef List Stack;

#define Stack_create() List_create()
#define Stack_destroy(stack) List_clear(stack)
#define Stack_push(stack, val) List_push(stack, val)
#define Stack_pop(stack) List_pop(stack)
#define Stack_peek(stack) List_last(stack)
#define Stack_count(stack) List_count(stack)
#define STACK_FOREACH(stack, cur) LIST_FOREACH(stack, last, prev, cur)
