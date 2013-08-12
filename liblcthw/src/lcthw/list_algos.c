#include <assert.h>
#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int List_insert_sorted(List *list, void *value, List_compare  cmp)
{
	 assert(list != NULL && "List cannot be NULL");
	 
	 if(list->first == NULL && list->last == NULL) {
	 	  List_push(list, value);
	 	  return 0;
	 } else if(cmp(List_first(list), value) > 0) {
	 	  List_unshift(list, value);
	 	  return 0;
	 }
	 
	 LIST_FOREACH(list, first, next, cur) {
		  if(cmp(cur->value, value) > 0) {
			   List_add_before(list, cur, value);
			   break;
		  } else if(cur == list->last) {
			   List_push(list, value);
			   break;
		  }
	 }

	 return 0;
}

int List_bubble_sort(List *list, List_compare cmp) 
{
	 assert(list != NULL && "List cannot be NULL.");
	 
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
	 
	 sorted(list, cmp);
	 
	 return 0;
error:
	 return -1;
}


List *merge(List *left, List *right, List_compare cmp)
{ 
	 assert(left != NULL && right != NULL && "Cannot have NULL left or right!");
	 List *result = List_create();
	 ListNode *value = NULL;
	 
	 while (List_count(left) > 0 || List_count(right) > 0) {
		  if(List_count(left) > 0 && List_count(right) > 0) {
			   if(cmp(List_first(left), List_first(right)) <= 0 ) {
					value = List_shift(left);
			   } else {
					value = List_shift(right);
			   }
			   check(value != NULL, "List shifting in mergesort failed.");
			   List_push(result, value);
			   
		  } else if(left->count > 0) {
			   List_push(result, List_shift(left));
		  } else if(right->count > 0) {
			   List_push(result, List_shift(right));
		  }
		  
		  check(List_count(left) >= 0, "Left branch cannot be negative length.");
		  check(List_count(right) >= 0, "Right branch cannot be negative length.");

	 }

	 check(result->first != NULL && result->last != NULL,
		   "Cannot have empty result!");
	 return result;
	 
error:
	 return NULL;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	 assert(list != NULL && "Input is null!");

	 
	 if(list->count <= 1) {
		  return list;
	 } 

	 List *left = List_create();
	 check(left != NULL, "Left list creation failed.");

	 List *right = List_create();
	 check(right != NULL, "Right list creation failed.");

	 int split = List_count(list) / 2;
	 
	 LIST_FOREACH(list, first, next, cur) {
		  if(split > 0) {
			   List_push(left, cur->value);
		  } else {
			   List_push(right, cur->value);
		  }
		  
		  split--;
	 }

	 List *sort_left = List_merge_sort(left, cmp);
	 check(sort_left != NULL, "Left sort failed!");
	 sorted(left, cmp)
	 
	 List *sort_right = List_merge_sort(right, cmp);
	 check(sort_right != NULL, "Right sort failed!");
	 sorted(right, cmp);
	 
	 if(sort_left != left) List_destroy(left);
	 if(sort_right != right) List_destroy(right);
	 
	 return merge(sort_left, sort_right, cmp);

	 
error:
	 return NULL;
}
