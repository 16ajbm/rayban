#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>

const float EPSILON = 1e-5;

inline bool is_equal(float a, float b) { return fabs(a - b) < EPSILON; }

inline int clamp(int value, int min_value, int max_value) {
    return std::max(min_value, std::min(value, max_value));
}

inline float clamp(float value, float min_value, float max_value) {
    return std::max(min_value, std::min(value, max_value));
}

#endif  // HELPERS_H