// Include the standard input / output header files
#include <stdio.h>
// Include the assertion header file. Use this to get assert()
#include <assert.h>
// Include the standard library. Use this to get malloc and free
#include <stdlib.h>
// Include the string header file. Helps us handle strings
#include <string.h>

// Declare a new structure named Person which includes...
struct Person {
	 // ...a string named "name"
	 char *name;
	 // ... an integer named "age"
	 int age;
	 // ... an integer named "height"
	 int height;
	 // ... and finally an integer named "height"
	 int weight;
// And these four variables are the only ones inside Person
};

// Create a function which returns Person that accepts the listed arguments
struct Person *Person_create(char *name, int age, int height, int weight)
{
	 // Create a pointer of type Person, with the requisite size
	 struct Person *who = malloc(sizeof(struct Person));
	 //Did we get the memory? If not ABORT
	 assert(who != NULL);

	 // set the person's name to a pointer to a newly duplicated string
	 who->name = strdup(name);
	 // set the value of age inside person to the argument age
	 who->age = age;
	 // set the value of height inside person to the argument height
	 who->height = height;
	 // set the value of weight inside person to the argument weight
	 who->weight = weight;

	 // return the pointer of the person 
	 return who;
}

// Create a function named Person_destroy which returns nothing
// and recieves a pointer to a Person struct
void Person_destroy(struct Person *who)
{
	 // Check to see if the pointer is valid.
	 assert(who != NULL);
	 // Free memory associated with the duplicated string in name
	 free(who->name);
	 // Free the rest of the memory
	 free(who);
}

//A function named Person_print that returns nothing
void Person_print(struct Person *who)
{
	 // Prints out all values of person with
	 // everything other than the name indented
	 printf("Name: %s\n", who->name);
	 printf("\tAge: %d\n", who->age);
	 printf("\tHeight: %d\n", who->height);
	 printf("\tWeight: %d\n", who->weight);
}

// Main function ahoy
int main(int argc, char *argv[])
{
	 // make two people structures
	 struct Person *joe = Person_create(
		  "Joe Alex", 32, 64, 140);

	 struct Person *frank = Person_create(
		  "Frank Blank", 20, 72, 180);

	 // print them out where they are in memory
	 printf("Joe is at memory location %p:\n", joe);
	 Person_print(joe);

	 printf("Frank is at memory location %p:\n", frank);
	 Person_print(frank);

	 // make everyone age 20 years and print them again
	 joe->age += 20;
	 joe->height -= 2;
	 joe->weight += 40;
	 Person_print(joe);

	 frank->age += 20;
	 frank->weight += 20;
	 Person_print(frank);

	 // destroy them both so we clean up
	 Person_destroy(joe);
	 Person_destroy(frank);

	 return 0;
}
