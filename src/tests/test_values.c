#include "tetris_test.h"

START_TEST(test_get_piece_shifts_O) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
      {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
      {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
      {{0, -1}, {0, 0}, {1, -1}, {1, 0}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(1, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_I) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
      {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(2, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_S) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
      {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(3, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_Z) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
      {{-1, 1}, {0, 1}, {0, 0}, {1, 0}},
      {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
      {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(4, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_L) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{1, -1}, {0, -1}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
      {{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
      {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(5, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_J) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{0, -1}, {0, 0}, {0, 1}, {1, 1}},
      {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}},
      {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {1, 0}, {1, -1}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(6, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_get_piece_shifts_T) {
  Coordinate_t expected[POS_COUNT][PIECE_SIZE] = {
      {{0, -1}, {0, 0}, {0, 1}, {1, 0}},
      {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
      {{-1, 0}, {0, -1}, {0, 0}, {0, 1}},
      {{-1, 0}, {0, 0}, {1, 0}, {0, -1}}};

  for (int pos = 0; pos < POS_COUNT; pos++) {
    for (int num = 0; num < PIECE_SIZE; num++) {
      Coordinate_t result = get_piece_shifts(7, pos, num);
      ck_assert_int_eq(result.row, expected[pos][num].row);
      ck_assert_int_eq(result.col, expected[pos][num].col);
    }
  }
}
END_TEST

START_TEST(test_random_piece_basic) {
  Piece_t res = random_piece();

  ck_assert_int_ge(res.type, 1);
  ck_assert_int_le(res.type, PIECE_COUNT);

  ck_assert_int_eq(res.coords.row, 0);
  ck_assert_int_eq(res.coords.col, 5);
  ck_assert_int_eq(res.pos, 0);
}
END_TEST

START_TEST(test_get_iteration_delay_basic) {
  int expected_delays[] = {500, 450, 400, 350, 300, 250, 200, 150, 100, 50};

  for (int level = 1; level <= 10; level++) {
    int delay = get_iteration_delay(level);
    ck_assert_int_eq(delay, expected_delays[level - 1]);
  }
}
END_TEST

START_TEST(test_get_iteration_delay_boundary) {
  int delay_min_level = get_iteration_delay(1);
  int delay_max_level = get_iteration_delay(10);

  ck_assert_int_eq(delay_min_level, 500);
  ck_assert_int_eq(delay_max_level, 50);
}
END_TEST

START_TEST(test_get_points_basic) {
  int expected_points[] = {0, 100, 300, 700, 1500};

  for (int count = 0; count <= 4; count++) {
    int points = get_points(count);
    ck_assert_int_eq(points, expected_points[count]);
  }
}
END_TEST

START_TEST(test_get_points_boundary) {
  int points_min_count = get_points(0);
  int points_max_count = get_points(4);

  ck_assert_int_eq(points_min_count, 0);
  ck_assert_int_eq(points_max_count, 1500);
}
END_TEST

START_TEST(test_get_level_boundary_basic) {
  int expected_boundaries[] = {600, 1200, 1800, 2400, 3000};

  for (int level = 1; level <= 5; level++) {
    int boundary = get_level_boundary(level);
    ck_assert_int_eq(boundary, expected_boundaries[level - 1]);
  }
}
END_TEST

START_TEST(test_get_level_boundary_boundary) {
  int boundary_min_level = get_level_boundary(1);
  int boundary_max_level = get_level_boundary(10);

  ck_assert_int_eq(boundary_min_level, 600);
  ck_assert_int_eq(boundary_max_level, 6000);
}
END_TEST

Suite *suite_values() {
  Suite *s = suite_create("VALUES");
  TCase *tc = tcase_create("values_tc");

  // get_piece_shifts
  tcase_add_test(tc, test_get_piece_shifts_O);
  tcase_add_test(tc, test_get_piece_shifts_I);
  tcase_add_test(tc, test_get_piece_shifts_S);
  tcase_add_test(tc, test_get_piece_shifts_Z);
  tcase_add_test(tc, test_get_piece_shifts_L);
  tcase_add_test(tc, test_get_piece_shifts_J);
  tcase_add_test(tc, test_get_piece_shifts_T);

  // random_piece
  tcase_add_test(tc, test_random_piece_basic);

  // get_iteration_delay
  tcase_add_test(tc, test_get_iteration_delay_basic);
  tcase_add_test(tc, test_get_iteration_delay_boundary);

  // get_points
  tcase_add_test(tc, test_get_points_basic);
  tcase_add_test(tc, test_get_points_boundary);

  // get_level_boundary
  tcase_add_test(tc, test_get_level_boundary_basic);
  tcase_add_test(tc, test_get_level_boundary_boundary);

  suite_add_tcase(s, tc);
  return s;
}
