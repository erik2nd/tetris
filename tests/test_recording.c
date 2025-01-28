#include "tetris_test.h"

START_TEST(test_load_high_score_basic) {
  FILE *file;
  int original_high_score = 0;

  file = fopen(FILE_PATH, "r");
  if (file != NULL) {
    fscanf(file, "%d", &original_high_score);
    fclose(file);
  }

  file = fopen(FILE_PATH, "w");
  ck_assert_ptr_nonnull(file);
  fprintf(file, "1000");
  fclose(file);

  int high_score = load_high_score();

  ck_assert_int_eq(high_score, 1000);

  file = fopen(FILE_PATH, "w");
  ck_assert_ptr_nonnull(file);
  fprintf(file, "%d", original_high_score);
  fclose(file);
}
END_TEST

START_TEST(test_save_high_score_basic) {
  FILE *file;
  int original_high_score = 0;

  file = fopen(FILE_PATH, "r");
  if (file != NULL) {
    fscanf(file, "%d", &original_high_score);
    fclose(file);
  }

  GameInfo_t info = {NULL, NULL, 0, 1000, 1, 1, 0};

  save_high_score(&info);

  file = fopen(FILE_PATH, "r");
  ck_assert_ptr_nonnull(file);

  int saved_high_score;
  fscanf(file, "%d", &saved_high_score);
  fclose(file);

  ck_assert_int_eq(saved_high_score, info.high_score);

  file = fopen(FILE_PATH, "w");
  ck_assert_ptr_nonnull(file);
  fprintf(file, "%d", original_high_score);
  fclose(file);
}
END_TEST

Suite *suite_recording() {
  Suite *s = suite_create("RECORDING");
  TCase *tc = tcase_create("recording_tc");

  // load_high_score
  tcase_add_test(tc, test_load_high_score_basic);

  // save_high_score
  tcase_add_test(tc, test_save_high_score_basic);

  suite_add_tcase(s, tc);
  return s;
}
