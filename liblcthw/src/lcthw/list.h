#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

/* Creates a node for a doubly linked list, */
/* A node consists of a value and pointers  */
/* to previous and next values.  */
/* Would only be a singly linked list otherwise */


typedef struct ListNode {
	 struct ListNode *next;
	 struct ListNode *prev;
	 void *value;
} ListNode;

/*   Creates a List data structure, with a count */
/* 	 containing the length of the list and */
/* 	 pointers to the first and last nodes */
/* 	 So long as count is not zero both the fist */
/* 	 and last node should be pointing to non-NULL values */

typedef struct List {
	 int count;
	 ListNode *first;
	 ListNode *last;
} List;

// Creates an empty list with length zero.
List *List_create();

// Frees all the memory associated with the list
// data structure
void List_destroy(List *list);

// Frees the memory containing value of all the entries
// associated with each node in the list data structure.
void List_clear(List *list);

// Frees all the memory associated with the values
// on the list and then destroys the list data structure
// itself
void List_clear_destroy(List *list);

// Macro to automatically to return length of list
#define List_count(A) ((A)->count)

// Macro to automatically return the value of the
// first/last element of a list. NULL if the node
// doesn't exist. 
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

// Add / remove from the last node on the list
// Can be thought of as stack operators, with the 
// last node being the "top" of the stack
void List_push(List *list, void *value);
void *List_pop(List *list);

// Add / Remove from the first node on the list
// Can be though of as the stack operators push/pop,
// with the first node being the "top" of the stack.
void List_unshift(List *list, void *value);
void *List_shift(List *list);


// Removes a node in the list corresponding to the pointer
// and returns with a pointer to the value of that node
// Used as a helper function in push, pop, shift and unshift
void *List_remove(List *list, ListNode *node);


// From list Element L, start at the node at L->S (Can be
// list->first or node->next for example)
// Travel in the direction of the next node according to what
// the string M is and name the location of the current node V.

// You both V and _node are needed, _node can be thought of as
// the private variable used for iterating over the list
// V can be thought of as the pointer I want to reach and
// possibly mutate in the course of the loop
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; \
	 ListNode *V = NULL; \
	 for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
