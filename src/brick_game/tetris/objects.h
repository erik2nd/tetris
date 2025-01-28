/**
 * @file objects.h
 * @brief File containing definitions of enums and structures
 */

#ifndef TETRIS_OBJECTS_H
#define TETRIS_OBJECTS_H

/**
 * @brief Enumeration representing possible game states.
 *
 * This enumeration defines the possible states that the game can be in. Each
 * state corresponds to a specific phase or condition of the game, such as the
 * beginning of the game, the main gameplay, pausing, or the end of the game.
 *
 * @see handle_states
 * @see userInput
 */
typedef enum {
  Begin,     /**< The game is in the beginning state. */
  Play,      /**< The game is in the main gameplay state. */
  Stop,      /**< The game is paused. */
  Again,     /**< The game is reset and starts again. */
  Exit,      /**< The game is exiting. */
  Game_over, /**< The game is over. */
  Move,      /**< The player can move the current piece. */
  Shift,     /**< The current piece is being shifted down. */
  Score_up   /**< The player's score is being updated. */
} GameState_t;

/**
 * @brief Enumeration representing possible user actions in the game.
 *
 * This enumeration defines the possible user actions that can be performed
 * during the game. Each action corresponds to a specific key press or button
 * click that the player can use to interact with the game.
 *
 * @see userInput
 */
typedef enum {
  Start,     /**< Start the game. */
  Pause,     /**< Pause the game. */
  Terminate, /**< Terminate the game. */
  Left,      /**< Move the current piece to the left. */
  Right,     /**< Move the current piece to the right. */
  Up,        /**< Drop the current piece to the bottom. */
  Down,      /**< Move the current piece down one row. */
  Action     /**< Rotate the current piece. */
} UserAction_t;

/**
 * @brief Structure representing the game information.
 *
 * This structure contains various fields that store important game information,
 * such as the game field, the next piece display area, the current score, the
 * high score, the current level, the game speed, and the pause state.
 *
 * @see updateCurrentState
 * @see increase_score
 * @see clear_field
 */
typedef struct {
  int **field;    /**< The game field where pieces are placed. */
  int **next;     /**< The next piece display area. */
  int score;      /**< The current score of the player. */
  int high_score; /**< The highest score achieved in the game. */
  int level;      /**< The current level of the game. */
  int speed;      /**< The current speed of the game. */
  int pause; /**< The pause state of the game (1 for paused, 0 for not paused).
              */
} GameInfo_t;

/**
 * @brief Structure representing a coordinate in matrix.
 *
 * This structure contains two integer fields that represent the row and column
 * coordinates in matrix. It is used to represent the position of a block within
 * a piece or the game field.
 *
 * @see get_piece_shifts
 * @see place_piece
 * @see remove_piece
 */
typedef struct {
  int row; /**< The row value. */
  int col; /**< The column value. */
} Coordinate_t;

/**
 * @brief Structure representing a game piece.
 *
 * This structure contains fields that store information about a game piece,
 * such as its type, coordinates, and orientation position. The type determines
 * the shape of the piece, the coordinates represent the position of the piece
 * on the game field, and the orientation position determines the current
 * orientation of the piece.
 *
 * @see random_piece
 * @see place_piece
 * @see remove_piece
 * @see rotate_piece
 */
typedef struct {
  int type;            /**< The type of the piece. */
  Coordinate_t coords; /**< The coordinates of the piece on the game field. */
  int pos;             /**< The orientation of the piece. */
} Piece_t;

/**
 * @brief Structure representing the expanded game information.
 *
 * This structure contains the game information, the current piece, the next
 * piece, the game timer, and the current and previous game states. It is used
 * to manage the overall state of the game, including the current piece, the
 * next piece to be played, and the timing and state transitions.
 *
 * @see updateCurrentState
 * @see userInput
 * @see handle_states
 */
typedef struct {
  GameInfo_t info;        /**< The game information. */
  Piece_t cur_piece;      /**< The current piece being played. */
  Piece_t next_piece;     /**< The next piece to be played. */
  int timer;              /**< The game timer. */
  GameState_t state;      /**< The current game state. */
  GameState_t prev_state; /**< The previous game state. */
} ExpandedGameInfo_t;

#endif
