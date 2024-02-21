#ifndef THE_GAME_PCC_TETROMINO_H
#define THE_GAME_PCC_TETROMINO_H

#include <vector>

// Coordinate type for representing the position of the tetromino
struct Coordinate {
    int x, y;

    Coordinate operator+(const Coordinate &);

    Coordinate operator-(const Coordinate &);

    Coordinate operator*(int);

    Coordinate operator/(int);
};

// Enum type for representing the type of the tetromino
enum TetrominoType {
    TETROMINO_I, TETROMINO_J, TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, TETROMINO_Z
};

// Matrix type for representing tetromino shapes
typedef std::vector <std::vector<bool>> matrix_t;
typedef std::vector<bool> row_t;

// Coordinates with initial position of the tetromino, the top center of the board
constexpr Coordinate
INITIAL_POSITION{
3, 0};

// Tetromino shapes
static const matrix_t SHAPE_I = {{0, 0, 0, 0},
                                 {1, 1, 1, 1},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}};

static const matrix_t SHAPE_J = {{1, 0, 0},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_L = {{0, 0, 1},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_O = {{0, 1, 1, 0},
                                 {0, 1, 1, 0},
                                 {0, 0, 0, 0}};

static const matrix_t SHAPE_S = {{0, 1, 1},
                                 {1, 1, 0},
                                 {0, 0, 0}};

static const matrix_t SHAPE_T = {{0, 1, 0},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_Z = {{1, 1, 0},
                                 {0, 1, 1},
                                 {0, 0, 0}};

class Tetromino {
private:
    // The position of the tetromino
    Coordinate position = INITIAL_POSITION;
    Coordinate prev_position = INITIAL_POSITION;

protected:
    Tetromino(matrix_t initial_shape)
            : shape(initial_shape), prev_shape(initial_shape),
              row_size(initial_shape[0].size()), col_size(initial_shape.size()) {
    }

    // The shape of the tetromino
    matrix_t shape;

    // The previous shape of the tetromino
    matrix_t prev_shape;

    // Save the current state of the tetromino
    inline void save_state();

public:

    // Move the tetromino to the right, left, and down
    void move_right();

    void move_left();

    void move_down();

    // Rotate the tetromino
    virtual void rotate();

    // Undo the last move
    void undo();

    // Get the position of the tetromino
    const Coordinate &get_position() const;

    // TODO
    const bool is_filled(const Coordinate &) const;

    const int row_size;
    const int col_size;
};

// Derived classes for each type of tetromino

class ITetromino : public Tetromino {
public:
    ITetromino() : Tetromino(SHAPE_I) {
    }

    void rotate() override;
};

class JTetromino : public Tetromino {
public:
    JTetromino() : Tetromino(SHAPE_J) {
    }
};

class LTetromino : public Tetromino {
public:
    LTetromino() : Tetromino(SHAPE_L) {
    }
};

class OTetromino : public Tetromino {
public:
    OTetromino() : Tetromino(SHAPE_O) {
    }

    void rotate() override;
};

class STetromino : public Tetromino {
public:
    STetromino() : Tetromino(SHAPE_S) {
    }
};

class TTetromino : public Tetromino {
public:
    TTetromino() : Tetromino(SHAPE_T) {
    }
};

class ZTetromino : public Tetromino {
public:
    ZTetromino() : Tetromino(SHAPE_Z) {
    }
};

#endif //THE_GAME_PCC_TETROMINO_H