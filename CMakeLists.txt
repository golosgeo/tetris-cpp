cmake_minimum_required(VERSION 3.27)
project(the_game_pcc)

set(CURSES_LIBRARY "/usr/lib64/libncurses.so")
set(CURSES_INCLUDE_PATH "/usr/include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(the_game_pcc main.cpp)
add_library(the_game_pcc_lib STATIC
        Board.cpp
        Board.h
        Tetromino.cpp
        Tetromino.h
        TetrisGame.cpp
        TetrisGame.h
        Screen.cpp
        Screen.h
        Utils.cpp
        Utils.h
)

target_link_libraries(the_game_pcc ${CURSES_LIBRARIES} the_game_pcc_lib)

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( the_game_pcc PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( the_game_pcc PRIVATE /W4 )
endif()
