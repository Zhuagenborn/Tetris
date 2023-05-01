/**
 * @file next_tetromino_board.h
 * @brief A board showing the next tetromino.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "board.h"
#include "color_env.h"
#include "tetromino.h"


namespace ui {

class NextTetrominoBoard : public Board {
public:
    NextTetrominoBoard(const Point& pos) noexcept {
        assert(IsValidPosition(pos));
        board_ = newwin(height_ + 2, width_ * cell_sym.width + 2, pos.y, pos.x);
        box(board_, 0, 0);
        Clear();
    }

    void Update(const Tetromino& tetromino) noexcept {
        Clear();
        const auto color {tetromino.GetColor()};
        for (std::size_t x {0}; x < tetromino.GetWidth(); ++x) {
            for (std::size_t y {0}; y < tetromino.GetHeight(); ++y) {
                if (tetromino.Filled({x, y})) {
                    const ColorEnvironment env {board_, color};
                    mvwaddch(board_, y + 1, x * cell_sym.width + 1,
                             cell_sym.filled);
                } else {
                    const ColorEnvironment env {board_, Color::Non};
                    mvwaddch(board_, y + 1, x * cell_sym.width + 1,
                             cell_sym.blank);
                }
            }
        }

        Refresh();
    }

    void Clear() noexcept {
        const ColorEnvironment env {board_, Color::Non};
        for (std::size_t x {0}; x < width_; ++x) {
            for (std::size_t y {0}; y < height_; ++y) {
                mvwaddch(board_, y + 1, x * cell_sym.width + 1, cell_sym.blank);
            }
        }

        Refresh();
    }

    ~NextTetrominoBoard() noexcept {
        delwin(board_);
    }

    Point GetPosition() const noexcept override {
        return GetBoardPosition(board_);
    }

    std::size_t GetHeight() const noexcept override {
        return GetBoardHeight(board_);
    }

    std::size_t GetWidth() const noexcept override {
        return GetBoardWidth(board_);
    }

private:
    static constexpr std::size_t width_ {4};

    static constexpr std::size_t height_ {4};

    static constexpr std::string_view title_ {"Score: "};

    void Refresh() noexcept {
        wrefresh(board_);
    }

    WINDOW* board_;
};

}  // namespace ui