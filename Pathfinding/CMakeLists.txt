cmake_minimum_required(VERSION 3.24)
project(Pathfinding)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pathfinding assets main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR c:/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS window system graphics REQUIRED)
include_directories(c:/SFML/include)
target_link_libraries(Pathfinding sfml-window sfml-system sfml-graphics)