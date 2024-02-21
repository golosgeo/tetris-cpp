#include <iostream>
#include "TetrisGame.h"

int main(int argc, char* argv[]) {
    // Check if the user wants to see the help message
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            std::cout << "Tetris game\n";
            std::cout << "Usage: ./the_game_pcc\n\n";
            std::cout << "Controls\n";
            std::cout << "a: Move left\n";
            std::cout << "d: Move right\n";
            std::cout << "s: Move down\n";
            std::cout << "w: Rotate\n";
            return 0;
        }
    }

    // Create a game object and run it
    TetrisGame game;
    game.run();

    return 0;
}