#ifndef lcthw_stats_h
#define lcthw_stats_h

#include <math.h>

typedef struct Stats {
	 double sum;
	 double sumsq;
	 unsigned long n;
	 double min;
	 double max;
} Stats;

Stats *Stats_recreate(double sum, double sumsq, unsigned long n, double min, double max);

Stats *Stats_create();

#define Stats_mean(S) (S)->sum / (S)->n

#define Stats_stddev(S) sqrt( ((S)->sumsq - ((S)->sum * (S)->sum / (S)->n)) / ((S)->n -1))

void Stats_sample(Stats *st, double s);

void Stats_dump(Stats *st);

void Stats_destroy(Stats *st);

#endif
