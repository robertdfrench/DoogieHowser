#include <stdlib.h>
#include <check.h>
#include "../src/force.h"

START_TEST (test_force_is_zero_for_same_particle)
{
  double x1,y1 = 0.1;
  int force = (int) force_calculate_magnitude(x1,y1,x1,y1);
  ck_assert_int_eq(force, 0);
}
END_TEST

Suite* force_suite(void) {
	   Suite *s = suite_create("Force");
	   TCase *tc_core = tcase_create("Core");
	   tcase_add_test(tc_core,test_force_is_zero_for_same_particle);
	   suite_add_tcase(s, tc_core);

	   return s;
}

int main (void) {
	   int number_failed;
	   Suite *s = force_suite();
	   SRunner *sr = srunner_create(s);
	   srunner_run_all(sr, CK_NORMAL);
	   number_failed = srunner_ntests_failed (sr);
	   srunner_free (sr);
	   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
