#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct List {
	 struct Node *head;
};

struct Node {
	 char *item;
	 struct Node *next;
};

void die(char *message)
{
	 if(errno) {
		  perror(message);
	 } else {
		  printf("%s\n", message);
	 }

	 exit(1);
}

struct List *stack_init()
{
	 struct List *lst = malloc(sizeof(struct List));
	 assert(lst != NULL);
	 
	 lst->head = NULL; 

	 return lst;
}

int stack_is_empty(struct List *lst)
{
	 if(!lst->head) {
		  return 1;
	 } else {
		  return 0;
	 }
}

void stack_push(struct List *lst, char *item)
{
	 struct Node *node = malloc(sizeof(struct Node));

	 node->item = strdup(item);
	 node->next = lst->head;

	 lst->head = node;
}

struct Node *stack_pop(struct List *lst)
{
	 struct Node *node = lst->head;
	 lst->head = lst->head->next;
	 
	 return node;
}

void stack_peek(struct List *lst)
{
	 printf("The top of the stack is: %s\n", lst->head->item);
}

void destroy_stack(struct List *lst)
{
	 if(lst) {
	 /* WARNING: BELOW NEEDS TO BE CHANGED TO WHILE */
		  if(lst->head) {
			   struct Node *curr_node = lst->head;
			   struct Node *temp = NULL;
					while(curr_node) {
						 temp = curr_node->next;
						 free(curr_node->item);
						 free(curr_node);
						 curr_node = temp;
					}
		  }
		  free(lst);
	 }
}

void print_stack(struct List *lst)
{
	 struct Node *cur_node = lst->head;
	 while(cur_node) {
		  printf("%s\t", cur_node->item);
		  cur_node = cur_node->next;
	 }
	 printf("\n");
}

int main(int argc, char *argv[])
{
	 int i = 0;
	 int count = argc - 1;
	 char **inputs = argv + 1;

	 struct List *lst = stack_init();

	 if(stack_is_empty(lst)) {
		  printf("Stack is empty.\n");
	 } else {
		  printf("Stack is not empty.\n");
	 }
	 
	 for(i = 0; i < count; i++)	 stack_push(lst, inputs[i]);
	 print_stack(lst);

	 stack_peek(lst);
	 
	 if(stack_is_empty(lst)) {
		  printf("Stack is empty.\n");
	 } else {
		  printf("Stack is not empty.\n");
	 }

	 struct Node *node = stack_pop(lst);
	 printf("Popped item: %s\n", node->item);
	 free(node->item);
	 free(node);
	 print_stack(lst);
	 
	 destroy_stack(lst);
}
