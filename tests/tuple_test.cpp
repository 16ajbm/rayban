#include "tuple.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(PointTestCase) {
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

BOOST_AUTO_TEST_CASE(VectorTestCase) {
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

BOOST_AUTO_TEST_CASE(PointConstructorTestCase) {
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    // Create a point using the constructor
    auto point = Tuple::Point(x, y, z);

    BOOST_CHECK_EQUAL(point, Tuple(x, y, z, 1.0f));
}

BOOST_AUTO_TEST_CASE(VectorConstructorTestCase) {
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    // Create a vector using the constructor
    auto vector = Tuple::Vector(x, y, z);

    BOOST_CHECK_EQUAL(vector, Tuple(x, y, z, 0.0f));
}

BOOST_AUTO_TEST_CASE(TupleAdditionCase) {
    Tuple a1 = Tuple(3.0f, -2.0f, 5.0f, 1.0f);
    Tuple a2 = Tuple(-2.0f, 3.0f, 1.0f, 0.0f);

    BOOST_CHECK_EQUAL(a1 + a2, Tuple(1.0f, 1.0f, 6.0f, 1.0f));
}

BOOST_AUTO_TEST_CASE(TupleSubtractionCase) {
    Tuple p1 = Tuple::Point(3.0f, 2.0f, 1.0f);
    Tuple p2 = Tuple::Point(5.0f, 6.0f, 7.0f);

    BOOST_CHECK_EQUAL(p1 - p2, Tuple::Vector(-2.0f, -4.0f, -6.0f));
}

BOOST_AUTO_TEST_CASE(PointSubtractVectorCase) {
    Tuple p = Tuple::Point(3.0f, 2.0f, 1.0f);
    Tuple v = Tuple::Vector(5.0f, 6.0f, 7.0f);

    BOOST_CHECK_EQUAL(p - v, Tuple::Point(-2.0f, -4.0f, -6.0f));
}

BOOST_AUTO_TEST_CASE(VectorSubtractVectorCase) {
    Tuple v1 = Tuple::Vector(3.0f, 2.0f, 1.0f);
    Tuple v2 = Tuple::Vector(5.0f, 6.0f, 7.0f);

    BOOST_CHECK_EQUAL(v1 - v2, Tuple::Vector(-2.0f, -4.0f, -6.0f));
}

BOOST_AUTO_TEST_CASE(ZeroSubtractVectorCase) {
    Tuple zero = Tuple::Vector(0.0f, 0.0f, 0.0f);
    Tuple v = Tuple::Vector(1.0f, -2.0f, 3.0f);

    BOOST_CHECK_EQUAL(zero - v, Tuple::Vector(-1.0f, 2.0f, -3.0f));
}

BOOST_AUTO_TEST_CASE(NegateTupleCase) {
    Tuple a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);

    BOOST_CHECK_EQUAL(-a, Tuple(-1.0f, 2.0f, -3.0f, 4.0f));
}

BOOST_AUTO_TEST_CASE(ScalarMultiplierCase) {
    Tuple a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    float scalar = 3.5f;

    BOOST_CHECK_EQUAL(a * scalar, Tuple(3.5f, -7.0f, 10.5f, -14.0f));
}

BOOST_AUTO_TEST_CASE(FractionalScalarMultiplierCase) {
    Tuple a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    float scalar = 0.5f;

    BOOST_CHECK_EQUAL(a * scalar, Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

BOOST_AUTO_TEST_CASE(ScalarDivisionCase) {
    Tuple a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    float scalar = 2.0f;

    BOOST_CHECK_EQUAL(a / scalar, Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

BOOST_AUTO_TEST_CASE(ZeroScalarDivisionCase) {
    Tuple a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    float scalar = 0.0f;

    BOOST_CHECK_THROW(a / scalar, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(MagnitudeUnitXVectorCase) {
    Tuple v = Tuple::Vector(1.0f, 0.0f, 0.0f);

    BOOST_CHECK_EQUAL(v.magnitude(), 1.0f);
}

BOOST_AUTO_TEST_CASE(MagnitudeUnitYVectorCase) {
    Tuple v = Tuple::Vector(0.0f, 1.0f, 0.0f);

    BOOST_CHECK_EQUAL(v.magnitude(), 1.0f);
}

BOOST_AUTO_TEST_CASE(MagnitudeUnitZVectorCase) {
    Tuple v = Tuple::Vector(0.0f, 0.0f, 1.0f);

    BOOST_CHECK_EQUAL(v.magnitude(), 1.0f);
}

BOOST_AUTO_TEST_CASE(MagnitudeVectorCase) {
    Tuple v = Tuple::Vector(1.0f, 2.0f, 3.0f);

    BOOST_CHECK_EQUAL(v.magnitude(), sqrt(14.0f));
}

BOOST_AUTO_TEST_CASE(MagnitudeNegativeVectorCase) {
    Tuple v = Tuple::Vector(-1.0f, -2.0f, -3.0f);

    BOOST_CHECK_EQUAL(v.magnitude(), sqrt(14.0f));
}

BOOST_AUTO_TEST_CASE(NormalizeXVectorCase) {
    Tuple v = Tuple::Vector(4.0f, 0.0f, 0.0f);

    Tuple normalized = v.normalize();

    BOOST_CHECK_EQUAL(normalized, Tuple::Vector(1.0f, 0.0f, 0.0f));
}

BOOST_AUTO_TEST_CASE(NormalizeVectorCase) {
    Tuple v = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple normalized = v.normalize();

    // Book specifies approximate
    BOOST_CHECK(is_equal(normalized.x, 1.0f / sqrt(14.0f)));
    BOOST_CHECK(is_equal(normalized.y, 2.0f / sqrt(14.0f)));
    BOOST_CHECK(is_equal(normalized.z, 3.0f / sqrt(14.0f)));
    BOOST_CHECK(is_equal(normalized.w, 0.0f));
}

BOOST_AUTO_TEST_CASE(MagnitudeOfNormalizedVectorCase) {
    Tuple v = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple normalized = v.normalize();

    BOOST_CHECK(is_equal(normalized.magnitude(), 1.0f));
}

BOOST_AUTO_TEST_CASE(DotProductCase) {
    Tuple a = Tuple::Vector(1.0f, 2.0f, 3.0f);
    Tuple b = Tuple::Vector(2.0f, 3.0f, 4.0f);

    BOOST_CHECK_EQUAL(a.dot(b), 20.0f);
}