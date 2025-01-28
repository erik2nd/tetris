/**
 * @file frontend.c
 * @brief Source file for tetris frontend
 */

#include "frontend.h"

void init_ncurses() {
  initscr();
  noecho();
  timeout(0);
  curs_set(0);
  keypad(stdscr, TRUE);
}

void cleanup() {
  wclear(stdscr);
  endwin();
  printf("The program is completed. The terminal has been restored.\n");
}

void init_wins(WINDOW **info, WINDOW **field, WINDOW **score, WINDOW **level,
               WINDOW **next) {
  *info =
      newwin(WIN_HEIGHT, WIN_WIDTH * 2 + 1, WIN_Y, WIN_X - WIN_WIDTH / 2 - 1);
  *field = newwin(WIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X - WIN_WIDTH / 2 - 1);
  *score = newwin(SUBWIN_HEIGHT, WIN_WIDTH, WIN_Y, WIN_X + WIN_WIDTH / 2);
  *level = newwin(SUBWIN_HEIGHT, WIN_WIDTH, WIN_Y + SUBWIN_HEIGHT,
                  WIN_X + WIN_WIDTH / 2);
  *next = newwin(NEXT_HEIGHT, WIN_WIDTH, WIN_Y + 2 * SUBWIN_HEIGHT,
                 WIN_X + WIN_WIDTH / 2);
}

void clear_wins(WINDOW *info, WINDOW *field, WINDOW *score, WINDOW *level,
                WINDOW *next) {
  wclear(info);
  wclear(field);
  wclear(score);
  wclear(level);
  wclear(next);
  wrefresh(info);
  wrefresh(field);
  wrefresh(score);
  wrefresh(level);
  wrefresh(next);
}

void print_field(WINDOW *win, int **field) {
  werase(win);
  box(win, 0, 0);

  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      if (field[i][j]) {
        int pair_number = piece_color(field[i][j]);
        wattron(win, COLOR_PAIR(pair_number));
        mvwprintw(win, i + 1, j * 2 + 1, "  ");
        wattroff(win, COLOR_PAIR(pair_number));
      }
    }
  }

  wnoutrefresh(win);
}

void print_level(WINDOW *win, int level, int speed) {
  werase(win);
  box(win, 0, 0);

  char text[20] = "";
  sprintf(text, "Level:  %d", level);
  mvwprintw(win, 2, 5, "%s", text);

  float value = get_speed(speed);
  if ((int)(value * 100) % 100 == 0) {
    sprintf(text, "Speed:  %dx", (int)value);
  } else {
    sprintf(text, "Speed:  %.2fx", value);
  }
  mvwprintw(win, 4, 5, "%s", text);

  wnoutrefresh(win);
}

void print_score(WINDOW *win, int score, int high_score) {
  werase(win);
  box(win, 0, 0);

  char text[20] = "";
  sprintf(text, "Score:  %d", score);
  mvwprintw(win, 2, 5, "%s", text);

  sprintf(text, "Best:   %d", high_score);
  mvwprintw(win, 4, 5, "%s", text);

  wnoutrefresh(win);
}

void print_next(WINDOW *win, int **next) {
  werase(win);
  box(win, 0, 0);

  mvwprintw(win, 2, 8, "Next: ");

  for (int i = 0; i < NEXT_ROWS; i++) {
    for (int j = 0; j < NEXT_COLS; j++) {
      if (next[i][j]) {
        int pair_number = piece_color(next[i][j]);
        wattron(win, COLOR_PAIR(pair_number));
        mvwprintw(win, i + 1 + 3, j * 2 + 1 + 5, "  ");
        wattroff(win, COLOR_PAIR(pair_number));
      }
    }
  }

  wnoutrefresh(win);
}

void print_game(WINDOW *field, WINDOW *score, WINDOW *level, WINDOW *next,
                GameInfo_t info) {
  print_field(field, info.field);
  print_score(score, info.score, info.high_score);
  print_level(level, info.level, info.speed);
  print_next(next, info.next);
  doupdate();
}

void print_title(WINDOW *win, int height, int coord, const char *text[],
                 int color) {
  wattron(win, COLOR_PAIR(color));
  for (int i = 0; i < height; i++) {
    mvwprintw(win, i + WIN_HEIGHT / 2 - height / 2 - 1, coord, "%s", text[i]);
  }
  wattroff(win, COLOR_PAIR(color));
}

