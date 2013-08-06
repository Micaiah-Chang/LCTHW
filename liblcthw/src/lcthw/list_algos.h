#include <lcthw/list.h>

typedef int (*List_compare)(char *, char *);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

