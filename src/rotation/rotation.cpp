#include "rotation.h"

#include <cassert>
#include <unordered_map>


std::string to_string(const Angle angle) noexcept {
    const static std::unordered_map<Angle, std::string_view> names {
        {Angle::Degree0, "Degree 0"},
        {Angle::Degree90, "Degree 90"},
        {Angle::Degree180, "Degree 180"},
        {Angle::Degree270, "Degree 270"}};

    assert(names.contains(angle));
    return names.at(angle).data();
}

std::ostream& operator<<(std::ostream& io, const Angle angle) noexcept {
    return io << to_string(angle);
}

Rotatable::Rotatable(const Angle angle) noexcept : angle_ {angle} {}

Angle Rotatable::GetAngle() const noexcept {
    return angle_;
}

void Rotatable::RotateLeft() noexcept {
    angle_ = RotateAngleLeft(angle_);
}

void Rotatable::RotateRight() noexcept {
    angle_ = RotateAngleRight(angle_);
}

void Rotatable::RotateTo(const Angle angle) noexcept {
    angle_ = angle;
}