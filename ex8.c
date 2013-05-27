#include <stdio.h>

int main(int argc, char *argv[])
{
  int areas[] = {10, 12, 13, 14, 20};
  char name[] = "Zed";
  char full_name[] = {
	'Z','e', 'd',
	' ', 'A', '.', ' ',
	'S', 'h', 'a', 'w', '\0'
  };

  // WARNING: On some systems you may have to change the
  // %ld in this code to a %u since it will use unsigned ints
  printf("The size of an int: %u\n", sizeof(int));
  printf("The size of areas (int[]): %u\n",
		 sizeof(areas));
  printf("The number of ints in areas: %u\n",
		 sizeof(areas) / sizeof(int));
  printf("The first area is %d, the 2nd %d.\n",
		 areas[0], areas[1]);
  
  printf("The size of a char: %u\n", sizeof(char));
  printf("The size of the name(char[]): %u\n",
		 sizeof(name));
  printf("The number of chars: %u\n",
		 sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %u\n",
		 sizeof(full_name));
  printf("The number of chars: %u\n",
		 sizeof(full_name) / sizeof(char));

  printf("name=\"%s\" and full_name=\"%s\"\n",
		 name, full_name);

  return 0;
}
