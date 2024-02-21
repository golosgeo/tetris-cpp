#include "TetrisGame.h"

TetrisGame::TetrisGame() : cycle_counter(),
                           game_screen(),
                           game_board(),
                           current_tetromino(create_tetromino()),
                           random_generator(TETROMINO_I, TETROMINO_Z) {
    game_screen.update_score_window(score);
}

void TetrisGame::run() {

    // Display the start screen and wait for the user to press any key.
    game_screen.display_start_screen();
    sleep_until_user_input();

    // The game loop
    do {
        run_frame();
    } while (!is_game_end);

    // Display the game over screen and wait for the user to press 'q'.
    game_screen.display_game_over_screen(score);
    sleep_until_user_input('q');

    return;
}

void TetrisGame::run_frame() {
    // Sleep for a frame duration
    sleep_for_frame_duration();

    // If the current tetromino is nullptr, create a new tetromino.
    if (!current_tetromino) {
        current_tetromino = create_tetromino();

        // If the new tetromino is not valid, the game ends.
        if (!game_board.is_valid(*current_tetromino)) {
            is_game_end = true;
            return;
        }
    }

    // Tetramino not touched the bottom
    bool is_tetromino_bottom_touched = false;

    // Move the current tetromino down if the cycle counter is zero.
    if (cycle_counter.is_zero()) {
        current_tetromino->move_down();

        // If the current tetromino is valid, update the main window.
        if (game_board.is_valid(*current_tetromino)) {
            game_screen.update_main_window(game_board, *current_tetromino);
        } else {
            // If the current tetromino is not valid (i.e. it intersects with the fixed tetrominoes), undo the move and set the flag to true.
            current_tetromino->undo();
            is_tetromino_bottom_touched = true;
        }
    }

    // Decrement the cycle counter.
    cycle_counter--;


    char user_input = get_user_input();
    switch (user_input) {
        case 'a':
            current_tetromino->move_left();
            break;
        case 's':
            current_tetromino->move_down();

            // If the current tetromino is not valid, undo the move and set the flag to true.
            if (!game_board.is_valid(*current_tetromino)) {
                current_tetromino->undo();
                is_tetromino_bottom_touched = true;
            }

            break;
        case 'w':
            current_tetromino->rotate();
            break;
        case 'd':
            current_tetromino->move_right();
            break;
    }

    // After move, if the current tetromino is valid, update the main window.
    if (game_board.is_valid(*current_tetromino))
        game_screen.update_main_window(game_board, *current_tetromino);
    else
        current_tetromino->undo();

    // Amount of erased rows, not initialized yet.
    unsigned int erased_rows;

    // If the current tetromino touched the bottom.
    if (is_tetromino_bottom_touched) {
        // Fix the current tetromino to the board.
        game_board.fix(*current_tetromino);
        // Reset unique pointer of the current tetromino.
        current_tetromino.reset();

        // Erase full rows.
        erased_rows = game_board.erase_full_rows();

        // Update the score.
        if (erased_rows == 4) {
            score += score_tetris;
        } else if (erased_rows < 4 && erased_rows > 0) {
            score += erased_rows * score_row;
        }

        // Update main and score windows.
        game_screen.update_main_window(game_board);
        game_screen.update_score_window(score);

        return;
    }

    // End of 1 frame.
    return;
}

void TetrisGame::sleep_for_frame_duration() const {
    static const std::chrono::milliseconds frame_duration_in_ms(100);
    std::this_thread::sleep_for(frame_duration_in_ms);

    return;
}

tetromino_ptr_t TetrisGame::create_tetromino() {
    using std::map;
    using std::pair;
    using std::all_of;

    // Static map to keep track of the generated tetromino types.
    static map<TetrominoType, bool> is_generated;

    // If all the tetromino types are generated, clear the map.
    bool is_every_type_generated
            = all_of(is_generated.begin(),
                     is_generated.end(),
                     [](pair<TetrominoType, bool> e) { return e.second; });

    if (is_every_type_generated) {
        is_generated.clear();

        for (int i = TETROMINO_I; i != TETROMINO_Z; i++)
            is_generated[static_cast<TetrominoType>(i)] = false;
    }

    // Generate a random tetromino type until a non-generated tetromino type is found.
    TetrominoType random_tetromino_type;

    do {
        random_tetromino_type
                = static_cast<TetrominoType>(random_generator());
    } while (is_generated[random_tetromino_type]);

    is_generated[random_tetromino_type] = true;

    switch (random_tetromino_type) {
        case TETROMINO_I:
            return tetromino_ptr_t(new ITetromino());
        case TETROMINO_J:
            return tetromino_ptr_t(new JTetromino());
        case TETROMINO_L:
            return tetromino_ptr_t(new LTetromino());
        case TETROMINO_O:
            return tetromino_ptr_t(new OTetromino());
        case TETROMINO_S:
            return tetromino_ptr_t(new STetromino());
        case TETROMINO_T:
            return tetromino_ptr_t(new TTetromino());
        case TETROMINO_Z:
            return tetromino_ptr_t(new ZTetromino());
        default:
            return nullptr;
    }
}

void TetrisGame::sleep_until_user_input(char wait_for_key) const {
    wtimeout(game_screen.main_window, -1);
    char user_input;
    do {
        user_input = wgetch(game_screen.main_window);
    } while (wait_for_key != '\0' && user_input != wait_for_key);
    wtimeout(game_screen.main_window, 0);
    return;
}

const char TetrisGame::get_user_input() const {
    char user_input = wgetch(game_screen.main_window);
    // Flush the input buffer, so that the next call to wgetch will not get the buffered input.
    // Only the most recent input will be processed.
    flushinp();
    return user_input;
}