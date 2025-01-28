/**
 * @file frontend.h
 * @brief Tetris frontend header file
 */

#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <ncurses.h>
#include <stdlib.h>

#include "../../brick_game/tetris/defines.h"
#include "../../brick_game/tetris/objects.h"

#define WIN_HEIGHT 22
#define WIN_WIDTH 22

#define SUBWIN_HEIGHT 7
#define NEXT_HEIGHT 8

#define WIN_Y (LINES - WIN_HEIGHT) / 2
#define WIN_X (COLS - WIN_WIDTH) / 2

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define WHITE 7

#define BLUE_FONT 8
#define GREEN_FONT 9
#define CYAN_FONT 10
#define RED_FONT 11
#define MAGENTA_FONT 12
#define YELLOW_FONT 13

#define O 1
#define I 2
#define S 3
#define Z 4
#define L 5
#define J 6
#define T 7

/**
 * @brief Initializes the ncurses library.
 *
 * This function initializes the ncurses library, which is used for creating
 * text-based user interface in the terminal. It sets up the terminal for
 * non-blocking input, disables echoing of input characters, hides the cursor,
 * and enables the use of special keys (like arrow keys) for input.
 */
void init_ncurses();
/**
 * @brief Cleans up and restores the terminal after the program completes.
 *
 * This function clears the terminal screen, restores the terminal to its normal
 * state, and prints a message indicating that the program has completed. It
 * should be called before the program exits to ensure that the terminal is
 * properly restored.
 */
void cleanup();

/**
 * @brief Initializes the windows for the game interface.
 *
 * This function creates and initializes the windows for the game interface,
 * including the main game field, the score display, the level display, and the
 * next piece display. Each window is created with specific dimensions and
 * positions relative to the terminal screen.
 *
 * @param info  Pointer to the window for current state information.
 * @param field Pointer to the window for the game field.
 * @param score Pointer to the window for the score display.
 * @param level Pointer to the window for the level display.
 * @param next  Pointer to the window for the next piece display.
 *
 */
void init_wins(WINDOW **info, WINDOW **playground, WINDOW **score,
               WINDOW **level, WINDOW **next);
/**
 * @brief Clears and refreshes the game windows.
 *
 * This function clears the contents of the game windows and refreshes them to
 * ensure that the terminal screen is updated. It clears the main game field,
 * the score display, the level display, and the next piece display.
 *
 * @param info  Pointer to the window for current state information.
 * @param field Pointer to the window for the game field.
 * @param score Pointer to the window for the score display.
 * @param level Pointer to the window for the level display.
 * @param next  Pointer to the window for the next piece display.
 */
void clear_wins(WINDOW *info, WINDOW *playground, WINDOW *score, WINDOW *level,
                WINDOW *next);

/**
 * @brief Prints a title in a specified window with a given color.
 *
 * This function prints a title in the specified window at a given vertical
 * coordinate. The title is printed with a specified color and consists of
 * multiple lines of text. The function iterates through the lines of text and
 * prints each one at the appropriate position in the window.
 *
 * @param win    Pointer to the window where the title will be printed.
 * @param height The number of lines in the title.
 * @param coord  The horizontal coordinate where the title will be printed.
 * @param text   Array of strings representing the lines of the title.
 * @param color  The color pair to use for printing the title.
 */
void print_title(WINDOW *win, int height, int coord, const char *text[],
                 int color);
/**
 * @brief Prints the "TETRIS" title.
 *
 * This function prints the "TETRIS" title in a specified window using different
 * colors for each letter. It also prints a prompt to start the game below the
 * title. The function uses the `print_title` function to print each letter.
 *
 * @param win Pointer to the window where the title and prompt will be printed.
 *
 * @see print_title
 */
void print_start(WINDOW *win);
/**
 * @brief Prints the "PAUSE" title.
 *
 * This function prints the "PAUSE" title in a specified window using a blue
 * color. It also prints a prompt to continue the game below the title. The
 * function uses the `print_title` function to print the title.
 *
 * @param win Pointer to the window where the title and prompt will be printed.
 *
 * @see print_title
 */
