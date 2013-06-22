#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

struct Stack {
	 int *items;
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

void *push(struct Stack *stack, int item)
{
	 int *new_item = malloc(sizeof(int));
	 *new_item = item;
	 int size = sizeof(*(stack->items));
	 printf("%d \n", size);

	 free(new_item);
}

int pop(struct Stack *stack)
{
	 
}

int top(struct Stack *stack)
{
	 
}

void destroy_stack(struct Stack *stack)
{
	 if(stack) {
		  if(stack->items) {
			   free(stack->items);
		  }
		  free(stack);
	 }
}

int main(int argc, char *argv[])
{
	 int i = 0;
	 int count = argc - 1;
	 char **inputs = argv + 1;
	 
	 struct Stack *stck = malloc(sizeof(struct Stack));
	 
	 if(argc < 2) die("Please enter an array of numbers");

	 int *numbers = malloc(count * sizeof(int));
	 if(!numbers) die("Memory error.");

	 for(i = 0; i < count; i++) {
		  numbers[i] = atoi(inputs[i]);
		  push(stck, numbers[i]);
	 }

	 free(numbers);
	 destroy_stack(stck);
}
