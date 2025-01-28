/**
 * @file backend.c
 * @brief Source file for tetris backend
 */

#include "backend.h"

UserAction_t user_action(int key) {
  UserAction_t action;
  switch (key) {
    case 's':
    case 'S':
      action = Start;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Action;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case ' ':
      action = Up;
      break;
    default:
      action = -1;
      break;
  }
  return action;
}

ExpandedGameInfo_t *get_instance() {
  static ExpandedGameInfo_t instance;
  static int game_number = 0;
  if (instance.info.field == NULL) {
    instance.info.field = calloc(FIELD_ROWS, sizeof(int *));
    for (int i = 0; i < FIELD_ROWS; i++) {
      instance.info.field[i] = calloc(FIELD_COLS, sizeof(int));
    }
    instance.info.next = calloc(NEXT_ROWS, sizeof(int *));
    for (int i = 0; i < NEXT_ROWS; i++) {
      instance.info.next[i] = calloc(NEXT_COLS, sizeof(int));
    }

    instance.info.score = INIT_SCORE;
    instance.info.high_score = load_high_score();
    instance.info.level = INIT_LEVEL;
    instance.info.speed = instance.info.level;
    instance.info.pause = 0;

    srand(time(NULL) ^ getpid());
    instance.cur_piece = random_piece();
    instance.next_piece = random_piece();
    fill_next_piece(&instance.info, instance.next_piece);
    instance.timer = INIT_TIMER;
    if (game_number) {
      instance.state = -1;
      instance.prev_state = Game_over;
    } else {
      instance.state = Begin;
      instance.prev_state = Begin;
    }
    game_number++;
  }
  return &instance;
}

bool is_beyond_bounds(int row, int col) {
  bool res = false;
  if (row < 0 || row >= FIELD_ROWS || col < 0 || col >= FIELD_COLS) res = true;
  return res;
}

bool can_place(GameInfo_t *info, Piece_t piece) {
  bool res = true;
  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    if (is_beyond_bounds(row, col) || info->field[row][col]) {
      res = false;
      break;
    }
  }
  return res;
}

void place_piece(GameInfo_t *info, Piece_t piece) {
  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    info->field[row][col] = piece.type;
  }
}

void remove_piece(GameInfo_t *info, Piece_t piece) {
  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    info->field[row][col] = 0;
  }
}

void move_piece_side(GameInfo_t *info, Piece_t *piece, int shift) {
  remove_piece(info, *piece);
  piece->coords.col += shift;
  if (!can_place(info, *piece)) piece->coords.col -= shift;
  place_piece(info, *piece);
}

void move_piece_down(GameInfo_t *info, Piece_t *piece) {
  remove_piece(info, *piece);
  piece->coords.row++;
  if (!can_place(info, *piece)) piece->coords.row--;
  place_piece(info, *piece);
}

void drop_piece(GameInfo_t *info, Piece_t *piece) {
  remove_piece(info, *piece);
  while (can_place(info, *piece)) piece->coords.row++;
  piece->coords.row--;
  place_piece(info, *piece);
}

void rotate_piece(GameInfo_t *info, Piece_t *piece) {
  remove_piece(info, *piece);
  int back = piece->pos;
  piece->pos = (piece->pos + 1) % POS_COUNT;
  if (!can_place(info, *piece)) piece->pos = back;
  place_piece(info, *piece);
}

bool is_row_full(GameInfo_t *info, int row) {
  bool res = true;
  for (int j = 0; j < FIELD_COLS; j++) {
    if (!info->field[row][j]) {
      res = false;
      break;
    }
  }
  return res;
}

