#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "canvas.h"
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
    Environment env{Tuple::Vector(0.0f, -0.1f, 0.0f),
                    Tuple::Vector(0.1f, 0.0f, 0.0f)};

    // Canvas
    int canvas_height = 250;
    int canvas_width = 250;
    Canvas canvas(canvas_width, canvas_height, Tuple::Colour(0.0f, 0.0f, 0.0f));

    // File
    std::ofstream outFile("canvas.ppm");

    int ticks = 0;

    float scale = 10.0f;

    while (projectile.position.y >= 0.0f) {
        projectile = tick(env, projectile);
        std::cout << "Tick: " << ticks++ << std::endl;
        std::cout << "Position: " << projectile.position << std::endl;

        int x = static_cast<int>(std::round(projectile.position.x * scale));
        int y = static_cast<int>(std::round(projectile.position.y * scale));

        int canvas_x = x;
        int canvas_y = canvas_height - 1 - y;

        if (canvas_x > 0 && canvas_x < canvas_width && canvas_y > 0 &&
            canvas_y < canvas_height) {
            canvas.write_pixel(canvas_x, canvas_y,
                               Tuple::Colour(1.0f, 0.0f, 0.0f));
        }
    }

    std::string ppm = canvas.canvas_to_ppm();

    if (outFile.is_open()) {
        outFile << ppm;
        outFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return 0;
}
