/**
 * @file o.h
 * @brief The underlying shape of the tetromino @p O.
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

/**
 * The shape is:
 *
 * ```
 * O O
 * O O
 * ```
 */
class O : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {2};

    static constexpr std::size_t width_ {2};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, true}, {true, true}}};
};

}  // namespace shape