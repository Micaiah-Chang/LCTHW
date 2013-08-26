#include "minunit.h"
#include <lcthw/bstrlib.h>

static bstring a, b;

char *test_bfromcstr()
{
	 b = bfromcstr(NULL);
	 mu_assert(b == NULL, "Can't make bstring from NULL.");

	 b = bfromcstr("Hello");
	 mu_assert(strcmp((const char *)b->data,"Hello") == 0 , "bstring does not match c string!");
	 bdestroy(b);

	 return NULL;
}

char *test_blk2bstr()
{
	 b = blk2bstr("Hello", -1);
	 mu_assert(b == NULL, "Return NULL when read length is negative");

	 b = blk2bstr(NULL, 10);
	 mu_assert(b == NULL, "Return NULL when NULL pointer is passed as string");

	 b = blk2bstr("Hello", 5);
	 mu_assert(strcmp((char *)b->data, "Hello") == 0, "bstr should be equal to string");

	 bdestroy(b);
	 b = blk2bstr("Hello", 4);
	 mu_assert(strcmp((const char *)b->data, "Hell") == 0, "bstr should be equal to string");
	 mu_assert(strcmp((const char *)b->data, "Hello") != 0, "bstr shoul not be equal to string");

	 return NULL;
}

char *test_bstrcpy()
{
	 a = bstrcpy(b);

	 int rc = strcmp((const char *)a->data, (const char *)b->data);
	 mu_assert(rc == 0, "bstring failed to copy successfully.");
	 bdestroy(a);
	 bdestroy(b);
	 return NULL;
}

char *test_bassign()
{
	 a = bfromcstr("Hello");
	 mu_assert(a != NULL, "Creation failed.");

	 b = bfromcstr("World");
	 mu_assert(b != NULL, "Creation failed.");

	 int rc = bassign(a, b);
	 mu_assert(rc == BSTR_OK, "Failed to copy");

	 rc = strcmp((char *)b->data, (char *)a->data);
	 mu_assert(rc == 0, "Not identical");

	 return NULL;
}

char *test_bassigncstr()
{
	 int rc = bassigncstr(b, "Hello");
	 mu_assert(rc == BSTR_OK, "bassigncstr failed");

	 rc = strcmp((char *)b->data, "Hello");
	 mu_assert(rc == 0, "Strings did not match");

	 return NULL;
}

char *test_bassignblk()
{
	 int rc = bassignblk(b, (void *)"moo", 5);
	 mu_assert(BSTR_OK == rc, "bassignblk failed.");

	 rc = strcmp("moo", (char *)b->data);
	 mu_assert(0 == rc, "String not expected result.");

	 bdestroy(b);

	 return NULL;
}

char *test_bconcat()
{
	 b = bfromcstr("Hello ");
	 mu_assert(b != NULL, "Failed to create a string");

	 int rc = bconcat(b, a);
	 mu_assert(rc == 0, "Failed to cat");

	 rc = strcmp((char *)b->data, "Hello World");
	 mu_assert(rc == 0, "Concat not expected result");

	 bdestroy(a);

	 return NULL;
}

char *test_bstricmp()
{
	 a = bstrcpy(b);

	 int rc = bstricmp(a, b);
	 mu_assert(rc == 0, "bstr comparison not equal");
	 return NULL;
}

char *test_biseq()
{
	 int rc = biseq(a, b);
	 mu_assert(rc == 1, "biseq isn't equal equal");
	 bdestroy(b);

	 return NULL;
}

char *test_binstr()
{

	 b = bfromcstr("orld");
	 int rc = binstr(a, 0, b);
	 mu_assert(rc != BSTR_ERR, "Did not find string in b");
	 return NULL;
}

char *test_bfindreplace()
{
	 bstring c = bfromcstr("eird");
	 int rc = bfindreplace(a, b, c, 0);
	 mu_assert(rc != BSTR_ERR, "Did not successfully find or replace");
	 bstring d = bfromcstr("Hello Weird");
	 rc = biseq(a, d);
	 mu_assert(rc == 1, "Not equal to expected string" );
	 rc = biseq(a, c);
	 mu_assert(rc == 0, "a should not be equal to c");

	 bdestroy(b);
	 bdestroy(c);
	 bdestroy(d);

	 return NULL;
}

char *test_bsplit()
{
	 struct bstrList *list;
	 list = bsplit(a, ' ');

	 mu_assert(list != NULL, "List failed to be created");
	 b = bfromcstr("Hello");
	 int rc = bstrcmp(list->entry[0], b);
	 mu_assert(rc == 0, "Unexpected mismatch for first entry");

	 bdestroy(b);

	 b = bfromcstr("Weird");
	 rc = bstrcmp(list->entry[1], b);
	 mu_assert(rc == 0, "Unexpected mismatch for first entry");

	 bdestroy(b);
	 bstrListDestroy(list);
	 return NULL;
}

char *test_bformat()
{
	 char *temp = "Pleb.";
	 b = bformat("Hello %s", temp);
	 mu_assert(b != NULL, "Did not format correctly");

	 bstring d = bfromcstr("Hello Pleb.");
	 int rc = bstrcmp(b, d);
	 mu_assert(rc == 0, "Unexpected mismatch from bformat.");

	 bdestroy(d);
	 return NULL;
}

char *test_blength()
{
	 int rc = blength(b);
	 mu_assert(rc == 11, "Wrong length for string \"Hello Pleb.\"");

	 bdestroy(a);
	 a = bfromcstr("");
	 rc = blength(a);
	 mu_assert(0 == rc, "Wrong length for empty string.");

	 bdestroy(a);

	 return NULL;
}

char *test_bchar()
{
	 char temp;
	 temp = bchar(b, 3);
	 mu_assert('l' == temp, "Returned with wrong character");

	 temp = bchar(b, 20);
	 mu_assert(0 == temp, "Should fail on entry past end of string");

	 bdestroy(b);
	 return NULL;
}

char *all_tests() {
	 mu_suite_start();

	 mu_run_test(test_bfromcstr);
	 mu_run_test(test_blk2bstr);
	 mu_run_test(test_bstrcpy);

	 mu_run_test(test_bassign);
	 mu_run_test(test_bassigncstr);
	 mu_run_test(test_bassignblk);

	 mu_run_test(test_bconcat);
	 mu_run_test(test_bstricmp);
	 mu_run_test(test_biseq);

	 mu_run_test(test_binstr);
	 mu_run_test(test_bfindreplace);
	 mu_run_test(test_bsplit);

	 mu_run_test(test_bformat);
	 mu_run_test(test_blength);
	 mu_run_test(test_bchar);

	 return NULL;
}

RUN_TESTS(all_tests);