void print_start(WINDOW *win) {
  box(win, 0, 0);

  const char *T_letter[] = {"######", "  ##   ", "  ##   ", "  ##   ",
                            "  ##   "};
  const char *E_letter[] = {"#####", "##   ", "#### ", "##   ", "#####"};
  const char *R_letter[] = {"##### ", "##  ##", "##### ", "##  ##", "##  ##"};
  const char *I_letter[] = {"######", "  ##  ", "  ##  ", "  ##  ", "######"};
  const char *S_letter[] = {" #### ", "##    ", " #### ", "    ##", " #### "};

  print_title(win, 5, 2, T_letter, RED_FONT);
  print_title(win, 5, 9, E_letter, YELLOW_FONT);
  print_title(win, 5, 15, T_letter, GREEN_FONT);
  print_title(win, 5, 22, R_letter, CYAN_FONT);
  print_title(win, 5, 29, I_letter, BLUE_FONT);
  print_title(win, 5, 36, S_letter, MAGENTA_FONT);

  mvwprintw(win, 17, 14, "Press S to play");

  wrefresh(win);
}

void print_game_over(WINDOW *win) {
  box(win, 0, 0);
  wattron(win, COLOR_PAIR(GREEN_FONT));

  const char *text[] = {
      " ####   ####  ##   # #####", "##     ##  ## ### ## ##   ",
      "## ### ###### ## # # #### ", "##  ## ##  ## ##   # ##   ",
      " ####  ##  ## ##   # #####", "                          ",
      " ####  ##  ## ##### ##### ", "##  ## ##  ## ##    ##  ##",
      "##  ## ##  ## ####  ##### ", "##  ##  ####  ##    ##  ##",
      " ####    ##   ##### ##  ##"};

  print_title(win, 11, 9, text, GREEN_FONT);

  mvwprintw(win, 18, 12, "Press S to play again");

  wrefresh(win);
}

void print_pause(WINDOW *win) {
  box(win, 0, 0);
  wattron(win, COLOR_PAIR(BLUE_FONT));

  const char *text[] = {
      "#####   ####  ##  ##  ####  #####", "##  ## ##  ## ##  ## ##     ##   ",
      "#####  ###### ##  ##  ####  #### ", "##     ##  ## ##  ##     ## ##   ",
      "##     ##  ##  ####   ####  #####"};

  print_title(win, 5, 6, text, BLUE_FONT);

  mvwprintw(win, 17, 13, "Press S to continue");

  wrefresh(win);
}

float get_speed(int speed) {
  float first = (11 - 1) * 0.05;
  float value = (11 - speed) * 0.05;
  return first / value;
}

void init_colorpairs() {
  for (int color = 0; color <= 7; color++) {
    init_pair(color, curs_color(color), curs_color(color));
  }
  for (int color = 8; color <= 13; color++) {
    init_pair(color, curs_color(color - 7), COLOR_BLACK);
  }
}

short curs_color(int color) {
  short res = 0;
  switch (7 & color) { /* RGB */
    case 0:            /* 000 */
      res = (COLOR_BLACK);
      break;
    case 1: /* 001 */
      res = (COLOR_BLUE);
      break;
    case 2: /* 010 */
      res = (COLOR_GREEN);
      break;
    case 3: /* 011 */
      res = (COLOR_CYAN);
      break;
    case 4: /* 100 */
      res = (COLOR_RED);
      break;
    case 5: /* 101 */
      res = (COLOR_MAGENTA);
      break;
    case 6: /* 110 */
      res = (COLOR_YELLOW);
      break;
    case 7: /* 111 */
      res = (COLOR_WHITE);
      break;
  }
  return res;
}

int piece_color(int piece) {
  int res = 0;
  switch (piece) {
    case O:
      res = MAGENTA;
      break;
    case I:
      res = RED;
      break;
    case S:
      res = GREEN;
      break;
    case Z:
      res = CYAN;
      break;
    case L:
      res = WHITE;
      break;
    case J:
      res = YELLOW;
      break;
    case T:
      res = BLUE;
      break;
  }
  return res;
}
