/**
 * @file i.h
 * @brief The underlying shape of the tetromino @p I.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "shape.h"

#include <array>


namespace shape {

namespace i {

/**
 * @brief The horizontal tetromino @p I.
 *
 * @details
 * The shape is:
 *
 * ```
 * O O O O
 * ```
 */
class Horizontal : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {1};

    static constexpr std::size_t width_ {4};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true}, {true}, {true}, {true}}};
};

/**
 * @brief The vertical tetromino @p I.
 *
 * @details
 * The shape is:
 *
 * ```
 * O
 * O
 * O
 * O
 * ```
 */
class Vertical : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {4};

    static constexpr std::size_t width_ {1};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, true, true, true}}};
};

using Degree0 = Vertical;

using Degree90 = Horizontal;

}  // namespace i

}  // namespace shape