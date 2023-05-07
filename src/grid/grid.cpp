#include "grid.h"

#include <cassert>


void Cell::Clear() noexcept {
    SetColor(Color::Non);
}

bool Cell::Filled() const noexcept {
    return GetColor() != Color::Non;
}

Color Cell::GetColor() const noexcept {
    return color_;
}

void Cell::SetColor(const Color color) noexcept {
    color_ = color;
}

Angle Grid::MovableTetromino::GetAngle() const noexcept {
    return tetromino_->GetAngle();
}

void Grid::MovableTetromino::RotateLeft() noexcept {
    tetromino_->RotateLeft();
}

void Grid::MovableTetromino::RotateRight() noexcept {
    tetromino_->RotateRight();
}

void Grid::MovableTetromino::RotateTo(const Angle angle) noexcept {
    tetromino_->RotateTo(angle);
}

void Grid::MovableTetromino::SetPosition(Point pos) noexcept {
    pos_ = std::move(pos);
}

Point Grid::MovableTetromino::GetPosition() const noexcept {
    return pos_;
}

Grid::MovableTetromino::MovableTetromino(std::unique_ptr<Tetromino> tetromino,
                                         Point pos) noexcept :
    tetromino_ {std::move(tetromino)}, pos_ {std::move(pos)} {}

std::size_t Grid::MovableTetromino::GetHeight() const noexcept {
    return tetromino_->GetHeight();
}

std::size_t Grid::MovableTetromino::GetWidth() const noexcept {
    return tetromino_->GetWidth();
}

bool Grid::MovableTetromino::Filled(const Point& pos) const noexcept {
    return tetromino_->Filled(pos);
}

Color Grid::MovableTetromino::GetColor() const noexcept {
    return tetromino_->GetColor();
}

void Grid::MovableTetromino::SetColor(const Color color) noexcept {
    return tetromino_->SetColor(color);
}

std::unique_ptr<Grid::MovableTetromino>
Grid::MovableTetromino::GetTetrominoByAngle(const Angle angle) const noexcept {
    return std::make_unique<MovableTetromino>(
        tetromino_->GetTetrominoByAngle(angle), pos_);
}

Grid::Grid(const std::size_t width, const std::size_t height) noexcept :
    width_ {width}, height_ {height} {
    assert(width_ >= min_width_ && height_ >= min_height_);
    entrance_ = {width_ / 2, 0};
    cells_.resize(width_);
    for (auto& col : cells_) {
        col.resize(height_);
    }
}

std::size_t Grid::GetHeight() const noexcept {
    return height_;
}

std::size_t Grid::GetWidth() const noexcept {
    return width_;
}

Color Grid::GetColor(const Point& pos) const noexcept {
    if (FilledByTetromino(pos)) {
        return tetromino_->GetColor();
    } else if (pos.x < width_ && pos.y < height_) {
        return cells_[pos.x][pos.y].GetColor();
    } else {
        return Color::Non;
    }
}

bool Grid::Filled(const Point& pos) const noexcept {
    if (FilledCell(pos)) {
        return true;
    } else {
        return FilledByTetromino(pos);
    }
}

bool Grid::FilledCell(const Point& pos) const noexcept {
    return Shape::Filled<decltype(cells_)>(cells_, pos, true);
}

void Grid::Reset() noexcept {
    tetromino_.reset();
    ClearCells({0, 0}, width_, height_);
}

bool Grid::PushTetromino(std::unique_ptr<Tetromino> tetromino,
                         const std::optional<Point> pos) noexcept {
    assert(!tetromino_);
    tetromino_ = std::make_unique<MovableTetromino>(std::move(tetromino));
    if (MoveTetrominoTo(pos.value_or(entrance_))) {
        return true;
    } else {
        tetromino_.reset();
        return false;
    }
}

bool Grid::HasCollision(const Shape& shape, const Point& pos) const noexcept {
    for (std::size_t i {0}; i < shape.GetWidth(); ++i) {
        for (std::size_t j {0}; j < shape.GetHeight(); ++j) {
            if (FilledCell({pos.x + i, pos.y + j}) && shape.Filled({i, j})) {
                return true;
            }
        }
    }

    return false;
}

bool Grid::CanMoveTetrominoTo(const Point& pos) const noexcept {
    assert(tetromino_);
    return !HasCollision(*tetromino_, pos);
}

bool Grid::MoveTetrominoTo(const Point& pos) noexcept {
    assert(tetromino_);
    if (CanMoveTetrominoTo(pos)) {
        tetromino_->SetPosition(pos);
        return true;
    } else {
        return false;
    }
}

