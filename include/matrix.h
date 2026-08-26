#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>

class Matrix {
    using Row = std::initializer_list<T>;
    using NestedList = std::initializer_list<Row>;
    using Dimension = size_t;
    using DimensionPair = std::pair<Dimension, Dimension>;
    using MatrixData = std::vector<T>;

   public:
    Dimension n;
    Dimension m;
    MatrixData data;

    Matrix<T>(Dimension n, Dimension m, MatrixData data)
        : n(n), m(m), data(data) {
        if ((n == 0) || (m == 0)) {
            throw std::invalid_argument("dimension of size zero");
        }
    }

    Matrix<T>(NestedList rows) : Matrix(from_nested_list(rows)) {}

    static Matrix from_nested_list(NestedList rows) {
        DimensionPair dimension_pair = dimensions(rows);
        std::vector<T> flattened_data = flatten(rows);

        return Matrix(dimension_pair.first, dimension_pair.second,
                      flattened_data);
    };

    static DimensionPair dimensions(NestedList rows) {
        if (rows.size() == 0) {
            throw std::invalid_argument("empty list");
        }

        size_t m = rows.begin()[0].size();

        for (Row row : rows) {
            if (row.size() != m) {
                throw std::invalid_argument("inconsistent column size");
            }
        }

        return std::make_pair(rows.size(), m);
    };

    static MatrixData flatten(NestedList rows) {
        MatrixData matrix_data;
        DimensionPair dimension_pair = dimensions(rows);

        matrix_data.reserve(dimension_pair.first * dimension_pair.second);

        for (Row row : rows) {
            for (T value : row) {
                matrix_data.push_back(value);
            }
        }

        return matrix_data;
    };

    const T& operator()(size_t row, size_t col) const {
        if (is_out_of_bounds(row, col)) {
            throw std::invalid_argument("index out of range");
        }
        return data[index(row, col)];
    };

    T& operator()(size_t row, size_t col) {
        if (is_out_of_bounds(row, col)) {
            throw std::invalid_argument("index out of range");
        }
        return data[index(row, col)];
    }

    bool is_out_of_bounds(size_t row, size_t col) const {
        return ((row >= n) || (col >= m));
    }

    size_t index(size_t row, size_t col) const { return row * m + col; }
};

#endif  // TUPLE_H