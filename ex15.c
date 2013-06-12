#include <stdio.h>

void index_print(int ages[], char *names[], int count)
{
	 // first way of using indexing
	 int i = 0;
	 for(i = 0; i < count; i++) {
		  // printf("Count: %d\n", count);
		  printf("%s has %d years alive.\n",
				 names[i], ages[i]);
	 }	 
	 printf("---\n");
}

void pointer_print(int *cur_age, char **cur_name, int count)
{
	 int i = 0;
	 // second way using pointers
	 for(i = 0; i < count; i++) {
		  printf("%s is %d years old.\n",
				 *(cur_name+i),*(cur_age+i));
	 }

	 printf("---\n");	 
}

void ptr_as_array_print(int *cur_age, char **cur_name, int count)
{
	 int i = 0;
	 	 // third way, pointers are just arrays
	 for(i = 0; i < count; i++) {
		  printf("%s is %d years old again.\n",
				 cur_name[i], cur_age[i]);
	 }

	 printf("---\n");
}

void ptr_arith_print(int ages[], char *names[],
					 int *cur_age, char **cur_name,
					 int count)
{
	 	 // fourth way with pointers in a stupid complex way
	 for(cur_name = (names + count - 1), cur_age = (ages + count - 1);
		 (cur_age - ages) >= 0;
		 cur_name--, cur_age--)
	 {
		  printf("%s lived %d years so far.\n",
				 *cur_name, *cur_age);
	 }
}

int main(int argc, char *argv[])
{
	 // create two arrays we care about
	 int ages[] = {23, 43, 12, 89, 2}; 
	 char *names[] = {
		  "Alan", "Frank",
		  "Mary", "John", "Lisa"
	 };

	 // safely get the size of ages
	 int count = sizeof(ages) / sizeof(int);
	 int i = 0;

	 index_print(ages, names, count);

	 // setup the pointers to the start of the arrays
	 int *cur_age = ages;
	 char **cur_name = names;
	 pointer_print(cur_age, cur_name, count);
	 ptr_as_array_print(cur_age, cur_name, count);
	 ptr_arith_print(ages, names, cur_age, cur_name, count);
	 
	 printf("Addresses: \n");
	 for(i = 0; i < count; i++){
		  printf("Ages[%d]: %p\t", count, &ages[i]);
		  printf("Name[%d]: %p\n", count, &names[i]);
	 }
	 
	 return 0;
}
