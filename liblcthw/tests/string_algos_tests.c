#include "minunit.h"
#include <lcthw/string_algos.h>
#include <lcthw/bstrlib.h>
#include <time.h>

#define TEST_GO 0
#ifdef TEST_GO
#include <lcthw/stats.h>
#include <math.h>
#endif

struct tagbstring IN_STR = bsStatic("I have ALPHA beta ALPHA and oranges ALPHA");
struct tagbstring ALPHA = bsStatic("ALPHA");
const int TEST_TIME = 1;

char *test_find_and_scan()
{
	 StringScanner *scan = StringScanner_create(&IN_STR);
	 mu_assert(scan != NULL, "Failed to make the scanner.");

	 int find_i = String_find(&IN_STR, &ALPHA);
	 mu_assert(find_i > 0, "Failed to find 'ALPHA' in test string.");

	 int scan_i = StringScanner_scan(scan, &ALPHA);
	 mu_assert(scan_i >0, "Failed to find 'ALPH' with scan.");
	 mu_assert(scan_i == find_i, "find and scan don't match");

	 scan_i = StringScanner_scan(scan, &ALPHA);
	 mu_assert(scan_i > find_i, "should find another ALPHA after the first.");

	 scan_i = StringScanner_scan(scan, &ALPHA);
	 mu_assert(scan_i > find_i, "should find another ALPHA after the first.");

	 mu_assert(StringScanner_scan(scan, &ALPHA) == -1, "shouldn't find it");

	 StringScanner_destroy(scan);

	 return NULL;
}

char *test_binstr_performance()
{
	 int i = 0;
	 int found_at = 0;
	 unsigned long find_count = 0;
	 time_t elapsed = 0;
	 time_t warmup_start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = binstr(&IN_STR, 0, &ALPHA);
			   mu_assert(found_at != BSTR_ERR, "Failed to find!");
		  }

		  elapsed = time(NULL) - warmup_start;
	 } while (elapsed <= TEST_TIME);


	 elapsed = 0;
	 time_t start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = binstr(&IN_STR, 0, &ALPHA);
			   mu_assert(found_at != BSTR_ERR, "Failed to find!");
			   find_count++;
		  }

		  elapsed = time(NULL) - start;
	 } while (elapsed <= TEST_TIME);

	 debug("BINSTR COUNT: %lu, END TIME: %d, OPS: %f",
		   find_count, (int)elapsed, (double)find_count / elapsed);
	 return NULL;
}

char *test_find_performance()
{
	 int i = 0;
	 int found_at = 0;
	 unsigned long find_count = 0;
	 time_t elapsed = 0;
	 time_t warmup_start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = String_find(&IN_STR, &ALPHA);
		  }

		  elapsed = time(NULL) - warmup_start;
	 } while (elapsed <= TEST_TIME);

	 elapsed = 0;
	 time_t start = time(NULL);

	 	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = String_find(&IN_STR, &ALPHA);
			   find_count++;
		  }

		  elapsed = time(NULL) - start;
	 } while (elapsed <= TEST_TIME);

	 debug("FIND COUNT: %lu, END TIME: %d, OPS: %f",
		   find_count, (int)elapsed, (double)find_count / elapsed);

	 return NULL;
}

char *test_scan_performance()
{
	 int i = 0;
	 int found_at = 0;
	 unsigned long find_count = 0;
	 time_t elapsed = 0;
	 StringScanner *scan = StringScanner_create(&IN_STR);

	 time_t warmup_start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = 0;
			   do {
					found_at = StringScanner_scan(scan, &ALPHA);
			   } while (found_at != -1);
		  }

		  elapsed = time(NULL) - warmup_start;
	 } while (elapsed <= TEST_TIME);

	 elapsed = 0;
	 time_t start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = 0;
			   do {
					found_at = StringScanner_scan(scan, &ALPHA);
					find_count++;
			   } while (found_at != -1);
		  }

		  elapsed = time(NULL) - start;
	 } while (elapsed <= TEST_TIME);

	 debug("SCAN COUNT: %lu, END TIME: %d, OPS: %f",
		   find_count, (int)elapsed, (double)find_count / elapsed);

	 StringScanner_destroy(scan);

	 return NULL;
}

char *test_performance_stats()
{
	 int i = 0;
	 int found_at = 0;
	 unsigned long find_count = 0;
	 time_t elapsed = 0;
	 StringScanner *scan = StringScanner_create(&IN_STR);

	 time_t warmup_start = time(NULL);

	 do {
		  for(i = 0; i < 1000; i++) {
			   found_at = 0;
			   do {
					found_at = StringScanner_scan(scan, &ALPHA);
			   } while (found_at != -1);
		  }

		  elapsed = time(NULL) - warmup_start;
	 } while (elapsed <= TEST_TIME);

	 elapsed = 0;
	 Stats *st = Stats_create();

	 time_t start = time(NULL);
	 time_t prev = start;

	 do {
		  prev = time(NULL) - start;
		  for(i = 0; i < 1000; i++) {
			   found_at = 0;
			   do {
					found_at = StringScanner_scan(scan, &ALPHA);
					find_count++;
			   } while (found_at != -1);
		  }
		  elapsed = time(NULL) - start;
		  Stats_sample(st, (double)(elapsed-prev));
	 } while (elapsed <= TEST_TIME);

	 debug("SCAN COUNT: %lu, OPS: %f MEAN: %f VARIANCE: %f",
		   find_count, st->sum, Stats_mean(st), Stats_stddev(st));

	 elapsed = 0;

	 Stats *st_means = Stats_create();
	 Stats *st_stddev = Stats_create();

	 start = time(NULL);
	 prev = start;

	 const int N = 10;
	 for(i = 0; i < N; i++) {
		  st->sum = 0;
		  st->sumsq = 0;
		  st->n = 0;
		  st->min = 0;
		  st->max = 0;
		  do {
			   prev = time(NULL) - start;
			   for(i = 0; i < 1000; i++) {
					found_at = 0;
					do {
						 found_at = StringScanner_scan(scan, &ALPHA);
						 find_count++;
					} while (found_at != -1);
			   }
			   elapsed = time(NULL) - start;
			   Stats_sample(st, (double)(elapsed-prev));
		  } while (elapsed <= TEST_TIME);
		  Stats_sample(st_means, Stats_mean(st));
		  Stats_sample(st_stddev, Stats_stddev(st));
	 }

	 debug("SCAN COUNT: %lu, MEAN OF MEANS: %f MEAN OF VARIANCES: %f",
		   find_count*N, Stats_mean(st_means), Stats_mean(st_stddev));

	 StringScanner_destroy(scan);


	 return NULL;
}



char *all_tests()
{
	 mu_suite_start();

	 mu_run_test(test_find_and_scan);

	 // this is an idiom for commenting out sections of code

	 if (TEST_GO) {
		  mu_run_test(test_scan_performance);
		  mu_run_test(test_find_performance);
		  mu_run_test(test_binstr_performance);
		  mu_run_test(test_performance_stats);
	 }

	 return NULL;
}

RUN_TESTS(all_tests);
