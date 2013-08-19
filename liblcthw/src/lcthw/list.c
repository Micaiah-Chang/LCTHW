#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>


List *List_create()
{
	 return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
	 assert(list != NULL && "Cannot destroy a NULL list.");
	 LIST_FOREACH(list, first, next, cur) {
		  if(cur->prev) {
			   free(cur->prev);
		  }
	 }

	 free(list->last);
	 free(list);
}

void List_clear(List *list)
{
	 assert(list != NULL && "Cannot clear a NULL object.");
	 LIST_FOREACH(list, first, next, cur) {
		  free(cur->value);
	 }
}


void List_clear_destroy(List *list)
{
	 assert(list != NULL &&
			"Cannot clear and destroy object if it is NULL");

	 LIST_FOREACH(list, first, next, cur) {
		  free(cur->value);

		  if(cur->prev) {
			   free(cur->prev);
		  }
	 }

	 free(list->last);
	 free(list);
}

void List_push(List *list, void *value)
{
	 assert(list != NULL && "list is NULL! Cannot push.");
	 assert(value != NULL && "Value at node cannot be NULL!");

	 ListNode *node = calloc(1, sizeof(ListNode));
	 check_mem(node);

	 node->value = value;

	 if(list->last == NULL) {
		  list->first = node;
		  list->last = node;
	 } else {
		  list->last->next = node;
		  node->prev = list->last;
		  list->last = node;
	 }

	 list->count++;

	 // fallthrough

error:
	 assert(list->count >= 0 && "List cannot be negative length!");
	 assert(list->count > 0 ? list->first != NULL : 1 && "Cannot have nonzero length list with NULL first pointer");
	 return;
}

void *List_pop(List *list)
{
	 assert(list != NULL && "list is NULL! Cannot pop.");

	 ListNode *node = list->last;
	 return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
	 assert(list != NULL && "list is NULL! Cannot unshift");
	 assert(value != NULL && "Value at node cannot be NULL!");

	 ListNode *node = calloc(1, sizeof(ListNode));
	 check_mem(node);

	 node->value = value;

	 if(list->first == NULL) {
		  list->first = node;
		  list->last = node;
	 } else {
		  node->next = list->first;
		  list->first->prev = node;
		  list->first = node;
	 }

	 list->count++;


error:
	 assert(list->count >= 0 && "List cannot be negative length!");
	 assert(list->count > 0 ? list->first != NULL : 1 && "Cannot have nonzero length list with NULL first pointer");

	 return;
}

void *List_shift(List *list)
{
	 assert(list != NULL && "list is NULL! Cannot shift");

	 ListNode *node = list->first;
	 return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	 assert(list != NULL && "list is NULL! Cannot remove!");
	 assert(node != NULL && "Must have a node to remove that is not NULL.");

	 void *result = NULL;

	 check(list->first && list->last, "List is empty");
	 check(node, "node can't be NULL");

	 if(node == list->first && node == list->last) {
		  list->first = NULL;
		  list->last = NULL;
	 } else if(node == list->first) {
		  list->first = node->next;
		  check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
		  list->first->prev = NULL;
	 } else if(node == list->last) {
		  list->last = node->prev;
		  check(list->last != NULL, "Invalid list, somehow got a last that is NULL.");
		  list->last->next = NULL;
	 } else {
		  ListNode *after = node->next;
		  ListNode *before = node->prev;
		  after->prev = before;
		  before->next = after;
		  // Note this last case assumes that the node is
		  // 1) In the Center of the list
		  // 2) That it doesn't also have NULL next or prev
		  // pointers
	 }

	 list->count--;

	 result = node->value;
	 free(node);

	 // fallthrough

error:
	 assert(list->count >= 0 && "List cannot be negative length!");
	 assert(list->count > 0 ? list->first != NULL : 1 && "Cannot have nonzero length list with NULL first pointer");

	 return result;
}

void List_swap(ListNode *node1, ListNode *node2)
{
	 assert(node1 != NULL && "Cannot have NULL nodes");
	 assert(node2 != NULL && "Cannot have NULL nodes");

	 void *tmp = node1->value;

	 node1->value = node2->value;
	 node2->value = tmp;


	 return;
}

void List_add_after(List *list, ListNode *refnode, void *value)
{
	 assert(refnode != NULL && "Reference node is NULL!");

	 if(refnode == list->last) {
		  List_push(list, value);
	 } else {
		  ListNode *node = calloc(1, sizeof(ListNode));
		  check_mem(node);

		  node->value = value;

		  ListNode *after = refnode->next;
		  after->prev = node;
		  refnode->next = node;

		  node->next = after;
		  node->prev = refnode;

		  list->count++;
	 }

error:
	 assert(list->count >= 0 && "List cannot be negative length!");
	 assert(list->count > 0 ? list->first != NULL : 1 && "Cannot have nonzero length list with NULL first pointer");

	 return;

}


void List_add_before(List *list, ListNode *refnode, void *value)
{
	 assert(refnode != NULL && "Reference node is NULL!");

	 if(refnode == list->first) {
		  List_unshift(list, value);
	 } else {
		  ListNode *node = calloc(1, sizeof(ListNode));
		  check_mem(node);

		  node->value = value;

		  ListNode *before = refnode->prev;
		  before->next = node;
		  refnode->prev = node;

		  node->next = refnode;
		  node->prev = before;

		  list->count++;
	 }

error:
	 assert(list->count >= 0 && "List cannot be negative length!");
	 assert(list->count > 0 ? list->first != NULL : 1 && "Cannot have nonzero length list with NULL first pointer");

	 return;

}

void List_join(List *list1, List *list2)
{
	 LIST_FOREACH(list2, first, next, cur) {
		  cur = cur;
		  void *value = List_shift(list2);
		  List_push(list1, value);
	 }

	 List_clear_destroy(list2);

}
