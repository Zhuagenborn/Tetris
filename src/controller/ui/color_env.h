/**
 * @file color_env.h
 * @brief The color mode.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "color.h"

#include <ncurses.h>

#include <unordered_map>


namespace ui {

/**
 * A color environment.
 */
class ColorEnvironment {
public:
    //! Try to enable a color environment.
    ColorEnvironment(WINDOW* const win, const Color color) noexcept :
        win_ {win}, color_ {color} {
        if (Enabled()) {
            wattron(win_, COLOR_PAIR(static_cast<short>(color_)));
        }
    }

    //! Disable the color environment.
    ~ColorEnvironment() noexcept {
        if (Enabled()) {
            wattroff(win_, COLOR_PAIR(static_cast<short>(color_)));
        }
    }

    //! Whether the color mode is enabled.
    static bool Enabled() noexcept {
        static const Initializer initer;
        return initer.Enabled();
    }

private:
    //! The initializer for the color mode.
    class Initializer {
    public:
        Initializer() noexcept {
            if (has_colors()) {
                enabled_ = true;
                start_color();
                const auto default_color {use_default_colors()};
                init_pair(static_cast<short>(Color::Non), default_color,
                          default_color);
                init_pair(static_cast<short>(Color::Red), COLOR_RED,
                          default_color);
                init_pair(static_cast<short>(Color::Green), COLOR_GREEN,
                          default_color);
                init_pair(static_cast<short>(Color::Blue), COLOR_BLUE,
                          default_color);
                init_pair(static_cast<short>(Color::Yellow), COLOR_YELLOW,
                          default_color);
                init_pair(static_cast<short>(Color::Magenta), COLOR_MAGENTA,
                          default_color);
                init_pair(static_cast<short>(Color::Cyan), COLOR_CYAN,
                          default_color);
                init_pair(static_cast<short>(Color::White), COLOR_WHITE,
                          default_color);
            }
        }

        bool Enabled() const noexcept {
            return enabled_;
        }

    private:
        bool enabled_ {false};
    };

    Color color_;

    WINDOW* win_;
};

}  // namespace ui