void print_pause(WINDOW *win);
/**
 * @brief Prints the "GAME OVER" title.
 *
 * This function prints the "GAME OVER" title in a specified window using a
 * green color. It also prints a prompt to play again below the title. The
 * function uses the `print_title` function to print the title.
 *
 * @param win Pointer to the window where the title and prompt will be printed.
 *
 * @see print_title
 */
void print_game_over(WINDOW *win);
/**
 * @brief Prints the game information in the specified windows.
 *
 * This function prints the current game state in the specified windows,
 * including the game field, the score, the level, and the next piece. It uses
 * the `print_field`, `print_score`, `print_level`, and `print_next` functions
 * to print the respective parts of the game state.
 *
 * @param field Pointer to the window where the game field will be printed.
 * @param score Pointer to the window where the score will be printed.
 * @param level Pointer to the window where the level will be printed.
 * @param next  Pointer to the window where the next piece will be printed.
 * @param info  The `GameInfo_t` structure containing the game state.
 *
 * @see print_field
 * @see print_score
 * @see print_level
 * @see print_next
 */
void print_game(WINDOW *playground, WINDOW *score, WINDOW *level, WINDOW *next,
                GameInfo_t info);

/**
 * @brief Prints the game field in the specified window.
 *
 * This function prints the game field in the specified window, using different
 * colors for each type of piece. It iterates through the game field and prints
 * each piece at the appropriate position in the window. The function uses the
 * `piece_color` function to determine the color of each piece.
 *
 * @param win   Pointer to the window where the game field will be printed.
 * @param field The matrix representing the game field.
 *
 * @see piece_color
 */
void print_field(WINDOW *win, int **);
/**
 * @brief Prints the current score and high score in the specified window.
 *
 * This function prints the current score and high score in the specified
 * window. It formats the scores into strings and prints them at the appropriate
 * positions in the window.
 *
 * @param win        Pointer to the window where the scores will be printed.
 * @param score      The current score.
 * @param high_score The high score.
 */
void print_score(WINDOW *win, int score, int high_score);
/**
 * @brief Prints the current level and speed in the specified window.
 *
 * This function prints the current level and speed in the specified window. It
 * formats the level and speed into strings and prints them at the appropriate
 * positions in the window. The speed is calculated using the `get_speed`
 * function and formatted accordingly.
 *
 * @param win   Pointer to the window where the level and speed will be printed.
 * @param level The current level.
 * @param speed The current speed.
 *
 * @see get_speed
 */
void print_level(WINDOW *win, int level, int speed);
/**
 * @brief Prints the next piece in the specified window.
 *
 * This function prints the next piece in the specified window, using different
 * colors for each type of piece. It iterates through the next piece array and
 * prints each block at the appropriate position in the window. The function
 * uses the `piece_color` function to determine the color of each block.
 *
 * @param win  Pointer to the window where the next piece will be printed.
 * @param next The matrix representing the next piece.
 *
 * @see piece_color
 */
void print_next(WINDOW *win, int **next);
/**
 * @brief Calculates the game speed based on the current level.
 *
 * This function calculates the game speed based on the current level. The speed
 * is calculated as a ratio of the initial speed to the current speed.
 *
 * @param speed The current speed level.
 * @return float The calculated game speed.
 */
float get_speed(int speed);

/**
 * @brief Initializes color pairs for the ncurses library.
 *
 * This function initializes color pairs for the ncurses library, which are used
 * to display text and blocks in different colors. The function sets up color
 * pairs for both foreground and background colors, as well as for foreground
 * colors with a black background.
 *
 * @see curs_color
 */
void init_colorpairs();
/**
 * @brief Converts a color code to a corresponding ncurses color constant.
 *
 * This function converts a color code to a corresponding ncurses color
 * constant. The color code is a 3-bit value representing the RGB components of
 * the color. The function uses a switch statement to map each color code to the
 * appropriate ncurses color constant.
 *
 * @param color The color code to convert.
 * @return short The corresponding ncurses color constant.
 */
short curs_color(int color);
/**
 * @brief Returns the color code for a given piece type.
 *
 * This function returns the color code for a given piece type. The color code
 * is used to determine the color of the piece when it is displayed on the
 * screen. The function uses a switch statement to map each piece type to the
 * appropriate color code.
 *
 * @param piece The type of the piece.
 * @return int The color code for the piece.
 */
int piece_color(int piece);

#endif
