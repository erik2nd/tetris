#include "tetris_test.h"

START_TEST(test_update_timer_zero_timer) {
  ExpandedGameInfo_t info = {.timer = DELAY, .state = Move};

  update_timer(&info);

  ck_assert_int_eq(info.timer, 0);
  ck_assert_int_eq(info.state, Shift);
}
END_TEST

START_TEST(test_update_timer_positive_timer) {
  ExpandedGameInfo_t info = {.timer = DELAY + 50, .state = Move};

  update_timer(&info);

  ck_assert_int_eq(info.timer, 50);
  ck_assert_int_eq(info.state, Move);
}
END_TEST

START_TEST(test_update_timer_negative_timer) {
  ExpandedGameInfo_t info = {.timer = 0, .state = Move};

  update_timer(&info);

  ck_assert_int_eq(info.timer, -10);
  ck_assert_int_eq(info.state, Shift);
}
END_TEST

START_TEST(test_update_current_piece_updates_correctly) {
  ExpandedGameInfo_t info;

  info.info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }

  Piece_t piece1 = {.type = 1, .pos = 0, .coords = {5, 5}};
  Piece_t piece2 = {.type = 2, .pos = 0, .coords = {5, 5}};

  info.cur_piece = piece1;
  info.next_piece = piece2;

  update_current_piece(&info);

  ck_assert_int_eq(info.cur_piece.type, 2);
  ck_assert_int_ge(info.next_piece.type, 1);
  ck_assert_int_le(info.next_piece.type, 7);

  for (int i = 0; i < NEXT_ROWS; i++) {
    free(info.info.next[i]);
  }
  free(info.info.next);
}
END_TEST

START_TEST(test_fill_next_piece_empty) {
  GameInfo_t info;

  info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  fill_next_piece(&info, piece);

  ck_assert_int_eq(info.next[0][2], piece.type);
  ck_assert_int_eq(info.next[1][2], piece.type);
  ck_assert_int_eq(info.next[0][1], piece.type);
  ck_assert_int_eq(info.next[1][1], piece.type);

  for (int i = 0; i < NEXT_ROWS; i++) {
    free(info.next[i]);
  }
  free(info.next);
}
END_TEST

START_TEST(test_fill_next_piece_already_placed) {
  GameInfo_t info;

  info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }

  info.next[0][2] = 2;
  info.next[1][2] = 2;
  info.next[0][1] = 2;
  info.next[1][1] = 2;

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};

  fill_next_piece(&info, piece);

  ck_assert_int_eq(info.next[0][2], piece.type);
  ck_assert_int_eq(info.next[1][2], piece.type);
  ck_assert_int_eq(info.next[0][1], piece.type);
  ck_assert_int_eq(info.next[1][1], piece.type);

  for (int i = 0; i < NEXT_ROWS; i++) {
    free(info.next[i]);
  }
  free(info.next);
}
END_TEST

START_TEST(test_make_shift_down) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  info.info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;
  info.info.level = 1;

  make_shift(&info);

  ck_assert_int_eq(info.cur_piece.coords.row, 6);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);
  ck_assert_int_eq(info.timer, get_iteration_delay(1));
  ck_assert_int_eq(info.state, Move);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
  for (int i = 0; i < NEXT_ROWS; i++) {
    free(info.info.next[i]);
  }
  free(info.info.next);
}
END_TEST

START_TEST(test_make_shift_cannot_place) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  info.info.next = calloc(NEXT_ROWS, sizeof(int *));
  for (int i = 0; i < NEXT_ROWS; i++) {
    info.info.next[i] = calloc(NEXT_COLS, sizeof(int));
  }
  Piece_t piece1 = {.type = 1, .pos = 0, .coords = {18, 5}};
  Piece_t piece2 = {.type = 2, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece1;
  info.next_piece = piece2;
  info.info.level = 1;

  make_shift(&info);

  ck_assert_int_eq(info.cur_piece.coords.row, 5);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);
  ck_assert_int_eq(info.timer, get_iteration_delay(1));
  ck_assert_int_eq(info.state, Move);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
  for (int i = 0; i < NEXT_ROWS; i++) {
    free(info.info.next[i]);
  }
  free(info.info.next);
}
END_TEST