int clear_full_rows(ExpandedGameInfo_t *info) {
  int count = 0;
  bool erase = false;
  if (is_piece_on_field(&info->info, info->cur_piece)) {
    erase = true;
    remove_piece(&info->info, info->cur_piece);
  }
  for (int i = FIELD_ROWS - 1; i >= 0; i--) {
    if (is_row_full(&info->info, i)) {
      count++;
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < FIELD_COLS; j++) {
          info->info.field[k][j] = info->info.field[k - 1][j];
        }
      }
      for (int j = 0; j < FIELD_COLS; j++) {
        info->info.field[0][j] = 0;
      }
      i++;
    }
  }
  if (erase) place_piece(&info->info, info->cur_piece);
  if (count)
    info->state = Score_up;
  else
    info->state = Play;
  return count;
}

bool is_piece_on_field(GameInfo_t *info, Piece_t piece) {
  int res = true;
  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, piece.pos, i);
    int row = piece.coords.row + shift.row;
    int col = piece.coords.col + shift.col;
    if (info->field[row][col] != piece.type) {
      res = false;
      break;
    }
  }
  return res;
}

bool is_game_over(ExpandedGameInfo_t *info) {
  bool res = false, erase = false;
  if (is_piece_on_field(&info->info, info->cur_piece)) {
    erase = true;
    remove_piece(&info->info, info->cur_piece);
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 3; j < 7; j++) {
      if (info->info.field[i][j]) {
        res = true;
        break;
      }
    }
  }
  if (erase) place_piece(&info->info, info->cur_piece);
  return res;
}

int get_iteration_delay(int level) { return ((11 - level) * 0.05) * 1000; }

void update_timer(ExpandedGameInfo_t *info) {
  info->timer -= DELAY;
  if (info->timer <= 0)
    info->state = Shift;
  else
    info->state = Move;
}

void make_shift(ExpandedGameInfo_t *info) {
  remove_piece(&info->info, info->cur_piece);
  info->cur_piece.coords.row++;
  if (!can_place(&info->info, info->cur_piece)) {
    info->cur_piece.coords.row--;
    place_piece(&info->info, info->cur_piece);
    update_current_piece(info);
  }
  info->timer = get_iteration_delay(info->info.level);
  if (can_place(&info->info, info->cur_piece))
    place_piece(&info->info, info->cur_piece);
  info->state = Move;
}

void update_current_piece(ExpandedGameInfo_t *info) {
  info->cur_piece = info->next_piece;
  info->next_piece = random_piece();
  fill_next_piece(&info->info, info->next_piece);
}

Piece_t random_piece() {
  Piece_t res;
  res.type = 1 + (rand() % PIECE_COUNT);
  res.coords.row = 0;
  res.coords.col = 5;
  res.pos = 0;
  return res;
}

void fill_next_piece(GameInfo_t *info, Piece_t piece) {
  for (int i = 0; i < NEXT_ROWS; i++) {
    for (int j = 0; j < NEXT_COLS; j++) {
      info->next[i][j] = 0;
    }
  }
  for (int i = 0; i < PIECE_SIZE; i++) {
    Coordinate_t shift = get_piece_shifts(piece.type, 0, i);
    int row = shift.row;
    int col = 2 + shift.col;
    info->next[row][col] = piece.type;
  }
}

void make_move(ExpandedGameInfo_t *info, UserAction_t action) {
  switch (action) {
    case Right:
      move_piece_side(&info->info, &info->cur_piece, RIGHT);
      break;
    case Left:
      move_piece_side(&info->info, &info->cur_piece, LEFT);
      break;
    case Up:
      drop_piece(&info->info, &info->cur_piece);
      break;
    case Down:
      move_piece_down(&info->info, &info->cur_piece);
      break;
    case Action:
      rotate_piece(&info->info, &info->cur_piece);
      break;
    default:
      break;
  }
}

void increase_score(GameInfo_t *info, int count) {
  info->score += get_points(count);
  if (info->high_score < info->score) {
    info->high_score = info->score;
    save_high_score(info);
  }
  if (info->level < 10) {
    while (info->score >= get_level_boundary(info->level)) {
      info->level++;
      info->speed++;
    }
  }
}

int get_points(int count) {
  const int points[] = {0, 100, 300, 700, 1500};
  return points[count];
}

