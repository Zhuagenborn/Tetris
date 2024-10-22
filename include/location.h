/**
 * @file location.h
 * @brief The movable object and coordinate.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-28
 */

#pragma once

#include <cstddef>

//! A coordinate.
struct Point {
    constexpr Point(const std::size_t x = 0, const std::size_t y = 0) noexcept :
        x {x}, y {y} {}

    std::size_t x;
    std::size_t y;
};

class Locatable {
public:
    virtual Point GetPosition() const noexcept = 0;

    virtual ~Locatable() noexcept = default;
};

class Movable : public Locatable {
public:
    virtual void SetPosition(Point) noexcept = 0;

    virtual ~Movable() noexcept = default;
};