#include <boost/test/unit_test.hpp>

#include "tuple.h"

BOOST_AUTO_TEST_CASE(PointTestCase)
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;
    float w = 1.0f;

    // Make a tuple w/ w = 1.0
    auto point = Tuple(x, y, z, w);

    BOOST_CHECK_EQUAL(point.x, x);
    BOOST_CHECK_EQUAL(point.y, y);
    BOOST_CHECK_EQUAL(point.z, z);
    BOOST_CHECK_EQUAL(point.w, w);
    BOOST_CHECK_EQUAL(point.is_point(), true);
    BOOST_CHECK_EQUAL(point.is_vector(), false);
}

BOOST_AUTO_TEST_CASE(VectorTestCase)
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;
    float w = 0.0f;

    // Make a tuple w/ w = 0.0
    auto vector = Tuple(x, y, z, w);

    BOOST_CHECK_EQUAL(vector.x, x);
    BOOST_CHECK_EQUAL(vector.y, y);
    BOOST_CHECK_EQUAL(vector.z, z);
    BOOST_CHECK_EQUAL(vector.w, w);
    BOOST_CHECK_EQUAL(vector.is_point(), false);
    BOOST_CHECK_EQUAL(vector.is_vector(), true);
}

BOOST_AUTO_TEST_CASE(PointConstructorTestCase)
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    // Create a point using the constructor
    auto point = Tuple::Point(x, y, z);

    BOOST_CHECK_EQUAL(point, Tuple(x, y, z, 1.0f));
}

BOOST_AUTO_TEST_CASE(VectorConstructorTestCase)
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    // Create a vector using the constructor
    auto vector = Tuple::Vector(x, y, z);

    BOOST_CHECK_EQUAL(vector, Tuple(x, y, z, 0.0f));
}