void Grid::ClearCells(const Point& pos, const std::size_t x_len,
                      const std::size_t y_len) noexcept {
    for (std::size_t i {0}; i < x_len; ++i) {
        for (std::size_t j {0}; j < y_len; ++j) {
            const auto x {pos.x + i};
            const auto y {pos.y + j};
            if (x < width_ && y < height_) {
                cells_[x][y].Clear();
            }
        }
    }
}

bool Grid::IsLineFull(const std::size_t y) const noexcept {
    assert(y < height_);
    for (std::size_t x {0}; x < width_; ++x) {
        if (!Filled({x, y})) {
            return false;
        }
    }

    return true;
}

bool Grid::IsLineEmpty(const std::size_t y) const noexcept {
    assert(y < height_);
    for (std::size_t x {0}; x < width_; ++x) {
        if (Filled({x, y})) {
            return false;
        }
    }

    return true;
}

void Grid::FixTetromino() noexcept {
    assert(tetromino_);
    const auto pos {tetromino_->GetPosition()};
    const auto color {tetromino_->GetColor()};
    assert(!CanMoveTetrominoTo({pos.x, pos.y + 1}));
    for (std::size_t i {0}; i < tetromino_->GetWidth(); ++i) {
        for (std::size_t j {0}; j < tetromino_->GetHeight(); ++j) {
            if (tetromino_->Filled({i, j})) {
                cells_[pos.x + i][pos.y + j].SetColor(color);
            }
        }
    }

    tetromino_.reset();
}

void Grid::ClearLine(std::size_t y) noexcept {
    assert(!tetromino_);
    assert(IsLineFull(y));
    while (y > 0) {
        --y;
        for (std::size_t x {0}; x < width_; ++x) {
            cells_[x][y + 1] = cells_[x][y];
        }

        if (IsLineEmpty(y)) {
            break;
        }
    }
}

std::size_t Grid::ClearLines() noexcept {
    std::size_t count {0};
    std::size_t y {height_};
    while (y > 0) {
        --y;
        if (IsLineEmpty(y)) {
            break;
        } else if (IsLineFull(y)) {
            ClearLine(y);
            ++y;
            ++count;
        }
    }

    return count;
}

bool Grid::MoveTetrominoToLeft() noexcept {
    assert(tetromino_);
    const auto pos {tetromino_->GetPosition()};
    return pos.x > 0 ? MoveTetrominoTo({pos.x - 1, pos.y}) : false;
}

bool Grid::MoveTetrominoToRight() noexcept {
    assert(tetromino_);
    const auto pos {tetromino_->GetPosition()};
    return MoveTetrominoTo({pos.x + 1, pos.y});
}

bool Grid::RotateTetrominoLeft() noexcept {
    assert(tetromino_);
    const auto angle {RotateAngleLeft(tetromino_->GetAngle())};
    const auto rotated {tetromino_->GetTetrominoByAngle(angle)};
    if (!HasCollision(*rotated, rotated->GetPosition())) {
        tetromino_->RotateLeft();
        return true;
    } else {
        return false;
    }
}

bool Grid::RotateTetrominoRight() noexcept {
    assert(tetromino_);
    const auto angle {RotateAngleRight(tetromino_->GetAngle())};
    const auto rotated {tetromino_->GetTetrominoByAngle(angle)};
    if (!HasCollision(*rotated, rotated->GetPosition())) {
        tetromino_->RotateRight();
        return true;
    } else {
        return false;
    }
}

bool Grid::FilledByTetromino(const Point& pos) const noexcept {
    if (tetromino_) {
        if (const auto tetromino_pos {tetromino_->GetPosition()};
            pos.x >= tetromino_pos.x && pos.y >= tetromino_pos.y) {
            return tetromino_->Filled(
                {pos.x - tetromino_pos.x, pos.y - tetromino_pos.y});
        }
    }

    return false;
}

bool Grid::TetrominoDescend(std::size_t& cleared_line_count) noexcept {
    assert(tetromino_);
    cleared_line_count = 0;
    const auto pos {tetromino_->GetPosition()};
    const auto moved {MoveTetrominoTo({pos.x, pos.y + 1})};
    if (!moved) {
        FixTetromino();
        cleared_line_count = ClearLines();
    }

    return moved;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid) noexcept {
    for (std::size_t y {0}; y < grid.GetHeight(); ++y) {
        for (std::size_t x {0}; x < grid.GetWidth(); ++x) {
            os << (grid.Filled({x, y}) ? 'O' : '.');
            if (x != grid.GetWidth() - 1) {
                os << ' ';
            }
        }

        os << '\n';
    }

    return os;
}