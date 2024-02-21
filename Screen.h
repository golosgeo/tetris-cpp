#ifndef THE_GAME_PCC_SCREEN_H
#define THE_GAME_PCC_SCREEN_H

#include <ncurses.h>
#include <string>

#include "Board.h"

class Screen {
private:
    // Window constants
    const int main_window_width = 2 * 10 + 2;
    const int main_window_height = 21 + 2;
    const Coordinate main_window_position{1, 1};

    const int score_window_width = 12;
    const int score_window_height = 3;
    const Coordinate score_window_position{24, 1};

    enum ColorPair {
        WHITE_BLACK_PAIR, YELLOW_BLACK_PAIR
    };

    // Window pointers
    WINDOW *main_window;
    WINDOW *score_window;

    void draw_square_normal(const Coordinate &) const;

    void draw_square_highlighted(const Coordinate &) const;

    void erase_square(const Coordinate &) const;

    void refresh_window(WINDOW *) const;

    void display_start_screen() const;

    void display_game_over_screen(int score) const;

    friend class TetrisGame;

public:
    Screen();

    ~Screen();

    void update_score_window(int) const;

    void update_main_window(const Board &) const;

    void update_main_window(const Board &, const Tetromino &) const;
};

#endif //THE_GAME_PCC_SCREEN_H