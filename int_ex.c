#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

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

	 intmax_t max = INTMAX_MAX;
	 printf("The size of intmax is %d\n", sizeof(max));
	 printf("Value of INTMAX_MAX is %lld\n", max);
	 int64_t alt_max = INT64_MAX;
	 printf("It is equivalant to int64's max: %lld\n", alt_max);

	 int_least16_t least = 10;
	 printf("An integer with at least 16 bits has size: %d\n", sizeof(least));
	 printf("It has value: %d\n", least);
	 
	 int_fast16_t fast = 100;
	 printf("The fastest integer with at least 16 bits has size: %d\n", sizeof(fast));
	 printf("Has value: %d\n", fast);

	 printf("Notice that the fastest integer has 32 bits... exactly corresponding to the 32 bit architecture of the computer!\n");

	 intptr_t intptr = 10;
	 printf("intptr takes up this many bytes: %d\n", sizeof(intptr));
     printf("It has value %d\n", intptr);

	 ptrdiff_t diff = 5;

	 printf("ptrdiff can take up this many bytes: %d\n", sizeof(diff));
	 printf("The ptrdiff type has value: %td\n", diff);
	 printf("The maximum difference between two pointers is %d\n", PTRDIFF_MAX);

	 size_t size = 100000;
	 printf("The size_t type is size: %d\n", sizeof(size));
	 printf("The value for size is: %zu\n", size);
	 printf("The maximum value for size_t is: %zu\n", SIZE_MAX);

	 i = 3;
	 j = 5;
	 printf("This is i %d and this is j %d\n", i, j);
	 printf("This is bitwise or of both: %d\n", (i | j));
	 printf("This is a bitwise xor of both: %d\n", (i ^ j));
	 printf("This is a 2's complement of i: %d\n", (~i));
	 printf("Two's Complement is  -(abs(x)+1)\n");
	 printf("Two's complement of 0 is: %d\n", ~0);

	 printf("Shift left once for j: %d\n", (j << 1));
	 printf("Shift right once for j: %d\n", (j >> 1));

	 
	 return 0;
}
