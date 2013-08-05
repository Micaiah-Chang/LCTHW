#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	 int i = 0;
	 int *thing = NULL;
	 
	 while (i < 100) {
		  usleep(3000);
		  if(i > 10) {
			   thing[i] = 1;
		  }
		  i++;
	 }
	 
	 return 0;
}
