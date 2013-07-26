#include <stdint.h>
#include <stdio.h>

typedef enum {
	 SPRING, SUMMER, FALL, WINTER
} seasons;

int main(int argc, char *argv[])
{
	 int i = 1;
	 printf("This is an int: %d\n", i);

	 double d = 1.1;
	 printf("This is a double: %lf\n", d);

	 float f = 1.2;
	 printf("This is a float: %f\n", f);

	 char c = 'c';
	 printf("This is a char: %c\n", c);

	 printf("This is the size of a char: %d\n", sizeof(c));
	 printf("This is the size of an int: %d\n", sizeof(i));

	 seasons season = SPRING;
	 printf("This is C's representation of an enum SPRING: %d\n", season);;

	 season++;
	 printf("We can increment it too and get %d!\n", season);

	 season = -20;
	 printf("What do we see when it's negative? %d\n", season);

	 unsigned short j = 1;
	 printf("This short int is unsigned: %d\n", j);

	 j--;
	 j--;
	 printf("Now it's negative one: %d\n", j);

	 long l = 0;
	 printf("This is a long: %ld\n", l);

	 int8_t int8 = 1;
	 printf("This is an int8_t: %d\n", int8);

	 printf("The maximum value achievable is %d for signed\n", INT8_MAX);
	 printf("The minimum value achievable is %d for unsigned\n", INT8_MIN);

	 printf("The maximum value for unsigned is: %d\n", UINT8_MAX);

	 printf("The size of int8_t in bytes is %d\n", sizeof(int8_t));




	 return 0;
}
