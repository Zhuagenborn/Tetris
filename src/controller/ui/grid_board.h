/**
 * @file grid_board.h
 * @brief A board showing a playing field.
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
#include "grid.h"

#include <chrono>
#include <memory>


namespace ui {

class GridBoard : public Board {
public:
    GridBoard(const Point& pos, std::shared_ptr<const Grid> grid,
              const std::chrono::steady_clock::duration input_time_out) noexcept
        :
        grid_ {std::move(grid)} {
        assert(IsValidPosition(pos));
        assert(grid_->GetWidth() <= std::numeric_limits<int>::max());
        assert(grid_->GetHeight() <= std::numeric_limits<int>::max());

        board_ = newwin(grid_->GetHeight() + 2,
                        grid_->GetWidth() * cell_sym.width + 2, pos.y, pos.x);
        InitSettings(input_time_out);
        box(board_, 0, 0);
        Clear();
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

    int Input() noexcept {
        return wgetch(board_);
    }

    void Update() noexcept {
        for (std::size_t x {0}; x < grid_->GetWidth(); ++x) {
            for (std::size_t y {0}; y < grid_->GetHeight(); ++y) {
                if (grid_->Filled({x, y})) {
                    const ColorEnvironment env {board_,
                                                grid_->GetColor({x, y})};
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
        for (std::size_t x {0}; x < grid_->GetWidth(); ++x) {
            for (std::size_t y {0}; y < grid_->GetHeight(); ++y) {
                mvwaddch(board_, y + 1, x * cell_sym.width + 1, cell_sym.blank);
            }
        }

        Refresh();
    }

    ~GridBoard() noexcept {
        delwin(board_);
    }

private:
    void InitSettings(
        const std::chrono::steady_clock::duration input_time_out) noexcept {
        const auto milliseconds {
            std::chrono::duration_cast<std::chrono::milliseconds>(
                input_time_out)
                .count()};
        assert(milliseconds <= std::numeric_limits<int>::max());
        noecho();
        cbreak();
        curs_set(0);
        keypad(board_, true);
        wtimeout(board_, milliseconds);
    }

    void Refresh() noexcept {
        wrefresh(board_);
    }

    WINDOW* board_;

    std::shared_ptr<const Grid> grid_;
};

}  // namespace ui