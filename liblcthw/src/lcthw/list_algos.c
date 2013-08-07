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

List *List_merge_sort(List *list, List_compare cmp)
{
	 if(list->count <= 1) {
		  return list;
	 } else if(list->count > 1) {
		  List *left = List_create();
		  List *right = List_create();
		  int split = list->count / 2;
		  int i = 0;
		  ListNode *current = NULL;
		  for(i = 0, current = list->first;
			  i < list->count;
			  i++, current = current->next) {
			   if(i < split) List_push(left, current->value);
			   if(i >= split) List_push(right, current->value);
		  }
		  // left = merge_sort(left);
		  //right = merge_sort(right);
	 }


	 
	 List *ans = List_create();
	 List_unshift(ans, "xjvef");
	 List_unshift(ans, "abcd");	 
	 List_unshift(ans, "XXXX");
	 List_unshift(ans, "NDSS");
	 List_unshift(ans, "1234");
	 return ans;
error:
	 return NULL;
}

//List *merge(List *left, List *right)
//{
/* function merge(left, right) */
/*     // receive the left and right sublist as arguments. */
/*     // 'result' variable for the merged result of two sublists. */
/*     var list result */
/*     // assign the element of the sublists to 'result' variable until there is no element to merge.  */
/*     while length(left) > 0 or length(right) > 0 */
/*         if length(left) > 0 and length(right) > 0 */
/*            // compare the first two element, which is the small one, of each two sublists. */
/*             if first(left) <= first(right) */
/*                 // the small element is copied to 'result' variable. */
/*                 // delete the copied one(a first element) in the sublist. */
/*                 append first(left) to result */
/*                 left = rest(left) */
/*             else */
/*                 // same operation as the above(in the right sublist). */
/*                 append first(right) to result */
/*                 right = rest(right) */
/*         else if length(left) > 0 */
/*             // copy all of remaining elements from the sublist to 'result' variable, when there is no more element to compare with. */
/*             append first(left) to result */
/*             left = rest(left) */
/*         else if length(right) > 0 */
/*             // same operation as the above(in the right sublist). */
/*             append first(right) to result */
/*             right = rest(right) */
/*     end while */
/*     // return the result of the merged sublists(or completed one, finally). */
/*     // the length of the left and right sublists will grow bigger and bigger, after the next call of this function. */
	 /*     return result */
// }
