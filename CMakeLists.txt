cmake_minimum_required(VERSION 3.25)
project(Maze_Test)

set(CMAKE_CXX_STANDARD 11)

add_executable(Maze_Test main.cpp Map.h Map.cpp DS_List.cpp DS_List.h Character.cpp Character.h)
target_link_libraries(Maze_Test -lmingw32 -lSDL2main -lSDL2)
