
#include <iostream>

class Tuple
{
public:
    float x, y, z, w;

    Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static Tuple Point(float x, float y, float z)
    {
        return Tuple(x, y, z, 1.0f);
    }

    static Tuple Vector(float x, float y, float z)
    {
        return Tuple(x, y, z, 0.0f);
    }

    bool is_point() const
    {
        return w == 1.0f;
    }

    bool is_vector() const
    {
        return w == 0.0f;
    }

    bool operator==(const Tuple &other) const
    {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    }

       friend std::ostream& operator<<(std::ostream& os, const Tuple& t) {
        return os << "Tuple(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
    }
};