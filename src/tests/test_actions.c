#include <limits.h>

#include "tetris_test.h"

START_TEST(test_user_action_start_lowercase) {
  ck_assert_int_eq(user_action('s'), Start);
}
END_TEST

START_TEST(test_user_action_start_uppercase) {
  ck_assert_int_eq(user_action('S'), Start);
}
END_TEST

START_TEST(test_user_action_pause_lowercase) {
  ck_assert_int_eq(user_action('p'), Pause);
}
END_TEST

START_TEST(test_user_action_pause_uppercase) {
  ck_assert_int_eq(user_action('P'), Pause);
}
END_TEST

START_TEST(test_user_action_terminate_lowercase) {
  ck_assert_int_eq(user_action('q'), Terminate);
}
END_TEST

START_TEST(test_user_action_terminate_uppercase) {
  ck_assert_int_eq(user_action('Q'), Terminate);
}
END_TEST

START_TEST(test_user_action_left) {
  ck_assert_int_eq(user_action(KEY_LEFT), Left);
}
END_TEST

START_TEST(test_user_action_right) {
  ck_assert_int_eq(user_action(KEY_RIGHT), Right);
}
END_TEST

START_TEST(test_user_action_up) {
  ck_assert_int_eq(user_action(KEY_UP), Action);
}
END_TEST

START_TEST(test_user_action_down) {
  ck_assert_int_eq(user_action(KEY_DOWN), Down);
}
END_TEST

START_TEST(test_user_action_space) { ck_assert_int_eq(user_action(' '), Up); }
END_TEST

START_TEST(test_user_action_default) {
  ck_assert_int_eq(user_action('d'), UINT_MAX);
}
END_TEST

Suite *suite_actions() {
  Suite *s = suite_create("ACTIONS");
  TCase *tc = tcase_create("actions_tc");

  tcase_add_test(tc, test_user_action_start_lowercase);
  tcase_add_test(tc, test_user_action_start_uppercase);
  tcase_add_test(tc, test_user_action_pause_lowercase);
  tcase_add_test(tc, test_user_action_pause_uppercase);
  tcase_add_test(tc, test_user_action_terminate_lowercase);
  tcase_add_test(tc, test_user_action_terminate_uppercase);
  tcase_add_test(tc, test_user_action_left);
  tcase_add_test(tc, test_user_action_right);
  tcase_add_test(tc, test_user_action_up);
  tcase_add_test(tc, test_user_action_down);
  tcase_add_test(tc, test_user_action_space);
  tcase_add_test(tc, test_user_action_default);

  suite_add_tcase(s, tc);
  return s;
}
