/**
 * @file color.h
 * @brief Graphic colors.
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

/**
 * @warning
 * The developer must place @p Non first and @p White last.
 * They are used to count the number of colors.
 */
enum class Color { Non, Red, Green, Blue, Yellow, Magenta, Cyan, White };

std::string to_string(Color) noexcept;

std::ostream& operator<<(std::ostream&, Color) noexcept;

Color GetRandomColor() noexcept;

/**
 * @interface Colored
 */
class Colored {
public:
    virtual Color GetColor() const noexcept = 0;

    virtual void SetColor(Color) noexcept = 0;

    virtual ~Colored() noexcept = default;
};