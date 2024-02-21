#include "Tetromino.h"

Coordinate Coordinate::operator+(const Coordinate &other) {
    return Coordinate{x + other.x, y + other.y};
}

Coordinate Coordinate::operator-(const Coordinate &other) {
    return Coordinate{x - other.x, y - other.y};
}

Coordinate Coordinate::operator*(int other) {
    return Coordinate{x * other, y * other};
}

Coordinate Coordinate::operator/(int other) {
    return Coordinate{x / other, y / other};
}

inline void Tetromino::save_state() {
    prev_position = position;
    prev_shape = shape;

    return;
}

void Tetromino::move_right() {
    save_state();

    position.x++;
}

void Tetromino::move_left() {
    save_state();

    position.x--;
}

void Tetromino::move_down() {
    save_state();

    position.y++;
}

void Tetromino::rotate() {
    save_state();

    const Coordinate origin{1, 1};

    // The new shape is a 90-degree clockwise rotation of the original shape.
    matrix_t new_shape(col_size, row_t(row_size, false));
    Coordinate new_coordinate;

    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            if (shape[i][j]) {
                new_coordinate = Coordinate{j, i} - origin;
                new_coordinate = Coordinate{-new_coordinate.y, new_coordinate.x} + origin;
                new_shape[new_coordinate.y][new_coordinate.x] = true;
            }
        }
    }

    shape = new_shape;

    return;
}

void Tetromino::undo() {
    // Swap the current state with the previous state.
    // WARNING: Do not call this function more than once in a row! It will mess up the positions and shapes!
    std::swap<Coordinate>(position, prev_position);
    std::swap<matrix_t>(shape, prev_shape);

    return;
}

const Coordinate &Tetromino::get_position() const {
    return position;
}

const bool Tetromino::is_filled(const Coordinate &coordinate) const {
    // If the coordinate is out of the shape's bounds, return false.
    return shape[coordinate.y][coordinate.x];
}

void ITetromino::rotate() {
    save_state();

    constexpr
    Coordinate origin{3, 3};

    // The new shape is a 90-degree clockwise rotation of the original shape.
    matrix_t new_shape(col_size, row_t(row_size, false));
    Coordinate new_coordinate;

    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            if (shape[i][j]) {
                new_coordinate = Coordinate{j, i} * 2 - origin;
                new_coordinate = Coordinate{-new_coordinate.y, new_coordinate.x} + origin;
                new_coordinate = new_coordinate / 2;
                new_shape[new_coordinate.y][new_coordinate.x] = true;
            }
        }
    }

    shape = new_shape;

    return;
}

void OTetromino::rotate() {
    // Do nothing because the O-tetromino is a square and it doesn't change when rotated.
    save_state();

    return;
}