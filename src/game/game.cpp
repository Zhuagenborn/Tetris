#include "game.h"

#include <algorithm>
#include <cassert>


GameSettings& GameSettings::SetNextCount(const std::size_t count) noexcept {
    next_count_ = std::max<decltype(next_count_)>(1, count);
    return *this;
}

GameSettings& GameSettings::SetDescendTime(
    const std::chrono::steady_clock::duration time) noexcept {
    descend_time_ = time;
    return *this;
}

Game::Game(std::shared_ptr<Grid> grid, GameSettings settings) noexcept :
    grid_ {std::move(grid)}, settings_ {std::move(settings)} {}

std::size_t Game::GetScore() const noexcept {
    const std::lock_guard lock {mtx_};
    return score_;
}

std::shared_ptr<const Grid> Game::GetGrid() const noexcept {
    return grid_;
}

Game::~Game() noexcept {
    if (descend_loop_) {
        descend_loop_->join();
    }
}

const GameSettings& Game::GetSettings() const noexcept {
    return settings_;
}

bool Game::IsOver() const noexcept {
    const std::lock_guard lock {mtx_};
    return !running_;
}

void Game::Start() noexcept {
    assert(!descend_loop_);
    grid_->Reset();
    score_ = 0;
    running_ = true;
    GenerateNextTetrominoes(settings_.GetNextCount());
    const auto pushed {PushNextTetromino()};
    assert(pushed);

    descend_loop_ = std::make_unique<std::thread>([this]() {
        while (!IsOver()) {
            Act(Action::Descend);
            std::this_thread::sleep_for(settings_.GetDescendTime());
        }
    });
}

ActionResult Game::Act(const Action action) noexcept {
    if (IsOver()) {
        return ActionResult::GameOver;
    }

    const std::lock_guard lock {mtx_};
    auto succeeded {false};
    switch (action) {
        case Action::Non: {
            return ActionResult::Succeeded;
        }
        case Action::MoveToLeft: {
            succeeded = grid_->MoveTetrominoToLeft();
            break;
        }
        case Action::MoveToRight: {
            succeeded = grid_->MoveTetrominoToRight();
            break;
        }
        case Action::RotateLeft: {
            succeeded = grid_->RotateTetrominoLeft();
            break;
        }
        case Action::RotateRight: {
            succeeded = grid_->RotateTetrominoRight();
            break;
        }
        case Action::Descend: {
            std::size_t cleared_line_count {0};
            succeeded = grid_->TetrominoDescend(cleared_line_count);
            score_ += cleared_line_count;
            if (!succeeded) {
                if (PushNextTetromino()) {
                    return ActionResult::TetrominoFixed;
                } else {
                    running_ = false;
                    return ActionResult::GameOver;
                }
            } else {
                return ActionResult::Succeeded;
            }
        }
        default: {
            assert(false);
        }
    }

    return succeeded ? ActionResult::Succeeded : ActionResult::Failed;
}

std::vector<std::reference_wrapper<const Tetromino>> Game::GetNextTetrominoes()
    const noexcept {
    const std::lock_guard lock {mtx_};
    std::vector<std::reference_wrapper<const Tetromino>> tetrominoes;
    std::ranges::for_each(next_tetrominoes_,
                          [&tetrominoes](const auto& tetromino) noexcept {
                              tetrominoes.push_back(*tetromino);
                          });
    return tetrominoes;
}

bool Game::PushNextTetromino() noexcept {
    assert(!next_tetrominoes_.empty());
    const auto pushed {
        grid_->PushTetromino(std::move(next_tetrominoes_.front()))};
    GenerateNextTetrominoes(1);
    return pushed;
}

void Game::GenerateNextTetrominoes(const std::size_t count) noexcept {
    for (std::size_t i {0}; i < count; ++i) {
        const auto type {tetromino::GetRandomType()};
        next_tetrominoes_.push_back(tetromino::Create(type));

        if (next_tetrominoes_.size() > settings_.GetNextCount()) {
            next_tetrominoes_.pop_front();
        }
    }
}