/**
 * @file s.h
 * @brief The underlying shape of the tetromino @p S.
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

namespace s {

/**
 * @brief The tetromino @p S.
 *
 * @details
 * The shape is:
 *
 * ```
 *   O O
 * O O
 * ```
 */
class Horizontal : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {2};

    static constexpr std::size_t width_ {3};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{false, true}, {true, true}, {true, false}}};
};

/**
 * @brief The tetromino @p S.
 *
 * @details
 * The shape is:
 *
 * ```
 * O
 * O O
 *   O
 * ```
 */
class Vertical : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {3};

    static constexpr std::size_t width_ {2};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, true, false}, {false, true, true}}};
};

using Degree0 = Horizontal;

using Degree90 = Vertical;

}  // namespace s

}  // namespace shape