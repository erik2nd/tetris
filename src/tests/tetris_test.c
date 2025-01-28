#include "tetris_test.h"

int main() {
  Suite *suite_array[] = {suite_actions(),  suite_instance(), suite_checkups(),
                          suite_placing(),  suite_moving(),   suite_updating(),
                          suite_clearing(), suite_values(),   suite_recording(),
                          suite_specifics()};
  printf("\n");
  for (unsigned long i = 0; i < sizeof(suite_array) / sizeof(suite_array[0]);
       i++) {
    run_test_cases(suite_array[i]);
    printf("\n");
  }
  return 0;
}

void run_test_cases(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
