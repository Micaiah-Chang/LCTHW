#include <assert.h>
#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int List_bubble_sort(List *list, List_compare cmp)
{
	 int n = list->count;
	 int temp = 0;
	 int i = 0;
	 while (n != 0) {
		  temp = 0;
		  i = 0;
		  LIST_FOREACH(list, first, next, cur) {
			   i++;
			   if(cur->next == NULL) {
					break;
			   } else if(cmp(cur->value, cur->next->value) > 0) {
					List_swap(cur, cur->next);
					temp = i;
			   }
		  }
		  n = temp;			   
	 }
		  
	 return 0;
error:
	 return -1;
}


List *merge(List *left, List *right, List_compare cmp)
{
	 List *result = List_create();

	 while (List_count(left) > 0 || List_count(right) > 0) {
		  if(List_count(left) > 0 && List_count(right) > 0) {
			   if(cmp(List_first(left), List_first(right)) <= 0 ) {
					List_push(result, List_shift(left));
			   } else {
					List_push(result, List_shift(right));
			   }
			   
		  } else if(left->count > 0) {
			   List_push(result, List_shift(left));
		  } else if(right->count > 0) {
			   List_push(result, List_shift(right));
		  }
	 }

	 check(result->first != NULL && result->last != NULL,
		   "Cannot have empty result!");
	 return result;
error:
	 return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	 if(list->count <= 1) {
		  return list;
	 } 
	 List *left = List_create();
	 List *right = List_create();
	 int split = List_count(list) / 2;
	 
	 ListNode *current = NULL;
	 LIST_FOREACH(list, first, next, cur) {
		  if(split > 0) {
			   List_push(left, cur->value);
		  } else {
			   List_push(right, cur->value);
		  }
		  
		  split--;
	 }

	 List *sort_left = List_merge_sort(left, cmp);
	 List *sort_right = List_merge_sort(right, cmp);

	 if(sort_left != left) List_destroy(left);
	 if(sort_right != right) List_destroy(right);
	 
	 return merge(sort_left, sort_right, cmp);

	 
error:
	 return NULL;
}

