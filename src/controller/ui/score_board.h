/**
 * @file score_board.h
 * @brief A score board.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "board.h"


namespace ui {

class ScoreBoard : public Board {
public:
    ScoreBoard(const Point& pos, const std::size_t width) noexcept {
        assert(IsValidPosition(pos));
        assert(min_width <= width && width <= std::numeric_limits<int>::max());
        board_ = newwin(1, width, pos.y, pos.x);
        ShowTitle();
        Clear();
    }

    void Update(const std::size_t score) noexcept {
        wmove(board_, 0, title_.length());
        wclrtoeol(board_);
        mvwprintw(board_, 0, title_.length(), "%zu", score);
        Refresh();
    }

    void Clear() noexcept {
        Update(0);
    }

    ~ScoreBoard() noexcept {
        delwin(board_);
    }

    Point GetPosition() const noexcept override {
        return GetBoardPosition(board_);
    }

    std::size_t GetHeight() const noexcept override {
        return 1;
    }

    std::size_t GetWidth() const noexcept override {
        return GetBoardWidth(board_);
    }

private:
    static constexpr std::size_t min_width {9};

    static constexpr std::string_view title_ {"Score: "};

    void Refresh() noexcept {
        wrefresh(board_);
    }

    void ShowTitle() noexcept {
        mvwprintw(board_, 0, 0, title_.data());
    }

    WINDOW* board_;
};

}  // namespace ui