#include <stdio.h>

/* Warning: This program is wrong on purpose*/

int main()
{
  int age = 10;
  int height = 71;

  printf("I am %d years old.\n", age);
  printf("I am %d inches tall.\n", height);
  // Fixed for Valgrind now
  return 0;
}