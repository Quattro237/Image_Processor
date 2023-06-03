#include <catch.hpp>

#include "TestImage.h"
#include "../Filters/CropFilter.h"
#include "../Filters/GrayscaleFilter.h"
#include "../Filters/NegativeFilter.h"
#include "../Filters/GaussianBlurFilter.h"
#include "../Filters/EdgeDetectionFilter.h"
#include "../Filters/SharpeningFilter.h"
#include "../Filters/TwirlFilter.h"

const PixelTable PIXELS = {{{0.5, 0.3, 0.1}, {0.1, 1.0, 0.05}, {0.4, 0.0, 1.0}},
                           {{0.44, 0.22, 0.6}, {0.9, 0.4, 0.33}, {0.9, 0.8, 0.4}},
                           {{0.23, 0.9, 0.67}, {0.0, 1.0, 0.39}, {0.21, 0.65, 0.33}}};

namespace {
void TestFunction(const Filter& filter, const PixelTable& final_pixels) {
    TestImage image(PIXELS);
    filter.ApplyFilter(image);
    REQUIRE(image.CheckPixelTable(final_pixels));
}
}  // namespace

TEST_CASE("CropFilter test") {
    {
        CropFilter crop(2, 2);
        const PixelTable final_pixels = {{{0.44, 0.22, 0.6}, {0.9, 0.4, 0.33}}, {{0.23, 0.9, 0.67}, {0.0, 1.0, 0.39}}};

        TestFunction(crop, final_pixels);
    }
    {
        CropFilter crop(4, 4);
        TestFunction(crop, PIXELS);
    }
}

TEST_CASE("GrayscaleFilter test") {
    GrayscaleFilter gs;
    const PixelTable final_pixels = {{{0.337, 0.337, 0.337}, {0.622, 0.622, 0.622}, {0.233, 0.233, 0.233}},
                                     {{0.329, 0.329, 0.329}, {0.541, 0.541, 0.541}, {0.784, 0.784, 0.784}},
                                     {{0.673, 0.673, 0.673}, {0.631, 0.631, 0.631}, {0.481, 0.481, 0.481}}};
    TestFunction(gs, final_pixels);
}

TEST_CASE("NegativeFilter test") {
    NegativeFilter ng;
    const PixelTable final_pixels = {{{0.5, 0.7, 0.9}, {0.9, 0.0, 0.95}, {0.6, 1.0, 0.0}},
                                     {{0.56, 0.78, 0.4}, {0.1, 0.6, 0.67}, {0.1, 0.2, 0.6}},
                                     {{0.77, 0.1, 0.33}, {1.0, 0.0, 0.61}, {0.79, 0.35, 0.67}}};
    TestFunction(ng, final_pixels);
}

TEST_CASE("GaussianBlurFilter test") {
    GaussianBlurFilter blur(2);
    const PixelTable final_pixels = {{{0.394, 0.472, 0.386}, {0.392, 0.460, 0.458}, {0.401, 0.422, 0.547}},
                                     {{0.360, 0.562, 0.435}, {0.364, 0.552, 0.463}, {0.377, 0.523, 0.504}},
                                     {{0.311, 0.662, 0.480}, {0.316, 0.648, 0.468}, {0.329, 0.619, 0.466}}};
    TestFunction(blur, final_pixels);
}

TEST_CASE("EdgeDetectionFilter test") {
    const double threshold = 0.1;
    EdgeDetectionFilter edge(threshold);
    const PixelTable final_pixels = {{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}},
                                     {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}},
                                     {{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}};
    TestFunction(edge, final_pixels);
}

TEST_CASE("SharpeningFilter test") {
    SharpeningFilter sharp;
    const PixelTable final_pixels = {{{0.96, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.2, 0.0, 1.0}},
                                     {{0.13, 0.0, 1.0}, {1.0, 0.0, 0.2}, {1.0, 1.0, 0.0}},
                                     {{0.25, 1.0, 1.0}, {0.0, 1.0, 0.23}, {0.0, 0.15, 0.2}}};
    TestFunction(sharp, final_pixels);
}

TEST_CASE("TwirlFilter test") {
    const double angle = 180.0;
    TwirlFilter twirl(angle);
    const PixelTable final_pixels = {{{0.21, 0.65, 0.33}, {0.0, 1.0, 0.39}, {0.21, 0.65, 0.33}},
                                     {{0.9, 0.8, 0.4}, {0.9, 0.4, 0.33}, {0.9, 0.8, 0.4}},
                                     {{0.21, 0.65, 0.33}, {0.0, 1.0, 0.39}, {0.21, 0.65, 0.33}}};
    TestFunction(twirl, final_pixels);
}