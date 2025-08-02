#include <iostream>

#include "tuple.h"

struct Environment {
    Tuple gravity;
    Tuple wind;
};

struct Projectile {
    Tuple position;
    Tuple velocity;
};

Projectile tick(const Environment& env, const Projectile& proj) {
    Tuple position = proj.position + proj.velocity;
    Tuple velocity = proj.velocity + env.gravity + env.wind;

    return Projectile{position, velocity};
};

int main() {
    // Projectile
    Projectile projectile{Tuple::Point(0.0f, 1.0f, 0.0f),
                          Tuple::Vector(1.0f, 1.0f, 0.0f).normalize()};

    // Environment
    Environment env{Tuple::Vector(0.0f, -0.1f, 0.0f), Tuple::Vector(0.1f, 0.0f, 0.0f)};

    int ticks = 0;

    while (projectile.position.y >= 0.0f) {
        projectile = tick(env, projectile);
        std::cout << "Tick: " << ticks++ << std::endl;
        std::cout << "Position: " << projectile.position << std::endl;
    }

    return 0;
}
