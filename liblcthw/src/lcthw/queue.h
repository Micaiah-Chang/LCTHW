#include <lcthw/list.h>

typedef List Queue;

#define Queue_create() List_create()
#define Queue_destroy(queue) List_clear(queue)
#define Queue_send(queue, val) List_push(queue, val)
#define Queue_recv(queue) List_shift(queue)
#define Queue_peek(queue) List_first(queue)
#define Queue_count(queue) List_count(queue)
#define QUEUE_FOREACH(queue, cur) LIST_FOREACH(queue, first, next, cur)
