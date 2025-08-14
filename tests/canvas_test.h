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
            BOOST_CHECK_EQUAL(canvas.pixel_at(x, y),
                              Tuple::Colour(0.0f, 0.0f, 0.0f));
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

    // Debug: Show the first few lines
    std::cout << "PPM first 50 chars: '" << ppm.substr(0, 50) << "'"
              << std::endl;

    std::string pattern;
    pattern += "^P3\\n";
    pattern += std::to_string(width) + " ";
    pattern += std::to_string(height) + "\\n";
    pattern += "255\\n";
    pattern += "[\\s\\S]*";

    std::regex header_pattern(pattern);

    BOOST_CHECK(std::regex_match(ppm, header_pattern));
}

BOOST_AUTO_TEST_CASE(CanvasPPMPixelDataCase) {
    int width = 5;
    int height = 3;

    Canvas c(width, height);

    Tuple c1 = Tuple::Colour(1.5f, 0.0f, 0.0f);
    Tuple c2 = Tuple::Colour(0.0f, 0.5f, 0.0f);
    Tuple c3 = Tuple::Colour(-0.5f, 0.0f, 1.0f);

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    std::string ppm = c.canvas_to_ppm();

    std::string expected_data =
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    std::cout << "PPM Output:\n" << ppm << std::endl;

    std::string expected_full_ppm = "P3\n" + std::to_string(width) + " " +
                                    std::to_string(height) + "\n" + "255\n" +
                                    expected_data;

    BOOST_CHECK_EQUAL(ppm, expected_full_ppm);
}