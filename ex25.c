/** WARNING: This code is fresh and potentially isn't correct yet. **/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100
#define CHAR_MAX 256

char *convert_to_string(int input);

int read_string(char **out_string, int max_buffer)
{
	 *out_string = calloc(1, max_buffer + 1);
	 check_mem(*out_string);

	 char *result = fgets(*out_string, max_buffer, stdin);
	 check(result != NULL, "Input error");

	 return 0;

error:
	 if(*out_string) free(*out_string);
	 *out_string = NULL;
	 return -1;
}

int read_int(int *out_int)
{
	 char *input = NULL;	 
	 int rc = read_string(&input, MAX_DATA);
	 check(rc == 0, "Failed to read number.");

	 *out_int = atoi(input);

	 free(input);
	 return 0;

error:
	 if(input) free(input);
	 return -1;
}

int read_scan(const char *fmt, ...)
{
	 int i = 0;
	 int rc = 0;
	 int *out_int = NULL;
	 char *out_char = NULL;
	 char **out_string = NULL;
	 int max_buffer = 0;

	 va_list argp;
	 va_start(argp, fmt);

	 for(i = 0; fmt[i] != '\0'; i++) {
		  if(fmt[i] == '%') {
			   i++;
			   switch(fmt[i]) {
			   case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

			   case 'd':
					out_int = va_arg(argp, int *);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int");
					break;

			   case 'c':
					out_char = va_arg(argp, char *);
					*out_char = fgetc(stdin);
					break;

			   case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char **);
					rc = read_string(out_string, max_buffer);
					check(rc == 0, "Failed to read string.");
					break;

			   default:
					sentinel("Invalid format.");
			   } 
		  } else {
			   fgetc(stdin);
		  }

		  check(!feof(stdin) && !ferror(stdin), "Input error");
	 }

	 va_end(argp);
	 return 0;

error:
	 va_end(argp);
	 return -1;
}


int print_int(int out_int)
{
	 char *input = NULL;
	 input = convert_to_string(out_int);
	 check(input != NULL, "Failed to convert integer");
	 int i = 0;
	 for(i = 0; i < MAX_DATA + 2; i++) {
		  int rc = putchar(input[i]);
		  check(rc >= 0, "Failed to print integer.");
	 }
	 free(input);
	 return 0;

error:
	 if(input) free(input);
	 return -1;
}

char *convert_to_string(int input)
{
	 char *output = malloc(MAX_DATA + 2);
	 // Needs 2 for sign and null terminator

	 int len = 0;
	 for(; input > 0; len++) {
		  output[len] = (input % 10) + '0';
		  input /= 10;
	 }
	 output[len] = '\0';

	 // Reversing string
	 int i = 0;
	 char temp = 0;
	 for(i = 0; i < len / 2; i++) {
		  temp = output[i];
		  output[i] = output[len-i-1];
		  output[len-i-1] = temp;
	 }
	 check(output != NULL, "String reverse failed.");

	 return output;
error:
	 return NULL;
}

int print_string(const char *fmt, ...)
{
	 int i = 0;
	 int rc = 0;
	 int out_int = 0;

	 char out_char = '\0';
	 char *out_string = NULL;

	 va_list argp;
	 va_start(argp, fmt);
	 for(i = 0; fmt[i] != '\0'; i++) {
		  if(fmt[i] == '%') {
			   i++;
			   switch(fmt[i]) {
			   case '\0':
					sentinel("Invalid format, you ended with %%.");
					break;

			   case 'd':
					out_int = va_arg(argp, int);
					rc = print_int(out_int);
					check(rc == 0, "Failed to read int.");
					break;

			   case 'c':
					out_char = va_arg(argp, int);
					putchar(out_char);
					break;

			   case 's':
					out_string = va_arg(argp, char*);
					int i = 0;
					for(i = 0; i < MAX_DATA; i++) {
						 putchar(out_string[i]);
					}	 
					break;

			   default:
					sentinel("Invalid format.");
			   }
			   
		  } else {
			   putchar(fmt[i]);
		  }

	 }
	 
	 va_end(argp);
	 return 0;

error:
	 return -1;
}


int main(int argc, char *argv[])
{
	 char *first_name = NULL;
	 char initial = ' ';
	 char *last_name = NULL;
	 int age = 0;

	 print_string("What's your first name? ");
	 int rc = read_scan("%s", MAX_DATA, &first_name);
	 check(rc == 0, "Failed first name.");

	 print_string("What's your initial? ");
	 rc = read_scan("%c\n", &initial);
	 check(rc == 0, "Failed inital.");

	 print_string("What's your last name? ");
	 rc = read_scan("%s", MAX_DATA, &last_name);
	 check(rc == 0, "Failed last name.");

	 print_string("How old are you? ");
	 rc = read_scan("%d", &age);

	 print_string("---- RESULTS ----\n");
	 print_string("First Name: %s", first_name);
	 print_string("Initial: '%c'\n", initial);
	 print_string("Last Name: %s", last_name);
	 print_string("Age: %d\n", age);

	 free(first_name);
	 free(last_name);
	 return 0;
error:
	 return -1;
}
