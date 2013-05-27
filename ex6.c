#include <stdio.h>

int main(int argc, char *argv[])
{
  int distance = 100;
  float power = 2.345f;
  double super_power = 56789.4532;
  char initial = 'A';
  char first_name[] = "Zed";
  char last_name[] = "Shaw";
  char nothing[] = "";
  int hex = 13;
  int oct = 14;
  double dubs = 1.797693134862315e+30;
  
  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of power.\n", power);
  printf("You have %f awesome super powers.\n", super_power);
  printf("I have an initial %c.\n", initial);
  printf("I have a first name %s.\n", first_name);
  printf("I have a last name %s.\n", last_name);
  printf("My whole name is %s %c. %s.\n",
		 first_name, initial, last_name);
  printf("%s", nothing);
  printf("%d in Hex: %X\n", hex, hex);
  printf("%d in Octal: %o\n", oct, oct);
  printf("Double: %lf\n", dubs);
  
  return 0;
}
