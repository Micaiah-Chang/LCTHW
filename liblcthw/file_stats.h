#ifndef _file_stats_h
#define _file_stats_h

int read_file(FILE *f_no, Stats *st);

char *read_line(FILE *stream, char *cur_line, unsigned int n);

int read_numbers(char* cur_line, Stats *st, unsigned int n);

void sample_number(double num, Stats *st);


#endif
