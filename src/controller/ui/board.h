/**
 * @file board.h
 * @brief Graphical board interfaces.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "location.h"

#include <ncurses.h>

#include <cassert>
#include <limits>


namespace ui {

Point GetBoardPosition(const WINDOW* const win) noexcept {
    int x {0}, y {0};
    getbegyx(win, y, x);
    assert(x >= 0 && y >= 0);
    return {static_cast<std::size_t>(x), static_cast<std::size_t>(y)};
}

std::size_t GetBoardHeight(const WINDOW* const win) noexcept {
    const auto height {getmaxy(win)};
    assert(height >= 0);
    return static_cast<std::size_t>(height);
}

std::size_t GetBoardWidth(const WINDOW* const win) noexcept {
    const auto width {getmaxx(win)};
    assert(width >= 0);
    return static_cast<std::size_t>(width);
}

bool IsValidPosition(const Point& pos) noexcept {
    return pos.x <= std::numeric_limits<int>::max()
           && pos.y <= std::numeric_limits<int>::max();
}

/**
 * @interface Board
 * The interface of a graphical board.
 */
class Board : public Locatable {
public:
    virtual std::size_t GetHeight() const noexcept = 0;

    virtual std::size_t GetWidth() const noexcept = 0;

    virtual ~Board() noexcept = default;
};

//! The symbols for drawing cells.
struct CellSymbols {
    chtype blank;

    chtype filled;

    /**
     * The number of columns per cell on the terminal.
     * Usually, it should be set to 2 in order to make a cell look like a square.
     */
    std::size_t width;
};

constexpr CellSymbols cell_sym {' ', 'O', 2};

}  // namespace ui