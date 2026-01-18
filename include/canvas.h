#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>

#include "tuple.h"

const int LINE_LENGTH_LIMIT = 70;

class Canvas {
   public:
    union {
        struct {
            int width, height;
        };
        struct {
            int w, h;
        };
    };

    std::vector<Tuple> pixels;

    Canvas(int width, int height) : width(width), height(height) {
        pixels.resize(width * height, Tuple::Colour(0.0f, 0.0f, 0.0f));
    }

    Canvas(int width, int height, const Tuple& default_colour)
        : width(width), height(height) {
        pixels.resize(width * height, default_colour);
    }

    void write_pixel(int x, int y, const Tuple& colour) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel is out of bounds");
        }
        pixels[y * width + x] = colour;
    }

    Tuple& pixel_at(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel is out of bounds");
        }

        return pixels[y * width + x];
    }

    std::string canvas_to_ppm(int max = 255) const {
        std::string ppm;
        ppm += "P3\n";
        ppm += std::to_string(width) + " " + std::to_string(height) + "\n";
        ppm += std::to_string(max) + "\n";

        std::string line;

        for (size_t pixel_idx = 0; pixel_idx < pixels.size(); ++pixel_idx) {
            const Tuple& pixel = pixels[pixel_idx];

            int r = clamp(static_cast<int>(std::round(pixel.r * max)), 0, max);
            int g = clamp(static_cast<int>(std::round(pixel.g * max)), 0, max);
            int b = clamp(static_cast<int>(std::round(pixel.b * max)), 0, max);

            for (const std::string& token :
                 {std::to_string(r), std::to_string(g), std::to_string(b)}) {
                std::string to_add = (line.empty() ? "" : " ") + token;

                if (line.length() + to_add.length() > LINE_LENGTH_LIMIT) {
                    ppm += line + "\n";
                    line = token;
                } else {
                    line += to_add;
                }
            }

            if (pixel_idx % width == width - 1) {
                ppm += line + "\n";
                line.clear();
            }
        }

        if (!line.empty()) {
            ppm += line + "\n";
        }
        return ppm;
    }
};

#endif  // CANVAS_H