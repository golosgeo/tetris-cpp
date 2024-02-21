#ifndef THE_GAME_PCC_TETRISGAME_H
#define THE_GAME_PCC_TETRISGAME_H

#include <map>
#include <memory>
#include <algorithm>
#include <chrono>
#include <thread>

#include "Tetromino.h"
#include "Board.h"
#include "Screen.h"
#include "Utils.h"

// Typedef for the unique pointer of Tetromino piece.
typedef std::unique_ptr<Tetromino> tetromino_ptr_t;

// TetrisGame class is the main class of the game.
class TetrisGame {
private:

    // Indicates whether the game is ended or not.
    bool is_game_end;

    // DecreasingCycleCounter for controlling the speed of the game.
    DecreasingCycleCounter cycle_counter;
    RandomGenerator random_generator;

    // The game screen and board objects.
    Screen game_screen;
    Board game_board;

    // The current tetromino piece.
    tetromino_ptr_t current_tetromino;
    unsigned int score = 0;

    // Run 1 frame of the game.
    void run_frame();

    // Create a new tetromino piece.
    tetromino_ptr_t create_tetromino();

    // Sleep for the duration of a 1 frame.
    void sleep_for_frame_duration() const;

    // Sleep until the user input is received.
    void sleep_until_user_input(char wait_for_key = '\0') const;

    // Get the user input.
    const char get_user_input() const;

    // Score gain for each row and tetris.
    const unsigned int score_row = 100;
    const unsigned int score_tetris = 800;

public:
    TetrisGame();

    // Run the game.
    void run();
};


#endif //THE_GAME_PCC_TETRISGAME_H