START_TEST(test_make_move_right) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Right);

  ck_assert_int_eq(info.cur_piece.coords.col, 6);
  ck_assert_int_eq(info.cur_piece.coords.row, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_make_move_left) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Left);

  ck_assert_int_eq(info.cur_piece.coords.col, 4);
  ck_assert_int_eq(info.cur_piece.coords.row, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_make_move_up) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Up);

  ck_assert_int_eq(info.cur_piece.coords.row, 18);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_make_move_down) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Down);

  ck_assert_int_eq(info.cur_piece.coords.row, 6);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_make_move_rotate) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Action);

  ck_assert_int_eq(info.cur_piece.pos, 1);
  ck_assert_int_eq(info.cur_piece.coords.row, 5);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_make_move_default) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  make_move(&info, Start);

  ck_assert_int_eq(info.cur_piece.pos, 0);
  ck_assert_int_eq(info.cur_piece.coords.row, 5);
  ck_assert_int_eq(info.cur_piece.coords.col, 5);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_clear_full_rows_single_row) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  for (int i = 0; i < FIELD_COLS; i++) {
    info.info.field[19][i] = 1;
  }

  for (int i = 2; i < FIELD_ROWS - 1; i++) {
    for (int j = 0; j < FIELD_COLS - 1; j++) {
      info.info.field[i][j] = 2;
    }
  }

  int cleared_rows = clear_full_rows(&info);

  ck_assert_int_eq(cleared_rows, 1);
  ck_assert_int_eq(info.state, Score_up);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      ck_assert_int_eq(info.info.field[i][j], 0);
    }
  }
  for (int i = 3; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS - 1; j++) {
      ck_assert_int_eq(info.info.field[i][j], 2);
    }
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_clear_full_rows_multiple_rows) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  for (int i = 0; i < FIELD_COLS; i++) {
    info.info.field[18][i] = 1;
    info.info.field[19][i] = 1;
  }

  for (int i = 2; i < 18; i++) {
    for (int j = 0; j < FIELD_COLS - 1; j++) {
      info.info.field[i][j] = 3;
    }
  }

  int cleared_rows = clear_full_rows(&info);

  ck_assert_int_eq(cleared_rows, 2);
  ck_assert_int_eq(info.state, Score_up);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      ck_assert_int_eq(info.info.field[i][j], 0);
    }
  }
  for (int i = 4; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS - 1; j++) {
      ck_assert_int_eq(info.info.field[i][j], 3);
    }
  }

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_clear_full_rows_no_full_rows) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }
  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;

  int cleared_rows = clear_full_rows(&info);

  ck_assert_int_eq(cleared_rows, 0);
  ck_assert_int_eq(info.state, Play);

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_clear_full_rows_piece_removal_and_restore) {
  ExpandedGameInfo_t info;
  info.info.field = calloc(FIELD_ROWS, sizeof(int *));
  for (int i = 0; i < FIELD_ROWS; i++) {
    info.info.field[i] = calloc(FIELD_COLS, sizeof(int));
  }

  Piece_t piece = {.type = 1, .pos = 0, .coords = {5, 5}};
  info.cur_piece = piece;
  place_piece(&info.info, piece);

  clear_full_rows(&info);

  ck_assert(is_piece_on_field(&info.info, info.cur_piece));

  for (int i = 0; i < FIELD_ROWS; i++) {
    free(info.info.field[i]);
  }
  free(info.info.field);
}
END_TEST

START_TEST(test_increase_score_basic) {
  GameInfo_t info = {NULL, NULL, 0, 0, 1, 1, 0};
  int count = 1;

  increase_score(&info, count);

  ck_assert_int_eq(info.score, get_points(count));
  ck_assert_int_eq(info.high_score, info.score);
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.speed, 1);
}
END_TEST

START_TEST(test_increase_score_high_score_update) {
  GameInfo_t info = {NULL, NULL, 50, 40, 1, 1, 0};
  int count = 2;

  increase_score(&info, count);

  ck_assert_int_eq(info.score, 50 + get_points(count));
  ck_assert_int_eq(info.high_score, info.score);
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.speed, 1);
}
END_TEST

START_TEST(test_increase_score_level_up) {
  GameInfo_t info = {NULL, NULL, 500, 500, 1, 1, 0};
  int count = 2;

  increase_score(&info, count);

  ck_assert_int_eq(info.score, 500 + get_points(count));
  ck_assert_int_eq(info.high_score, info.score);
  ck_assert_int_eq(info.level, 2);
  ck_assert_int_eq(info.speed, 2);
}
END_TEST

