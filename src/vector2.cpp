#include "vector2.h"
#include <iostream>
#include <sstream>
#include <cmath>

Vector2::Vector2(float x, float y)
    : x(x), y(y) {}

Vector2::Vector2()
    : x(0), y(0) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

float Vector2::dot(const Vector2& other) const {
    return x * other.x + y * other.y;
}

Vector2 Vector2::normalize() const {
    float magnitude = std::sqrt(x * x + y * y);

    if (magnitude == 0.0f) {
        return Vector2(0.0f, 0.0f);
    }

    return Vector2(x / magnitude, y / magnitude);
}

Vector2 Vector2::reflect(const Vector2& normal) const {
    return *this - normal * (2 * this->dot(normal));
}

float Vector2::distance(Vector2 other) const {
    float dx = x - other.x;
    float dy = y - other.y;

    return std::sqrt(dx * dx + dy * dy);
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2::print() const {
    std::cout << "{ " << x << " " << y << " }" << std::endl;
}

std::string Vector2::toString() const {
    std::ostringstream oss;
    oss << "{ " << x << ", " << y << " }";
    return oss.str();
}
