#include "color.h"

#include <cassert>
#include <chrono>
#include <random>
#include <unordered_map>


Color GetRandomColor() noexcept {
    using ColorInt = std::underlying_type_t<Color>;
    static std::default_random_engine eng {static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count())};
    static std::uniform_int_distribution dist(
        static_cast<ColorInt>(Color::Non) + 1,
        static_cast<ColorInt>(Color::White));
    return static_cast<Color>(dist(eng));
}

std::string to_string(const Color color) noexcept {
    const static std::unordered_map<Color, std::string_view> names {
        {Color::Non, "Non"},       {Color::Red, "Red"},
        {Color::Green, "Green"},   {Color::Blue, "Blue"},
        {Color::Yellow, "Yellow"}, {Color::Magenta, "Magenta"},
        {Color::Cyan, "Cyan"},     {Color::White, "White"},
    };

    assert(names.contains(color));
    return names.at(color).data();
}

std::ostream& operator<<(std::ostream& io, const Color color) noexcept {
    return io << to_string(color);
}