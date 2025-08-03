#include <boost/test/unit_test.hpp>

#include "canvas.h"
#include "tuple.h"

BOOST_AUTO_TEST_CASE(CanvasInitializationTestCase) {
    int width = 10;
    int height = 20;

    Canvas canvas(width, height);

    BOOST_CHECK_EQUAL(canvas.width, width);
    BOOST_CHECK_EQUAL(canvas.height, height);
}