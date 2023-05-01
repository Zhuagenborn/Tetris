#include "tetromino.h"
#include "subtype/i.h"
#include "subtype/j.h"
#include "subtype/l.h"
#include "subtype/o.h"
#include "subtype/s.h"
#include "subtype/t.h"
#include "subtype/z.h"

#include <cassert>
#include <chrono>
#include <random>
#include <unordered_map>


Tetromino::Tetromino(const Angle angle,
                     const std::optional<Color> color) noexcept :
    Rotatable {angle} {
    if (color.value_or(Color::Non) == Color::Non) {
        SetColor(GetRandomColor());
    } else {
        SetColor(color.value());
    }

    assert(GetColor() != Color::Non);
}

Color Tetromino::GetColor() const noexcept {
    return color_;
}

void Tetromino::SetColor(const Color color) noexcept {
    color_ = color;
}

Point Tetromino::GetPosition() const noexcept {
    return pos_;
}

void Tetromino::SetPosition(Point pos) noexcept {
    pos_ = std::move(pos);
}

std::size_t Tetromino::GetHeight() const noexcept {
    return GetShape().GetHeight();
}

std::size_t Tetromino::GetWidth() const noexcept {
    return GetShape().GetWidth();
}

bool Tetromino::Filled(const Point& pos) const noexcept {
    return GetShape().Filled(pos);
}

const Shape& Tetromino::GetShape() const noexcept {
    return GetShape(GetAngle());
}

namespace tetromino {

/**
 * @brief Implement the @p GetShape method for a tetromino type with two types of rotated shapes.
 *
 * @tparam T A tetromino type.
 * @param t A namespace containing two shape definitions: @p Degree0 and @p Degree90.
 */
#define IMPLEMENT_TWO_DEGREES_GET_SHAPE(T, t)                    \
    const Shape& T::GetShape(const Angle angle) const noexcept { \
        switch (angle) {                                         \
            case Angle::Degree0:                                 \
            case Angle::Degree180: {                             \
                static const shape::t::Degree0 t;                \
                return t;                                        \
            }                                                    \
            case Angle::Degree90:                                \
            case Angle::Degree270: {                             \
                static const shape::t::Degree90 t;               \
                return t;                                        \
            }                                                    \
            default: {                                           \
                assert(false);                                   \
            }                                                    \
        }                                                        \
    }

/**
 * @brief Implement the @p GetShape method for a tetromino type with fours types of rotated shapes.
 *
 * @tparam T A tetromino type.
 * @param t A namespace containing four shape definitions from @p Degree0 to @p Degree270.
 */
#define IMPLEMENT_FOUR_DEGREES_GET_SHAPE(T, t)                   \
    const Shape& T::GetShape(const Angle angle) const noexcept { \
        switch (angle) {                                         \
            case Angle::Degree0: {                               \
                static const shape::t::Degree0 t;                \
                return t;                                        \
            }                                                    \
            case Angle::Degree90: {                              \
                static const shape::t::Degree90 t;               \
                return t;                                        \
            }                                                    \
            case Angle::Degree180: {                             \
                static const shape::t::Degree180 t;              \
                return t;                                        \
            }                                                    \
            case Angle::Degree270: {                             \
                static const shape::t::Degree270 t;              \
                return t;                                        \
            }                                                    \
            default: {                                           \
                assert(false);                                   \
            }                                                    \
        }                                                        \
    }

Type GetRandomType() noexcept {
    using TypeInt = std::underlying_type_t<Type>;
    static std::default_random_engine eng {static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count())};
    static std::uniform_int_distribution dist(static_cast<TypeInt>(Type::I),
                                              static_cast<TypeInt>(Type::Z));
    return static_cast<Type>(dist(eng));
}

std::string to_string(const Type type) noexcept {
    const static std::unordered_map<Type, std::string_view> names {
        {Type::O, "O"}, {Type::I, "I"}, {Type::T, "T"}, {Type::J, "J"},
        {Type::S, "S"}, {Type::Z, "Z"}, {Type::L, "L"}};

    assert(names.contains(type));
    return names.at(type).data();
}

std::ostream& operator<<(std::ostream& io, const Type type) noexcept {
    return io << to_string(type);
}

std::unique_ptr<Tetromino> Create(const Type type, const Angle angle,
                                  std::optional<Color> color) noexcept {
    switch (type) {
        case Type::O: {
            return std::make_unique<tetromino::O>(angle, std::move(color));
        }
        case Type::I: {
            return std::make_unique<tetromino::I>(angle, std::move(color));
        }
        case Type::J: {
            return std::make_unique<tetromino::J>(angle, std::move(color));
        }
        case Type::L: {
            return std::make_unique<tetromino::L>(angle, std::move(color));
        }
        case Type::Z: {
            return std::make_unique<tetromino::Z>(angle, std::move(color));
        }
        case Type::S: {
            return std::make_unique<tetromino::S>(angle, std::move(color));
        }
        case Type::T: {
            return std::make_unique<tetromino::T>(angle, std::move(color));
        }
        default: {
            assert(false);
        }
    }
}

const Shape& O::GetShape(Angle) const noexcept {
    static const shape::O o;
    return o;
}

IMPLEMENT_TWO_DEGREES_GET_SHAPE(I, i)
IMPLEMENT_TWO_DEGREES_GET_SHAPE(S, s)
IMPLEMENT_TWO_DEGREES_GET_SHAPE(Z, z)
IMPLEMENT_FOUR_DEGREES_GET_SHAPE(L, l)
IMPLEMENT_FOUR_DEGREES_GET_SHAPE(T, t)
IMPLEMENT_FOUR_DEGREES_GET_SHAPE(J, j)

}  // namespace tetromino