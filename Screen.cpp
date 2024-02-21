#include "Screen.h"

Screen::Screen() {
    // Starts the ncurses mode
    initscr();
    // No echoing of keyboard characters
    noecho();
    // Make cursor invisible
    curs_set(0);
    // Disables line buffering, making characters typed by the user immediately available to the program
    cbreak();
    //Starts the color functionality rutine
    start_color();
    // Initializes some color pair (name, character color, background color)
    init_pair(WHITE_BLACK_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW_BLACK_PAIR, COLOR_GREEN, COLOR_BLACK);

    // Creates a main window
    main_window = newwin(main_window_height,
                         main_window_width,
                         main_window_position.y,
                         main_window_position.x);

    // Creates a score window
    score_window = newwin(score_window_height,
                          score_window_width,
                          score_window_position.y,
                          score_window_position.x);

    // Main window will not wait for user input
    wtimeout(main_window, 0);

    // Creates box around windows
    box(main_window, 0, 0);
    box(score_window, 0, 0);

    // Writes the title of the windows
    mvwprintw(main_window, 0, 1, "Tetris");
    mvwprintw(score_window, 0, 1, "Score");
}

Screen::~Screen() {
    // Deletes the windows
    delwin(main_window);
    delwin(score_window);
    // Ends the ncurses mode
    endwin();
}

void Screen::display_start_screen() const {
    // Writes the simple start screen
    mvwprintw(main_window, main_window_height / 2 - 1, (main_window_width - 6) / 2, "Press");
    mvwprintw(main_window, main_window_height / 2, (main_window_width - 7) / 2, "any key");
    mvwprintw(main_window, main_window_height / 2 + 1, (main_window_width - 8) / 2, "to start");
    refresh_window(main_window);
}

void Screen::display_game_over_screen(int score) const {
    // Writes the simple game over screen
    mvwprintw(main_window, main_window_height / 2 - 1, (main_window_width - 9) / 2, "Game Over");
    mvwprintw(main_window, main_window_height / 2, (main_window_width - 10) / 2, "Score: %d", score);
    mvwprintw(main_window, main_window_height / 2 + 2, (main_window_width - 10) / 2, "q - Quit", score);
    refresh_window(main_window);
}

void Screen::update_main_window(const Board &board, const Tetromino &tetromino) const {

    // This cycle draws the board
    for (int i = 0; i < board.col_size; i++) {
        for (int j = 0; j < board.row_size; j++) {
            if (board.is_filled({j, i}))
                draw_square_normal({j, i});
            else
                erase_square({j, i});
        }
    }

    Coordinate position = tetromino.get_position();

    // Draws the tetromino. Do not erase other squares drawn before!
    for (int i = 0; i < tetromino.col_size; i++) {
        for (int j = 0; j < tetromino.row_size; j++) {
            if (tetromino.is_filled({j, i}))
                draw_square_highlighted({position.x + j, position.y + i});
        }
    }

    refresh_window(main_window);

    return;
}

void Screen::update_main_window(const Board &board) const {
    // This cycle draws the board without the tetromino
    for (int i = 0; i < board.col_size; i++) {
        for (int j = 0; j < board.row_size; j++) {
            if (board.is_filled({j, i}))
                draw_square_normal({j, i});
            else
                erase_square({j, i});
        }
    }

    refresh_window(main_window);
}

void Screen::draw_square_normal(const Coordinate &coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    // Draws a square with two spaces. The first space is the left half of the square, and the second space is the right half of the square.
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x,
             ' ' | A_REVERSE | COLOR_PAIR(WHITE_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1,
             ' ' | A_REVERSE | COLOR_PAIR(WHITE_BLACK_PAIR));

    return;
}

void Screen::draw_square_highlighted(const Coordinate &coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x,
             ' ' | A_REVERSE | COLOR_PAIR(YELLOW_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1,
             ' ' | A_REVERSE | COLOR_PAIR(YELLOW_BLACK_PAIR));

    return;
}

void Screen::erase_square(const Coordinate &coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x,
             ' ' | COLOR_PAIR(WHITE_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1,
             ' ' | COLOR_PAIR(WHITE_BLACK_PAIR));

    return;
}

void Screen::update_score_window(int score) const {
    // Updates the score window
    Coordinate cursor_coordinate{1, 1};

    mvwprintw(score_window, cursor_coordinate.y, cursor_coordinate.x, "%d", score);
    refresh_window(score_window);

    return;
}

void Screen::refresh_window(WINDOW *window) const {
    // Refreshes the window
    wrefresh(window);

    return;
}