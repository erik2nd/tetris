#include "tetris_test.h"

START_TEST(test_place_piece) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], piece.type);
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_place_piece_multiple_times) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece1 = {.type = 1, .pos = 0, .coords = {5, 5}};

  Piece_t piece2 = {.type = 2, .pos = 0, .coords = {7, 7}};

  place_piece(&info, piece1);
  place_piece(&info, piece2);

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece1.type, piece1.pos, i);
    int row = piece1.coords.row + shift.row;
    int col = piece1.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], piece1.type);
  }

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece2.type, piece2.pos, i);
    int row = piece2.coords.row + shift.row;
    int col = piece2.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], piece2.type);
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_remove_piece) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  place_piece(&info, piece);

  remove_piece(&info, piece);

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], 0);
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

START_TEST(test_remove_piece_multiple_times) {
  GameInfo_t info;
  info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece1 = {.type = 1, .pos = 0, .coords = {5, 5}};

  Piece_t piece2 = {.type = 2, .pos = 0, .coords = {7, 7}};

  place_piece(&info, piece1);
  place_piece(&info, piece2);

  remove_piece(&info, piece1);

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece1.type, piece1.pos, i);
    int row = piece1.coords.row + shift.row;
    int col = piece1.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], 0);
  }

  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece2.type, piece2.pos, i);
    int row = piece2.coords.row + shift.row;
    int col = piece2.coords.col + shift.col;
    ck_assert_int_eq(info.field[row][col], piece2.type);
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.field[i]);
  }
  free(info.field);
}
END_TEST

Suite *suite_placing() {
  Suite *s = suite_create("PLACING");
  TCase *tc = tcase_create("placing_tc");

  tcase_add_test(tc, test_place_piece);
  tcase_add_test(tc, test_place_piece_multiple_times);
  tcase_add_test(tc, test_remove_piece);
  tcase_add_test(tc, test_remove_piece_multiple_times);

  suite_add_tcase(s, tc);
  return s;
}
