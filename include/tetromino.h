/**
 * @file tetromino.h
 * @brief
 * Tetrominoes including:
 *
 * - @p I
 * - @p O
 * - @p T
 * - @p J
 * - @p L
 * - @p S
 * - @p Z
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "color.h"
#include "rotation.h"
#include "shape.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>


namespace tetromino {

enum class Type { I, J, L, O, S, T, Z };

Type GetRandomType() noexcept;

std::string to_string(Type) noexcept;

std::ostream& operator<<(std::ostream&, Type) noexcept;

}  // namespace tetromino

/**
 * @interface Tetromino
 * A tetromino that can be rotated and colored.
 */
class Tetromino : public Shape, public Rotatable, public Colored {
public:
    Tetromino(Angle angle = Angle::Degree0,
              std::optional<Color> color = std::nullopt) noexcept;

    Angle GetAngle() const noexcept override;

    void RotateLeft() noexcept override;

    void RotateRight() noexcept override;

    void RotateTo(Angle) noexcept override;

    std::size_t GetHeight() const noexcept override;

    std::size_t GetWidth() const noexcept override;

    bool Filled(const Point&) const noexcept override;

    Color GetColor() const noexcept override;

    void SetColor(Color) noexcept override;

    virtual tetromino::Type GetType() const noexcept = 0;

    //! Given an angle, get the rotated tetromino.
    virtual std::unique_ptr<Tetromino> GetTetrominoByAngle(
        Angle) const noexcept = 0;

protected:
    //! Get the underlying shape of the current angle.
    const Shape& GetShape() const noexcept;

    //! Given an angle, get the underlying shape.
    virtual const Shape& GetShape(Angle) const noexcept = 0;

    //! Clone a tetromino and rotate it to an angle.
    template <typename T>
        requires std::is_base_of_v<Tetromino, T>
    static std::unique_ptr<Tetromino> CloneAndRotateTo(
        T tetromino, const Angle angle) noexcept {
        auto rotated {std::make_unique<T>(std::move(tetromino))};
        rotated->RotateTo(angle);
        return rotated;
    }

private:
    Angle angle_;

    Color color_ {Color::Non};
};

namespace tetromino {

std::unique_ptr<Tetromino> Create(
    Type type, Angle angle = Angle::Degree0,
    std::optional<Color> color = std::nullopt) noexcept;

//! Define a tetromino class for the type @p T.
#define DEFINE_TETROMINO(T)                                        \
    class T : public Tetromino {                                   \
    public:                                                        \
        using Tetromino::Tetromino;                                \
                                                                   \
        Type GetType() const noexcept override { return Type::T; } \
                                                                   \
        std::unique_ptr<Tetromino> GetTetrominoByAngle(            \
            const Angle angle) const noexcept override {           \
            return CloneAndRotateTo(*this, angle);                 \
        }                                                          \
                                                                   \
    protected:                                                     \
        const Shape& GetShape(Angle) const noexcept override;      \
    }

DEFINE_TETROMINO(O);
DEFINE_TETROMINO(I);
DEFINE_TETROMINO(T);
DEFINE_TETROMINO(J);
DEFINE_TETROMINO(L);
DEFINE_TETROMINO(S);
DEFINE_TETROMINO(Z);

}  // namespace tetromino