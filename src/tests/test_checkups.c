#include "tetris_test.h"

START_TEST(test_within_bounds) {
  ck_assert_int_eq(is_beyond_bounds(5, 5), false);
  ck_assert_int_eq(is_beyond_bounds(0, 0), false);
  ck_assert_int_eq(is_beyond_bounds(FIELD_ROWS - 1, FIELD_COLS - 1), false);
}
END_TEST

START_TEST(test_beyond_bounds) {
  ck_assert_int_eq(is_beyond_bounds(-1, 5), true);
  ck_assert_int_eq(is_beyond_bounds(5, -1), true);
  ck_assert_int_eq(is_beyond_bounds(FIELD_ROWS, 5), true);
  ck_assert_int_eq(is_beyond_bounds(5, FIELD_COLS), true);
  ck_assert_int_eq(is_beyond_bounds(-1, -1), true);
  ck_assert_int_eq(is_beyond_bounds(FIELD_ROWS, FIELD_COLS), true);
}
END_TEST

START_TEST(test_piece_on_field) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  info.field[5][4] = 1;
  info.field[6][4] = 1;
  info.field[5][5] = 1;
  info.field[6][5] = 1;

  ck_assert_int_eq(is_piece_on_field(&info, piece), true);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_piece_not_on_field) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  ck_assert_int_eq(is_piece_on_field(&info, piece), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_piece_partially_on_field) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  info.field[5][4] = 1;
  info.field[6][4] = 1;

  ck_assert_int_eq(is_piece_on_field(&info, piece), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_row_full) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  for (int j = 0; j < FIELD_COLS; j++) {
    info.field[5][j] = 1;
  }

  ck_assert_int_eq(is_row_full(&info, 5), true);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_row_not_full) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  for (int j = 0; j < FIELD_COLS - 1; j++) {
    info.field[5][j] = 1;
  }

  ck_assert_int_eq(is_row_full(&info, 5), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_row_empty) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  for (int j = 0; j < FIELD_COLS; j++) {
    info.field[5][j] = 0;
  }

  ck_assert_int_eq(is_row_full(&info, 5), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_game_over_true) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  info.info.field[0][4] = 1;
  info.info.field[1][4] = 1;

  info.cur_piece.type = 1;
  info.cur_piece.pos = 0;
  info.cur_piece.coords.row = 0;
  info.cur_piece.coords.col = 5;

  ck_assert_int_eq(is_game_over(&info), true);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_game_over_false) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  info.cur_piece.type = 1;
  info.cur_piece.pos = 0;
  info.cur_piece.coords.row = 0;
  info.cur_piece.coords.col = 5;

  ck_assert_int_eq(is_game_over(&info), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_game_over_with_piece_on_field) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  info.info.field[0][4] = 1;
  info.info.field[1][4] = 1;
  info.info.field[0][5] = 1;
  info.info.field[1][5] = 1;
  info.info.field[1][6] = 2;

  info.cur_piece.type = 1;
  info.cur_piece.pos = 0;
  info.cur_piece.coords.row = 0;
  info.cur_piece.coords.col = 5;

  ck_assert_int_eq(is_game_over(&info), true);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_can_place_empty_field) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  ck_assert_int_eq(can_place(&info, piece), true);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_cannot_place_beyond_bounds) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {FIELD_ROWS, 5}};

  ck_assert_int_eq(can_place(&info, piece), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_cannot_place_occupied_field) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  info.field[5][5] = 1;

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  ck_assert_int_eq(can_place(&info, piece), false);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

Suite *suite_checkups() {
  Suite *s = suite_create("CHECKUPS");
  TCase *tc = tcase_create("checkups_tc");

  // is_beyond_bounds
  tcase_add_test(tc, test_within_bounds);
  tcase_add_test(tc, test_beyond_bounds);

  // is_piece_on_field
  tcase_add_test(tc, test_piece_on_field);
  tcase_add_test(tc, test_piece_not_on_field);
  tcase_add_test(tc, test_piece_partially_on_field);

  // is_row_full
  tcase_add_test(tc, test_row_full);
  tcase_add_test(tc, test_row_not_full);
  tcase_add_test(tc, test_row_empty);

  // is_game_over
  tcase_add_test(tc, test_game_over_true);
  tcase_add_test(tc, test_game_over_false);
  tcase_add_test(tc, test_game_over_with_piece_on_field);

  // can_place
  tcase_add_test(tc, test_can_place_empty_field);
  tcase_add_test(tc, test_cannot_place_beyond_bounds);
  tcase_add_test(tc, test_cannot_place_occupied_field);

  suite_add_tcase(s, tc);
  return s;
}
