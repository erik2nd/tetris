#include "tetris_test.h"

START_TEST(test_userInput_terminate) {
  ExpandedGameInfo_t *info = get_instance();
  info->state = Play;

  userInput(Terminate, false);

  ck_assert_int_eq(info->state, Exit);
}
END_TEST

START_TEST(test_userInput_pause) {
  ExpandedGameInfo_t *info = get_instance();
  info->state = Play;

  userInput(Pause, false);

  ck_assert_int_eq(info->state, Stop);
  ck_assert_int_eq(info->info.pause, 1);
}
END_TEST

START_TEST(test_userInput_start) {
  ExpandedGameInfo_t *info = get_instance();
  info->state = Stop;
  info->info.pause = 1;

  userInput(Start, false);

  ck_assert_int_eq(info->state, Play);
  ck_assert_int_eq(info->info.pause, 0);
}
END_TEST

START_TEST(test_userInput_move) {
  ExpandedGameInfo_t *info = get_instance();
  info->state = Play;

  userInput(Right, false);

  ck_assert_int_eq(info->state, Play);
}
END_TEST

START_TEST(test_userInput_score_up) {
  ExpandedGameInfo_t *info = get_instance();
  for (int i = 0; i < FIELD_COLS; i++) {
    info->info.field[19][i] = 1;
  }

  userInput(Right, false);

  ck_assert_int_eq(info->state, Play);
  exit_game(info);
}
END_TEST

START_TEST(test_userInput_game_over) {
  ExpandedGameInfo_t *info = get_instance();
  info->info.field[0][5] = 1;

  userInput(Right, false);

  ck_assert_int_eq(info->state, Game_over);
  exit_game(info);
}
END_TEST

START_TEST(test_updateCurrentState_basic) {
  GameInfo_t info = updateCurrentState();

  ck_assert_ptr_ne(info.field, NULL);
  ck_assert_ptr_ne(info.next, NULL);
  ck_assert_int_eq(info.score, INIT_SCORE);
  ck_assert_int_ge(info.high_score, -1);
  ck_assert_int_eq(info.level, INIT_LEVEL);
  ck_assert_int_eq(info.speed, INIT_LEVEL);
  ck_assert_int_eq(info.pause, 0);
}
END_TEST

START_TEST(test_updateCurrentState_after_change) {
  ExpandedGameInfo_t *instance = get_instance();
  instance->info.score = 1000;

  GameInfo_t info = updateCurrentState();

  ck_assert_ptr_ne(info.field, NULL);
  ck_assert_ptr_ne(info.next, NULL);
  ck_assert_int_eq(info.score, 1000);
  ck_assert_int_ge(info.high_score, -1);
  ck_assert_int_eq(info.level, INIT_LEVEL);
  ck_assert_int_eq(info.speed, INIT_LEVEL);
  ck_assert_int_eq(info.pause, 0);

  exit_game(instance);
}
END_TEST

Suite *suite_specifics() {
  Suite *s = suite_create("SPECIFICS");
  TCase *tc = tcase_create("specifics_tc");

  // userInput
  tcase_add_test(tc, test_userInput_terminate);
  tcase_add_test(tc, test_userInput_pause);
  tcase_add_test(tc, test_userInput_start);
  tcase_add_test(tc, test_userInput_move);
  tcase_add_test(tc, test_userInput_score_up);
  tcase_add_test(tc, test_userInput_game_over);

  // updateCurrentState
  tcase_add_test(tc, test_updateCurrentState_basic);
  tcase_add_test(tc, test_updateCurrentState_after_change);

  suite_add_tcase(s, tc);
  return s;
}
