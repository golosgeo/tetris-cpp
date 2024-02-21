#include "Board.h"
#include <functional>

Board::Board() : shape(col_size, row_t(row_size, false)) {
}

// Function to erase full rows and add empty rows to the top of the board
int Board::erase_full_rows() {
    using std::all_of;
    using std::remove_if;
    using std::function;

    function<bool(row_t)> is_row_full = [](row_t row) {
        return all_of(row.begin(), row.end(), [](bool e) { return e; });
    };

    // Erase full rows
    shape.erase(remove_if(shape.begin(), shape.end(), is_row_full), shape.end());

    int erased_rows = col_size - shape.size();

    // Add empty rows to the top of the board
    for (int i = 0; i < erased_rows; i++)
        shape.emplace(shape.begin(), row_t(row_size, false));

    return erased_rows;
}

void Board::fix(const Tetromino &tetromino) {
    // Fix the tetromino on the board
    Coordinate position = tetromino.get_position();

    for (int i = 0; i < tetromino.col_size; i++) {
        for (int j = 0; j < tetromino.row_size; j++) {
            if (tetromino.is_filled({j, i}))
                shape[position.y + i][position.x + j] = true;
        }
    }

    return;
}

bool Board::is_valid(const Tetromino &tetromino) const {
    // Check if the tetromino is out of board or collides with filled cells
    const Coordinate &position = tetromino.get_position();

    for (int i = 0; i < tetromino.col_size; i++) {
        for (int j = 0; j < tetromino.row_size; j++) {
            if (tetromino.is_filled({j, i})) {
                if (is_coordinate_out_of_bound({position.x + j, position.y + i}))
                    return false;

                if (is_filled({position.x + j, position.y + i}))
                    return false;
            }
        }
    }

    return true;
}

bool Board::is_coordinate_out_of_bound(const Coordinate &coordinate) const {
    // Check if the coordinate is out of board
    bool x_out_of_bound = (coordinate.x < 0 || coordinate.x >= row_size);
    bool y_out_of_bound = (coordinate.y < 0 || coordinate.y >= col_size);

    return x_out_of_bound || y_out_of_bound;
}

bool Board::is_filled(const Coordinate &position) const {
    return shape[position.y][position.x];
}