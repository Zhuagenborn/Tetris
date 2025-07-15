# Tetris

![C++](docs/badges/C++.svg)
[![CMake](docs/badges/Made-with-CMake.svg)](https://cmake.org)
[![Docker](docs/badges/Made-with-Docker.svg)](https://www.docker.com)
[![GitHub Actions](docs/badges/Made-with-GitHub-Actions.svg)](https://github.com/features/actions)
![Linux](docs/badges/Linux.svg)
![License](docs/badges/License-MIT.svg)

## Introduction

![Cover](cover.png)

A *Tetris* game running in the *Linux* terminal.

## Prerequisites

- Install [*CMake*](https://cmake.org).
- Install [*GoogleTest*](https://google.github.io/googletest).
- Install [*ncurses*](https://invisible-island.net/ncurses).

## Building

Set the location to the project folder and run:

```bash
mkdir build
cd build
cmake -DTETRIS_BUILD_TESTS=ON ..
cmake --build .
```

## Running Tests

Set the location to the `build` folder and run:

```bash
ctest -VV
```

## Running the Game

Set the location to the `build/bin` folder and run:

```bash
./tetris -x=<width> -y=<height>
```

For example:

```bash
./tetris -x=10 -y=15
```

## Structure

```
.
├── .clang-format
├── .gitignore
├── CITATION.cff
├── CMakeLists.txt
├── Dockerfile
├── LICENSE
├── README.md
├── cover.png
├── docs
│   └── badges
│       ├── C++.svg
│       ├── License-MIT.svg
│       ├── Linux.svg
│       ├── Made-with-CMake.svg
│       ├── Made-with-GitHub-Actions.svg
│       └── Made-with-Docker.svg
├── include
│   ├── args.h
│   ├── color.h
│   ├── controller.h
│   ├── game.h
│   ├── grid.h
│   ├── location.h
│   ├── rotation.h
│   ├── shape.h
│   └── tetromino.h
├── src
│   ├── CMakeLists.txt
│   ├── args
│   │   ├── CMakeLists.txt
│   │   └── args.cpp
│   ├── color
│   │   ├── CMakeLists.txt
│   │   └── color.cpp
│   ├── controller
│   │   ├── CMakeLists.txt
│   │   ├── controller.cpp
│   │   └── ui
│   │       ├── board.h
│   │       ├── color_env.cpp
│   │       ├── color_env.h
│   │       ├── grid_board.h
│   │       ├── next_tetromino_board.h
│   │       └── score_board.h
│   ├── game
│   │   ├── CMakeLists.txt
│   │   └── game.cpp
│   ├── grid
│   │   ├── CMakeLists.txt
│   │   └── grid.cpp
│   ├── location
│   │   └── CMakeLists.txt
│   ├── main.cpp
│   ├── rotation
│   │   ├── CMakeLists.txt
│   │   └── rotation.cpp
│   ├── shape
│   │   └── CMakeLists.txt
│   └── tetromino
│       ├── CMakeLists.txt
│       ├── subtype
│       │   ├── i.h
│       │   ├── j.h
│       │   ├── l.h
│       │   ├── o.h
│       │   ├── s.h
│       │   ├── t.h
│       │   └── z.h
│       └── tetromino.cpp
└── tests
    ├── CMakeLists.txt
    ├── grid_test.cpp
    ├── rotation_test.cpp
    └── tetromino_test.cpp
```

## Class Diagram

```mermaid
classDiagram

class Colored {
    <<interface>>
    GetColor() Color
    SetColor(Color)
}

class Rotatable {
    <<interface>>
    RotateLeft()
    RotateRight()
    GetAngle() Angle
    RotateTo(Angle)
}

class Locatable {
    <<interface>>
    GetPosition() Point
}

class Movable {
    <<interface>>
    SetPosition(Point)
}

Locatable <|-- Movable

class Shape {
    <<interface>>
    GetHeight() int
    GetWidth() int
    Filled(Point) bool
}

class Tetromino {
    <<abstract>>
    GetTetrominoByAngle(Angle) Tetromino
}

Shape <|.. Tetromino
Rotatable <|.. Tetromino
Colored <|.. Tetromino

Tetromino <|-- I
Tetromino <|-- O
Tetromino <|-- J
Tetromino <|-- L
Tetromino <|-- S
Tetromino <|-- T
Tetromino <|-- Z

class Grid {
    GetColor(Point) Color
    PushTetromino(Tetromino, Point) bool
    MoveTetrominoToLeft() bool
    MoveTetrominoToRight() bool
    RotateTetrominoLeft() bool
    RotateTetrominoRight() bool
    TetrominoDescend(int& cleared_line_count) bool
}

Shape <|.. Grid
Grid *-- Tetromino

Movable <|.. MovableTetromino
MovableTetromino --> Tetromino
Grid --> MovableTetromino

class Action {
    <<enumeration>>
    Non
    MoveToLeft
    MoveToRight
    RotateLeft
    RotateRight
    Descend
}

class Game {
    Start()
    Act(Action) ActionResult
    GetNextTetrominoes() Tetromino
    GetScore() int
    IsOver() bool
}

Game --> Grid
Game ..> Action

class Controller {
    Input()
    Update()
    Refresh()
}

Controller --> Game
```

## License

Distributed under the *MIT License*. See `LICENSE` for more information.