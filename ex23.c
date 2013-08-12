#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>

#define CASE1(action, N) case (N-1): action;
#define CASE2(action, N) case (N-2): action;
#define CASE3(action, N) case (N-3): action;
#define CASE4(action, N) case (N-4): action;
#define CASE5(action, N) case (N-5): action;
#define CASE6(action, N) case (N-6): action;
#define CASE7(action, N) case (N-7): action;
#define CASE8(action, N) case (N-8): action;

#define DEVICE8(action, N) \
	 CASE1(action,N) \
	 CASE2(action,N) \
	 CASE3(action,N) \
	 CASE4(action,N) \
	 CASE5(action,N) \
	 CASE6(action,N) \
	 CASE7(action,N) \
	 CASE8(action,N)


/* #define DUFF_DEVICE(action, count, N)			\ */
 /* int count_ = (count); \  */
/* 	 int n_ = (count + N - 1) / N; \ */
/* 	 switch(count % N) { \ */
/* 	 case 0: do  { action;						\ */
/* 			   DEVICE8(action, N)				\ */
/* 		  DEVICE8(action, (N-8))				\ */
/* 		  DEVICE8(action, (N-16))				\ */
/* 		  DEVICE8(action, (N-24))				\ */
/* 		  } while (n_-- > 0);					\ */
/* 	 } */

#define DUFF_DEVICE_8(aCount, aAction) \
	 int count_ = (aCount);			   \
	 int times_ = (count_ + 7) >> 3;   \
	 switch (count_ & 7){			   \
case 0: do { aAction;				   \
		  case 7: aAction;			   \
		  case 6: aAction;			   \
		  case 5: aAction;			   \
		  case 4: aAction;			   \
		  case 3: aAction;			   \
		  case 2: aAction;			   \
		  case 1: aAction;			   \
		  } while (--times_ > 0);	   \
	 }								   \


int normal_copy(char *from, char *to, int count)
{
	 int i = 0;

	 for(i = 0; i < count; i++) {
		  to[i] = from[i];
	 }

	 return i;
}


int Micaiahs_device(char *from, char *to, int count) {
	 {
	 DUFF_DEVICE_8(*to++ = *from++, count)
		  }
	 return count;
}

int duffs_device(char *from, char *to, int count)
{
	 {
		  int n = (count + 7) / 8;

		  switch(count % 8) {
		  case 0: do { *to++ = *from++;
			   case 7: *to++ = *from++;
			   case 6: *to++ = *from++;
			   case 5: *to++ = *from++;
			   case 4: *to++ = *from++;					
			   case 3: *to++ = *from++;
			   case 2: *to++ = *from++;
			   case 1: *to++ = *from++;
			   } while(--n > 0);
		  }
	 }
	 return count;
}

int zeds_device(char *from, char *to, int count)
{
	 {
		  int n = (count + 7) / 8;

		  switch(count % 8) {
		  case 0:
		  again: *to++ = *from++;

		  case 7: *to++ = *from++;
		  case 6: *to++ = *from++;
		  case 5: *to++ = *from++;
		  case 4: *to++ = *from++;
		  case 3: *to++ = *from++;
		  case 2: *to++ = *from++;
		  case 1: *to++ = *from++;
			   if(--n > 0) goto again;
		  }
	 }

	 return count;
}

int valid_copy(char *data, int count, char expects)
{
	 int i = 0;
	 for(i = 0; i < count; i++) {
		  if(data[i] != expects) {
			   log_err("[%d] %c != %c", i, data[i], expects);
			   return 0;
		  }
	 }

	 return 1;
}

int main(int argc, char *argv[])
{
	 char from[10000] = {'a'};
	 char to[10000] = {'c'};
	 int rc = 0;
	 int i = 0;
	 long long N = 900;
	 struct timespec before;

	 // setup the from to have some stuff
	 memset(from, 'x', 10000);
	 // set it to a failure mode
	 clock_gettime(CLOCK_REALTIME, &before);
	 for(i = 0; i < N; i++) {
		  
		  memset(to, 'y', 10000);
		  check(valid_copy(to, 10000, 'y'), "Not initialized right.");

	 
		  // use normal copy to
		  rc = normal_copy(from, to, 10000);
		  check(rc == 10000, "Normal copy failed: %d", rc);
		  check(valid_copy(to, 10000, 'x'), "Normal copy failed.");
	 }
	 
	 struct timespec after;
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("Normal copy: %lld", (after.tv_nsec - before.tv_nsec) / N);
	 
	 clock_gettime(CLOCK_REALTIME, &before);

	 for(i = 0; i < N; i++) {
		  memset(to, 'y', 10000);


		  // duffs version
		  rc = duffs_device(from, to, 10000);
		  check(rc == 10000, "Duff's device failed: %d", rc);
		  check(valid_copy(to, 10000, 'x'), "Duff's device failed copy.");
	 }
	 
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("Duff's Device: %lld", (after.tv_nsec - before.tv_nsec) / N);


	 
	 clock_gettime(CLOCK_REALTIME, &before);
	 // reset
	 for(i = 0; i < N; i++) {
		  memset(to, 'y', 10000);
		  rc = zeds_device(from, to, 10000);
		  check(rc == 10000, "Zed's device failed: %d", rc);
		  check(valid_copy(to, 10000, 'x'), "Zed's device failed copy.");
	 }

	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("Zeds Device: %lld", (after.tv_nsec - before.tv_nsec) / N);


	 /* memset(to, 'y', 10000); */
	 
	 /* clock_gettime(CLOCK_REALTIME, &before); */
	 
	 /* rc = Micaiahs_device(from, to, 10000); */
	 /* check(rc == 10000, "Micaiah's device failed %d", rc); */
	 /* check(valid_copy(to, 10000, 'x'), "Micaiah's device failed copy."); */

	 /* clock_gettime(CLOCK_REALTIME, &after); */
	 /* log_info("Micaiahs_device: %lld", (after.tv_nsec - before.tv_nsec)); */



	 clock_gettime(CLOCK_REALTIME, &before);
	 for(i = 0; i < N; i++) {
		  memset(to, 'y', 10000);
		  memcpy(to, from, 10000);
		  check(valid_copy(to, 10000, 'x'), "memcpy failed copy.");
	 }
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("memcpy: %lld", (after.tv_nsec - before.tv_nsec) / N);


	 clock_gettime(CLOCK_REALTIME, &before);

	 for(i = 0; i < N; i++) {
		  memset(to, 'y', 10000);
		  memmove(to, from, 10000);
		  check(valid_copy(to, 10000, 'x'), "memmove failed copy.");
	 }

	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("memmove: %lld", (after.tv_nsec - before.tv_nsec) / N);
	 clock_gettime(CLOCK_REALTIME, &before);
	 for(i = 0; i < N; i++) {
		  memset(to, 'y', 10000);
		  memset(to, 'x', 10000);
		  check(valid_copy(to, 10000, 'x'), "memset failed copy.");
	 }
	 clock_gettime(CLOCK_REALTIME, &after);
	 log_info("memset: %lld", (after.tv_nsec - before.tv_nsec) / N);
	 
	 return 0;
error:
	 return 1;
}
