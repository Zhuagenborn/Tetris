/**
 * @file z.h
 * @brief The underlying shape of the tetromino @p Z.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
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

namespace z {

/**
 * The shape is:
 *
 * ```
 * O O
 *   O O
 * ```
 */
class Horizontal : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {2};

    static constexpr std::size_t width_ {3};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, false}, {true, true}, {false, true}}};
};

/**
 * The shape is:
 *
 * ```
 *   O
 * O O
 * O
 * ```
 */
class Vertical : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {3};

    static constexpr std::size_t width_ {2};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{false, true, true}, {true, true, false}}};
};

using Degree0 = Horizontal;

using Degree90 = Vertical;

}  // namespace z

}  // namespace shape