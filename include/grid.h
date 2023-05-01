/**
 * @file grid.h
 * @brief The playing field.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "tetromino.h"

#include <iostream>
#include <memory>
#include <optional>
#include <vector>


/**
 * The cell used for building a playing field.
 */
class Cell : public Colored {
public:
    bool Filled() const noexcept;

    void Clear() noexcept;

    Color GetColor() const noexcept override;

    void SetColor(Color) noexcept override;

    operator bool() const noexcept {
        return Filled();
    }

private:
    Color color_ {Color::Non};
};

/**
 * A playing field.
 */
class Grid : public Shape {
public:
    Grid(std::size_t width, std::size_t height) noexcept;

    std::size_t GetHeight() const noexcept override;

    std::size_t GetWidth() const noexcept override;

    //! Whether a position is filled by fixed tetrominoes or the current tetromino.
    bool Filled(const Point&) const noexcept override;

    Color GetColor(const Point&) const noexcept;

    /**
     * @brief Push a tetromino into the grid.
     *
     * @return Whether the push succeeded. If it failed, the game should be over.
     */
    bool PushTetromino(std::unique_ptr<Tetromino>,
                       std::optional<Point> pos = std::nullopt) noexcept;

    /**
     * @brief Try to move the current tetromino 1 cell to the left.
     *
     * @return Whether the movement succeeded.
     */
    bool MoveTetrominoToLeft() noexcept;

    /**
     * @brief Try to move the current tetromino 1 cell to the right.
     *
     * @return Whether the movement succeeded.
     */
    bool MoveTetrominoToRight() noexcept;

    /**
     * @brief Try to rotate the current tetromino to the left by 90 degrees.
     *
     * @return Whether the rotation succeeded.
     */
    bool RotateTetrominoLeft() noexcept;

    /**
     * @brief Try to rotate the current tetromino to the right by 90 degrees.
     *
     * @return Whether the rotation succeeded.
     */
    bool RotateTetrominoRight() noexcept;

    /**
     * @brief
     * Try to descend the current tetromino by 1 cell.
     *
     * If the descent failed, the current tetromino will be fixed and full lines will be cleared.
     * A new tetromino should be pushed by calling @p PushTetromino.
     *
     * @param[out] cleared_line_count The number of cleared lines.
     * @return Whether the descent succeeded.
     */
    bool TetrominoDescend(std::size_t& cleared_line_count) noexcept;

    void Reset() noexcept;

private:
    static constexpr std::size_t min_width_ {4};

    static constexpr std::size_t min_height_ {4};

    /**
     * Whether a position is filled by fixed tetrominoes.
     * Unlike @p Filled, this method ignores the current tetromino.
     */
    bool FilledCell(const Point&) const noexcept;

    //! Whether a position is filled by the current tetromino.
    bool FilledByTetromino(const Point&) const noexcept;

    //! Whether a shape has a collision in a position.
    bool HasCollision(const Shape&, const Point&) const noexcept;

    //! Whether the current tetromino can be moved to a position.
    bool CanMoveTetrominoTo(const Point&) const noexcept;

    //! Try to move the current tetromino to a position.
    bool MoveTetrominoTo(const Point&) noexcept;

    void ClearCells(const Point& pos, const std::size_t x_len,
                    const std::size_t y_len) noexcept;

    //! Fix the current tetromino to the grid.
    void FixTetromino() noexcept;

    /**
     * @brief Clear all full lines.
     *
     * @return The number of cleared lines.
     */
    std::size_t ClearLines() noexcept;

    //! Clear a full line.
    void ClearLine(std::size_t y) noexcept;

    //! Whether a line is full.
    bool IsLineFull(std::size_t y) const noexcept;

    //! Whether a line is empty.
    bool IsLineEmpty(std::size_t y) const noexcept;

    std::size_t width_;

    std::size_t height_;

    //! The push entrance of tetrominoes.
    Point entrance_;

    std::vector<std::vector<Cell>> cells_;

    std::unique_ptr<Tetromino> tetromino_;
};

//! Print a grid, usually only for debugging.
std::ostream& operator<<(std::ostream&, const Grid&) noexcept;