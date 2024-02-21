#ifndef THE_GAME_PCC_BOARD_H
#define THE_GAME_PCC_BOARD_H

#include <algorithm>
#include "Tetromino.h"

class Board {
public:
    const int row_size = 10;
    const int col_size = 21;

private:
    matrix_t shape;

    bool is_coordinate_out_of_bound(const Coordinate &) const;

public:
    Board();

    int erase_full_rows();

    // Fix the tetromino on the board
    void fix(const Tetromino &);

    bool is_valid(const Tetromino &) const;

    bool is_filled(const Coordinate &) const;
};


#endif //THE_GAME_PCC_BOARD_H