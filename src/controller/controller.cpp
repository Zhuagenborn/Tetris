#include "controller.h"
#include "ui/grid_board.h"
#include "ui/next_tetromino_board.h"
#include "ui/score_board.h"


class Controller::Impl {
public:
    Impl(std::unique_ptr<Game> game) noexcept : game_ {std::move(game)} {
        grid_board_ = std::make_unique<ui::GridBoard>(
            Point {0, 0}, game_->GetGrid(),
            game_->GetSettings().GetDescendTime());

        const Point score_board_pos {0, grid_board_->GetHeight()};
        score_board_ = std::make_unique<ui::ScoreBoard>(score_board_pos,
                                                        score_board_width);

        const Point next_tetromino_board_pos {grid_board_->GetWidth() + 2, 0};
        next_tetromino_board_ =
            std::make_unique<ui::NextTetrominoBoard>(next_tetromino_board_pos);
    }

    void Refresh() noexcept {
        score_board_->Update(game_->GetScore());
        grid_board_->Update();

        if (const auto next_tetrominoes {game_->GetNextTetrominoes()};
            !next_tetrominoes.empty()) {
            next_tetromino_board_->Update(next_tetrominoes.front());
        } else {
            next_tetromino_board_->Clear();
        }
    }

    void Input() noexcept {
        switch (grid_board_->Input()) {
            case 'w':
            case KEY_UP: {
                action_ = Action::RotateLeft;
                break;
            }
            case 's':
            case KEY_DOWN: {
                action_ = Action::Descend;
                break;
            }
            case 'a':
            case KEY_LEFT: {
                action_ = Action::MoveToLeft;
                break;
            }
            case 'd':
            case KEY_RIGHT: {
                action_ = Action::MoveToRight;
                break;
            }
            default: {
                action_ = Action::Non;
                break;
            }
        }
    }

    void Update() noexcept {
        game_->Act(action_);
    }

    bool IsOver() const noexcept {
        return game_->IsOver();
    }

private:
    static constexpr std::size_t score_board_width {10};

    std::unique_ptr<Game> game_;

    Action action_ {Action::Non};

    std::unique_ptr<ui::GridBoard> grid_board_;

    std::unique_ptr<ui::ScoreBoard> score_board_;

    std::unique_ptr<ui::NextTetrominoBoard> next_tetromino_board_;
};

//! The initializer for the @p ncurses library.
Controller::Initializer::Initializer() noexcept {
    initscr();
    refresh();
}

Controller::Initializer::~Initializer() noexcept {
    endwin();
}

Controller::Controller(std::unique_ptr<Game> game) noexcept :
    impl_ {std::make_unique<Impl>(std::move(game))} {}

Controller::~Controller() noexcept = default;

void Controller::Refresh() noexcept {
    impl_->Refresh();
}

void Controller::Input() noexcept {
    impl_->Input();
}

void Controller::Update() noexcept {
    impl_->Update();
}

bool Controller::IsOver() const noexcept {
    return impl_->IsOver();
}