/**
 * @file backend.h
 * @brief Tetris backend header file
 */

#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#define _XOPEN_SOURCE 500

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "defines.h"
#include "objects.h"

/**
 * @brief Processes user input and updates the game state accordingly.
 *
 * This function processes user input and updates the game state based on the
 * input action. The function handles various actions such as terminating the
 * game, pausing the game, starting the game, and moving or rotating the current
 * piece. It also updates the game timer, performs shift operations, clears full
 * rows, and checks if the game is over.
 *
 * @param action The `UserAction_t` representing the user action to be
 * processed.
 * @param hold A boolean indicating whether the action is a hold action (not
 * used)
 *
 * @see UserAction_t
 * @see get_instance
 * @see exit_game
 * @see update_timer
 * @see make_shift
 * @see make_move
 * @see clear_full_rows
 * @see increase_score
 * @see sleep_ms
 * @see is_game_over
 * @see clear_field
 * @see handle_states
 */
void userInput(UserAction_t action, bool hold);
/**
 * @brief Returns the current game state.
 *
 * This function retrieves the current game state by calling the `get_instance`
 * function, which returns a pointer to the `ExpandedGameInfo_t` structure
 * containing the game state. The function then returns the `GameInfo_t`
 * structure embedded within the `ExpandedGameInfo_t` structure.
 *
 * @return GameInfo_t The current game state.
 *
 * @see GameInfo_t
 * @see ExpandedGameInfo_t
 * @see get_instance
 */
GameInfo_t updateCurrentState();

/**
 * @brief Determines the user action based on the input key.
 *
 * This function maps specific key inputs to corresponding user actions. The
 * keys can be either lowercase or uppercase letters, or special key codes. The
 * function returns an enumerated type `UserAction_t` that represents the action
 * associated with the input key.
 *
 * @param key The input key code. This can be a character (e.g., 's', 'S', 'p',
 * 'P', etc.) or a special key code (e.g., KEY_LEFT, KEY_RIGHT, etc.).
 * @return UserAction_t The action associated with the input key. Returns `-1`
 * if the key is not recognized.
 *
 * @see UserAction_t
 */
UserAction_t user_action(int);
/**
 * @brief Returns a singleton instance of the `ExpandedGameInfo_t` structure.
 *
 * This function initializes and returns a singleton instance of the
 * `ExpandedGameInfo_t` structure. The instance is created only once and reused
 * for subsequent calls. The function also initializes various game-related
 * fields and settings, such as the game field, next piece, score, level, and
 * other game states.
 *
 * @return ExpandedGameInfo_t* A pointer to the singleton instance of
 * `ExpandedGameInfo_t`.
 *
 * @see ExpandedGameInfo_t
 * @see random_piece
 * @see fill_next_piece
 * @see load_high_score
 */
ExpandedGameInfo_t* get_instance();

/**
 * @brief Checks if a given row and column are beyond the bounds of the game
 * field.
 *
 * This function determines whether the specified row and column are outside the
 * valid range of the game field.
 *
 * @param row The row index to check.
 * @param col The column index to check.
 * @return bool `true` if the row or column is beyond the bounds of the game
 * field, otherwise `false`.
 */
bool is_beyond_bounds(int row, int col);
/**
 * @brief Checks if a given piece is on the game field.
 *
 * This function verifies whether a specified piece is positioned on the game
 * field.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece The `Piece_t` structure representing the piece to be checked.
 * @return bool `true` if the piece is on the game field, otherwise `false`.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see get_piece_shifts
 */
bool is_piece_on_field(GameInfo_t* info, Piece_t piece);
/**
 * @brief Checks if a specified row in the game field is completely filled.
 *
 * This function determines whether a given row in the game field is fully
 * occupied by pieces.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param row The row index to check.
 * @return bool `true` if the row is completely filled, otherwise `false`.
 *
 * @see GameInfo_t
 */
bool is_row_full(GameInfo_t* info, int row);
/**
 * @brief Checks if the game is over by determining if any piece has reached the
 * top rows of the game field.
 *
 * This function checks if the game is over by examining the top rows of the
 * game field.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game state.
 * @return bool `true` if the game is over, otherwise `false`.
 *
 * @see ExpandedGameInfo_t
 * @see is_piece_on_field
 * @see remove_piece
 * @see place_piece
 */
