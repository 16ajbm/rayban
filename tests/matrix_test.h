#include <boost/test/unit_test.hpp>

#include "matrix.h"

BOOST_AUTO_TEST_SUITE(MatrixTests)

BOOST_AUTO_TEST_CASE(Construct4x4MatrixCase) {
    auto matrix = Matrix<float>({{1.0, 2.0, 3.0, 4.0},
                                 {5.5, 6.5, 7.5, 8.5},
                                 {9.0, 10.0, 11.0, 12.0},
                                 {13.5, 14.5, 15.5, 16.5}});

    BOOST_CHECK_EQUAL(matrix(0, 0), 1.0);
    BOOST_CHECK_EQUAL(matrix(0, 3), 4.0);
    BOOST_CHECK_EQUAL(matrix(1, 0), 5.5);
    BOOST_CHECK_EQUAL(matrix(1, 2), 7.5);
    BOOST_CHECK_EQUAL(matrix(2, 2), 11.0);
    BOOST_CHECK_EQUAL(matrix(3, 0), 13.5);
    BOOST_CHECK_EQUAL(matrix(3, 2), 15.5);
}

BOOST_AUTO_TEST_CASE(Construct2x2MatrixCase) {
    auto matrix = Matrix<float>({{-3.0, 5.0}, {1.5, -2.0}});

    BOOST_CHECK_EQUAL(matrix(0, 0), -3.0);
    BOOST_CHECK_EQUAL(matrix(0, 1), 5.0);
    BOOST_CHECK_EQUAL(matrix(1, 0), 1.5);
    BOOST_CHECK_EQUAL(matrix(1, 1), -2.0);
}

BOOST_AUTO_TEST_CASE(Construct3x3MatrixCase) {
    auto matrix =
        Matrix<float>({{-3.0, 5.0, 0.0}, {1.0, -2.0, -7.0}, {0.0, 1.0, 1.0}});

    BOOST_CHECK_EQUAL(matrix(0, 0), -3.0);
    BOOST_CHECK_EQUAL(matrix(1, 1), -2.0);
    BOOST_CHECK_EQUAL(matrix(2, 2), 1.0);
}

BOOST_AUTO_TEST_SUITE_END()
