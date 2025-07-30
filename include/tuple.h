
#include <iostream>

#include "helpers.h"

class Tuple {
   public:
    float x, y, z, w;

    Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static Tuple Point(float x, float y, float z) { return Tuple(x, y, z, 1.0f); }

    static Tuple Vector(float x, float y, float z) { return Tuple(x, y, z, 0.0f); }

    float magnitude() const { return sqrt(x * x + y * y + z * z + w * w); }

    Tuple normalize() const {
        float mag = this->magnitude();

        if (is_equal(mag, 0.0f)) {
            throw std::runtime_error("Cannot normalize a zero vector!");
        }
        return Tuple(x / mag, y / mag, z / mag, w / mag);
    }

    float dot(const Tuple& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    bool is_point() const { return is_equal(w, 1.0f); }

    bool is_vector() const { return is_equal(w, 0.0f); }

    bool operator==(const Tuple& other) const {
        return (is_equal(x, other.x) && is_equal(y, other.y) && is_equal(z, other.z) &&
                is_equal(w, other.w));
    }

    Tuple operator+(const Tuple& other) const {
        return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Tuple operator-() const { return Tuple(-x, -y, -z, -w); }

    Tuple operator-(const Tuple& other) const {
        return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Tuple operator*(float scalar) const {
        return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Tuple operator/(float scalar) const {
        if (is_equal(scalar, 0.0f)) {
            throw std::runtime_error("Divide by zero!");
        }
        return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    friend std::ostream& operator<<(std::ostream& os, const Tuple& t) {
        return os << "Tuple(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    }
};