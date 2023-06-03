#include "NegativeFilter.h"

void NegativeFilter::ApplyFilter(Image& image) const {
    uint32_t image_width = image.GetWidth();
    uint32_t image_height = image.GetHeight();

    for (int64_t row = 0; row < image_height; ++row) {
        for (int64_t column = 0; column < image_width; ++column) {
            Pixel& pixel = image.At(row, column);

            pixel.red = 1.0 - pixel.red;
            pixel.green = 1.0 - pixel.green;
            pixel.blue = 1.0 - pixel.blue;
        }
    }
}
