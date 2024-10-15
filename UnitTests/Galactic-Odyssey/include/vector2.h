#ifndef VECTOR2_HPP
#define VECTOR2_HPP
#include <string>

class Vector2 {
   public:
    float x, y;

    Vector2(float x, float y);
    Vector2();

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    float dot(const Vector2& other) const;
    Vector2 normalize() const;
    Vector2 reflect(const Vector2& normal) const;
    float distance(Vector2 other) const;
    float length() const;

    void print() const;
    std::string toString() const;
};

#endif
