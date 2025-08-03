#include <boost/test/unit_test.hpp>
#include <regex>

#include "canvas.h"
#include "tuple.h"

BOOST_AUTO_TEST_CASE(CanvasInitializationTestCase) {
    int width = 10;
    int height = 20;

    Canvas canvas(width, height);

    BOOST_CHECK_EQUAL(canvas.width, width);
    BOOST_CHECK_EQUAL(canvas.height, height);

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            BOOST_CHECK_EQUAL(canvas.pixel_at(x, y), Tuple::Colour(0.0f, 0.0f, 0.0f));
        }
    }
}

BOOST_AUTO_TEST_CASE(CanvasWritePixelTestCase) {
    Canvas c(10, 20);

    Tuple red = Tuple::Colour(1.0f, 0.0f, 0.0f);

    c.write_pixel(2, 3, red);

    BOOST_CHECK_EQUAL(c.pixel_at(2, 3), red);
}

BOOST_AUTO_TEST_CASE(CanvasPPMHeaderCase) {
    int width = 5;
    int height = 3;

    Canvas c(width, height);
    std::string ppm = c.canvas_to_ppm();

    std::string pattern =
        "^P3\\n" + std::to_string(width) + " " + std::to_string(height) + "\\n255\\n.*";
    std::regex header_pattern(pattern);

    BOOST_CHECK(std::regex_match(ppm, header_pattern));
}