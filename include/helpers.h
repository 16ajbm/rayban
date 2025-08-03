#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>

const float EPSILON = 1e-5;

inline bool is_equal(float a, float b) { return fabs(a - b) < EPSILON; }

#endif  // HELPERS_H