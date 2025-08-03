#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>

#include "tuple.h"

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

    void write_pixel(int x, int y, const Tuple& color) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel is out of bounds");
        }
        pixels[y * width + x] = color;
    }

    Tuple& pixel_at(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel is out of bounds");
        }

        return pixels[y * width + x];
    }

    std::string canvas_to_ppm() const {
        std::string ppm;
        ppm += "P3\n";
        ppm += std::to_string(width) + " " + std::to_string(height) + "\n";
        ppm += "255\n";

        return ppm;
    }
};

#endif  // CANVAS_H