int get_level_boundary(int level) { return level * 600; }

Coordinate_t get_piece_shifts(int piece, int pos, int num) {
  static const Coordinate_t shifts[PIECE_COUNT][POS_COUNT][PIECE_SIZE] = {
      // O
      {{{0, -1}, {0, 0}, {1, -1}, {1, 0}},
       {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
       {{0, -1}, {0, 0}, {1, -1}, {1, 0}},
       {{0, -1}, {0, 0}, {1, -1}, {1, 0}}},
      // I
      {{{0, -2}, {0, -1}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
       {{0, -2}, {0, -1}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}},
      // S
      {{{1, -1}, {1, 0}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
       {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}},
      // Z
      {{{0, -1}, {0, 0}, {1, 0}, {1, 1}},
       {{-1, 1}, {0, 1}, {0, 0}, {1, 0}},
       {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
       {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}},
      // L
      {{{1, -1}, {0, -1}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
       {{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
       {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}},
      // J
      {{{0, -1}, {0, 0}, {0, 1}, {1, 1}},
       {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}},
       {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {1, 0}, {1, -1}}},
      // T
      {{{0, -1}, {0, 0}, {0, 1}, {1, 0}},
       {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
       {{-1, 0}, {0, -1}, {0, 0}, {0, 1}},
       {{-1, 0}, {0, 0}, {1, 0}, {0, -1}}}};
  return shifts[piece - 1][pos][num];
}

int load_high_score() {
  int high_score = 0;
  FILE *file = fopen(FILE_PATH, "r");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void save_high_score(GameInfo_t *info) {
  FILE *file = fopen(FILE_PATH, "w");
  if (file != NULL) {
    fprintf(file, "%d", info->high_score);
    fclose(file);
  }
}

void userInput(UserAction_t action, bool hold) {
  ExpandedGameInfo_t *info = get_instance();
  info->prev_state = info->state;
  if (hold) info->state = -1;
  if (action == Terminate) {
    info->state = Exit;
    exit_game(info);
    return;
  }
  if (action == Pause) {
    info->info.pause = 1;
    info->state = Stop;
  }
  if (action == Start) {
    info->info.pause = 0;
    info->state = Play;
  }
  if (info->state == Play) {
    update_timer(info);
    if (info->state == Shift) make_shift(info);
    if (info->state == Move) make_move(info, action);
    int rows = clear_full_rows(info);
    if (info->state == Score_up) {
      increase_score(&info->info, rows);
      info->state = Play;
    }
    sleep_ms(DELAY);
  }
  if (is_game_over(info)) {
    info->state = Game_over;
    clear_field(&info->info);
  }
  handle_states(info);
}

GameInfo_t updateCurrentState() {
  ExpandedGameInfo_t *info = get_instance();
  return info->info;
}

void handle_states(ExpandedGameInfo_t *info) {
  if (info->prev_state == Game_over) {
    if (info->state == Play) info->state = Again;
    if (info->state == Stop) info->state = Game_over;
  }

  if (info->prev_state == Begin && info->state == Stop) info->state = Begin;

  if (info->state == Again) {
    reset_game(info);
    info->state = Play;
  }
}

void sleep_ms(int ms) { usleep(ms * 1000); }

void clear_field(GameInfo_t *info) {
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      info->field[i][j] = 0;
    }
  }
}

void reset_game(ExpandedGameInfo_t *info) {
  exit_game(info);
  info = get_instance();
}

void exit_game(ExpandedGameInfo_t *info) {
  if (info->info.field != NULL) {
    for (int i = 0; i < FIELD_ROWS; i++) {
      free(info->info.field[i]);
    }
    free(info->info.field);
    info->info.field = NULL;
  }
  if (info->info.next != NULL) {
    for (int i = 0; i < NEXT_ROWS; i++) {
      free(info->info.next[i]);
    }
    free(info->info.next);
    info->info.next = NULL;
  }
}
