#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcthw/stats.h>
#include <lcthw/bstrlib.h>
#include "file_stats.h"
#include <lcthw/dbg.h>

#define MAX_LINE 80
#define DELIMITER ' '

/* TODO: Defensive programming checks */
/* Refactor with bstrlib */
/* Generalize program to work with header files */
/* Loudly warn when file is not completely read */
/* Dynamically resize the read buffer */
/* Free all memory leaks, check with VALGRIND */
/* Check with code complete on argument input order convention */

int read_file(FILE *f_no, Stats *st) {
	 char *cur_line = calloc(MAX_LINE, sizeof(char));
	 char *return_check;

	 while(cur_line[0] != EOF) {
		  return_check = read_line(f_no, cur_line, MAX_LINE);
		  if(return_check != NULL && *cur_line != EOF ) {
			   read_numbers(cur_line, st, MAX_LINE);
		  } else {
			   break;
		  }
	 }

	 Stats_dump(st);

	 free(cur_line);
	 return 0;
}

char* read_line(FILE *stream, char *cur_line, unsigned int n) {
	 cur_line = fgets(cur_line, (int)n, stream);
	 return cur_line;
}

int read_numbers(char *cur_line, Stats *st, unsigned int n) {
	 char cur_number[MAX_LINE] = {'\0'};
	 int cur_index = 0;
	 unsigned int i = 0;
	 for(i = 0; i < n; i++) {
		  if(cur_line[i] != DELIMITER && cur_line[i] != '\n') {
			   cur_number[cur_index] = cur_line[i];
			   cur_index++;
		  } else {
			   cur_number[cur_index] = '\0';
			   // printf("%f\n",atof(cur_number));
			   Stats_sample(st, atof(cur_number));
			   cur_index = 0;
		  }
	 }

	 int rc = 1;
	 return rc;

error:
	 rc = 0;
	 return rc;
}

void sample_number(double num, Stats *st) {
	 Stats_sample(st, num);
}



int main(int argc, char *argv[])
{
	 Stats *st = Stats_create();

	 FILE *f_no = fopen("numbers.txt", "r");
	 int rc = read_file(f_no, st);

	 if (rc != 0) {
		  printf("Error in closing!");
		  return -1;
	 }

	 Stats_destroy(st);

	 fclose(f_no);
	 return 0;
}
