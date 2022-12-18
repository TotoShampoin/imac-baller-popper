#include "vector.h"

Vec2 Vec2::operator-() {
    return Vec2 { -x, -y };
}

Vec2 Vec2::operator+(Vec2& other) {
    return Vec2 {
        this->x + other.x,
        this->y + other.y,
    };
}
Vec2 Vec2::operator-(Vec2& other) {
    return Vec2 {
        this->x - other.x,
        this->y - other.y,
    };
}
Vec2 Vec2::operator*(float other) {
    return Vec2 {
        this->x - other,
        this->y - other,
    };
}

Vec2& Vec2::operator+=(Vec2& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}
Vec2& Vec2::operator-=(Vec2& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
Vec2& Vec2::operator*=(float other) {
    this->x *= other;
    this->y *= other;
    return *this;
}

bool Vec2::operator==(Vec2& other) {
    return  this->x == other.x &&
            this->y == other.y;
}

float Vec2::magnitude2() {
    return x * x + y * y;
}
