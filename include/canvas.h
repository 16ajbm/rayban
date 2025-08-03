#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
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

    Tuple& pixel(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel is out of bounds");
        }

        return pixels[y * width + x];
    }
};

#endif  // CANVAS_H