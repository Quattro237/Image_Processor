#include "EdgeDetectionFilter.h"

#include "GrayscaleFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(const double threshold)
    : MatrixFilter(MatrixFilter::EDGE_MATRIX), threshold_(threshold){};

void EdgeDetectionFilter::ApplyFilter(Image& image) const {
    GrayscaleFilter gs_filter;
    gs_filter.ApplyFilter(image);

    MatrixFilter::ApplyFilter(image);

    for (int64_t row = 0; row < image.GetHeight(); ++row) {
        for (int64_t column = 0; column < image.GetWidth(); ++column) {
            Pixel& pixel = image.At(row, column);
            if (pixel.red > threshold_) {
                pixel.red = 1.0;
                pixel.green = 1.0;
                pixel.blue = 1.0;
            } else {
                pixel.red = 0.0;
                pixel.green = 0.0;
                pixel.blue = 0.0;
            }
        }
    }
}
