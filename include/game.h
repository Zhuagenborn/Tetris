/**
 * @file game.h
 * @brief Game actions and settings.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "grid.h"

#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>


enum class Action {
    Non,
    MoveToLeft,
    MoveToRight,
    RotateLeft,
    RotateRight,
    Descend
};

enum class ActionResult {
    //！ The action succeeded.
    Succeeded,

    //! The action failed.
    Failed,

    //! The descent failed and the current tetromino was fixed.
    TetrominoFixed,

    //! The game is over.
    GameOver
};

class GameSettings {
public:
    //! Set the number of next tetrominoes. The minimum is 1.
    GameSettings& SetNextCount(std::size_t) noexcept;

    //! Set the descent rate.
    GameSettings& SetDescendTime(std::chrono::steady_clock::duration) noexcept;

    constexpr std::size_t GetNextCount() const noexcept {
        return next_count_;
    }

    constexpr std::chrono::steady_clock::duration GetDescendTime()
        const noexcept {
        return descend_time_;
    }

private:
    std::size_t next_count_ {1};

    std::chrono::steady_clock::duration descend_time_ {
        std::chrono::seconds {1}};
};

class Game {
public:
    Game(std::shared_ptr<Grid>, GameSettings) noexcept;

    void Start() noexcept;

    ActionResult Act(Action) noexcept;

    std::size_t GetScore() const noexcept;

    bool IsOver() const noexcept;

    /**
     * @brief Get the next tetrominoes.
     *
     * @warning
     * When each time @p Action::Descend is executed and @p ActionResult::TetrominoFixed is returned,
     * the previous return value is longer be valid.
     */
    std::vector<std::reference_wrapper<const Tetromino>> GetNextTetrominoes()
        const noexcept;

    std::shared_ptr<const Grid> GetGrid() const noexcept;

    const GameSettings& GetSettings() const noexcept;

    ~Game() noexcept;

private:
    void GenerateNextTetrominoes(std::size_t) noexcept;

    bool PushNextTetromino() noexcept;

    mutable std::mutex mtx_;

    std::unique_ptr<std::thread> descend_loop_;

    std::shared_ptr<Grid> grid_;

    std::deque<std::unique_ptr<Tetromino>> next_tetrominoes_;

    std::size_t score_ {0};

    bool running_ {false};

    GameSettings settings_;
};