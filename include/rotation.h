/**
 * @file rotation.h
 * @brief Rotation operations.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-28
 */

#pragma once

#include <iostream>
#include <string>
#include <type_traits>


enum class Angle { Degree0, Degree90, Degree180, Degree270 };

constexpr std::size_t angle_count {4};

//! Rotate an angle to the left by 90 degrees.
constexpr Angle RotateAngleLeft(const Angle angle) noexcept {
    static_assert(std::is_convertible_v<std::underlying_type_t<Angle>, int>);

    const auto next {static_cast<std::underlying_type_t<Angle>>(angle) + 1};
    return static_cast<Angle>(next % angle_count);
}

//! Rotate an angle to the right by 90 degrees.
constexpr Angle RotateAngleRight(const Angle angle) noexcept {
    static_assert(std::is_convertible_v<std::underlying_type_t<Angle>, int>);

    if (const auto next {static_cast<std::underlying_type_t<Angle>>(angle) - 1};
        next >= 0) {
        return static_cast<Angle>(next);
    } else {
        return Angle::Degree270;
    }
}

std::string to_string(Angle) noexcept;

std::ostream& operator<<(std::ostream&, Angle) noexcept;

/**
 * @interface Rotatable
 */
class Rotatable {
public:
    virtual Angle GetAngle() const noexcept = 0;

    virtual void RotateLeft() noexcept = 0;

    virtual void RotateRight() noexcept = 0;

    virtual void RotateTo(Angle) noexcept = 0;

    virtual ~Rotatable() noexcept = default;
};