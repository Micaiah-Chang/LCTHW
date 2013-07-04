#include <stdio.h>
#include "dbg.h"

int call_by_value(int func_val);
void call_by_reference(int *adr_var, int *ptr_var);

void call_by_reference(int *adr_var, int *ptr_var)
{
	 log_info("Inside func, adr_var val: %d ptr_var: %d", *adr_var, *ptr_var);
	 log_info("Inside func, adr_var adr: %p ptr_var: %p", adr_var, ptr_var);
	 // Reassigning here

	 *adr_var = 2;

	 log_info("After reassignment adr_var val: %d ptr_var: %d", *adr_var, *ptr_var);

	 log_info("After reassignment adr_var adr: %p ptr_var: %p", adr_var, ptr_var);

	 
}

int call_by_value(int func_val)
{
	 log_info("func value: %d", func_val);

	 func_val = 1;

	 log_info("After reassigning: %d", func_val);
	 log_info("The address of func_val: %p", &func_val);

	 return func_val;
}

int main(int argc, char *argv[])
{
	 int test_var = 5;
	 int *test_adr = &test_var;
	 int return_var = 0;
	 
	 printf("Test_var is %d\n", test_var);
	 printf("It is located at: %p\n", &test_var);
	 printf("Test_adr's location should be the same: %p\n", test_adr);


	 printf("This is the return var before: %d\n", return_var);
	 return_var = call_by_value(test_var);

	 printf("This is the test_var after: %d\n", test_var);
	 printf("This is the return var after: %d\n", return_var);
	 printf("This is the address of the return var: %p\n", &return_var);
	 //Above should be different than addr inside of var

	 call_by_reference(&test_var, test_adr);

	 return 0;
}
