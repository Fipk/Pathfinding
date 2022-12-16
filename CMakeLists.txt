cmake_minimum_required(VERSION 3.21)
project(Pathfinding)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Pathfinding)
include_directories(Pathfinding/header)
include_directories(Pathfinding/src)
include_directories(Pathfinding/assets)

add_executable(Pathfinding
        Pathfinding/header/CheckpointState.h
        Pathfinding/header/DefaultState.h
        Pathfinding/header/EditState.h
        Pathfinding/header/EndState.h
        Pathfinding/header/Graph.h
        Pathfinding/header/PathFinder.h
        Pathfinding/header/StartState.h
        Pathfinding/header/WallState.h
        Pathfinding/src/CheckpointState.cpp
        Pathfinding/src/DefaultState.cpp
        Pathfinding/src/EndState.cpp
        Pathfinding/src/Graph.cpp
        Pathfinding/src/PathFinder.cpp
        Pathfinding/src/StartState.cpp
        Pathfinding/src/WallState.cpp
        Pathfinding/src/Button.cpp
        Pathfinding/header/Button.h
		Pathfinding/src/ButtonGrid.cpp
        Pathfinding/header/ButtonGrid.h
        Pathfinding/src/Game.cpp
        Pathfinding/header/Game.h
        Pathfinding/src/GameObject.cpp
        Pathfinding/header/GameObject.h
		Pathfinding/src/Grid.cpp
        Pathfinding/header/Grid.h
        Pathfinding/main.cpp)

set(SFML_ROOT "PATH_TO/SFML-2.5.1")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    target_link_libraries(Pathfinding sfml-graphics sfml-window sfml-system)
endif ()