START_TEST(test_increase_score_max_level) {
  GameInfo_t info = {NULL, NULL, 5400, 5400, 9, 9, 0};
  int count = 2;

  increase_score(&info, count);

  ck_assert_int_eq(info.score, 5400 + get_points(count));
  ck_assert_int_eq(info.high_score, info.score);
  ck_assert_int_eq(info.level, 10);
  ck_assert_int_eq(info.speed, 10);
}
END_TEST

START_TEST(test_increase_score_no_level_up) {
  GameInfo_t info = {NULL, NULL, 5400, 5400, 10, 10, 0};
  int count = 2;

  increase_score(&info, count);

  ck_assert_int_eq(info.score, 5400 + get_points(count));
  ck_assert_int_eq(info.high_score, info.score);
  ck_assert_int_eq(info.level, 10);
  ck_assert_int_eq(info.speed, 10);
}
END_TEST

START_TEST(test_handle_states_game_over_to_play) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Play,
                             .prev_state = Game_over};

  handle_states(&info);

  ck_assert_int_eq(info.state, Play);

  ExpandedGameInfo_t *instance = get_instance();
  exit_game(instance);
}
END_TEST

START_TEST(test_handle_states_game_over_to_stop) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Stop,
                             .prev_state = Game_over};

  handle_states(&info);

  ck_assert_int_eq(info.state, Game_over);

  ExpandedGameInfo_t *instance = get_instance();
  exit_game(instance);
}
END_TEST

START_TEST(test_handle_states_begin_to_stop) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Stop,
                             .prev_state = Begin};

  handle_states(&info);

  ck_assert_int_eq(info.state, Begin);

  ExpandedGameInfo_t *instance = get_instance();
  exit_game(instance);
}
END_TEST

START_TEST(test_handle_states_again_to_play) {
  ExpandedGameInfo_t info = {.info = {NULL, NULL, 0, 0, 1, 1, 0},
                             .cur_piece = {0, {0, 0}, 0},
                             .next_piece = {0, {0, 0}, 0},
                             .timer = 0,
                             .state = Again,
                             .prev_state = Game_over};

  handle_states(&info);

  ck_assert_int_eq(info.state, Play);

  ExpandedGameInfo_t *instance = get_instance();
  exit_game(instance);
}
END_TEST

Suite *suite_updating() {
  Suite *s = suite_create("UPDATING");
  TCase *tc = tcase_create("updating_tc");

  // update_timer
  tcase_add_test(tc, test_update_timer_zero_timer);
  tcase_add_test(tc, test_update_timer_positive_timer);
  tcase_add_test(tc, test_update_timer_negative_timer);

  // update_current_piece
  tcase_add_test(tc, test_update_current_piece_updates_correctly);

  // fill_next_piece
  tcase_add_test(tc, test_fill_next_piece_empty);
  tcase_add_test(tc, test_fill_next_piece_already_placed);

  // make_shift
  tcase_add_test(tc, test_make_shift_down);
  tcase_add_test(tc, test_make_shift_cannot_place);

  // make_move
  tcase_add_test(tc, test_make_move_right);
  tcase_add_test(tc, test_make_move_left);
  tcase_add_test(tc, test_make_move_up);
  tcase_add_test(tc, test_make_move_down);
  tcase_add_test(tc, test_make_move_rotate);
  tcase_add_test(tc, test_make_move_default);

  // clear_full_rows
  tcase_add_test(tc, test_clear_full_rows_single_row);
  tcase_add_test(tc, test_clear_full_rows_multiple_rows);
  tcase_add_test(tc, test_clear_full_rows_no_full_rows);
  tcase_add_test(tc, test_clear_full_rows_piece_removal_and_restore);

  // increase_score
  tcase_add_test(tc, test_increase_score_basic);
  tcase_add_test(tc, test_increase_score_high_score_update);
  tcase_add_test(tc, test_increase_score_level_up);
  tcase_add_test(tc, test_increase_score_max_level);
  tcase_add_test(tc, test_increase_score_no_level_up);

  // handle_states
  tcase_add_test(tc, test_handle_states_game_over_to_play);
  tcase_add_test(tc, test_handle_states_game_over_to_stop);
  tcase_add_test(tc, test_handle_states_begin_to_stop);
  tcase_add_test(tc, test_handle_states_again_to_play);

  suite_add_tcase(s, tc);
  return s;
}