bool is_game_over(ExpandedGameInfo_t* info);
/**
 * @brief Checks if a given piece can be placed on the game field without
 * overlapping or going out of bounds.
 *
 * This function determines whether a specified piece can be placed on the game
 * field without overlapping with existing pieces or going out of the field's
 * bounds.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece The `Piece_t` structure representing the piece to be checked.
 * @return bool `true` if the piece can be placed on the game field, otherwise
 * `false`.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see get_piece_shifts
 * @see is_beyond_bounds
 */
bool can_place(GameInfo_t* info, Piece_t piece);

/**
 * @brief Places a given piece on the game field.
 *
 * This function places a specified piece on the game field by iterating through
 * each block of the piece and setting the corresponding cell in the game field
 * to the piece's type.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece The `Piece_t` structure representing the piece to be placed.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see get_piece_shifts
 * @see can_place
 */
void place_piece(GameInfo_t* info, Piece_t piece);
/**
 * @brief Removes a given piece from the game field.
 *
 * This function removes a specified piece from the game field by iterating
 * through each block of the piece and setting the corresponding cell in the
 * game field to 0.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece The `Piece_t` structure representing the piece to be removed.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see get_piece_shifts
 */
void remove_piece(GameInfo_t* info, Piece_t piece);

/**
 * @brief Moves a given piece sideways on the game field.
 *
 * This function attempts to move a specified piece sideways by a given shift
 * amount. It first removes the piece from the game field, adjusts the piece's
 * column coordinate by the shift amount, and then checks if the piece can be
 * placed in the new position using the `can_place` function. If the piece
 * cannot be placed in the new position, the column coordinate is reverted to
 * its original value. Finally, the piece is placed back on the game field.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece A pointer to the `Piece_t` structure representing the piece to
 * be moved.
 * @param shift The amount by which to shift the piece's column coordinate.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see remove_piece
 * @see can_place
 * @see place_piece
 */
void move_piece_side(GameInfo_t* info, Piece_t* piece, int shift);
/**
 * @brief Moves a given piece down on the game field.
 *
 * This function attempts to move a specified piece down by one row. It first
 * removes the piece from the game field, increments the piece's row coordinate
 * by one, and then checks if the piece can be placed in the new position using
 * the `can_place` function. If the piece cannot be placed in the new position,
 * the row coordinate is reverted to its original value. Finally, the piece is
 * placed back on the game field.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece A pointer to the `Piece_t` structure representing the piece to
 * be moved.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see remove_piece
 * @see can_place
 * @see place_piece
 */
void move_piece_down(GameInfo_t* info, Piece_t* piece);
/**
 * @brief Drops a given piece to the bottom of the game field.
 *
 * This function drops a specified piece to the bottom of the game field by
 * repeatedly moving the piece down one row until it can no longer be placed in
 * the new position. It first removes the piece from the game field, then
 * increments the piece's row coordinate until the `can_place` function returns
 * `false`. The row coordinate is then decremented by one to place the piece in
 * the last valid position. Finally, the piece is placed back on the game field.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece A pointer to the `Piece_t` structure representing the piece to
 * be dropped.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see remove_piece
 * @see can_place
 * @see place_piece
 */
void drop_piece(GameInfo_t* info, Piece_t* piece);
/**
 * @brief Rotates a given piece on the game field.
 *
 * This function attempts to rotate a specified piece by changing its
 * orientation. It first removes the piece from the game field, then increments
 * the piece's orientation position by one and takes the result modulo
 * `POS_COUNT` to ensure it wraps around if necessary. The function then checks
 * if the piece can be placed in the new orientation using the `can_place`
 * function. If the piece cannot be placed in the new orientation, the
 * orientation is reverted to its original value. Finally, the piece is placed
 * back on the game field.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * field.
 * @param piece A pointer to the `Piece_t` structure representing the piece to
 * be rotated.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see remove_piece
 * @see can_place
 * @see place_piece
 */
void rotate_piece(GameInfo_t* info, Piece_t* piece);

/**
 * @brief Updates the game timer and changes the game state accordingly.
 *
 * This function decrements the game timer by the specified delay amount. If the
 * timer reaches or goes below zero, the game state is set to `Shift`,
 * indicating that the piece should be moved down. Otherwise, the game state
 * remains `Move`, allowing the player to continue moving the piece.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game timer and state.
 *
 * @see ExpandedGameInfo_t
 */
