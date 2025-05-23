/**
 * @file t.h
 * @brief The underlying shape of the tetromino @p T.
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

namespace t {

/**
 * @brief The tetromino @p T.
 *
 * @details
 * The shape is:
 *
 * ```
 * O O O
 *   O
 * ```
 */
class Degree0 : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {2};

    static constexpr std::size_t width_ {3};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, false}, {true, true}, {true, false}}};
};

/**
 * @brief The tetromino @p T.
 *
 * @details
 * The shape is:
 *
 * ```
 * O
 * O O
 * O
 * ```
 */
class Degree90 : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {3};

    static constexpr std::size_t width_ {2};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{true, true, true}, {false, true, false}}};
};

/**
 * @brief The tetromino @p T.
 *
 * @details
 * The shape is:
 *
 * ```
 *   O
 * O O O
 * ```
 */
class Degree180 : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {2};

    static constexpr std::size_t width_ {3};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{false, true}, {true, true}, {false, true}}};
};

/**
 * @brief The tetromino @p T.
 *
 * @details
 * The shape is:
 *
 * ```
 *   O
 * O O
 *   O
 * ```
 */
class Degree270 : public Shape {
public:
    IMPLEMENT_SHAPE(width_, height_, cells_)

private:
    static constexpr std::size_t height_ {3};

    static constexpr std::size_t width_ {2};

    static inline constexpr std::array<std::array<bool, height_>, width_>
        cells_ {{{false, true, false}, {true, true, true}}};
};

}  // namespace t

}  // namespace shape