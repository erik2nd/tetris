#include "tetris_test.h"

START_TEST(test_move_piece_side_left) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  move_piece_side(&info, &piece, LEFT);

  ck_assert_int_eq(piece.coords.col, 4);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_move_piece_side_right) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  move_piece_side(&info, &piece, RIGHT);

  ck_assert_int_eq(piece.coords.col, 6);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_move_piece_side_blocked) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  info.field[5][6] = 2;

  move_piece_side(&info, &piece, 1);

  ck_assert_int_eq(piece.coords.col, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_move_piece_down) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  move_piece_down(&info, &piece);

  ck_assert_int_eq(piece.coords.row, 6);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_move_piece_down_blocked) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  info.field[7][5] = 2;

  move_piece_down(&info, &piece);

  ck_assert_int_eq(piece.coords.row, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_move_piece_down_to_bottom) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {FIELD_ROWS - 2, 5}};

  place_piece(&info, piece);

  move_piece_down(&info, &piece);

  ck_assert_int_eq(piece.coords.row, FIELD_ROWS - 2);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_drop_piece_to_bottom) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {0, 5}};

  place_piece(&info, piece);

  drop_piece(&info, &piece);

  ck_assert_int_eq(piece.coords.row, FIELD_ROWS - 2);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_drop_piece_blocked) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {0, 5}};

  place_piece(&info, piece);

  info.field[5][5] = 2;

  drop_piece(&info, &piece);

  ck_assert_int_eq(piece.coords.row, 3);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_drop_piece_already_at_bottom) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {FIELD_ROWS - 2, 5}};

  place_piece(&info, piece);

  drop_piece(&info, &piece);

  ck_assert_int_eq(piece.coords.row, FIELD_ROWS - 2);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_rotate_piece) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  rotate_piece(&info, &piece);

  ck_assert_int_eq(piece.pos, 1);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_rotate_piece_blocked) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 2, .pos = 1, .coords = {5, 9}};

  place_piece(&info, piece);

  rotate_piece(&info, &piece);

  ck_assert_int_eq(piece.pos, 1);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_rotate_piece_multiple_times) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  for (int i = 0; i < POS_COUNT; i++) {
    rotate_piece(&info, &piece);
  }

  ck_assert_int_eq(piece.pos, 0);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

Suite *suite_moving() {
  Suite *s = suite_create("MOVING");
  TCase *tc = tcase_create("moving_tc");

  // move_piece_side
  tcase_add_test(tc, test_move_piece_side_left);
  tcase_add_test(tc, test_move_piece_side_right);
  tcase_add_test(tc, test_move_piece_side_blocked);

  // move_piece_down
  tcase_add_test(tc, test_move_piece_down);
  tcase_add_test(tc, test_move_piece_down_blocked);
  tcase_add_test(tc, test_move_piece_down_to_bottom);

  // drop_piece
  tcase_add_test(tc, test_drop_piece_to_bottom);
  tcase_add_test(tc, test_drop_piece_blocked);
  tcase_add_test(tc, test_drop_piece_already_at_bottom);

  // rotate_piece
  tcase_add_test(tc, test_rotate_piece);
  tcase_add_test(tc, test_rotate_piece_blocked);
  tcase_add_test(tc, test_rotate_piece_multiple_times);

  suite_add_tcase(s, tc);
  return s;
}
