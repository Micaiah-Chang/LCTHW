#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>
#include <lcthw/dbg.h>


typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

// Takes a list and inserts something at a given value using List_compare
int List_insert_sorted(List *list, void *value, List_compare cmp);

#ifdef NDEBUG
#define sorted(M, cmp)
#else
#define sorted(M, cmp) LIST_FOREACH(list, first, next, cur) { \
		  if(cur->next && cmp(cur->value, cur->next->value) > 0) { \
			   debug("%s %s", (char *) cur->value, (char *)cur->next->value); \
			   sentinel("List not sorted."); \
		  } \
}
#endif


#endif
