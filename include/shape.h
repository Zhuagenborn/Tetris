/**
 * @file shape.h
 * @brief The basic shape.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-28
 */

#pragma once

#include "location.h"

#include <concepts>

/**
 * @concept Is2DArray
 * A 2D array type with values that can be converted to @p bool.
 */
template <typename T>
concept Is2DArray = requires(T o) {
    { o[0][0] } -> std::convertible_to<bool>;
    { o.size() } -> std::convertible_to<std::size_t>;
};

/**
 * @interface Shape
 */
class Shape {
public:
    virtual std::size_t GetHeight() const noexcept = 0;

    virtual std::size_t GetWidth() const noexcept = 0;

    //! Whether a position is filled.
    virtual bool Filled(const Point&) const noexcept = 0;

    virtual ~Shape() noexcept = default;

protected:
    /**
     * @brief Whether a position is filled.
     *
     * @param cells A 2D array of cells.
     * @param pos A position.
     * @param filled_if_over_border Filled or not if the position exceeds the cells border.
     */
    template <Is2DArray Cells>
    static bool Filled(const Cells& cells, const Point& pos,
                       const bool filled_if_over_border = false) noexcept {
        if (pos.x < cells.size() && pos.y < cells[0].size()) {
            return cells[pos.x][pos.y];
        } else {
            return filled_if_over_border;
        }
    }
};

/**
 * Implement the @p Shape interface.
 */
#define IMPLEMENT_SHAPE(width, height, cells)                   \
    constexpr std::size_t GetHeight() const noexcept override { \
        return height;                                          \
    }                                                           \
                                                                \
    constexpr std::size_t GetWidth() const noexcept override {  \
        return width;                                           \
    }                                                           \
                                                                \
    bool Filled(const Point& pos) const noexcept override {     \
        return Shape::Filled(cells, pos);                       \
    }