void update_timer(ExpandedGameInfo_t* info);
/**
 * @brief Updates the current piece with the next piece and generates a new next
 * piece.
 *
 * This function updates the current piece in the game with the next piece and
 * then generates a new next piece using the `random_piece` function. The new
 * next piece is then filled into the game field using the `fill_next_piece`
 * function.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * current and next pieces.
 *
 * @see ExpandedGameInfo_t
 * @see random_piece
 * @see fill_next_piece
 */
void update_current_piece(ExpandedGameInfo_t* info);
/**
 * @brief Fills the next piece display area with the specified piece.
 *
 * This function clears the next piece display area and then fills it with the
 * specified piece. It iterates through each block of the piece and places it in
 * the appropriate cell of the next piece display area. The function assumes
 * that the piece type and position are correctly set.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the next piece
 * display area.
 * @param piece The `Piece_t` structure representing the piece to be displayed
 * in the next piece area.
 *
 * @see GameInfo_t
 * @see Piece_t
 * @see get_piece_shifts
 */
void fill_next_piece(GameInfo_t* info, Piece_t piece);
/**
 * @brief Performs a shift operation, moving the current piece down one row.
 *
 * This function attempts to move the current piece down one row. It first
 * removes the piece from the game field, increments the piece's row coordinate,
 * and checks if the piece can be placed in the new position using the
 * `can_place` function. If the piece cannot be placed in the new position, the
 * row coordinate is reverted to its original value, the piece is placed back on
 * the game field, and the current piece is updated with the next piece. The
 * function then sets the game timer to the delay for the current level and
 * ensures the piece is placed back on the game field if it can be placed.
 * Finally, the game state is set to `Move`.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game state.
 *
 * @see ExpandedGameInfo_t
 * @see remove_piece
 * @see can_place
 * @see place_piece
 * @see update_current_piece
 * @see get_iteration_delay
 */
void make_shift(ExpandedGameInfo_t* info);
/**
 * @brief Processes a user action and updates the current piece accordingly.
 *
 * This function processes a specified user action and updates the current piece
 * based on the action. The possible actions include moving the piece to the
 * right, left, down, or rotating the piece. If the action is `Up`, the piece is
 * dropped to the bottom of the game field. The function uses the appropriate
 * movement or rotation function based on the action.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * current piece and game state.
 * @param action The `UserAction_t` representing the user action to be
 * processed.
 *
 * @see ExpandedGameInfo_t
 * @see UserAction_t
 * @see move_piece_side
 * @see drop_piece
 * @see move_piece_down
 * @see rotate_piece
 */
void make_move(ExpandedGameInfo_t* info, UserAction_t action);
/**
 * @brief Clears full rows from the game field and updates the game state.
 *
 * This function checks for full rows in the game field and clears them if
 * found. It iterates through each row from the bottom to the top, and if a row
 * is full, it shifts all rows above it down by one position. The function also
 * increments the count of cleared rows. If the current piece is on the field,
 * it is temporarily removed to avoid interference with the row clearing
 * process. After clearing the rows, the current piece is placed back on the
 * field if it was removed. The function then updates the game state based on
 * whether any rows were cleared.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game field and state.
 * @return int The number of rows cleared.
 *
 * @see ExpandedGameInfo_t
 * @see is_piece_on_field
 * @see remove_piece
 * @see is_row_full
 * @see place_piece
 */
int clear_full_rows(ExpandedGameInfo_t* info);
/**
 * @brief Increases the game score based on the number of cleared rows and
 * updates the high score if necessary.
 *
 * This function increases the game score based on the number of rows cleared,
 * using the `get_points` function to determine the points awarded for the
 * cleared rows. If the new score exceeds the current high score, the high score
 * is updated and saved using the `save_high_score` function. Additionally, the
 * function checks if the player has reached the next level by comparing the
 * current score to the level boundary using the `get_level_boundary` function.
 * If the player reaches the next level, the level and speed are incremented.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the game
 * score, high score, level, and speed.
 * @param count The number of rows cleared.
 *
 * @see GameInfo_t
 * @see get_points
 * @see save_high_score
 * @see get_level_boundary
 */
