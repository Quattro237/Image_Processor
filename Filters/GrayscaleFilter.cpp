#include "GrayscaleFilter.h"

#include <cmath>

const double GrayscaleFilter::RED_COMPONENT = 0.299;
const double GrayscaleFilter::GREEN_COMPONENT = 0.587;
const double GrayscaleFilter::BLUE_COMPONENT = 0.114;

void GrayscaleFilter::ApplyFilter(Image& image) const {
    uint32_t image_width = image.GetWidth();
    uint32_t image_height = image.GetHeight();

    for (int64_t row = 0; row < image_height; ++row) {
        for (int64_t column = 0; column < image_width; ++column) {
            double new_value = 0;
            Pixel& pixel = image.At(row, column);
            new_value = RED_COMPONENT * pixel.red + GREEN_COMPONENT * pixel.green + BLUE_COMPONENT * pixel.blue;
            pixel.red = new_value;
            pixel.green = new_value;
            pixel.blue = new_value;
        }
    }
}
