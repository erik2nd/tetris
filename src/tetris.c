/**
 * @file tetris.c
 * @brief Tetris main source file
 */

#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

/**
 * @brief Main game loop for the Tetris game.
 *
 * This function represents the main game loop for the Tetris game. It
 * initializes the game windows, sets up the game state, and handles user input
 * and game state updates. The function uses various helper functions to manage
 * the game state, print the game interface, and handle user actions.
 *
 * @see init_wins
 * @see cleanup
 * @see get_instance
 * @see print_start
 * @see print_pause
 * @see userInput
 * @see user_action
 * @see clear_wins
 * @see sleep_ms
 * @see print_game_over
 * @see print_game
 * @see updateCurrentState
 */
void tetris();

/**
 * @brief Main function to start the Tetris game.
 *
 * This function initializes the ncurses library, sets up the color pairs, and
 * starts the Tetris game.
 *
 * @return int The exit status of the program.
 *
 * @see init_ncurses
 * @see init_colorpairs
 * @see tetris
 */
int main() {
  init_ncurses();
  start_color();
  init_colorpairs();
  bkgdset(COLOR_PAIR(BLACK));

  tetris();

  return 0;
}

void tetris() {
  WINDOW *aux = NULL, *field = NULL, *score = NULL, *level = NULL, *next = NULL;
  init_wins(&aux, &field, &score, &level, &next);
  refresh();

  atexit(cleanup);

  ExpandedGameInfo_t *info = get_instance();

  while (info->state != Exit) {
    if (info->state == Begin) print_start(aux);

    if (info->state == Stop) print_pause(aux);

    userInput(user_action(getch()), false);

    if (info->state != info->prev_state) {
      clear_wins(aux, field, score, level, next);
      sleep_ms(DELAY);
    }

    if (info->state == Game_over) print_game_over(aux);

    if (info->state == Play)
      print_game(field, score, level, next, updateCurrentState());
  }
}

/**
 * @mainpage Tetris Game Documentation
 *
 * Welcome to the documentation for the Tetris game! This documentation provides
 * an overview of the game's structure, functions, and classes.
 *
 * ## Overview
 *
 * The Tetris game is a classic puzzle game where players manipulate falling
 * tetrominoes to create complete lines. This implementation uses the ncurses
 * library for the terminal user interface.
 *
 * ## Key features
 *
 * - A finite state machine is used to formalize the logic of the game
 * - The program is developed according to the principles of structured
 * programming
 * - The library (implementing the logic of the game) code is placed in the
 * `src/brick_game/tetris` folder
 * - The program interface code is in the `src/gui/cli` folder
 *
 * ## Game mechanics
 *
 * - Rotation of piece
 * - Horizontal movement of pieces
 * - Acceleration of the piece's fall
 * - Level and speed mechanic
 * - Score and high score mechanic
 * - Displaying the next piece
 * - Destruction of filled rows
 * - End of the game when the top of the board is reached
 *
 * ## Control buttons
 *
 * - `s` — start
 * - `p` — pause
 * - `q` — exit
 * - Left arrow — move piece to the left
 * - Right arrow — move piece to the right
 * - Down arrow — accelerate piece
 * - Up arrow — rotate piece
 * - Space — drop piece
 *
 * @author Erik
 * @date 01.10.2024
 */
