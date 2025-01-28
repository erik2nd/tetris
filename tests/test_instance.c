#include <limits.h>

#include "tetris_test.h"

START_TEST(test_initialization) {
  ExpandedGameInfo_t *instance = get_instance();

  ck_assert_ptr_ne(instance->info.field, NULL);
  ck_assert_ptr_ne(instance->info.next, NULL);
  ck_assert_int_eq(instance->info.score, INIT_SCORE);
  ck_assert_int_ge(instance->info.high_score, -1);
  ck_assert_int_eq(instance->info.level, INIT_LEVEL);
  ck_assert_int_eq(instance->info.speed, INIT_LEVEL);
  ck_assert_int_eq(instance->info.pause, 0);
  ck_assert_int_ge(instance->cur_piece.type, 1);
  ck_assert_int_lt(instance->cur_piece.type, 8);
  ck_assert_int_ge(instance->next_piece.type, 1);
  ck_assert_int_lt(instance->next_piece.type, 8);
  ck_assert_int_eq(instance->timer, INIT_TIMER);
  ck_assert_int_eq(instance->state, Begin);
  ck_assert_int_eq(instance->prev_state, Begin);

  exit_game(instance);
}
END_TEST

START_TEST(test_second_call_state) {
  ExpandedGameInfo_t *instance = get_instance();

  ck_assert_int_eq(instance->state, UINT_MAX);
  ck_assert_int_eq(instance->prev_state, Game_over);

  exit_game(instance);
}
END_TEST

Suite *suite_instance() {
  Suite *s = suite_create("INSTANCE");
  TCase *tc = tcase_create("instance_tc");

  tcase_add_test(tc, test_initialization);
  tcase_add_test(tc, test_second_call_state);

  suite_add_tcase(s, tc);
  return s;
}