void increase_score(GameInfo_t* info, int count);
/**
 * @brief Handles transitions between game states and performs necessary
 * actions.
 *
 * This function manages transitions between different game states and performs
 * actions based on the current and previous states.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game state and other game information.
 *
 * @see ExpandedGameInfo_t
 * @see reset_game
 */
void handle_states(ExpandedGameInfo_t* info);
/**
 * @brief Pauses the execution of the program for a specified number of
 * milliseconds.
 *
 * This function pauses the execution of the program for the specified number of
 * milliseconds by calling the `usleep` function with the appropriate argument.
 *
 * @param ms The number of milliseconds to pause the execution.
 */
void sleep_ms(int ms);

/**
 * @brief Frees allocated memory.
 *
 * This function frees the allocated memory for the game field and the next
 * piece display area.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game field and next piece display area.
 *
 * @see ExpandedGameInfo_t
 */
void exit_game(ExpandedGameInfo_t* info);
/**
 * @brief Resets the game by freeing allocated memory and refilling the game
 * instance.
 *
 * This function resets the game by first freeing the allocated memory for the
 * game field and the next piece display area using the `exit_game` function.
 *
 * @param info A pointer to the `ExpandedGameInfo_t` structure containing the
 * game state and other game information.
 *
 * @see ExpandedGameInfo_t
 * @see exit_game
 * @see get_instance
 */
void reset_game(ExpandedGameInfo_t* info);
/**
 * @brief Clears the game field.
 *
 * This function clears the game field by iterating through each cell and
 * setting its value to 0.
 *
 * @see GameInfo_t
 */
void clear_field(GameInfo_t* info);
/**
 * @brief Retrieves the shifts for a specific block of a piece in a given
 * orientation.
 *
 * This function returns the shifts for a specific block of a piece in a given
 * orientation. The shifts are determined based on the piece type, orientation
 * position, and block number. The function uses a static array of
 * `Coordinate_t` structures to store the shifts for each piece type and
 * orientation.
 *
 * @param piece The type of the piece.
 * @param pos The orientation position of the piece.
 * @param num The block number within the piece.
 * @return Coordinate_t The shifts for the specified block of the piece.
 *
 * @see Coordinate_t
 */

Coordinate_t get_piece_shifts(int piece, int pos, int num);
/**
 * @brief Generates a random piece with a random type and initial position.
 *
 * This function generates a random piece by selecting a random type from the
 * available piece types. The piece's initial position is set to the top center
 * of the game field, with the row coordinate set to 0 and the column coordinate
 * set to 5. The orientation position is set to 0.
 *
 * @return Piece_t A randomly generated piece with a random type and initial
 * position.
 *
 * @see Piece_t
 */
Piece_t random_piece();
/**
 * @brief Calculates the delay for each game iteration based on the current
 * level.
 *
 * This function calculates the delay for each game iteration based on the
 * current level.
 *
 * @param level The current game level.
 * @return int The delay for each game iteration in milliseconds.
 */
int get_iteration_delay(int level);
/**
 * @brief Returns the points awarded for clearing a given number of rows.
 *
 * This function returns the points awarded for clearing a given number of rows.
 * The points are determined based on a predefined array that maps the number of
 * cleared rows to the corresponding points.
 *
 * @param count The number of rows cleared.
 * @return int The points awarded for clearing the specified number of rows.
 */
int get_points(int count);
/**
 * @brief Returns the score boundary for reaching the next level.
 *
 * This function returns the score boundary for reaching the next level.
 *
 * @param level The current game level.
 * @return int The score boundary for reaching the next level.
 */
int get_level_boundary(int level);

/**
 * @brief Loads the high score from a file.
 *
 * This function loads the high score from a file specified by `FILE_PATH`. If
 * the file exists and contains a valid integer, the high score is read from the
 * file and returned. If the file does not exist or cannot be read, the function
 * returns 0.
 *
 * @return int The high score loaded from the file, or 0 if the file does not
 * exist or cannot be read.
 */
int load_high_score();
/**
 * @brief Saves the high score to a file.
 *
 * This function saves the high score to a file specified by `FILE_PATH`.
 *
 * @param info A pointer to the `GameInfo_t` structure containing the high score
 * to be saved.
 *
 * @see GameInfo_t
 */
void save_high_score(GameInfo_t* info);

#endif
