#include "tetris_test.h"

START_TEST(test_exit_game_field_not_null) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Play,
                             .prev_state = Game_over};

  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  info.info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }

  exit_game(&info);

  ck_assert_ptr_null(info.info.field);
  ck_assert_ptr_null(info.info.next);
}
END_TEST

START_TEST(test_exit_game_field_null) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Play,
                             .prev_state = Game_over};

  exit_game(&info);

  ck_assert_ptr_null(info.info.field);
  ck_assert_ptr_null(info.info.next);
}
END_TEST

START_TEST(test_reset_game_basic) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {5, {0, 0}, 0},
                             .timer = 0,
                             .state = Play,
                             .prev_state = Game_over};

  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  info.info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }

  reset_game(&info);

  ck_assert_ptr_null(info.info.field);
  ck_assert_ptr_null(info.info.next);

  ExpandedGameInfo_t *instance = get_instance();
  exit_game(instance);
}
END_TEST

START_TEST(test_clear_field_basic) {
  GameInfo_t info = {.field = malloc(FIELD_ROWS * sizeof(int *)),
                     .next = NULL,
                     .score = 0,
                     .high_score = 0,
                     .level = 1,
                     .speed = 1,
                     .pause = 0};

  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = malloc(FIELD_COLS * sizeof(int));
    for (int j = 0; j < FIELD_COLS; j++) {
      info.field[i][j] = 1;
    }
  }

  clear_field(&info);

  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      ck_assert_int_eq(info.field[i][j], 0);
    }
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

Suite *suite_clearing() {
  Suite *s = suite_create("CLEARING");
  TCase *tc = tcase_create("clearing_tc");

  // exit_game
  tcase_add_test(tc, test_exit_game_field_not_null);
  tcase_add_test(tc, test_exit_game_field_null);

  // reset_game
  tcase_add_test(tc, test_reset_game_basic);

  // clear_field
  tcase_add_test(tc, test_clear_field_basic);

  suite_add_tcase(s, tc);
  return s;
}
